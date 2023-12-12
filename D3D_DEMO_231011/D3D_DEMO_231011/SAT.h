#pragma once

#include <iostream>
#include <vector>
#include <cmath>

class Vector2 {
public:
    float x; // x-coordinate
    float y; // y-coordinate

    // Constructor
    Vector2(float x, float y) : x(x), y(y) {}

    // Dot product: Dot(a, b) = |a||b|cosθ
    static float Dot(const Vector2& a, const Vector2& b) {
        return a.x * b.x + a.y * b.y;
    }

    // Normal vector for perpendicular line
    static Vector2 Normal(const Vector2& a) {
        return Vector2(a.y, -a.x);
    }

    // Vector subtraction
    static Vector2 Minus(const Vector2& a, const Vector2& b) {
        return Vector2(a.x - b.x, a.y - b.y);
    }

    // Vector rotation
    static Vector2 Rotate(const Vector2& point, float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);
        return Vector2(
            point.x * cosA - point.y * sinA,
            point.x * sinA + point.y * cosA
        );
    }
};

class PolygonSAT {
public:
    std::vector<Vector2> vertices; // Vertex coordinates, should be in clockwise order
    float rotation; // Rotation angle in radians

    // コンストラクタ
    PolygonSAT(const std::vector<Vector2>& vertices, float rotation) : vertices(vertices), rotation(rotation) {
        // 回転を適用
        for (Vector2& vertex : this->vertices) {
            vertex = Vector2::Rotate(vertex, rotation);
        }
    }


    // Projection of the polygon onto a given axis
    std::vector<float> Projection(const Vector2& axis) const {
        float min = Vector2::Dot(axis, vertices[0]);
        float max = min;

        for (std::size_t i = 1; i < vertices.size(); i++) {
            float p = Vector2::Dot(axis, vertices[i]);
            if (p < min) {
                min = p;
            }
            else if (p > max) {
                max = p;
            }
        }
        return { min, max };
    }

    // 回転後の頂点座標を取得する
    std::vector<Vector2> GetRotatedVertices() const {
        std::vector<Vector2> rotatedVertices;
        for (const Vector2& vertex : vertices) {
            rotatedVertices.push_back(Vector2::Rotate(vertex, rotation)); // マイナス方向に回転
        }
        return rotatedVertices;
    }
};

bool Collide(const PolygonSAT& a, const PolygonSAT& b);

