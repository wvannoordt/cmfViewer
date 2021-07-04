#ifndef GL_SCENE_H
#define GL_SCENE_H

#include <vector>
#include "src/View/GlSceneObject.h"
#include "src/View/SceneView.h"

#include "src/SceneObjects/CubeObject.h"
#include "src/SceneObjects/CmfCartesianMeshObject.h"
#include "src/SceneObjects/TriangulationObject.h"
#include "src/SceneObjects/CmfSurfaceTriangulationObject.h"

class GlScene
{
    public:
        GlScene(void);
        ~GlScene(void);
        void PaintObjects(void);
        SceneView& GetCurrentView(void);
        void AddObject(GlSceneObject* newObject);
        std::vector<GlSceneObject*>& GetObjects(void);
    private:
        std::vector<GlSceneObject*> sceneObjects;
        SceneView currentView;
        GlSceneObject* selectedObject = NULL;
};

#endif
