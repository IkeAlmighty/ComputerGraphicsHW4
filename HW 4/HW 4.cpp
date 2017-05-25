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
void main(void){ \n\
	gl_Position = vertex; \n\
}";
static char* fsSource = "#version 120 \n\
void main(void){\n\
	gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);\n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

GLfloat *object;
int vertexCount;
GLushort *indices;
int indexCount;

int main(int argc, char* argv[])
{
	OBJStreamLoader loader = OBJStreamLoader("C:/Users/Isaac/Dropbox/Coding Resources/wwnnsthl4k-LibertyStatue/LibertyStatue/LibertStatue.obj");
	
	//load the object:
	object = loader.getVertexes();
	indices = loader.getIndices();

	vertexCount = loader.vertexCount();
	indexCount = loader.indexCount();

	/*for (int i = 0; i < loader.vertexCount(); i++) {
		std::cout << object[i]<<" ";
		if (i % 3 == 0 && i > 0) {
			std::cout << "\n";
		}
	}

	for (int i = 0; i < loader.indexCount(); i++) {
		std::cout << indices[i] << " ";
		if (i % 3 == 0 && i > 0) {
			std::cout << "\n";
		}
	}*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 700);
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
	location = glGetAttribLocation(prog, "vertex");
	glEnableVertexAttribArray(location);

	//draw Object from loader. We load the object when the program starts, so 
	//we only have to use a reference here.
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 0, object);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glFlush();
	glutSwapBuffers();
}

