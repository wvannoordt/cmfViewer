#ifndef GL_SCENE_OBJECT_H
#define GL_SCENE_OBJECT_H

#include "cmf.h"
#include <QOpenGLFunctions>
#include <GL/glu.h>

struct SceneObjectBoundingBox
{
    cmf::Vec<float, 6> bounds = 0;

    float& operator [] (int i) {return bounds[i];}
};

class GlSceneObject
{
    public:
        GlSceneObject(void){}
        virtual ~GlSceneObject(void){};
        virtual void PaintObject(void)=0;
        void SetLinesEnabled(bool val) {linesEnabled = val;}
        bool LinesAreEnabled(void) {return linesEnabled;}
        void SetFacesEnabled(bool val) {facesEnabled = val;}
        bool FacesAreEnabled(void) {return facesEnabled;}
        SceneObjectBoundingBox& GetBoundingBox(void) {return box;}
        void IndicateBoundingBox(void)
        {
            cmf::Vec3<float> vertex  = 0;
            float displace = 0.1;
            float cornerSize = 0.1;
            cmf::Vec3<float> color(0.0, 0.0, 0.0);
            float lineWidth = 3.0;
            for (int k = 0; k < 2; k++)
            {
                vertex[2] = box[4+k] + displace*(2*k-1);
                for (int j = 0; j < 2; j++)
                {
                    vertex[1] = box[2+j] + displace*(2*j-1);
                    for (int i = 0; i < 2; i++)
                    {
                        vertex[0] = box[i] + displace*(2*i-1);
                        glLineWidth(lineWidth);
                        glBegin(GL_LINES);
                        glColor3f(color[0], color[1], color[2]);
                        glVertex3f(vertex[0], vertex[1], vertex[2]);
                        glVertex3f(vertex[0]-(2*i-1)*cornerSize, vertex[1], vertex[2]);
                        glEnd();

                        glLineWidth(lineWidth);
                        glBegin(GL_LINES);
                        glColor3f(color[0], color[1], color[2]);
                        glVertex3f(vertex[0], vertex[1], vertex[2]);
                        glVertex3f(vertex[0], vertex[1]-(2*j-1)*cornerSize, vertex[2]);
                        glEnd();

                        glLineWidth(lineWidth);
                        glBegin(GL_LINES);
                        glColor3f(color[0], color[1], color[2]);
                        glVertex3f(vertex[0], vertex[1], vertex[2]);
                        glVertex3f(vertex[0], vertex[1], vertex[2]-(2*k-1)*cornerSize);
                        glEnd();
                    }
                }
            }
        }
    private:
        bool linesEnabled = true;
        bool facesEnabled = true;
    protected:
        SceneObjectBoundingBox box;
        cmf::Vec3<float> lineColor = 0.3;
        float lineWidth = 2.0f;
};

#endif
