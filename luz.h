#ifndef LUZ_H
#define LUZ_H
#include "rgb.h"
#include "point.h"

class luz
{
public:
    luz();
    luz(RGB R, Point Pos);
    RGB R;
    Point P;
};

#endif // LUZ_H
