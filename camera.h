#ifndef CAMERA_H
#define CAMERA_H
#include "observador.h"

class Camera
{
public:
    Camera();
    Camera(float w, float h, float d, int sizeX, int sizeY, Observador O);
    float w,h,d,DX,DY;
    Observador* Obs;
};

#endif // CAMERA_H
