#pragma once

#include <iostream>
//#include <cmath>
#include <vector>
//#include <cfloat>
#include <tuple>
//#include <algorithm> // �K�v�ȃw�b�_�[�t�@�C��


// 3D�x�N�g���̒�`
struct Vector3 {
    float x, y, z;

    // �f�t�H���g�R���X�g���N�^���`���ă����o�[�ϐ���0�ŏ�����
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // �x�N�g���̌��Z
    Vector3 operator-(const Vector3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    // �x�N�g���̊O��
    Vector3 Cross(const Vector3& other) const {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    }

    // �x�N�g���̒���
    float Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // �x�N�g���̐��K��
    Vector3 Normalize() const {
        float length = Length();
        if (length != 0) {
            return { x / length, y / length, z / length };
        }
        return { 0.0f, 0.0f, 0.0f };
    }
};

// �N�H�[�^�j�I���̒�`
struct Quaternion {
    Quaternion();
    float w, x, y, z;

    Quaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

    // ��]�s�񂩂�N�H�[�^�j�I���𐶐�
    static Quaternion FromEulerAngles(float pitch, float yaw, float roll) {
        float cy = std::cos(roll * 0.5f);
        float sy = std::sin(roll * 0.5f);
        float cp = std::cos(pitch * 0.5f);
        float sp = std::sin(pitch * 0.5f);
        float cr = std::cos(yaw * 0.5f);
        float sr = std::sin(yaw * 0.5f);

        return {
            cr * cp * cy + sr * sp * sy,
            sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy,
            cr * cp * sy - sr * sp * cy
        };
    }

    // �N�H�[�^�j�I���̋������擾
    Quaternion Conjugate() const {
        return { w, -x, -y, -z };
    }

    // �N�H�[�^�j�I���̐�
    Quaternion operator*(const Quaternion& other) const {
        return {
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w
        };
    }

    // �N�H�[�^�j�I�������]�s����擾
    std::vector<std::vector<float>> ToRotationMatrix() const {
        float wx = w * x;
        float wy = w * y;
        float wz = w * z;
        float xx = x * x;
        float xy = x * y;
        float xz = x * z;
        float yy = y * y;
        float yz = y * z;
        float zz = z * z;

        return {
            {1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy)},
            {2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx)},
            {2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy)}
        };
    }
};

// 3D���p�`�̒�`
class PolygonSAT3D {
public:
    PolygonSAT3D();
    std::vector<Vector3> vertices;
    Quaternion rotation;
    //float rotationX, rotationY, rotationZ;  // �e���ɑ΂����]�p�x�i�P��: ���W�A���j

    // ���̎擾
    std::vector<Vector3> GetAxes() const {
        std::vector<Vector3> axes;

        for (std::size_t i = 0; i < vertices.size(); i++) {
            const Vector3& p1 = vertices[i];
            const Vector3& p2 = vertices[(i + 1) % vertices.size()];
            axes.push_back((p2 - p1).Normalize());
        }

        return axes;
    }

    // ���e
    std::pair<float, float> Projection(const Vector3& axis) const {
        float minProj = FLT_MAX;
        float maxProj = -FLT_MAX;

        for (const Vector3& vertex : vertices) {
            // ��]���l�����č��W�ϊ�
            Vector3 rotatedVertex = RotatePoint(vertex, rotation);

            float dotProduct = rotatedVertex.x * axis.x + rotatedVertex.y * axis.y + rotatedVertex.z * axis.z;
            minProj = (std::min)(minProj, dotProduct);
            maxProj = (std::max)(maxProj, dotProduct);
        }

        return { minProj, maxProj };
    }

    // �|�C���g���N�H�[�^�j�I���ɂ���ĉ�]������
    Vector3 RotatePoint(const Vector3& point, const Quaternion& quaternion) const {
        // �N�H�[�^�j�I������]�s��ɕϊ�
        auto rotationMatrix = quaternion.ToRotationMatrix();

        // �|�C���g����]�s��ŕϊ�
        return {
            point.x * rotationMatrix[0][0] + point.y * rotationMatrix[1][0] + point.z * rotationMatrix[2][0],
            point.x * rotationMatrix[0][1] + point.y * rotationMatrix[1][1] + point.z * rotationMatrix[2][1],
            point.x * rotationMatrix[0][2] + point.y * rotationMatrix[1][2] + point.z * rotationMatrix[2][2]
        };
    }

    // ��]��̒��_���擾���郁�\�b�h
    std::vector<Vector3> GetRotatedVertices() const {
        std::vector<Vector3> rotatedVertices;

        // �e���ɑ΂����]�s��̌v�Z
        const float cosX = std::cos(rotation.x);
        const float sinX = std::sin(rotation.x);
        const float cosY = std::cos(rotation.y);
        const float sinY = std::sin(rotation.y);
        const float cosZ = std::cos(rotation.z);
        const float sinZ = std::sin(rotation.z);

        for (const auto& vertex : vertices) {
            Vector3 rotatedVertex;

            // X����]
            rotatedVertex.x = vertex.x;
            rotatedVertex.y = vertex.y * cosX - vertex.z * sinX;
            rotatedVertex.z = vertex.y * sinX + vertex.z * cosX;

            // Y����]
            float tempX = rotatedVertex.x * cosY + rotatedVertex.z * sinY;
            rotatedVertex.z = -rotatedVertex.x * sinY + rotatedVertex.z * cosY;
            rotatedVertex.x = tempX;

            // Z����]
            tempX = rotatedVertex.x * cosZ - rotatedVertex.y * sinZ;
            rotatedVertex.y = rotatedVertex.x * sinZ + rotatedVertex.y * cosZ;
            rotatedVertex.x = tempX;

            rotatedVertices.push_back(rotatedVertex);
        }

        return rotatedVertices;
    }
};

class SAT
{
public:
    static bool Collide3D(const PolygonSAT3D& a, const PolygonSAT3D& b);

    void Setvertex(const std::vector<Vector3> ver);
    std::vector<Vector3> Getvertex();
private:
    std::vector<Vector3> testver;
};

