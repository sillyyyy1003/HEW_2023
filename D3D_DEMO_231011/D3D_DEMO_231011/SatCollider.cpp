#include "SatCollider.h"

// 各辺に対して垂直なベクトルのリストを作成する
std::vector<Vector2> getAxes(const PolygonSAT& a, const PolygonSAT& b) {
    std::vector<Vector2> axes;

    for (std::size_t i = 0; i < a.vertices.size(); i++) {
        const Vector2& p1 = a.vertices[i];
        const Vector2& p2 = (i == a.vertices.size() - 1) ? a.vertices[0] : a.vertices[i + 1];
        axes.push_back(Vector2::Normal(Vector2::Minus(p2, p1)));
    }

    for (std::size_t i = 0; i < b.vertices.size(); i++) {
        const Vector2& p1 = b.vertices[i];
        const Vector2& p2 = (i == b.vertices.size() - 1) ? b.vertices[0] : b.vertices[i + 1];
        axes.push_back(Vector2::Normal(Vector2::Minus(p2, p1)));
    }

    return axes;
}

// 当たり判定本体
bool Collide(const PolygonSAT& a, const PolygonSAT& b) {

    // 軸のリスト
    std::vector<Vector2> axes = getAxes(a, b);

    for (std::size_t i = 0; i < axes.size(); i++) {
        const std::vector<float>& ap = a.Projection(axes[i]); // 軸に対しての射影
        const std::vector<float>& bp = b.Projection(axes[i]);

        if (!((ap[0] <= bp[0] && bp[0] <= ap[1]) || (bp[0] <= ap[0] && ap[0] <= bp[1]))) {
            return false; // 射影同士が重なっていないなら当たっていない
        }
    }
    return true; // すべての垂直なベクトルに対して射影が重なっていれば当たっている
}