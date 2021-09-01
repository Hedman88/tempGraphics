//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "render/MeshResource.h"
#include "render/Camera.h"
#include "core/mathLib.h"

const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec4 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"uniform mat4 matrix;\n"
"void main()\n"
"{\n"
"	gl_Position = matrix * pos;\n"
"	Color = color;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"}\n";

using namespace Display;
namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ExampleApp::ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

	GLfloat buf[] =
	{
		-0.5f,	-0.5f,	-1,			// pos 0
		1,		0,		0,		1,	// color 0
		0,		0.5f,	-1,			// pos 1
		0,		1,		0,		1,	// color 0
		0.5f,	-0.5f,	-1,			// pos 2
		0,		0,		1,		1	// color 0
	};

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLint length = static_cast<GLint>(std::strlen(vs));
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);

		// get error log
		GLint shaderLogSize;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// setup pixel shader
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = static_cast<GLint>(std::strlen(ps));
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);

		// get error log
		shaderLogSize;
		glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	MeshResource mr = MeshResource();
	Vertex vertices[24] = {	
		// Front
		Vertex{Vector(-0.5, -0.5, 0.5), Vector(1,0,0,1)},
		Vertex{Vector(-0.5, 0.5, 0.5), Vector(1,0,0,1)},
		Vertex{Vector(0.5, -0.5, 0.5), Vector(1,0,0,1)},
		Vertex{Vector(0.5, 0.5, 0.5), Vector(1,0,0,1)},

		// Left
		Vertex{Vector(-0.5, -0.5, 0.5), Vector(0,1,0,1)},
		Vertex{Vector(-0.5, 0.5, 0.5), Vector(0,1,0,1)},
		Vertex{Vector(-0.5, -0.5, -0.5), Vector(0,1,0,1)},
		Vertex{Vector(-0.5, 0.5, -0.5), Vector(0,1,0,1)},

		// Right
		Vertex{Vector(0.5, -0.5, -0.5), Vector(0,0,1,1)},
		Vertex{Vector(0.5, 0.5, -0.5), Vector(0,0,1,1)},
		Vertex{Vector(0.5, -0.5, 0.5), Vector(0,0,1,1)},
		Vertex{Vector(0.5, 0.5, 0.5), Vector(0,0,1,1)},

		// Over
		Vertex{Vector(-0.5, 0.5, -0.5), Vector(1,1,1,1)},
		Vertex{Vector(-0.5, 0.5, 0.5), Vector(1,1,1,1)},
		Vertex{Vector(0.5, 0.5, -0.5), Vector(1,1,1,1)},
		Vertex{Vector(0.5, 0.5, 0.5), Vector(1,1,1,1)},

		// Under
		Vertex{Vector(-0.5, -0.5, 0.5), Vector(0,0,0,1)},
		Vertex{Vector(-0.5, -0.5, -0.5), Vector(0,0,0,1)},
		Vertex{Vector(0.5, -0.5, 0.5), Vector(0,0,0,1)},
		Vertex{Vector(0.5, -0.5, -0.5), Vector(0,0,0,1)},

		// Back
		Vertex{Vector(-0.5, -0.5, -0.5), Vector(1,0,1,1)},
		Vertex{Vector(-0.5, 0.5, -0.5), Vector(1,0,1,1)},
		Vertex{Vector(0.5, -0.5, -0.5), Vector(1,0,1,1)},
		Vertex{Vector(0.5, 0.5, -0.5), Vector(1,0,1,1)}
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
	mr.UploadToGPU(vertices, 24, indices, 12);

	Vector v[4] = {
		Vector(cosf(0.785), -sinf(0.785), 0, 0),
		Vector(sinf(0.785), cosf(0.785), 0, 0),
		Vector(0, 0, 1, 0),
		Vector(0, 0, 0, 1)
	};
	Matrix mat = Matrix(v);

	int width, height;
	window->GetSize(width, height);
	Camera camera = Camera(90, width, height, 0.001, 1000);

	// This variable controls the quads rotation.
	int i = 0;

	// This variable controls the quads movement in the x-axis.
	int j = 0;
	bool right = true;

	GLint matrixLoc = glGetUniformLocation(program, "matrix");


	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();

		camera.AddPos(Vector(0, 0, -0.001));
		//camera.SetRot(RotationY(0.01 * i));

		glUseProgram(this->program);
		// Calling the shader and giving it a new value to use as matrix.
		glUniformMatrix4fv(matrixLoc, 1, true, (camera.GetVPMatrix()  * RotationY(0.01 * i)).data2);
		mr.Render();

		// Incrementing position and rotation variables
		i++;
		if (right) {
			j++;
		}
		else {
			j--;
		}
		if (j >= 50) {
			right = false;
		}
		else if (j <= -50) {
			right = true;
		}
		this->window->SwapBuffers();
	}
}

} // namespace Example