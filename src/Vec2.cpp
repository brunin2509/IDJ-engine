//
// Created by bruno on 23/03/18.
//

#include <cmath>
#include "Vec2.h"

Vec2::Vec2() {
    x = 0.0;
    y = 0.0;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator+(Vec2 v2) {
    return {this->x + v2.x, this->y + v2.y};
}

Vec2 Vec2::operator-(Vec2 v2) {
    return {this->x - v2.x, this->y - v2.y};
}

Vec2 Vec2::operator*(float c) {
    return {this->x * c, this->y * c};
}

float Vec2::Magnitude() {
    return std::sqrt(this->x*this->x + this->y*this->y);
}

Vec2 Vec2::Normalized() {
    auto magnitude = this->Magnitude();
    return {this->x/magnitude, this->y/magnitude};
}

float Vec2::Distance(Vec2 v2) {
    return (*this-(v2)).Magnitude();
}

float Vec2::XInclination() {
    return std::atan2(this->y, this->x);
}

float Vec2::InclinationOfDifference(Vec2 v2) {
    return (*this-(v2)).XInclination();
}

Vec2 Vec2::Rotate(float radians) {
    return {this->x*std::cos(radians) - this->y*std::sin(radians), this->y*std::cos(radians) + this->x*std::sin(radians)};
}

Vec2 Vec2::Norm(Vec2 v) {
    return v.Normalized();
}

float Vec2::Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 Vec2::Rotate(Vec2 v, float radians) {
    return v.Rotate(radians);
}






