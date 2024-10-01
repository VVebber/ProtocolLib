#include "command.h"

Command::Command(QString command) : m_command(command)
{
  m_variableData = "";
}

bool Command::isCommand(QString str)
{
  return m_command == str;
}

int Command::size(){
  return m_variableData.toList().size();
}

void Command::setVariableData(QString str)
{
  m_variableData = str;
}

void Command::setVariableData(float integer)
{
  m_variableData.toList().push_back(QString::number(Qinteger));
}

void Command::setVariableData(int integer)
{
  m_variableData.toList().push_back(integer);
}

QString Command::getVariableData()
{
  return m_variableData.toString();
}

int Command::getVariableDataMas(int i)
{
  return m_variableData.toList().at(i).toInt();
}
