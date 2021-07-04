#ifndef GLVIEWWINDOW_H
#define GLVIEWWINDOW_H

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/glu.h>

#include "src/View/SceneView.h"
#include "src/View/GlScene.h"

class MainWindow;
class GlViewWindow : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GlViewWindow(QWidget* parent = nullptr);
    ~GlViewWindow(void);
    void IncrementRotation(float incrAzimuth, float incrZenith);
    void IncrementShift(float incrX, float incrY);
    void SetRootWindow(MainWindow* window);
    void ResetView(void);
    GlScene& GetScene(void);
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    void ApplyView(const SceneView& view);
private:
    void QColorToRGB(const QColor& c, float& r, float& g, float& b) const;
    GlScene scene;
    int lastMouseX, lastMouseY;
    MainWindow* mainWindow = NULL;
};

#endif // GLVIEWWINDOW_H
