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
  virtual Command getNextCommand() = 0;
  virtual void addData(QByteArray data = QByteArray()) = 0;

  virtual ~Protocol() = default;

protected:
  int countSub(const QString str, const QString subStr);
  int countSub(const QByteArray str, const char subStr);

protected:
  QQueue<QByteArray> m_data;
  QByteArray m_dataError;
};

#endif // PROTOCOL_H
