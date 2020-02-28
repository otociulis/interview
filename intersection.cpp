#include <iostream>

class Vector3D {
	double _x, _y, _z;
public:
	Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) : _x(x), _y(y), _z(z) {}

	Vector3D cross(const Vector3D& v) const {
		return Vector3D(_y * v._z - _z * v._y,
			_z * v._x - _x * v._z,
			_x * v._y - _y * v._x);
	}

	double length() const { return sqrt(_x * _x + _y * _y + _z * _z); }
	Vector3D operator +(const Vector3D& v) const {
		return Vector3D(_x + v._x, _y + v._y, _z + v._z);
	}
	Vector3D operator *(double v) const { return Vector3D(_x * v, _y * v, _z * v); }
	Vector3D operator /(double v) const { return Vector3D(_x / v, _y / v, _z / v); }

	friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
};

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
	os << "(" << v._x << "," << v._y << "," << v._z << ")";
	return os;
}

/*
Plane equation in form a * x + b * y + c * z + d = 0
*/
class Plane {
	double _a, _b, _c, _d;
public:
	Plane(double a, double b, double c, double d) : _a(a), _b(b), _c(c), _d(d) {}
	double d() const { return _d; }

	Vector3D normal() const { return Vector3D(_a, _b, _c); }
};

bool intersectionLine(const Plane& a, const Plane& b, Vector3D& p1, Vector3D& p2) {
	const auto an = a.normal();
	const auto bn = b.normal();
	const auto cn = an.cross(bn); // Normal of third intersecting plane
	const auto det = cn.length() * cn.length();

	// If determinant is 0 planes are parallel (or identical)
	if (det < std::numeric_limits<double>::epsilon()) {
		return false;
	}

	// We'll use three plane intersection approach from Graphics Gems

	p1 = (cn.cross(bn) * a.d() + an.cross(cn) * b.d()) / det;
	p2 = p1 + cn;

	return true;
}

int main(int argc, char **argv) {
	Plane a(1, -1, 2, -3);
	Plane b(2, 1, -4, 6);
	Vector3D p1, p2;

	if (!intersectionLine(a, b, p1, p2)) {
		std::cout << "Planes are not intersecting";
	}
	else {
		std::cout << p1 << std::endl;
		std::cout << p2 << std::endl;
	}
}
