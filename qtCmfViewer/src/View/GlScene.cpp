#include "GlScene.h"

GlScene::GlScene(void)
{

}

GlScene::~GlScene(void)
{

}

SceneView& GlScene::GetCurrentView(void)
{
    return currentView;
}

void GlScene::PaintObjects(void)
{
    auto& sceneObjects = this->items;
    for (auto& obj: sceneObjects)
    {
        obj->PaintObject();
    }
    if (selectedObject != NULL)
    {
        selectedObject->IndicateBoundingBox();
    }
}
