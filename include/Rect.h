//
// Created by bruno on 23/03/18.
//

#ifndef INC_140017658_T1_RECT_H
#define INC_140017658_T1_RECT_H

#include "Vec2.h"

class Rect {
public:
    Rect();
    Rect(float x, float y, float w, float h);

    float x;
    float y;
    float w;
    float h;

    Rect operator+(Vec2 vec);
    Rect operator=(Vec2 vec);
    Rect operator+=(Vec2 vec);
    Vec2 Center();
    Vec2 DifferenceBetweenCenters(Rect r2);
    bool Contains(Vec2 vec);
    void Centralize();
    void PlaceCenterAt(Vec2 pos);

};


#endif //INC_140017658_T1_RECT_H
