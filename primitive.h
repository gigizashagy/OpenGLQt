#ifndef PRIMITIVE_H
#define PRIMITIVE_H

class Mesh;
class Primitive
{
public:
    static Mesh* Cube(float width);
    static Mesh* Plane(float width);
    static Mesh* SkyBoxCube(float width);
};

#endif // PRIMITIVE_H
