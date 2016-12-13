#pragma once
class Point3D
{
public:
	Point3D() { };
	Point3D(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	~Point3D();

	void set(Point3D p)
	{
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}

	double getX() { return x; };
	double getY() { return y; };
	double getZ() { return z; };
	void set(int x_, int y_, int z_) { x = x_; y = y_; z = z_; };
	void setX(int x_) { x = x_; };
	void setY(int y_) { y = y_; };
	void setZ(int z_) { z = z_; };

protected:
	double x = 0.0;
	double y = 0.0;
	double z = .0;
};
