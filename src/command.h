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
    PointGraphing=200,
    DrawStartOrFin=300,
    TypeSignalSetting=400
  };

  Command(CommandType command);
  Command();

  bool isCommand(QString str);
  bool isCommand(CommandType str);
  bool isValid();
  bool isCategory(QString str);
  int size();

  void addVariableData(int inteter);
  void setVariableData(QString str);
  void setCommandType(CommandType type);
  QString getVariableData();
  CommandType getCommandType();
  int atVariableData(int i);
private:
    CommandType m_command;
    QVariant m_variableData;
};

#endif // COMMAND_H
