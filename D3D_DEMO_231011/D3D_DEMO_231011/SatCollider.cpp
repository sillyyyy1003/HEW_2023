#include "SatCollider.h"

// �e�ӂɑ΂��Đ����ȃx�N�g���̃��X�g���쐬����
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

// �����蔻��{��
bool Collide(const PolygonSAT& a, const PolygonSAT& b) {

    // ���̃��X�g
    std::vector<Vector2> axes = getAxes(a, b);

    for (std::size_t i = 0; i < axes.size(); i++) {
        const std::vector<float>& ap = a.Projection(axes[i]); // ���ɑ΂��Ă̎ˉe
        const std::vector<float>& bp = b.Projection(axes[i]);

        if (!((ap[0] <= bp[0] && bp[0] <= ap[1]) || (bp[0] <= ap[0] && ap[0] <= bp[1]))) {
            return false; // �ˉe���m���d�Ȃ��Ă��Ȃ��Ȃ瓖�����Ă��Ȃ�
        }
    }
    return true; // ���ׂĂ̐����ȃx�N�g���ɑ΂��Ďˉe���d�Ȃ��Ă���Γ������Ă���
}