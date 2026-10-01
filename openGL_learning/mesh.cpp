#include "mesh.h"
#include <iostream>

using namespace std;

std::vector<Vertex> Vertex::genList(float* vertices, int noVertices) {
    std::vector<Vertex> ret(noVertices);

    int stride = 5; 

    for (int i = 0; i < noVertices; i++) {
        ret[i].pos = glm::vec3(
            vertices[i * stride + 0],
            vertices[i * stride + 1],
            vertices[i * stride + 2]
        );

        ret[i].texCoord = glm::vec2(
            vertices[i * stride + 3],
            vertices[i * stride + 4]
        );
    }

    return ret;
}

Mesh::Mesh()
    : VAO(0), VBO(0), EBO(0) {
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : vertices(vertices), indices(indices), textures(textures), VAO(0), VBO(0), EBO(0) {
    setup(); 
}

void Mesh::render(Shader shader) {
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i].bind();
        shader.setInt(textures[i].name.c_str(), i); 
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Reset active texture
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Set attribute pointers
    // vertex.position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

    // vertex.texCoord
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}