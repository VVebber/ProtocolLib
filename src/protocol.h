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
  Protocol() = default;

  virtual QByteArray encode(Command::CommandType command, QVariant data) = 0;

  virtual Command decode(QByteArray messageCode) = 0;

  virtual ~Protocol() = default;

protected:

};

#endif // PROTOCOL_H
