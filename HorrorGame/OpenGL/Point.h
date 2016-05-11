#pragma once
#include <iostream>

template <class T>
class Point2D
{
protected:
	T x;
	T y;
public:
	Point2D(T x = 0, T y = 0);

	T getX() const;
	T getY() const;
	void setX(T x);
	void setY(T y);
	void setXY(T x, T y);
};


template <class T>
class Point3D
{
protected:
	T x;
	T y;
	T z;
public:
	Point3D(T x = 0, T y = 0, T z = 0);

	T getX() const;
	T getY() const;
	T getZ() const;
	void setX(T x);
	void setY(T y);
	void setZ(T z);
	void setXYZ(T x, T y, T z);
};


/*** class Point2D ***/
template <class T>
Point2D<T>::Point2D(T x = 0, T y = 0) : x(x), y(y) { }

template <class T>
T Point2D<T>::getX() const { return this->x; }

template <class T>
T Point2D<T>::getY() const { return this->y; }

template <class T>
void Point2D<T>::setX(T x) { this->x = x; }

template <class T>
void Point2D<T>::setY(T y) { this->y = y; }

template <class T>
void Point2D<T>::setXY(T x, T y) { this->x = x; this->y = y; }


/*** class Point3D ***/
template <class T>
Point3D<T>::Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) { }

template <class T>
void Point3D<T>::setXYZ(T x, T y, T z) { this->x = x; this->y = y; this->z = z; }

template <class T>
void Point3D<T>::setX(T x) { this->x = x; }

template <class T>
void Point3D<T>::setY(T y) { this->y = y; }

template <class T>
void Point3D<T>::setZ(T z) { this->z = z; }

template <class T>
T Point3D<T>::getX() const { return this->x; }

template <class T>
T Point3D<T>::getY() const { return this->y; }

template <class T>
T Point3D<T>::getZ() const { return this->z; }