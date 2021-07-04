#include "mainwindow.h"
#include "cmf.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    cmf::CreateParallelContext(&argc, &argv);
    cmf::globalSettings.colorOutput = false;
    cmf::globalSettings.debugLevel = 5;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
