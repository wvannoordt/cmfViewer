#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<GlViewWindow*> allGlScenes = ui->mainTabsWindow->findChildren<GlViewWindow*>();
    for (auto& scn:allGlScenes) scn->SetRootWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::KeyIsPressed(Qt::Key k)
{
    int ki = (int)k;
    if (isPressed.find(ki)==isPressed.end()) isPressed[ki] = false;
    return isPressed[ki];
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    isPressed[e->key()] = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    isPressed[e->key()] = false;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

