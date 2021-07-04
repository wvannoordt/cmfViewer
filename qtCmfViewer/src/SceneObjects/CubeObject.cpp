#include "CubeObject.h"

CubeObject::CubeObject(cmf::Vec3<float> center_in, cmf::Vec3<float> radii_in)
{
    center = center_in;
    radii = radii_in;
    for (int idir = 0; idir < 3; idir++)
    {
        box[2*idir]   = center[idir]-radii[idir];
        box[2*idir+1] = center[idir]+radii[idir];
    }
}

void CubeObject::PaintObject(void)
{
    cmf::Vec3<float> vertex = 0;
    cmf::Vec3<float> color = 0;
    float comp = 0.6;
    if (FacesAreEnabled())
    {
        for (int idir = 0; idir < 3; idir++)
        {
            int idir1 = (idir+1)%3;
            int idir2 = (idir+2)%3;
            for (int pm = -1; pm <= 1; pm += 2)
            {
                vertex[idir] = center[idir]+pm*radii[idir];
                glBegin(GL_POLYGON);
                glColor3f(comp, comp, comp);
                comp -= 0.05;
                for (int p2 = -1; p2 <= 1; p2+=2)
                {
                    for (int p1 = -1; p1 <= 1; p1+=2)
                    {
                        vertex[idir1] = center[idir1]+p1*p2*radii[idir1];
                        vertex[idir2] = center[idir2]+p2*radii[idir2];
                        glVertex3f(vertex[0], vertex[1], vertex[2]);
                    }
                }
                glEnd();
            }
        }
    }
    if (LinesAreEnabled())
    {
        float inflate = 1.0001;
        for (int idir = 0; idir < 3; idir++)
        {
            int idir1 = (idir+1)%3;
            int idir2 = (idir+2)%3;
            for (int pm = -1; pm <= 1; pm += 2)
            {
                vertex[idir] = center[idir]+pm*inflate*radii[idir];
                glLineWidth(lineWidth);
                glBegin(GL_LINE_LOOP);
                glColor3f(lineColor[0], lineColor[1], lineColor[2]);
                for (int p2 = -1; p2 <= 1; p2+=2)
                {
                    for (int p1 = -1; p1 <= 1; p1+=2)
                    {
                        vertex[idir1] = center[idir1]+p1*p2*inflate*radii[idir1];
                        vertex[idir2] = center[idir2]+p2*inflate*radii[idir2];
                        glVertex3f(vertex[0], vertex[1], vertex[2]);
                    }
                }
                glEnd();
            }
        }
    }
}
