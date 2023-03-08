#include "geometry.h"
#include <cmath>


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

void rotateOy(point3d& p, double oy)
{
    double oldX = p.x;
    double oldZ = p.z;
    p.x = oldX*cos(oy) + oldZ*sin(oy);
    p.z = -oldX*sin(oy) + oldZ*cos(oy);
}

void rotateOx(point3d& p, double ox)
{
    double oldY = p.y;
    double oldZ = p.z;
    p.y = oldY*cos(ox) + oldZ*sin(ox);
    p.z = -oldY*sin(ox) + oldZ*cos(ox);
}

void rotatePoints(point3d& p, triangle& t, double ox, double oy)
{
    rotateOy(p,oy);
    rotateOy(t.p1,oy);
    rotateOy(t.p2,oy);
    rotateOy(t.p3,oy);
    //std::cout<< p.x << ' ' <<  p.y <<  ' ' <<p.z;
    rotateOx(p,ox);
    rotateOx(t.p1,ox);
    rotateOx(t.p2,ox);
    rotateOx(t.p3,ox);
}

void findOy(double& oy, point3d p)
{
    oy =  acos( (0*p.x+p.z*p.z)/(sqrt((double)0*0+p.z*p.z)*sqrt((double)p.x*p.x+p.z*p.z)));
}

void findOx(double& ox, point3d p)
{
    ox = acos( (p.z*p.z+0*p.y)/(sqrt((double)p.z*p.z+0*0)*sqrt((double)p.z*p.z+p.y*p.y)));
}

void findAnglesForRotate(double& ox, double& oy, point3d p)
{
    findOy(oy, p);
    findOx(ox, p);
}

bool isVisible(triangle t, point3d p)
{
    double ox, oy;
    findAnglesForRotate(ox, oy, p);
    rotatePoints(p, t, -ox,-oy);
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

