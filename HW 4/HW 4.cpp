// HW 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gl/glew.h"
#include "gl/glut.h"
#include "OBJStreamLoader.h"

#pragma comment(lib, "glew32.lib")

using namespace std;

void init(void);
void display(void);

static char* vsSource = "#version 120 \n\
attribute vec4 vertex; \n\
attribute vec4 aColor; \n\
varying vec4 vColor; \n\
void main(void){ \n\
	gl_Position = vertex; \n\
	vColor = aColor; \n\
}";
static char* fsSource = "#version 120 \n\
varying vec4 vColor;\n\
void main(void){\n\
	gl_FragColor = vColor;\n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

GLfloat *vertices;
int vertexCount;
GLushort *indices;
int indexCount;

//taken from prof's code---
GLfloat colors[] = {
	0.5F, 0.5F, 0.5F, 1.0F, // black
	0.5F, 0.5F, 1.0F, 1.0F, // blue
	0.5F, 1.0F, 0.5F, 1.0F, // green
	0.5F, 1.0F, 1.0F, 1.0F, // cyan
	1.0F, 0.5F, 0.5F, 1.0F, // red
	1.0F, 0.5F, 1.0F, 1.0F, // magenta
	1.0F, 1.0F, 0.5F, 1.0F, // yellow
	1.0F, 1.0F, 1.0F, 1.0F, // white
};
//---

int main(int argc, char* argv[])
{
	OBJStreamLoader loader = OBJStreamLoader("C:/Users/Isaac/Dropbox/Coding Resources/Object Files/stanfordbunny.obj");
	
	//load the object:
	vertices = loader.getVertices();
	indices = loader.getIndices();

	vertexCount = loader.vertexCount();
	indexCount = loader.indexCount();

	/*for (int i = 0; i < loader.vertexCount() - 2; i+=3) {
		std::cout << "v: " << vertices[i] << " " << vertices[i + 1] << " " << vertices[i + 2] << "\n";
		vertexCount++;
	}

	for (int i = 0; i < loader.indexCount() - 2; i += 3) {
		std::cout << "f: " << indices[i] << " " << indices[i + 1] << " " << indices[i + 2] << "\n";
	}*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Object Loader");

	glutDisplayFunc(display);	

	glewInit();
	init();
	glutMainLoop();


    return 0;
}

void init() {
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	prog = glCreateProgram();

	glShaderSource(vs, 1, &vsSource, NULL);
	glShaderSource(fs, 1, &fsSource, NULL);

	glCompileShader(vs);
	glCompileShader(fs);

	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glUseProgram(prog);
}

void display() {
	GLuint location;

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	location = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, vertices);

	location = glGetAttribLocation(prog, "vertex");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, vertices);
	
	//glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	try {
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, indices);
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	glFlush();
}

