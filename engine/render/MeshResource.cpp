#include "config.h"
#include "render/MeshResource.h"


Vertex::Vertex() {
    pos = Vector3D();
    color = Vector4D();
}

Vertex::Vertex(float x, float y, float z, Vector4D color) {
    pos = Vector3D(x, y, z);
    this->color = color;
}


MeshResource* MeshResource::Quad(const Vector3D size, const Vector4D color[4]) {
    Vertex vertices[4] = { Vertex(0.5 * size.x, 0.5 * size.y, -1, color[0]), Vertex(-0.5 * size.x, 0.5 * size.y, -1, color[1]), Vertex(0.5 * size.x, -0.5 * size.y, -1, color[2]), Vertex(-0.5 * size.x, -0.5 * size.y, -1, color[3]) };
    unsigned int indices[6] = { 0, 1, 2, 1, 2, 3 };

    return new MeshResource(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(int));
}

MeshResource::MeshResource(Vertex vertices[], int Verticeslength, unsigned int indices[], int indicesLength) : indices(indicesLength)
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 7 * Verticeslength, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesLength, indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshResource::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (GLvoid*)(sizeof(float) * 3));
    glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}