#include "protocolxml.h"
#include "command.h"
#include "constants.h"

#include <QString>
#include <QSequentialIterable>

ProtocolXML::ProtocolXML()
{

}


QByteArray ProtocolXML::encode(Command::CommandType command, QVariant data)
{

  QDomDocument XMLDocument;
  QDomElement root = XMLDocument.createElement("task");

  QDomElement commandXML = XMLDocument.createElement(COMMAND);
  QDomText commandXMLText = XMLDocument.createTextNode(QString(command));

  commandXML.appendChild(commandXMLText);
  root.appendChild(commandXML);
  if(data.isValid())
  {
    QDomElement variableDataXML = XMLDocument.createElement(VARIABLEDATA);
    root.appendChild(variableDataXML);
    if (data.canConvert<int>())
    {
      QDomText variableDataXMLText = XMLDocument.createTextNode(data.toString());
      variableDataXML.appendChild(variableDataXMLText);
    }
    else if (data.canConvert<double>())
    {
      QDomText variableDataXMLText = XMLDocument.createTextNode(data.toString());
      variableDataXML.appendChild(variableDataXMLText);
    }
    else if (data.canConvert<QString>())
    {
      QDomText variableDataXMLText = XMLDocument.createTextNode(data.toString());
      variableDataXML.appendChild(variableDataXMLText);
    }
    else if (data.canConvert<QVariantList>())
    {
      QSequentialIterable iterable = data.value<QSequentialIterable>();
      for(const QVariant& v : iterable)
      {
        QDomElement listItem = XMLDocument.createElement(ITEM);
        QDomText variableDataXMLText = XMLDocument.createTextNode(v.toString());
        listItem.appendChild(variableDataXMLText);
        variableDataXML.appendChild(listItem);
      }
    }
    else
    {
      qDebug()<< "ProtocolXLM encode error";
    }
  }
  XMLDocument.appendChild(root);

  qDebug()<<XMLDocument.toByteArray(0);

  qDebug()<<root.elementsByTagName(VARIABLEDATA).at(0).toElement().childNodes().at(0).toText().data();

  return XMLDocument.toByteArray(0);
}

void ProtocolXML::addData(QByteArray data)
{

}


Command ProtocolXML::getNextCommand()
{
  QDomDocument main;
  main.setContent(m_data.dequeue());
  QDomElement box = main.documentElement().toElement();

  QString command  = box.elementsByTagName(COMMAND).at(0).toElement().childNodes().at(0).toText().data();
  Command com(Command::CommandType(command.toInt()));

  QDomNodeList VariableData = box.elementsByTagName(VARIABLEDATA).at(0).childNodes();
  if(box.elementsByTagName(VARIABLEDATA).at(0).toElement().childNodes().at(0).toText().data().isEmpty())
  {
    if(VariableData.size() > 1)
    {
      for (int i = 0; i < VariableData.size(); ++i)
      {
        com.addVariableData(VariableData.at(i).toElement().childNodes().at(0).toText().data().toInt());
      }
    } else
    {
      com.setVariableData(VariableData.at(0).toElement().childNodes().at(0).toText().data());
    }
  }
  return com;
}
