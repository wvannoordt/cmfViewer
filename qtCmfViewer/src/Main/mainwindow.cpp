#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cmf.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    activeScene = NULL;
    allGlScenes = ui->mainTabsWindow->findChildren<GlViewWindow*>();
    for (auto& scn:allGlScenes)
    {
        scn->SetRootWindow(this);
        activeScene = scn;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto& obj: meshes)
    {
        delete obj;
    }
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
    if (e->key()==(int)(Qt::Key_Q))
    {
        PTLDialog dl;
        dl.setModal(true);

        PTL::PropertyTree inputPrototype;
        cmf::CartesianMeshInputInfo info;
        info.Define(inputPrototype["CartesianMesh"]);
        dl.ShowPTLPropertySection(inputPrototype["CartesianMesh"]);
        dl.exec();
        if (dl.WasClosedWithConfirmation())
        {
            inputPrototype["CartesianMesh"].StrictParse();
            auto mesh = new cmf::CartesianMesh(info);
            meshes.push_back(mesh);
            activeScene->GetScene().AddObject(new CmfCartesianMeshObject(mesh));
        }
        activeScene->update();
    }
    if (KeyIsPressed(Qt::Key_Control) && (e->key()==(int)(Qt::Key_M)))
    {
        for (auto& obj:activeScene->GetScene().GetObjects())
        {
            wireFrameMode = !wireFrameMode;
            obj->SetFacesEnabled(!wireFrameMode);
            obj->SetLinesEnabled(true);
        }
        activeScene->update();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    isPressed[e->key()] = false;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_resetViewButton_clicked()
{
    if (activeScene != NULL)
    {
        activeScene->ResetView();
    }
}

