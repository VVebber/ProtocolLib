#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QDomDocument>
#include <QJsonDocument>
#include "command.h"

class QJsonObject;
class QTcpSocket;
class QByteArray;
class Command;

class Protocol : public QJsonDocument, public QDomDocument
{
public:
  Protocol();

  virtual QByteArray encode(Command::CommandType command, QVariant data) = 0;

  virtual Command decode(QByteArray messageCode) = 0;

  virtual ~Protocol() = default;
private:
  const QString m_command;
  const QString m_variableData;
  const QString m_iteml;
};

#endif // PROTOCOL_H
