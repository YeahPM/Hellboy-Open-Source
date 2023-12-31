#pragma once
#include <ostream>



template <class T>
class Vec4
{
public:
	T x, y, w, h;
	Vec4() : x(0), y(0), w(0), h(0) {}
	Vec4(T _x, T _y, T _w, T _h) : x(_x), y(_y), w(_w), h(_h) {}

	// setters
	void set(Vec4<T>& vec4)
	{
		this->x = vec4.x;
		this->y = vec4.y;
		this->w = vec4.w;
		this->h = vec4.h;
	}

	void set(T _x, T _y, T _h, T _w)
	{
		this->x = _x;
		this->y = _y;
		this->w = _w;
		this->h = _h;
	}

	void set(T n)
	{
		this->x = n;
		this->y = n;
		this->w = n;
		this->h = n;
	}

	// reset 
	void reset()
	{
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
	}

	// operation functions
	Vec4<T>& add(const Vec4<T>& vec4)
	{
		this->x += vec4.x;
		this->y += vec4.y;
		this->w += vec4.w;
		this->h += vec4.h;
		return *this;
	}

	Vec4<T>& sub(const Vec4<T>& vec4)
	{
		this->x -= vec4.x;
		this->y -= vec4.y;
		this->w -= vec4.w;
		this->h -= vec4.h;
		return *this;
	}

	Vec4<T>& mul(const Vec4<T>& vec4)
	{
		this->x *= vec4.x;
		this->y *= vec4.y;
		this->w *= vec4.w;
		this->h *= vec4.h;
		return *this;
	}

	Vec4<T>& div(const Vec4<T>& vec4)
	{
		this->x /= vec4.x;
		this->y /= vec4.y;
		this->w /= vec4.w;
		this->h /= vec4.h;
		return *this;
	}

	// operators for type T
	Vec4<T>& operator+(const T& n) { return this->add({ n, n, n, n }); }
	Vec4<T>& operator-(const T& n) { return this->sub({ n, n, n, n }); }
	Vec4<T>& operator*(const T& n) { return this->mul({ n, n, n, n }); }
	Vec4<T>& operator/(const T& n) { return this->div({ n, n, n, n }); }

	Vec4<T>& operator+=(const T& n) { return this->add({ n, n, n, n }); }
	Vec4<T>& operator-=(const T& n) { return this->sub({ n, n, n, n }); }
	Vec4<T>& operator*=(const T& n) { return this->mul({ n, n, n, n }); }
	Vec4<T>& operator/=(const T& n) { return this->div({ n, n, n, n }); }

	// operators for Vec4<T>
	Vec4<T>& operator+(const Vec4<T>& vec4) { return this->add(vec4); }
	Vec4<T>& operator-(const Vec4<T>& vec4) { return this->sub(vec4); }
	Vec4<T>& operator*(const Vec4<T>& vec4) { return this->mul(vec4); }
	Vec4<T>& operator/(const Vec4<T>& vec4) { return this->div(vec4); }

	Vec4<T>& operator+=(const Vec4<T>& vec4) { return this->add(vec4); }
	Vec4<T>& operator-=(const Vec4<T>& vec4) { return this->sub(vec4); }
	Vec4<T>& operator*=(const Vec4<T>& vec4) { return this->mul(vec4); }
	Vec4<T>& operator/=(const Vec4<T>& vec4) { return this->div(vec4); }

	// 
	Vec4<T>& operator=(const Vec4<T>& vec4)
	{
		this->x = vec4.x;
		this->y = vec4.y;
		this->w = vec4.w;
		this->h = vec4.h;
		return *this;
	}

	bool operator==(Vec4<T>& vec4) { return (this->x == vec4.x && this->x == vec4.y); }

	Vec4<T>& operator++()
	{
		++this->x;
		++this->y;
		++this->w;
		++this->h;
		return *this;
	}

	Vec4<T>& operator--()
	{
		--this->x;
		--this->y;
		--this->w;
		--this->h;
		return *this;
	}

	friend inline std::ostream& operator<<(std::ostream& out, const Vec4<T> vec4)
	{
		out << "(" << vec4.x << ", " << vec4.y << ", " << vec4.w << ", " << vec4.h << ")";
		return out;
	}

};

