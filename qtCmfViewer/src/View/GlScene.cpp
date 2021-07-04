#include "GlScene.h"

GlScene::GlScene(void)
{

}

GlScene::~GlScene(void)
{
    for (auto& obj: sceneObjects)
    {
        delete obj;
    }
}

SceneView& GlScene::GetCurrentView(void)
{
    return currentView;
}

std::vector<GlSceneObject*>& GlScene::GetObjects(void)
{
    return sceneObjects;
}

void GlScene::AddObject(GlSceneObject* newObject)
{
    sceneObjects.push_back(newObject);
    selectedObject = newObject;
}

void GlScene::PaintObjects(void)
{
    for (auto& obj: sceneObjects)
    {
        obj->PaintObject();
    }
    if (selectedObject != NULL)
    {
        selectedObject->IndicateBoundingBox();
    }
}
