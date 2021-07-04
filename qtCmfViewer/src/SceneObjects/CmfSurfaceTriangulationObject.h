#ifndef CMF_SURFACE_TRIANGULATION_OBJECT_H
#define CMF_SURFACE_TRIANGULATION_OBJECT_H

#include "cmf.h"
#include "src/SceneObjects/TriangulationObject.h"
class CmfSurfaceTriangulationObject : public TriangulationObject
{
    public:
        CmfSurfaceTriangulationObject(cmf::SurfaceTriangulation* tri);
        ~CmfSurfaceTriangulationObject(void);
    private:
        cmf::SurfaceTriangulation* triangulation;

};

#endif
