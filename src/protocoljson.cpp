#include "protocoljson.h"
#include "command.h"
#include "constants.h"

#include <QSequentialIterable>
#include <QJsonObject>
#include <QTcpSocket>
#include <QJsonArray>

ProtocolJSON::ProtocolJSON() {
  m_dataError.clear();
}

QByteArray ProtocolJSON::encode(Command::CommandType command, QVariant data)
{
  QJsonObject message;
  message[COMMAND] = command;

  if(data.isValid())
  {

    if (data.canConvert<QString>())
    {
      message[VARIABLEDATA] = data.toString();
    }
    else if (data.canConvert<int>())
    {
      message[VARIABLEDATA] = data.toInt();
    }
    else if (data.canConvert<double>())
    {
      message[VARIABLEDATA] = data.toDouble();
    }
    else if (data.canConvert<QVariantList>())
    {
      QSequentialIterable iterable = data.value<QSequentialIterable>();
      QJsonArray mas;
      for(const QVariant& v : iterable)
      {
        int integer = v.toInt();
        mas.append(integer);
      }
      message[VARIABLEDATA] = mas;
    }
    else
    {
      qDebug()<< "ProtocolJSON encode error";
    }
  }

  QJsonDocument document(message);
  // qDebug()<<document;
  return document.toJson();
}

void ProtocolJSON::addData(QByteArray data)
{
  if(!data.isEmpty())
  {
    m_dataError += data;
  }
  QByteArray subData;
  if(m_dataError.indexOf('{') == 0 && m_dataError.indexOf('}') != -1)
  {
    subData = m_dataError.mid((0), m_dataError.indexOf('}') + 1);
    if(!(countSub(subData,'{') ==  1 && countSub(subData,'{') == countSub(subData,'}')))
    {
      m_dataError.remove(0, m_dataError.indexOf('{', 1));
      return;
    }
  }

  if(subData.contains(COMMAND) && subData.contains(VARIABLEDATA))
  {
    m_data.push_back(subData);
    m_dataError.remove(0, m_dataError.indexOf('}') + 2);
  }
}

Command ProtocolJSON::getNextCommand()
{
  if(m_data.size() == 0)
  {
    qDebug()<<"error: commandlist size == 0";
    Command command(Command::CommandType::TypeSignalSetting);
    return command;
  }

  QJsonDocument message;
  message = QJsonDocument::fromJson(m_data.dequeue());

  Command command(Command::CommandType(message[COMMAND].toInt()));
  if(message.object().contains(VARIABLEDATA))
  {
    if(message[VARIABLEDATA].isArray())
    {
      for(int i = 0; i < message[VARIABLEDATA].toArray().size(); i++)
        command.addVariableData(message[VARIABLEDATA].toArray().at(i).toInt());
    }
    else
    {
      command.setVariableData(message[VARIABLEDATA].toString());
    }
  }
  return command;
}
