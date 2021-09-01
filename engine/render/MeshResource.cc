#include "config.h"
#include "MeshResource.h"

void MeshResource::UploadToGPU(Vertex vertices[], int size, Index indices[], int size2) {
	glGenBuffers(1, &this->vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	this->vbsize = size;

	glGenBuffers(1, &this->indexBufferHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * size2, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	this->ibsize = size2 * 3;
}

void MeshResource::Render() {

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferHandle);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferHandle);

	glDrawElements(GL_TRIANGLES, ibsize, GL_UNSIGNED_INT, NULL);
}