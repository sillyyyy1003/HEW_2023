#include "Collider.h"

#define SQUAREWIDTH 0.8

Collider::Collider()
{
}

std::vector<Vector3> Collider::GetVerticies()
{
	return std::vector<Vector3>();
}

void Collider::InitCollider(COLLISION_TYPE _type)
{
	m_collisionType = _type;
	isActive = true;
}

void Collider::Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation)
{
	

}

Collider::~Collider(void)
{
}

std::vector<Vector3> Collider::SetTriangle(float _radius)
{
    Triangle triangle;
    triangle.A = { 0 , _radius };
    triangle.B = { _radius , -_radius };
    triangle.C = { -_radius , -_radius };

    // 1つ目の凸多角形の頂点座標を定義
    std::vector<Vector3> vertices = {
        Vector3(triangle.A.x, triangle.A.y,0),
        Vector3(triangle.B.x, triangle.B.y,0),
        Vector3(triangle.C.x, triangle.C.y,0),
    };

    return vertices;
}

std::vector<Vector3> Collider::SetSquare(float _widthX, float _widthY)
{
    SQURE squre;
    // 四角の下の三角
    squre.A = { _widthX,_widthY };
    squre.B = { _widthX,-_widthY };
    squre.C = { -_widthX,-_widthY };
    squre.D = { -_widthX,_widthY };

    // 1つ目の凸多角形の頂点座標を定義
    std::vector<Vector3> vertices = {
        Vector3(squre.A.x, squre.A.y,0),
        Vector3(squre.B.x, squre.B.y,0),
        Vector3(squre.C.x, squre.C.y,0),
        Vector3(squre.D.x, squre.D.y,0),
    };

    return vertices;
}

std::vector<Vector3> Collider::SetCircle(float radius)
{
    SQURE squre;
    float squarewidth = SQUAREWIDTH;
    // 四角の下の三角
    squre.A = { radius * squarewidth,radius * squarewidth };
    squre.B = { radius * squarewidth,-radius * squarewidth };
    squre.C = { -radius * squarewidth,-radius * squarewidth };
    squre.D = { -radius * squarewidth,radius * squarewidth };

    SQURE circle;
    // 四角の下の三角
    circle.A = { 0, radius };
    circle.B = { radius,0 };
    circle.C = { 0 , -radius };
    circle.D = { -radius,0 };


    // 1つ目の凸多角形の頂点座標を定義
    std::vector<Vector3> vertices = {
        Vector3(circle.A.x, circle.A.y,0),
        Vector3(squre.A.x, squre.A.y,0),
        Vector3(circle.B.x, circle.B.y,0),
        Vector3(squre.B.x, squre.B.y,0),
        Vector3(circle.C.x, circle.C.y,0),
        Vector3(squre.C.x, squre.C.y,0),
        Vector3(circle.D.x, circle.D.y,0),
        Vector3(squre.D.x, squre.D.y,0),
    };
    return vertices;
}