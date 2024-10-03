#include "protocol.h"
#include "Protocol_global.h"

bool Protocol::isDataEmpty()
{
  return m_dataError.isEmpty();
}

int Protocol::countSub(const QString str, const QString subStr)
{
  int x =0;
  for(int i = -1;; )
  {
    i = str.indexOf(subStr, i + 1);
    if(i  == -1)
    {
      return x;
    }
    else
    {
      x++;
    }
  }
}

int Protocol::countSub(const QByteArray str, const char subStr)
{
  int x =0;
  for(int i = -1;; )
  {
    i = str.indexOf(subStr, i + 1);
    if(i  == -1)
    {
      return x;
    }
    else
    {
      x++;
    }
  }
}
