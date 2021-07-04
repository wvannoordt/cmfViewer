#include "GlViewWindow.h"
#include "src/Main/mainwindow.h"
#include <QMouseEvent>
#include <cmath>
GlViewWindow::GlViewWindow(QWidget* parent) : QOpenGLWidget(parent)
{
    scene.GetCurrentView().zenith = 0.0;
    scene.GetCurrentView().azimuth = 0.0;
    lastMouseX = 0;
    lastMouseY = 0;
    scene.GetCurrentView().width = 0;
    scene.GetCurrentView().height = 0;
    normalizedLastMouseX = 0.0;
    normalizedLastMouseY = 0.0;
}

GlViewWindow::~GlViewWindow(void)
{

}

void GlViewWindow::ResetView(void)
{
    scene.GetCurrentView().Reset();
    this->update();
}

GlScene& GlViewWindow::GetScene(void)
{
    return scene;
}

void GlViewWindow::IncrementRotation(float incrAzimuth, float incrZenith)
{
    scene.GetCurrentView().zenith  += incrZenith;
    scene.GetCurrentView().azimuth += incrAzimuth;
    this->paintGL();
    this->update();
}

void GlViewWindow::IncrementShift(float incrX, float incrY)
{
    scene.GetCurrentView().IncrementShift(incrX, incrY);
    this->paintGL();
    this->update();
}

void GlViewWindow::initializeGL()
{
    initializeOpenGLFunctions();
    QColor col;
    col.setRed(34);
    col.setGreen(87);
    col.setBlue(168);
    float r, g, b;
    float alpha = 1.0f;
    this->QColorToRGB(col, r, g, b);
    glClearColor(r, g, b, alpha);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void GlViewWindow::QColorToRGB(const QColor& c, float& r, float& g, float& b) const
{
    r = ((float)c.red())/255.0f;
    g = ((float)c.green())/255.0f;
    b = ((float)c.blue())/255.0f;
}

void GlViewWindow::mousePressEvent(QMouseEvent* event)
{
    lastMouseX = event->x();
    lastMouseY = event->y();
    if (event->button() == Qt::LeftButton) leftMouseDown = true;
    if (event->button() == Qt::RightButton) rightMouseDown = true;
}

void GlViewWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) leftMouseDown = false;
    if (event->button() == Qt::RightButton) rightMouseDown = false;
}

void GlViewWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (rightMouseDown)
    {
        this->OnRightMouseMove(event);
    }
    else
    {
        this->OnLeftMouseMove(event);
    }
}

void GlViewWindow::OnLeftMouseMove(QMouseEvent* event)
{
    int deltaX = event->x() - lastMouseX;
    int deltaY = event->y() - lastMouseY;
    bool doShift = false;
    if (mainWindow!=NULL)
    {
        doShift = (mainWindow->KeyIsPressed(Qt::Key_Shift));
    }
    if (doShift)
    {
        this->IncrementShift(0.005*(float)deltaX, 0.005*(float)deltaY);
    }
    else
    {
        this->IncrementRotation(0.5*deltaX, 0.5*deltaY);
    }
    lastMouseX = event->x();
    lastMouseY = event->y();
}

void GlViewWindow::OnRightMouseMove(QMouseEvent* event)
{

}

void GlViewWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    scene.GetCurrentView().width = w;
    scene.GetCurrentView().height = h;
    float aspect = ((float)w) / ((float)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, aspect, 0.1, 400000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void GlViewWindow::SetRootWindow(MainWindow* window)
{
    mainWindow = window;
}

void GlViewWindow::ApplyView(const SceneView& view)
{
    float aspect = ((float)view.width) / ((float)view.height);
    gluPerspective(scene.GetCurrentView().GetAngle(), aspect, 0.1, 400000000);
    glTranslatef(0.0, 0.0, scene.GetCurrentView().zdisp);

    double k = 0.01745329251;
    float phi = scene.GetCurrentView().zenith;
    float theta = scene.GetCurrentView().azimuth;

    auto orbit = scene.GetCurrentView().orbit;
    glRotatef(theta, 0.0, 1.0, 0.0);
    glRotatef(phi, cos(k*theta), 0.0, sin(k*theta));
    glTranslatef(-orbit[0], -orbit[1], -orbit[2]);
}

void GlViewWindow::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y()<0)
    {
        scene.GetCurrentView().zdisp += 0.09*scene.GetCurrentView().zdisp;
    }
    else
    {
        scene.GetCurrentView().zdisp -= 0.09*scene.GetCurrentView().zdisp;
    }
    this->update();
}

void GlViewWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    this->ApplyView(scene.GetCurrentView());
    scene.PaintObjects();

    float eps = 0.001;
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0-eps, 0.0-eps, 0.0-eps);
    glVertex3f(0.5-eps, 0.0-eps, 0.0-eps);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0-eps, 0.0-eps, 0.0-eps);
    glVertex3f(0.0-eps, 0.5-eps, 0.0-eps);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0-eps, 0.0-eps, 0.0-eps);
    glVertex3f(0.0-eps, 0.0-eps, 0.5-eps);
    glEnd();
    glFlush();
}
