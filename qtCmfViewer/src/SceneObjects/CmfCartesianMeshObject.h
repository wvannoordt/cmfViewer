#ifndef CMF_CARTESIAN_MESH_OBJECT
#define CMF_CARTESIAN_MESH_OBJECT

#include "src/View/GlSceneObject.h"

class CmfCartesianMeshObject : public GlSceneObject
{
    public:
        CmfCartesianMeshObject(cmf::CartesianMesh* mesh_in);
        virtual void PaintObject(void) override;
    private:
        cmf::CartesianMesh* mesh;
};

#endif
