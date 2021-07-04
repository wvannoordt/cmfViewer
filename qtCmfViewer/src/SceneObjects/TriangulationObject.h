#ifndef TRIANGULATION_OBJECT_H
#define TRIANGULATION_OBJECT_H

#include "src/View/GlSceneObject.h"

class TriangulationObject : public GlSceneObject
{
    public:
        TriangulationObject(size_t numFaces_in);
        float& operator() (int i, int j, int v)
        {
            return vertexBuffer[9*i+3*j+v];
        }
        virtual void PaintObject(void);
        ~TriangulationObject(void);
    protected:
        void ComputeBoundingBox(void);
    private:
        size_t numFaces;
        float* vertexBuffer = NULL;
};

#endif
