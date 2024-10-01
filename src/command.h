#ifndef COMMAND_H
#define COMMAND_H
#include <QVariant>

QString pointGraphing = "point for graphing function";
QString drawStartOrFin = "setting draw point";
QString typeSignal = "setting the type of signal";

class Command
{
public:
  Command(QString command);

  bool isCommand(QString str);
  bool isCategory(QString str);
  int size();

  void setVariableData(QString str);
  void setVariableData(float integer);
  void setVariableData(int inteter);
  QString getVariableData();
  int getVariableDataMas(int i);
private:
    QString m_command;
    QVariant m_variableData;
};

#endif // COMMAND_H
