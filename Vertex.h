#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
    Vertex()
    {
    }

    Vertex(float iX, float iY, float iZ) :
        x(iX),
        y(iY),
        z(iZ)
    {
    }

    float x, y, z;
};

#endif // VERTEX_H
