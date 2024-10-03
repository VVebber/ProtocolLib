#include "protocoljson.h"
#include "command.h"
#include "constants.h"

#include <QSequentialIterable>
#include <QJsonObject>
#include <QTcpSocket>
#include <QJsonArray>

ProtocolJSON::ProtocolJSON() {}

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
  qDebug()<<document;
  return document.toJson();
}

Command ProtocolJSON::decode(QByteArray messageCode)
{
  QJsonDocument message;
  message = QJsonDocument::fromJson(messageCode);

  qDebug()<<"1)  "<<message[COMMAND].toInt();
  QString s(messageCode);
  qDebug()<<"2)  "<<s;

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
