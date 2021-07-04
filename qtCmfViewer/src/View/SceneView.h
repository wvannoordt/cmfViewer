#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H
#include <cmath>
#include "cmf.h"
struct SceneView
{
    float zenith;
    float azimuth;
    int width;
    int height;
    double pov = 75.0;
    float xScreenShift = 0.0;
    float yScreenShift = 0.0;
    float zdisp = -3.0;
    cmf::Vec3<float> orbit = 0;
    SceneView(void)
    {
        Reset();
    }
    void Reset(void)
    {
        zenith = 0;
        azimuth = 0;
        pov = 75.0;
        xScreenShift = 0.0;
        yScreenShift = 0.0;
        zdisp = -3.0;
        orbit = 0;
    }
    void IncrementShift(float incrX, float incrY)
    {
        xScreenShift += incrX;
        yScreenShift += incrY;
        auto x = XAxis();
        auto y = YAxis();
        x *= incrX;
        y *= incrY;
        orbit -= x;
        orbit += y;
    }
    cmf::Vec3<float> YAxis(void)
    {
        const double k = 0.01745329251;
        return cmf::Vec3<float> (cos(k*(zenith+90))*sin(-k*azimuth), sin(k*(zenith+90)), cos(k*(zenith+90))*cos(-k*azimuth));
    }

    cmf::Vec3<float> XAxis(void)
    {
        const double k = 0.01745329251;
        cmf::Vec3<float> r(cos(k*zenith)*sin(-k*azimuth), sin(k*zenith), cos(k*zenith)*cos(-k*azimuth));
        cmf::Vec3<float> y = YAxis();
        return cmf::Vec3<float>(y[1]*r[2]-y[2]*r[1], y[2]*r[0]-y[0]*r[2], y[0]*r[1]-y[1]*r[0]);
    }

    double GetAngle()
    {
        return pov;
    }
};

#endif
