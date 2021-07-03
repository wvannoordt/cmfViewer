#include "CubeObject.h"

CubeObject::CubeObject(cmf::Vec3<float> center_in, cmf::Vec3<float> radii_in)
{
    center = center_in;
    radii = radii_in;
}

void CubeObject::PaintObject(void)
{
    //back
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.4, 0.1);
    glVertex3f(center[0]-radii[0], center[1]-radii[1], center[2]-radii[2]);
    glVertex3f(center[0]-radii[0], center[1]+radii[1], center[2]-radii[2]);
    glVertex3f(center[0]+radii[0], center[1]+radii[1], center[2]-radii[2]);
    glVertex3f(center[0]+radii[0], center[1]-radii[1], center[2]-radii[2]);
    glEnd();

    //front
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.4, 0.3);
    glVertex3f(center[0]-radii[0], center[1]-radii[1], center[2]+radii[2]);
    glVertex3f(center[0]-radii[0], center[1]+radii[1], center[2]+radii[2]);
    glVertex3f(center[0]+radii[0], center[1]+radii[1], center[2]+radii[2]);
    glVertex3f(center[0]+radii[0], center[1]-radii[1], center[2]+radii[2]);
    glEnd();

    //left
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.6, 0.8);
    glVertex3f(center[0]-radii[0], center[1]-radii[1], center[2]+radii[2]);
    glVertex3f(center[0]-radii[0], center[1]+radii[1], center[2]+radii[2]);
    glVertex3f(center[0]-radii[0], center[1]+radii[1], center[2]-radii[2]);
    glVertex3f(center[0]-radii[0], center[1]-radii[1], center[2]-radii[2]);
    glEnd();

    //right
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.2, 0.1);
    glVertex3f(center[0]+radii[0], center[1]-radii[1], center[2]+radii[2]);
    glVertex3f(center[0]+radii[0], center[1]+radii[1], center[2]+radii[2]);
    glVertex3f(center[0]+radii[0], center[1]+radii[1], center[2]-radii[2]);
    glVertex3f(center[0]+radii[0], center[1]-radii[1], center[2]-radii[2]);
    glEnd();

    //top
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.1, 0.9);
    glVertex3f(center[0]+radii[0], center[1]+radii[1], center[2]+radii[2]);
    glVertex3f(center[0]-radii[0], center[1]+radii[1], center[2]+radii[2]);
    glVertex3f(center[0]-radii[0], center[1]+radii[1], center[2]-radii[2]);
    glVertex3f(center[0]+radii[0], center[1]+radii[1], center[2]-radii[2]);
    glEnd();

    //bottom
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.2, 0.9);
    glVertex3f(center[0]+radii[0], center[1]-radii[1], center[2]+radii[2]);
    glVertex3f(center[0]-radii[0], center[1]-radii[1], center[2]+radii[2]);
    glVertex3f(center[0]-radii[0], center[1]-radii[1], center[2]-radii[2]);
    glVertex3f(center[0]+radii[0], center[1]-radii[1], center[2]-radii[2]);
    glEnd();
}
