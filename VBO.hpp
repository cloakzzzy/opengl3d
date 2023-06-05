#pragma once

#include<glew.h>
#include <vector>

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(vector<float> vertices){
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_DYNAMIC_DRAW);
	}

	// Binds the VBO
	void Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}
	// Unbinds the VBO
	void Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	// Deletes the VBO
	void Delete() {
		glDeleteBuffers(1, &ID);
	}
};
