#ifndef PROTOCOLJSON_H
#define PROTOCOLJSON_H

#include "protocol.h"

class ProtocolJSON : public Protocol
{
public:
  ProtocolJSON();

  QByteArray encode(Command::CommandType command, QVariant data) override;

private:
  Command decode(QByteArray commandData) override;
};

#endif // PROTOCOLJSON_H
