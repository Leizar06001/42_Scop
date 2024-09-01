#include <scop.hpp>

std::vector<float> trivertices;
GLuint vertexbuffer;


ObjMesh::ObjMesh(std::vector<Vec3<float>> &in_trivertices) {
    glGenBuffers(1, &vertexbuffer);

    for(size_t i = 0; i < in_trivertices.size(); i++){
        trivertices.push_back(in_trivertices[i].x);
        trivertices.push_back(in_trivertices[i].y);
        trivertices.push_back(in_trivertices[i].z);
    }

    // std::vector<float> positions = {
    //     -1.0f, -1.0f, 0.0f, //bottom left
    //      1.0f, -1.0f, 0.0f, //bottom right
    //     -1.0f,  1.0f, 0.0f, //top left
    //      1.0f,  1.0f, 0.0f,  //top right
    //     -1.0f,  10.0f, 0.0f, //top left
    //      1.0f,  10.0f, 0.0f  //top right
    // };
    std::vector<int> colorIndices = {
        0, 1, 2, 3, 1, 2
    };
    // std::vector<int> elements = {
    //     0, 1, 2,
    //     2, 1, 3,
    //     2, 3, 4,
    //     3, 5, 4
    // };
    // element_count = 6;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VBOs.resize(2);

    //position
    glGenBuffers(1, &VBOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, trivertices.size() * sizeof(float),
        trivertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
    glEnableVertexAttribArray(0);

    //color
    // glGenBuffers(1, &VBOs[1]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    // glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(int),
    //     colorIndices.data(), GL_STATIC_DRAW);
    // glVertexAttribIPointer(1, 1, GL_INT, 4, (void*)0);
    // glEnableVertexAttribArray(1);

    //element buffer
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(int),
    //     elements.data(), GL_STATIC_DRAW);

        // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // attribute, size, type, normalized, stride, array buffer offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 2nd attribute buffer : colors
    // glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Draw the triangle !
    // std::cout << "triV : " << triVertices.size() << std::endl;

    // glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    // glBufferData(GL_ARRAY_BUFFER, triUvs.size() * sizeof(Vec2<float>), &triUvs[0], GL_STATIC_DRAW);


    // std::cout << "quadV : " << quadVertices.size() << std::endl;
    // glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(Vec3<float>), &quadVertices[0], GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    // glBufferData(GL_ARRAY_BUFFER, quadUvs.size() * sizeof(Vec2<float>), &quadUvs[0], GL_STATIC_DRAW);
    // Use GL_TRIANGLE_FAN instead of GL_QUADS
    // for (size_t i = 0; i < quadVertices.size(); i += 4) {
    //     glDrawArrays(GL_TRIANGLE_FAN, i, 4);
    // }

    glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);

}

void ObjMesh::draw() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, trivertices.size() * sizeof(Vec3<float>), &trivertices[0], GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, trivertices.size()); // 3 indices starting at 0 -> 1 triangle
    // glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
}

ObjMesh::~ObjMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(VBOs.size(), VBOs.data());
    glDeleteBuffers(1, &EBO);
}
