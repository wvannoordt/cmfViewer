#ifndef GL_SCENE_OBJECT_H
#define GL_SCENE_OBJECT_H

#include "cmf.h"
#include <QOpenGLFunctions>
#include <GL/glu.h>

struct SceneObjectBoundingBox
{
    cmf::Vec<float, 6> bounds = 0;

    float& operator [] (int i) {return bounds[i];}
};

class GlSceneObject
{
    public:
        GlSceneObject(void){}
        virtual ~GlSceneObject(void){};
        virtual void PaintObject(void)=0;
        void SetLinesEnabled(bool val) {linesEnabled = val;}
        bool LinesAreEnabled(void) {return linesEnabled;}
        void SetFacesEnabled(bool val) {facesEnabled = val;}
        bool FacesAreEnabled(void) {return facesEnabled;}
        SceneObjectBoundingBox& GetBoundingBox(void) {return box;}
    private:
        bool linesEnabled = true;
        bool facesEnabled = true;
    protected:
        SceneObjectBoundingBox box;
};

#endif
