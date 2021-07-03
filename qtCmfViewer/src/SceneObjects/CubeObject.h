#ifndef CUBE_OBJECT_H
#define CUBE_OBJECT_H

#include "src/View/GlSceneObject.h"

class CubeObject : public GlSceneObject
{
    public:
        CubeObject(cmf::Vec3<float> center_in, cmf::Vec3<float> radii_in);
        ~CubeObject(void){}
        virtual void PaintObject(void) override;
    private:
        cmf::Vec3<float> center, radii;
};

#endif
