#ifndef COMMAND_H
#define COMMAND_H
#include <QString>

#define pointGraphing = "point for graphing function";
#define startOutOrFin = "setting draw point";

class Command
{
public:
  Command(QString command);

  bool isCommand(QString str);
  bool isCategory(QString str);

  void setVariableData(QString str);
  QString getVariableData();
private:
    QString m_command;
    QString m_variableData;
};

#endif // COMMAND_H
