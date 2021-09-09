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
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*8));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferHandle);

	glDrawElements(GL_TRIANGLES, ibsize, GL_UNSIGNED_INT, NULL);
}

MeshResource MeshResource::Cube() {

    MeshResource cube = MeshResource();
	Vertex vertices[24] = {	
		// Front
		Vertex{Vector(-0.5, -0.5, 0.5), Vector(1,0,0,1), {0.5, 0.75}},
		Vertex{Vector(-0.5, 0.5, 0.5), Vector(1,0,0,1), {0.75, 0.75}},
		Vertex{Vector(0.5, -0.5, 0.5), Vector(1,0,0,1), {0.5, 1.0}},
		Vertex{Vector(0.5, 0.5, 0.5), Vector(1,0,0,1), {0.75, 1.0}},

		// Left
		Vertex{Vector(-0.5, -0.5, 0.5), Vector(0,1,0,1), {0.25, 0.5}},
		Vertex{Vector(-0.5, 0.5, 0.5), Vector(0,1,0,1), {0.5, 0.5}},
		Vertex{Vector(-0.5, -0.5, -0.5), Vector(0,1,0,1), {0.25, 0.75}},
		Vertex{Vector(-0.5, 0.5, -0.5), Vector(0,1,0,1), {0.5, 0.75}},

		// Right
		Vertex{Vector(0.5, -0.5, -0.5), Vector(0,0,1,1), {0.75, 0.5}},
		Vertex{Vector(0.5, 0.5, -0.5), Vector(0,0,1,1), {1.0, 0.5}},
		Vertex{Vector(0.5, -0.5, 0.5), Vector(0,0,1,1), {0.75, 0.75}},
		Vertex{Vector(0.5, 0.5, 0.5), Vector(0,0,1,1), {1.0, 0.75}},

		// Over
		Vertex{Vector(-0.5, 0.5, -0.5), Vector(1,1,1,1), {0.5, 0.5}},
		Vertex{Vector(-0.5, 0.5, 0.5), Vector(1,1,1,1), {0.75, 0.5}},
		Vertex{Vector(0.5, 0.5, -0.5), Vector(1,1,1,1), {0.5, 0.75}},
		Vertex{Vector(0.5, 0.5, 0.5), Vector(1,1,1,1), {0.75, 0.75}},

		// Under
		Vertex{Vector(-0.5, -0.5, 0.5), Vector(0,0,0,1), {0.0, 0.5}},
		Vertex{Vector(-0.5, -0.5, -0.5), Vector(0,0,0,1), {0.25, 0.5}},
		Vertex{Vector(0.5, -0.5, 0.5), Vector(0,0,0,1), {0.0, 0.75}},
		Vertex{Vector(0.5, -0.5, -0.5), Vector(0,0,0,1), {0.25, 0.75}},

		// Back
		Vertex{Vector(-0.5, -0.5, -0.5), Vector(1,0,1,1), {0.5, 0.25}},
		Vertex{Vector(-0.5, 0.5, -0.5), Vector(1,0,1,1), {0.75, 0.25}},
		Vertex{Vector(0.5, -0.5, -0.5), Vector(1,0,1,1), {0.5, 0.5}},
		Vertex{Vector(0.5, 0.5, -0.5), Vector(1,0,1,1), {0.75, 0.5}}
		};

	Index indices[12] = {
		Index{0,1,3},
		Index{0,2,3},

		Index{4,5,7},
		Index{4,6,7},
		
		Index{8,9,11},
		Index{8,10,11},
		
		Index{12,13,15},
		Index{12,14,15},
		
		Index{16,17,19},
		Index{16,18,19},
		
		Index{20,21,23},
		Index{20,22,23}
	};
	cube.UploadToGPU(vertices, 24, indices, 12);
    return cube;
}
