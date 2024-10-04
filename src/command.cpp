#include "command.h"
#include <QDebug>

Command::Command(){}

Command::Command(CommandType command) : m_command(command)
{
  m_variableData = "";
}

bool Command::isCommand(QString str)
{
  return m_command == str;
}

Command::CommandType Command::getCommandType(){
  return m_command;
}

bool Command::isValid()
{
  if(m_command == CommandType::DrawStartOrFin)
  {
    return true;
  }
  else if(m_command == CommandType::PointGraphing)
  {
    return true;
  } else if(m_command == CommandType::TypeSignalSetting)
  {
    return true;
  }
  return false;
}

bool Command::isCommand(CommandType str)
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

void Command::setCommandType(CommandType type)
{
  m_command = type;
}

// void Command::setVariableData(float integer)
// {
//   QString p;
//   m_variableData.toList().push_back(p.setNum(integer));
// }

void Command::addVariableData(int integer)
{
  QList<QVariant> list = m_variableData.toList();
  list.push_back(integer);
  m_variableData = list;
}

QString Command::getVariableData()
{
  return m_variableData.toString();
}

int Command::atVariableData(int i)
{
  return m_variableData.toList().at(i).toInt();
}
