#ifndef PROTOCOLXML_H
#define PROTOCOLXML_H

#include "protocol.h"

class ProtocolXML: public Protocol
{
public:
  ProtocolXML();

  QByteArray encode(Command::CommandType command, QVariant data) override;

private:
  Command decode(QByteArray commandData) override;
};

#endif // PROTOCOLXML_H
