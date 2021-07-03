#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>

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

private:
    Ui::MainWindow *ui;
    std::map<int, bool> isPressed;
};
#endif // MAINWINDOW_H
