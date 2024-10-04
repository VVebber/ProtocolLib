#include "protocol.h"
#include "constants.h"

Command Protocol::getNextCommand()
{
  QByteArray::iterator openCommand = std::find(m_dataBuffer.begin(), m_dataBuffer.end(), STX);
  if(openCommand == m_dataBuffer.end())
  {
    m_dataBuffer.clear();
    return Command();
  }

  QByteArray::iterator closeCommand = std::find(openCommand, m_dataBuffer.end(), ETX);
  if(closeCommand == m_dataBuffer.end())
  {
    return Command();
  }

  QByteArray commandData((const char*)openCommand, int(closeCommand - openCommand + 1));
  m_dataBuffer.remove( 0, int(closeCommand - openCommand + 1));

  QByteArray::reverse_iterator lastOpen = std::find(commandData.rbegin(), commandData.rend(), STX);
  commandData.remove(0, int(lastOpen.base() - commandData.begin()));

  // commandData.remove(0,1);
  commandData.chop(1);
  return decode(commandData);

}

void Protocol::addData(QByteArray data)
{
  m_dataBuffer += data;
}
