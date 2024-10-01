#ifndef PROTOCOLJSON_H
#define PROTOCOLJSON_H

#include "protocol.h"

class ProtocolJSON : public Protocol
{
public:
  ProtocolJSON();

  QByteArray encode(Command::CommandType command, QVariant data) override;
  Command decode(QByteArray messageCode) override;
};

#endif // PROTOCOLJSON_H
