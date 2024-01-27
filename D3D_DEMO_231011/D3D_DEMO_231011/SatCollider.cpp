#include "SatCollider.h"
#include <tuple>

PolygonSAT3D::PolygonSAT3D()
{
}

Quaternion::Quaternion()
{
}

bool SAT::Collide3D(const PolygonSAT3D& a, const PolygonSAT3D& b)
{
    // 軸のリスト
    std::vector < Vector3> axesA = a.GetAxes();
    std::vector<Vector3> axesB = b.GetAxes();

    // aの軸を追加
    axesA.push_back((a.vertices[1] - a.vertices[0]).Cross(a.vertices[2] - a.vertices[0]).Normalize());

    // bの軸を追加
    axesB.push_back((b.vertices[1] - b.vertices[0]).Cross(b.vertices[2] - b.vertices[0]).Normalize());

    for (const auto& axis : axesA) {
        float minA, maxA;
        std::tie(minA, maxA) = a.Projection(axis);

        float minB, maxB;
        std::tie(minB, maxB) = b.Projection(axis);

        if (!(maxA >= minB && maxB >= minA)) {
            return false;
        }
    }

    for (const auto& axis : axesB) {
        float minA, maxA;
        std::tie(minA, maxA) = a.Projection(axis);

        float minB, maxB;
        std::tie(minB, maxB) = b.Projection(axis);

        if (!(maxA >= minB && maxB >= minA)) {
            return false;
        }
    }

    return true;
}

void SAT::Setvertex(const std::vector<Vector3> ver)
{
    testver = ver;
}

std::vector<Vector3> SAT::Getvertex()
{
    return testver;
}