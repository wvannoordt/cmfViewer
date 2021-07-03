#ifndef GL_SCENE_OBJECT_H
#define GL_SCENE_OBJECT_H

#include "cmf.h"
#include <QOpenGLFunctions>
#include <GL/glu.h>

class GlSceneObject
{
    public:
        GlSceneObject(void){}
        virtual ~GlSceneObject(void){};
        virtual void PaintObject(void)=0;
};

#endif
