#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QDomDocument>
#include <QJsonDocument>

class QJsonObject;
class QTcpSocket;
class QByteArray;
class Command;

class Protocol : public QJsonDocument, public QDomDocument
{
public:
  Protocol() = default;

  virtual QByteArray encode(QString command, QVariant data) = 0;

  virtual Command decode(QByteArray messageCode) = 0;

  virtual ~Protocol() = default;
};

#endif // PROTOCOL_H
