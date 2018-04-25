//
// Created by bruno on 23/03/18.
//

#ifndef INC_140017658_T1_VEC2_H
#define INC_140017658_T1_VEC2_H

#define PI 3.14159265358979323846

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

    static Vec2 Norm(Vec2 v);
    static float Dot(Vec2 a, Vec2 b);
    static Vec2 Rotate(Vec2 v, float radians);

};


#endif //INC_140017658_T1_VEC2_H
