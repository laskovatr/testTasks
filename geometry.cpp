#include "geometry.h"
point3d::point3d()
{
}
point3d::point3d(double newX, double newY, double newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}
bool operator == (point3d p1, point3d p2)
{
    if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
        return true;
    return false;
}
bool operator != (point3d p1, point3d p2)
{
    if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
        return false;
    return true;
}

triangle::triangle(point3d newP1, point3d newP2, point3d newP3)
{
    p1 = newP1;
    p2 = newP2;
    p3 = newP3;
}

bool isInside(triangle t, point3d p)
{
    return (((p.x - t.p1.x)*(t.p2.y-t.p1.y)-(p.y-t.p1.y)*(t.p2.x-t.p1.x))*((t.p3.x - t.p1.x)*(t.p2.y-t.p1.y)-(t.p3.y-t.p1.y)*(t.p2.x-t.p1.x)) >= 0) &&
    (((p.x - t.p2.x)*(t.p3.y-t.p2.y)-(p.y-t.p2.y)*(t.p3.x-t.p2.x))*((t.p1.x - t.p2.x)*(t.p3.y-t.p2.y)-(t.p1.y-t.p2.y)*(t.p3.x-t.p2.x)) >= 0) &&
    (((p.x - t.p3.x)*(t.p1.y-t.p3.y)-(p.y-t.p3.y)*(t.p1.x-t.p3.x))*((t.p2.x - t.p3.x)*(t.p1.y-t.p3.y)-(t.p2.y-t.p3.y)*(t.p1.x-t.p3.x)) >= 0 )?
    true: false;
}

bool isBeforeTriangle(triangle t, point3d p)
{
    double z;
    double A = t.p1.y * (t.p2.z - t.p3.z) + t.p2.y * (t.p3.z - t.p1.z) + t.p3.y * (t.p1.z - t.p2.z);
    double B = t.p1.z * (t.p2.x - t.p3.x) + t.p2.z * (t.p3.x - t.p1.x) + t.p3.z * (t.p1.x - t.p2.x);
    double C = t.p1.x * (t.p2.y - t.p3.y) + t.p2.x * (t.p3.y - t.p1.y) + t.p3.x * (t.p1.y - t.p2.y);
    double D = t.p1.x * (t.p2.y*t.p3.z - t.p3.y*t.p2.z) + t.p2.x * (t.p3.y*t.p1.z - t.p1.y*t.p3.z) + t.p3.x * (t.p1.y*t.p2.z - t.p2.y*t.p1.z);
    D = -D;
    z = (-D - B*p.y - A*p.x) / C;

    if (z > p.z)
    {
        return true;
    }
    return false;
}

bool isVisible(triangle t, point3d p)
{
    if (t.p1.z > p.z && t.p2.z > p.z && t.p3.z > p.z)
    {
        return true;
    }
    else
    {
        if (!isInside(t,p))
        {
            return true;
        }
        else
        {
            if(isBeforeTriangle(t,p))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

