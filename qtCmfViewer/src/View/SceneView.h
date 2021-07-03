#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H
#include <cmath>
struct SceneView
{
    float zenith;
    float azimuth;
    int width;
    int height;
    double pov = 75.0;
    float xScreenShift = 0.0;
    float yScreenShift = 0.0;

    double GetAngle()
    {
        return pov;
    }
};

#endif
