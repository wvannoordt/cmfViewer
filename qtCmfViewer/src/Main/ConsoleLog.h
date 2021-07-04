#ifndef CONSOLELOG_H
#define CONSOLELOG_H

#include <QWidget>
#include <QPlainTextEdit>
#include "cmf.h"

class ConsoleLog : public QPlainTextEdit, public cmf::ICmfOutputStreamEndpoint
{
public:
    ConsoleLog(QWidget* parent = nullptr);
    ~ConsoleLog(void);
    void WriteString(const std::string& msg);
    void WriteString(const char* msg);
    virtual void AddString(const std::string& msg) override final;
};

#endif // CONSOLELOG_H
