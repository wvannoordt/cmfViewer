#include "ConsoleLog.h"
#include <QTextCursor>
ConsoleLog::ConsoleLog(QWidget* parent) : QPlainTextEdit(parent)
{
    cmf::cmfout.AddEndpoint(this);
}

ConsoleLog::~ConsoleLog(void)
{
    cmf::cmfout.ClearEndpoints();
}

void ConsoleLog::WriteString(const std::string& msg)
{
    QTextCursor c(this->document());
    c.insertText(QString::fromStdString(msg));
}

void ConsoleLog::WriteString(const char* msg)
{
    QTextCursor c(this->document());
    c.insertText(QString::fromStdString(msg));
}

void ConsoleLog::AddString(const std::string& msg)
{
    this->WriteString(msg);
}
