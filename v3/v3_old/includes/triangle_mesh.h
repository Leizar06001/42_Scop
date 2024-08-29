#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <scop.hpp>


class TriangleMesh {
    public:
    TriangleMesh();
    void draw();
    ~TriangleMesh();

    private:
    unsigned int EBO, VAO, element_count;
    std::vector<unsigned int> VBOs;
};

#endif