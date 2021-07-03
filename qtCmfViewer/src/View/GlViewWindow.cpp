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
    PTL::PropertyTree input;
    input.Read("/home/wvn/input.ptl");
    cmf::CartesianMeshInputInfo info(input["Domain"]);
    temporaryMesh = new cmf::CartesianMesh(info);
    scene.AddObject(new CmfCartesianMeshObject(temporaryMesh));
}

GlViewWindow::~GlViewWindow(void)
{
    delete temporaryMesh;
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
    scene.GetCurrentView().xScreenShift += incrX;
    scene.GetCurrentView().yScreenShift += incrY;
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
}

void GlViewWindow::mouseMoveEvent(QMouseEvent* event)
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
    glTranslatef(0.0, 0.0, -3.0);
    glTranslatef(scene.GetCurrentView().xScreenShift, -scene.GetCurrentView().yScreenShift, 0.0);

    double k = 0.01745329251;
    float phi = scene.GetCurrentView().zenith;
    float theta = scene.GetCurrentView().azimuth;
    glRotatef(theta, 0.0, 1.0, 0.0);
    glRotatef(phi, cos(k*theta), 0.0, sin(k*theta));
}

void GlViewWindow::wheelEvent(QWheelEvent* event)
{
    if (event->pixelDelta().y()>0)
    {
        scene.GetCurrentView().pov += 1.015;
    }
    else
    {
        scene.GetCurrentView().pov -= 1.015;
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

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}
