
#include <iostream>

using namespace std;

struct Vector
{
public:
	Vector(const int X, const int Y, const int Z) : x(X), y(Y), z(Z) {};

	int x;
	int y;
	int z;

	Vector& operator *(const int& Value)
	{
		x *= Value;
		y *= Value;
		z *= Value;

		return *this;
	}

	Vector& operator - (const Vector& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}
	
	friend istream& operator >> (istream& is, Vector& vector)
	{
		is >> vector.x >> vector.y >> vector.z;
		return is;
	}
};

int main()
{
	Vector v(1, 1, 1);
	Vector v2(3, 3, 3);
	
	const auto v3 = v2 - v;

	cout << v3.x << v3.y << v3.z<< endl;

	cin >> v;

	cout << endl << v.x << v.y << v.z;

	return 0;
}