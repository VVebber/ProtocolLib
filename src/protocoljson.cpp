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
<<<<<<< HEAD
=======
  message["empty"] = "empty_ms111111111111111111111114444444f";
>>>>>>> c7a2a6734bdcf978f2a9799bc065ae468463c9ab
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
<<<<<<< HEAD

  qDebug()<<"1)  "<<message[COMMAND].toInt();
  QString s(messageCode);
  qDebug()<<"2)  "<<s;

=======
>>>>>>> c7a2a6734bdcf978f2a9799bc065ae468463c9ab
  Command command(Command::CommandType(message[COMMAND].toInt()));
  if(message.object().contains(VARIABLEDATA))
  {
    if(message[VARIABLEDATA].isArray())
    {
      for(int i = 0; i < message[VARIABLEDATA].toArray().size(); i++)
<<<<<<< HEAD
        command.addVariableData(message[VARIABLEDATA].toArray().at(i).toInt());
=======
      command.addVariableData(message[VARIABLEDATA].toArray().at(i).toInt());
>>>>>>> c7a2a6734bdcf978f2a9799bc065ae468463c9ab
    }
    else
    {
      command.setVariableData(message[VARIABLEDATA].toString());
    }
  }
  return command;
}
