//
// Created by parth on 9/23/2025.
//

#ifndef ADV_GAME_PROG_TECH_VECTOR_H
#define ADV_GAME_PROG_TECH_VECTOR_H

class Vector2D {
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector2D() {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2D(float _x, float _y) : x(_x), y(_y) {}

    Vector2D operator*(float scalar) const;

    Vector2D operator/(float scalar) const;

    Vector2D operator+(Vector2D vector_2d) const;

    Vector2D operator-(Vector2D vector_2d) const;

    bool operator==(Vector2D vector_2d) const;

    bool operator!=(Vector2D vector_2d) const;

    Vector2D operator-() const;

    Vector2D &operator+=(const Vector2D &vector_2d);

    Vector2D &operator-=(const Vector2D &vector_2d);

    friend Vector2D operator*(float scalar, Vector2D vector_2d);

    Vector2D& normalize();

};

#endif //ADV_GAME_PROG_TECH_VECTOR_H