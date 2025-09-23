//
// Created by parth on 9/23/2025.
//

#include "Vector.h"

#include <cmath>
#include <math.h>

Vector2D Vector2D::operator*(float scalar) const {
    return {x * scalar, y * scalar};
}

Vector2D Vector2D::operator/(float scalar) const {
    return {x / scalar, y / scalar};
}

Vector2D Vector2D::operator+(Vector2D vector_2d) const {
    return {x + vector_2d.x, y + vector_2d.y};
}

Vector2D Vector2D::operator-(Vector2D vector_2d) const {
    return {x - vector_2d.x, y - vector_2d.y};
}

bool Vector2D::operator==(Vector2D vector_2d) const {
    return x == vector_2d.x && y == vector_2d.y;
}

bool Vector2D::operator!=(Vector2D vector_2d) const {
    return x != vector_2d.x || y != vector_2d.y;
}

Vector2D Vector2D::operator-() const {
    return {-x, -y};
}


Vector2D operator*(float scalar, Vector2D vector_2d) {
    return vector_2d * scalar;
}

Vector2D &Vector2D::operator+=(const Vector2D& vector_2d) {
    this->x += vector_2d.x;
    this->y += vector_2d.y;
    return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D& vector_2d) {
    this->x -= vector_2d.x;
    this->y -= vector_2d.y;
    return *this;
}

Vector2D &Vector2D::normalize() {
    float length = sqrt(x * x + y * y);

    if (length > 0) {
        this->x /= length;
        this->y /= length;
    }

    return *this;
}

