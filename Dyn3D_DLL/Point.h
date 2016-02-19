#pragma once

#ifndef POINT_H
#define POINT_H

#include "Matrix.h"

#define COLUMNS_CONST 4
#define ROWS_CONST 1

/*
Point performs just like a mathematical vector with form [x, y, z, I]*/
template<typename Type>
class Point : public Matrix<Type, ROWS_CONST, COLUMNS_CONST> {
public:
	Point() {}
	Point(const Type& x, const Type& y, const Type& z, const Type& I) {
		values[0] = x;
		values[1] = y;
		values[2] = z;
		values[3] = I;
	}
	Point(const Point& orig) : Matrix(orig) {}
	virtual ~Point() {}
	inline Type& x() {
		return values[0];
	}
	inline Type& y() {
		return values[1];
	}
	inline Type& z() {
		return values[2];
	}
	inline Type& I() {
		return values[3];
	}
	/*
	Gets the length of this Point.*/
	double magnituid() {
		return std::sqrt(x() * y() * z());
	}
	/*
	Returns a Point which points in the same direction as this one with a
	magnituid of 1.*/
	Point& unit() {
		return operator/(magnituid());
	}
	/*
	Returns the dot product of the two passed Points.*/
	static double dot(Point& u, Point& v) {
		return (u.x() * v.x()) + (u.y() * v.y()) + (u.z() * v.z());
	}
protected:
	inline virtual Matrix copy() {
		return Point(*this);
	}
};

template<typename Type>
struct std::hash<Point<Type>> {
	inline size_t operator()(Point<Type>& pnt) const {
		static const hash<Type> hasher;
		return hasher(pnt.x()) ^ (hasher(pnt.y()) << 1)
			^ (hasher(pnt.z()) << 2) ^ (hasher(pnt.I()) << 3);
	}
};

#endif
