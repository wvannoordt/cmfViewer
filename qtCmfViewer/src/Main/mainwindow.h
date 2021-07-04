#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include "src/Main/PTLDialog.h"
#include "src/View/GlViewWindow.h"
#include "cmf.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool KeyIsPressed(Qt::Key k);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent *e) override;

    void on_resetViewButton_clicked();

private:
    Ui::MainWindow *ui;
    std::map<int, bool> isPressed;
    QList<GlViewWindow*> allGlScenes;
    GlViewWindow* activeScene;
    //TEMPORARY
    std::vector<cmf::ICmfMesh*> meshes;
    bool wireFrameMode=false;
    //END TEMPORARY
};
#endif // MAINWINDOW_H
