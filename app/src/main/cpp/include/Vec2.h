#pragma once
#include <ostream>

template <class T>
class Vec2
{
public:
	T x, y;
	Vec2() : x(0), y(0) {}
	Vec2(T _x, T _y) : x(_x), y(_y) {}

	// setters
	void set(Vec2<T>& vec2)
	{
		this->x = vec2.x;
		this->y = vec2.y;
	}

	void set(T _x, T _y)
	{
		this->x = _x;
		this->y = _y;
	}

	void set(T n)
	{
		this->x = n;
		this->y = n;
	}

	// reset 
	void reset()
	{
		this->x = 0;
		this->y = 0;
	}

	// operation functions
	Vec2<T>& add(const Vec2<T>& vec2)
	{
		this->x += vec2.x;
		this->y += vec2.y;
		return *this;
	}

	Vec2<T>& sub(const Vec2<T>& vec2)
	{
		this->x -= vec2.x;
		this->y -= vec2.y;
		return *this;
	}

	Vec2<T>& mul(const Vec2<T>& vec2)
	{
		this->x *= vec2.x;
		this->y *= vec2.y;
		return *this;
	}

	Vec2<T>& div(const Vec2<T>& vec2)
	{
		this->x /= vec2.x;
		this->y /= vec2.y;
		return *this;
	}

	// operators for type T
	Vec2<T>& operator+(const T& n) { return this->add({ n, n }); }
	Vec2<T>& operator-(const T& n) { return this->sub({ n, n }); }
	Vec2<T>& operator*(const T& n) { return this->mul({ n, n }); }
	Vec2<T>& operator/(const T& n) { return this->div({ n, n }); }

	Vec2<T>& operator+=(const T& n) { return this->add({ n, n }); }
	Vec2<T>& operator-=(const T& n) { return this->sub({ n, n }); }
	Vec2<T>& operator*=(const T& n) { return this->mul({ n, n }); }
	Vec2<T>& operator/=(const T& n) { return this->div({ n, n }); }

	// operators for Vec2<T>
	Vec2<T>& operator+(const Vec2<T>& vec2) { return this->add(vec2); }
	Vec2<T>& operator-(const Vec2<T>& vec2) { return this->sub(vec2); }
	Vec2<T>& operator*(const Vec2<T>& vec2) { return this->mul(vec2); }
	Vec2<T>& operator/(const Vec2<T>& vec2) { return this->div(vec2); }

	Vec2<T>& operator+=(const Vec2<T>& vec2) { return this->add(vec2); }
	Vec2<T>& operator-=(const Vec2<T>& vec2) { return this->sub(vec2); }
	Vec2<T>& operator*=(const Vec2<T>& vec2) { return this->mul(vec2); }
	Vec2<T>& operator/=(const Vec2<T>& vec2) { return this->div(vec2); }

	// 
	Vec2<T>& operator=(const Vec2<T>& vec2)
	{
		this->x = vec2.x;
		this->y = vec2.y;
		return *this;
	}

	bool operator==(Vec2<T>& vec2) { return (this->x == vec2.x && this->x == vec2.y); }

	Vec2<T>& operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	Vec2<T>& operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	friend inline std::ostream& operator<<(std::ostream& out, const Vec2<T> vec2)
	{
		out << "(" << vec2.x << ", " << vec2.y << ")";
		return out;
	}

};

