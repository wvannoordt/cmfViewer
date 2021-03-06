#include "src/SceneObjects/CmfCartesianMeshObject.h"
#include "src/SceneObjects/CubeObject.h"
CmfCartesianMeshObject::CmfCartesianMeshObject(cmf::CartesianMesh* mesh_in)
{
    mesh = mesh_in;
    auto bnds = mesh->GetBlockBounds();
    for (int i = 0; i < 6; i++)
    {
        box[i]   = bnds[i];
    }
}

void CmfCartesianMeshObject::PaintObject(void)
{
    auto& msh = *mesh;
    for (auto& lb: msh)
    {
        cmf::Vec3<double> centerd = lb->GetBlockCenter();
        cmf::Vec3<float> center(centerd[0], centerd[1], centerd[2]);
        cmf::Vec3<float> radii = 0;
        for (int i = 0; i < CMF_DIM; i++)
        {
            cmf::Vec<double, 6> bnd = lb->GetBlockBounds();
            radii[i] = 0.5*(bnd[2*i+1] - bnd[2*i]);
        }
        CubeObject block(center, radii);

        block.SetLinesEnabled(this->LinesAreEnabled());
        block.SetFacesEnabled(this->FacesAreEnabled());
        block.PaintObject();
    }
}
