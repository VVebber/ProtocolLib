#ifndef COMMAND_H
#define COMMAND_H
#include <QVariant>

// #define pointGraphing "point for graphing function"
// #define drawStartOrFin  "setting draw point"
// #define typeSignalSetting  "setting the type of signal"

class Command
{
public:
  enum CommandType
  {
    PointGraphing,
    DrawStartOrFin,
    TypeSignalSetting
  };

  Command(CommandType command);

  bool isCommand(QString str);
  bool isCommand(CommandType str);
  bool isCategory(QString str);
  int size();

  void setVariableData(QString str);
  // void setVariableData(float integer);
  void addVariableData(int inteter);
  QString getVariableData();
  int atVariableData(int i);
private:
    CommandType m_command;
    QVariant m_variableData;
};

#endif // COMMAND_H
