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
  message["command"] = command;

  if(data.isValid())
  {
    if (data.canConvert<int>())
    {
      message["VariableData"] = data.toInt();
    }
    else if (data.canConvert<double>())
    {
      message["VariableData"] = data.toDouble();
    }
    else if (data.canConvert<QString>())
    {
      message["VariableData"] = data.toString();
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
      message["VariableData"] = mas;
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
  Command command(Command::CommandType(message["command"].toInt()));
  if(message.object().contains("VariableData"))
  {
    if(message["VariableData"].isArray())
    {
      for(int i = 0; i < message["VariableData"].toArray().size(); i++)
      command.addVariableData(message["VariableData"].toArray().at(i).toInt());
    }
    else
    {
      command.setVariableData(message["VariableData"].toString());
    }
  }
  return command;
}
