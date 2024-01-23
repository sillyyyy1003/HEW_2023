#include "PolygonCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

#define SQUAREWIDTH 0.8

PolygonCollider::PolygonCollider()
{
}

void PolygonCollider::InitCollider(DirectX::XMFLOAT3 _center, float _Radius, COLLISION_TYPE _type)
{
    Collider::InitCollider(_type);

    center = _center;
    radius = _Radius;

}

void PolygonCollider::UpdateRadius()
{
    radius = m_radius;
}

void PolygonCollider::UpdatePos()
{
    center = m_center;
}

void PolygonCollider::UpdateVerticies()
{
    verticies = SetTriangle(radius);
}

std::vector<Vector2> PolygonCollider::SetTriangle(float _radius)
{
    Triangle triangle;
    triangle.A = { 0 , _radius };
    triangle.B = { _radius , -_radius };
    triangle.C = { -_radius , -_radius };

    // 1つ目の凸多角形の頂点座標を定義
    std::vector<Vector2> vertices = {
        Vector2(triangle.A.x, triangle.A.y),
        Vector2(triangle.B.x, triangle.B.y),
        Vector2(triangle.C.x, triangle.C.y),
    };

    return vertices;
}

std::vector<Vector2> PolygonCollider::SetSquare(float _widthX, float _widthY)
{
    SQURE squre;
    // 四角の下の三角
    squre.A = { _widthX,_widthY };
    squre.B = { _widthX,-_widthY };
    squre.C = { -_widthX,-_widthY };
    squre.D = { -_widthX,_widthY };

    // 1つ目の凸多角形の頂点座標を定義
    std::vector<Vector2> vertices = {
        Vector2(squre.A.x, squre.A.y),
        Vector2(squre.B.x, squre.B.y),
        Vector2(squre.C.x, squre.C.y),
        Vector2(squre.D.x, squre.D.y),
    };

    return vertices;
}

std::vector<Vector2> PolygonCollider::SetCircle(float radius)
{
    SQURE squre;
    float squarewidth = SQUAREWIDTH;
    // 四角の下の三角
    squre.A = { radius* squarewidth,radius * squarewidth };
    squre.B = { radius * squarewidth,-radius * squarewidth };
    squre.C = { -radius * squarewidth,-radius * squarewidth };
    squre.D = { -radius * squarewidth,radius * squarewidth };

    SQURE circle;
    // 四角の下の三角
    circle.A = { 0, radius};
    circle.B = { radius,0 };
    circle.C = { 0 , -radius};
    circle.D = { -radius,0 };


    // 1つ目の凸多角形の頂点座標を定義
    std::vector<Vector2> vertices = {
        Vector2(circle.A.x, circle.A.y),
        Vector2(squre.A.x, squre.A.y),
        Vector2(circle.B.x, circle.B.y),
        Vector2(squre.B.x, squre.B.y),
        Vector2(circle.C.x, circle.C.y),
        Vector2(squre.C.x, squre.C.y),
        Vector2(circle.D.x, circle.D.y),
        Vector2(squre.D.x, squre.D.y),
    };
    return vertices;
}

void PolygonCollider::Update()
{
    if (!isActive)
    {
        return;
    }
    else {

        UpdatePos();

        UpdateRadius();

        UpdateVerticies();
    }

}

// ---図形の当たり判定の処理 ---//
bool PolygonCollider::SATBoxHit(BoxCollider* boxCollider)
{
    m_boxCollider = boxCollider->GetCollider();
    float boxradiusX = m_boxCollider.Extents.x;
    float boxradiusY = m_boxCollider.Extents.y;
    PolygonSAT Triangle(verticies, 0);
    PolygonSAT Box(SetSquare(boxradiusX, boxradiusY), 0);

    verticies = Triangle.GetRotatedVertices();
    std::vector<Vector2> Boxverticies = Box.GetRotatedVertices();

    // 四角
    for (auto& vertex : verticies) {
        vertex.x += center.x;
        vertex.y += center.y;
    }

    for (auto& vertex : Boxverticies) {
        vertex.x += m_boxCollider.Center.x;
        vertex.y += m_boxCollider.Center.y;
    }

    Triangle.vertices = verticies;
    Box.vertices = Boxverticies;

    bool collisionResult = Collide(Triangle, Box);

    // 結果を表示
    if (collisionResult)
    {
        return true;
    }
    return false;
}

bool PolygonCollider::SATCircleHit(SphereCollider* sphereCollider)
{
    m_sphereCollider = sphereCollider->GetCollider();
    PolygonSAT Triangle(verticies, 0);
    PolygonSAT Circle(SetCircle(m_sphereCollider.Radius), 0);

    verticies = Triangle.GetRotatedVertices();
    std::vector<Vector2> Circleverticies = Circle.GetRotatedVertices();

    // 四角
    for (auto& vertex : verticies) {
        vertex.x += center.x;
        vertex.y += center.y;
    }

    for (auto& vertex : Circleverticies) {
        vertex.x += m_boxCollider.Center.x;
        vertex.y += m_boxCollider.Center.y;
    }

    Triangle.vertices = verticies;
    Circle.vertices = Circleverticies;

    bool collisionResult = Collide(Triangle, Circle);

    // 結果を表示
    if (collisionResult)
    {
        return true;
    }

    return false;
}
