#include <math_utils.hpp>

// Convert degrees to radians
float degToRad(float degrees) {
    return degrees * M_PI / 180.0;
}

Vec3<float> vecPlusScalar(const Vec3<float> &vec, float b) {
    Vec3<float> res(0.0, 0.0, 0.0);
    res.x = vec.x + b;
    res.y = vec.y + b;
    res.z = vec.z + b;
    return res;
}

float vecScalarProduct(const Vec3<float> &vec1, const Vec3<float> &vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vec3<float> vecCrossProduct(const Vec3<float> &vec1, const Vec3<float> &vec2) {
    Vec3<float> res(0.0, 0.0, 0.0);
    res.x = vec1.y * vec2.z - vec1.z * vec2.y;
    res.y = vec1.z * vec2.x - vec1.x * vec2.z;
    res.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return res;
}

Vec3<float> vecNormalize(const Vec3<float> &vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    Vec3<float> res(0.0, 0.0, 0.0);
    res.x = vec.x / length;
    res.y = vec.y / length;
    res.z = vec.z / length;
    return res;
}




Mat4 Mat4::operator*(const Mat4& other) const {
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result(i, j) = 0;
            for (int k = 0; k < 4; k++) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

Vec4<float> Mat4::operator*(const Vec4<float>& vec) const {
    Vec4<float> result;
    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int j = 0; j < 4; j++) {
            result[i] += (*this)(i, j) * vec[j];
        }
    }
    return result;
}

Mat4 Mat4::translation(float x, float y, float z) {
    Mat4 result;
    result(0, 3) = x;
    result(1, 3) = y;
    result(2, 3) = z;
    return result;
}

Mat4 Mat4::rotation(float angle, float x, float y, float z) {
    Mat4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    float t = 1.0f - c;

    Vec3<float> axis(x, y, z);
    axis = axis * (1.0f / std::sqrt(axis.x * axis.x   + axis.y * axis.y + axis.z * axis.z));

    result(0, 0) = c + axis.x * axis.x * t;
    result(1, 0) = axis.y * axis.x * t + axis.z * s;
    result(2, 0) = axis.z * axis.x * t - axis.y * s;

    result(0, 1) = axis.x * axis.y * t - axis.z * s;
    result(1, 1) = c + axis.y * axis.y * t;
    result(2, 1) = axis.z * axis.y * t + axis.x * s;

    result(0, 2) = axis.x * axis.z * t + axis.y * s;
    result(1, 2) = axis.y * axis.z * t - axis.x * s;
    result(2, 2) = c + axis.z * axis.z * t;

    return result;
}

Mat4 Mat4::scale(float x, float y, float z) {
    Mat4 result;
    result(0, 0) = x;
    result(1, 1) = y;
    result(2, 2) = z;
    return result;
}

Mat4 Mat4::perspective(float fovy, float aspect, float near, float far) {
    Mat4 result;
    float tanHalfFovy = std::tan(fovy / 2);
    result(0, 0) = 1 / (aspect * tanHalfFovy);
    result(1, 1) = 1 / tanHalfFovy;
    result(2, 2) = -(far + near) / (far - near);
    result(2, 3) = -2 * far * near / (far - near);
    result(3, 2) = -1;
    result(3, 3) = 0;
    return result;
}

Mat4 mat4translate(Mat4 mat, Vec3<float> vec) {
    mat(0, 3) += vec.x;
    mat(1, 3) += vec.y;
    mat(2, 3) += vec.z;
    return mat;
}

Mat4 mat4rotate(Mat4 mat, float angle, Vec3<float> axis){
    float c = std::cos(angle);
    float s = std::sin(angle);
    float t = 1.0f - c;

    axis = axis * (1.0f / std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z));

    Mat4 result;
    result(0, 0) = c + axis.x * axis.x * t;
    result(1, 0) = axis.y * axis.x * t + axis.z * s;
    result(2, 0) = axis.z * axis.x * t - axis.y * s;

    result(0, 1) = axis.x * axis.y * t - axis.z * s;
    result(1, 1) = c + axis.y * axis.y * t;
    result(2, 1) = axis.z * axis.y * t + axis.x * s;

    result(0, 2) = axis.x * axis.z * t + axis.y * s;
    result(1, 2) = axis.y * axis.z * t - axis.x * s;
    result(2, 2) = c + axis.z * axis.z * t;

    return mat * result;
}

Mat4 mat4scale(Mat4 mat, Vec3<float> vec) {
    mat(0, 0) *= vec.x;
    mat(1, 1) *= vec.y;
    mat(2, 2) *= vec.z;
    return mat;
}


Mat4 lookAt(Vec3<float> pos, Vec3<float> target, Vec3<float> up) {
    Vec3<float> camDir = vecNormalize(pos - target);
    Vec3<float> camRight = vecNormalize(vecCrossProduct(up, camDir));
    Vec3<float> camUp = vecCrossProduct(camDir, camRight);

    Mat4 result; // Initialize to identity matrix

    // Set the rotation part (top-left 3x3 submatrix)
    result(0, 0) = camRight.x; result(0, 1) = camRight.y; result(0, 2) = camRight.z;
    result(1, 0) = camUp.x;    result(1, 1) = camUp.y;    result(1, 2) = camUp.z;
    result(2, 0) = -camDir.x;  result(2, 1) = -camDir.y;  result(2, 2) = -camDir.z;

    // Set the translation part
    result(0, 3) = -vecScalarProduct(camRight, pos);
    result(1, 3) = -vecScalarProduct(camUp, pos);
    result(2, 3) = vecScalarProduct(camDir, pos);

    return result;
}
