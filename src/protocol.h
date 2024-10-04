#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QQueue>
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

  bool isDataEmpty();
  virtual QByteArray encode(Command::CommandType command, QVariant data) = 0;
  void addData(QByteArray data = QByteArray());
  Command getNextCommand();

  virtual ~Protocol() = default;

protected:

  QByteArray m_dataBuffer;

private:
  virtual Command decode(QByteArray commandData) = 0;
};

#endif // PROTOCOL_H
