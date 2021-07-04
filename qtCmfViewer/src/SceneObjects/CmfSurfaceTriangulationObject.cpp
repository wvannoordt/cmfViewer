#include "src/SceneObjects/CmfSurfaceTriangulationObject.h"
#include "cmf.h"
using cmf::print;

CmfSurfaceTriangulationObject::CmfSurfaceTriangulationObject(cmf::SurfaceTriangulation* tri) : TriangulationObject(tri->GetNumFaces())
{
    triangulation = tri;
    for (size_t i = 0; i < tri->GetNumFaces(); i++)
    {
        for (int p = 0; p < 3; p++)
        {
            (*this)(i, p, 0) = (*tri)(i, p, 0);
            (*this)(i, p, 1) = (*tri)(i, p, 1);
            (*this)(i, p, 2) = (*tri)(i, p, 2);
        }
    }
    this->ComputeBoundingBox();
}

CmfSurfaceTriangulationObject::~CmfSurfaceTriangulationObject(void)
{

}
