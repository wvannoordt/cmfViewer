#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cmf.h"
using cmf::print;
#include <QFileDialog>

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
    activeConsole = NULL;
    auto allLogs = ui->mainTabsWindow->findChildren<ConsoleLog*>();
    for (auto& lg: allLogs) activeConsole = lg;
}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto& obj: meshes)
    {
        delete obj;
    }
    for (auto& obj: triangulations)
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

ConsoleLog* MainWindow::GetActiveConsole(void)
{
    return activeConsole;
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
        info.title = "CartesianMesh";
        dl.ShowPTLPropertySection(inputPrototype["CartesianMesh"]);
        dl.exec();
        if (dl.WasClosedWithConfirmation())
        {
            inputPrototype["CartesianMesh"].StrictParse();
            auto mesh = new cmf::CartesianMesh(info);
            meshes.push_back(mesh);
            activeScene->GetScene().Add<CmfCartesianMeshObject>(mesh);
            lastCartMesh = mesh;
        }
        activeScene->update();
    }
    if (e->key()==(int)(Qt::Key_R))
    {
        if ((lastCartMesh != NULL) && (lastSurfTri != NULL))
        {
            std::vector<cmf::RefinementTreeNode*> nodes;
            std::vector<char> refs;
            auto& msh = *lastCartMesh;
            auto& tri = *lastSurfTri;

            for (auto& lb:msh)
            {
                auto bnd = lb->GetBlockBoundsVec6();
                if (lb->IsTerminal() && tri.BoxIntersectsBoundary(bnd))
                {
                    nodes.push_back(lb);
                    refs.push_back(7);
                }
            }
            msh.Blocks()->RefineNodes(nodes, refs);
            activeScene->update();
        }
    }
    if (e->key()==(int)(Qt::Key_T))
    {
        QFileDialog dia;
        QString filename = dia.getOpenFileName();
        print(filename.toStdString());
        if (!filename.isNull())
        {
            auto trig = new cmf::SurfaceTriangulation();
            triangulations.push_back(trig);
            trig->DefineTriangulation(filename.toStdString());
            activeScene->GetScene().Add<CmfSurfaceTriangulationObject>(trig);
            activeScene->update();
            lastSurfTri = trig;
        }
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

