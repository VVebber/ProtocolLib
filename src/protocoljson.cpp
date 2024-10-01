#include "protocoljson.h"
#include "command.h"

#include <QSequentialIterable>
#include <QJsonObject>
#include <QTcpSocket>
#include <QJsonArray>

ProtocolJSON::ProtocolJSON() {}

QByteArray ProtocolJSON::encode(Command::CommandType command, QVariant data)
{
  QJsonObject message;
  message[m_command] = command;

  if(data.isValid())
  {

    if (data.canConvert<QString>())
    {
      message[m_variableData] = data.toString();
    }
    else if (data.canConvert<int>())
    {
      message[m_variableData] = data.toInt();
    }
    else if (data.canConvert<double>())
    {
      message[m_variableData] = data.toDouble();
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
      message[m_variableData] = mas;
    }
    else
    {
      qDebug()<< "ProtocolJSON encode error";
    }
  }

  QJsonDocument document(message);
  qDebug()<<document;
  return document.toJson();
}

Command ProtocolJSON::decode(QByteArray messageCode)
{
  QJsonDocument message;
  message = QJsonDocument::fromJson(messageCode);
  Command command(Command::CommandType(message[m_command].toInt()));
  if(message.object().contains(m_variableData))
  {
    if(message[m_variableData].isArray())
    {
      for(int i = 0; i < message[m_variableData].toArray().size(); i++)
      command.addVariableData(message[m_variableData].toArray().at(i).toInt());
    }
    else
    {
      command.setVariableData(message[m_variableData].toString());
    }
  }
  return command;
}
