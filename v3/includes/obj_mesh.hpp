#ifndef OBJ_MESH_H
#define OBJ_MESH_H

#include <scop.hpp>


class ObjMesh {
    public:
    ObjMesh(std::vector<Vec3<float>> &in_trivertices);
    void draw();
    ~ObjMesh();

    private:
    unsigned int EBO, VAO, element_count;
    std::vector<unsigned int> VBOs;
};

#endif
