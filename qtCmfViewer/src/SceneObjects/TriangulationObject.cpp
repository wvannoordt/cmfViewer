#include "src/SceneObjects/TriangulationObject.h"

TriangulationObject::TriangulationObject(size_t meshSize_in)
{
    numFaces = meshSize_in;
    vertexBuffer = (float*)malloc(sizeof(float)*9*numFaces);
}

void TriangulationObject::PaintObject(void)
{
    if (this->FacesAreEnabled())
    {
        for (size_t i = 0; i < numFaces; i++)
        {
            glBegin(GL_TRIANGLES);
            glColor3f(0.4, 0.4, 0.4);
            glVertex3f((*this)(i, 0, 0), (*this)(i, 0, 1), (*this)(i, 0, 2));
            glVertex3f((*this)(i, 1, 0), (*this)(i, 1, 1), (*this)(i, 1, 2));
            glVertex3f((*this)(i, 2, 0), (*this)(i, 2, 1), (*this)(i, 2, 2));
            glEnd();
        }
    }
    if (this->LinesAreEnabled())
    {
        for (size_t i = 0; i < numFaces; i++)
        {
            glLineWidth(lineWidth);
            glBegin(GL_LINE_LOOP);
            glColor3f(lineColor[0], lineColor[1], lineColor[2]);
            glVertex3f((*this)(i, 0, 0), (*this)(i, 0, 1), (*this)(i, 0, 2));
            glVertex3f((*this)(i, 1, 0), (*this)(i, 1, 1), (*this)(i, 1, 2));
            glVertex3f((*this)(i, 2, 0), (*this)(i, 2, 1), (*this)(i, 2, 2));
            glEnd();
        }
    }
}

void TriangulationObject::ComputeBoundingBox(void)
{
    for (size_t i = 0; i < numFaces; i++)
    {
        for (int p = 0; p < 3; p++)
        {
            for (int j = 0; j < 3; j++)
            {
                box[2*j]   = (box[2*j]   < (*this)(i,p,j))?(box[2*j]  ):((*this)(i,p,j));
                box[2*j+1] = (box[2*j+1] > (*this)(i,p,j))?(box[2*j+1]):((*this)(i,p,j));
            }
        }
    }
}

TriangulationObject::~TriangulationObject(void)
{
    if (vertexBuffer != NULL)
    {
        free(vertexBuffer);
    }
}
