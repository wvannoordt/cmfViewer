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

void GlScene::AddObject(GlSceneObject* newObject)
{
    sceneObjects.push_back(newObject);
}

void GlScene::PaintObjects(void)
{
    for (auto& obj: sceneObjects)
    {
        obj->PaintObject();
    }
}
