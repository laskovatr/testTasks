#ifndef GEOMETRY_H
#define GEOMETRY_H


class point3d
{
public:
    point3d();
    point3d(double newX, double newY, double newZ);
    double x;
    double y;
    double z;
};
bool operator == (point3d p1, point3d p2);
bool operator != (point3d p1, point3d p2);


class triangle
{
public:
    triangle(point3d newP1, point3d newP2, point3d newP3);
    point3d p1;
    point3d p2;
    point3d p3;

};

bool isVisible(triangle t, point3d p);
bool isInside(triangle t, point3d p);
#endif // GEOMETRY_H
