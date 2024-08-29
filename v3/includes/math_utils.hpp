#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <array>
#include <cstddef>
#include <cmath>
#include <stdexcept>

float degToRad(float degrees);

template <typename T, size_t N>
class Vec {
    private:
        std::array<T, N> _data;

    public:
        T& x;
        T& y;
        T& z;
        T& w;

        // Default constructor
        Vec() : 
            _data{},
            x(_data[0]),
            y(N > 1 ? _data[1] : _data[0]),
            z(N > 2 ? _data[2] : _data[0]),
            w(N > 3 ? _data[3] : _data[0])
        {}

        // Constructor with initializer list
        Vec(std::initializer_list<T> init) :
            x(_data[0]),
            y(N > 1 ? _data[1] : _data[0]),
            z(N > 2 ? _data[2] : _data[0]),
            w(N > 3 ? _data[3] : _data[0])
        {
            if (init.size() != N) {
                throw std::invalid_argument("Incorrect number of arguments");
            }
            std::copy(init.begin(), init.end(), _data.begin());
        }

        template <typename... Args>
        Vec(Args... args);

        Vec(const Vec<T, N>& other);
        Vec<T, N>& operator=(const Vec<T, N>& other);

        T&        operator[](size_t i) { return _data[i]; }
        const T&  operator[](size_t i) const { return _data[i]; }

        Vec<T, N> operator+(const Vec<T, N>& other) const;
        Vec<T, N> operator-(const Vec<T, N>& other) const;
        Vec<T, N> operator*(const Vec<T, N>& other) const;
        Vec<T, N> operator/(const Vec<T, N>& other) const;
        Vec<T, N> operator+(T scalar) const;
        Vec<T, N> operator-(T scalar) const;
        Vec<T, N> operator*(T scalar) const;
        Vec<T, N> operator/(T scalar) const;
};

template <typename T>
using Vec1 = Vec<T, 1>;

template <typename T>
using Vec2 = Vec<T, 2>;

template <typename T>
using Vec3 = Vec<T, 3>;

template <typename T>
using Vec4 = Vec<T, 4>;

// Non-template function declaration
Vec3<float> vecPlusScalar(const Vec3<float>& vec, float b);
float       vecScalarProduct(const Vec3<float>& vec1, const Vec3<float>& vec2);
Vec3<float> vecCrossProduct(const Vec3<float>& vec1, const Vec3<float>& vec2);
Vec3<float> vecNormalize(const Vec3<float>& vec);


// template <typename T, size_t N>
// Vec<T, N>::Vec() : _data{}, x(_data[0]), y(_data[1]), z(_data[2]), w(_data[3]) {}

template <typename T, size_t N>
template <typename... Args>
Vec<T, N>::Vec(Args... args) : _data{static_cast<T>(args)...}, 
                               x(_data[0]), y(_data[1]), z(_data[2]), w(_data[3]) {
    static_assert(sizeof...(args) == N, "Invalid number of arguments");
}

template <typename T, size_t N>
Vec<T, N>::Vec(const Vec<T, N>& other) : _data(other._data), 
                                         x(_data[0]), y(_data[1]), z(_data[2]), w(_data[3]) {}

template <typename T, size_t N>
Vec<T, N>& Vec<T, N>::operator=(const Vec<T, N>& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

// Vector operations

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator+(const Vec<T, N>& other) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] + other[i];
    }
    return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator-(const Vec<T, N>& other) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] - other[i];
    }
    return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator*(const Vec<T, N>& other) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] * other[i];
    }
    return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator/(const Vec<T, N>& other) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] / other[i];
    }
    return result;
}

// Scalar operations

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator+(T scalar) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] + scalar;
    }
    return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator-(T scalar) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] - scalar;
    }
    return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator*(T scalar) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] * scalar;
    }
    return result;
}

template <typename T, size_t N>
Vec<T, N> Vec<T, N>::operator/(T scalar) const {
    Vec<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = _data[i] / scalar;
    }
    return result;
}


class Mat4 {
private:
    std::array<float, 16> _data;

public:
    Mat4();  // Identity matrix
    Mat4(const Mat4& other);
    Mat4& operator=(const Mat4& other);

    float& operator()(size_t col, size_t row);
    const float& operator()(size_t col, size_t row) const;

    Mat4        operator*(const Mat4& other) const;         // Matrix multiplication
    Vec4<float> operator*(const Vec4<float>& vec) const;    // Matrix-vector multiplication

    static Mat4 translation(float x, float y, float z);
    static Mat4 rotation(float angle, float x, float y, float z);
    static Mat4 scale(float x, float y, float z);
    static Mat4 perspective(float fovy, float aspect, float near, float far);
};

Mat4 mat4translate(Mat4 mat, Vec3<float> vec);
Mat4 mat4rotate(Mat4 mat, float angle, Vec3<float> axis);
Mat4 mat4scale(Mat4 mat, Vec3<float> vec);
Mat4 lookAt(Vec3<float> pos, Vec3<float> target, Vec3<float> up);


// Mat4 implementations
inline Mat4::Mat4() : _data{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1} {}

inline Mat4::Mat4(const Mat4& other) : _data(other._data) {}

inline Mat4& Mat4::operator=(const Mat4& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

inline float& Mat4::operator()(size_t col, size_t row) {
    return _data[col + 4 * row];
}

inline const float& Mat4::operator()(size_t col, size_t row) const {
    return _data[col + 4 * row];
}

#endif