#ifndef PROTOCOLJSON_H
#define PROTOCOLJSON_H

#include "protocol.h"

class ProtocolJSON : public Protocol
{
public:
  ProtocolJSON();

  QByteArray encode(Command::CommandType command, QVariant data) override;
  Command getNextCommand() override;
  void addData(QByteArray data = QByteArray()) override;
};

#endif // PROTOCOLJSON_H
