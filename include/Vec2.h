//
// Created by bruno on 23/03/18.
//

#ifndef INC_140017658_T1_VEC2_H
#define INC_140017658_T1_VEC2_H

#include "Rect.h"

class Vec2 {
public:
    Vec2();
    Vec2(float x, float y);

    float x;
    float y;

    Vec2 operator+(Vec2 v2);
    Vec2 operator-(Vec2 v2);
    Vec2 operator*(float c);
    float Magnitude();
    Vec2 Normalized();
    float Distance(Vec2 v2);
    float XInclination();
    float InclinationOfDifference(Vec2 v2);
    Vec2 Rotate(float radians);
    Rect operator+(Rect rect);

};


#endif //INC_140017658_T1_VEC2_H
