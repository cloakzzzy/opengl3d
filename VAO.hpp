#pragma once

#include<glew.h>
#include"VBO.hpp"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	unsigned int VertexSize;
	// Constructor that generates a VAO ID
	VAO() {
		glGenVertexArrays(1, &ID);
	}

	// Links a VBO to the VAO using a certain layout
	void LinkVBO(VBO& VBO, GLuint vertexsize, GLuint layout, GLuint compsize, GLuint fromstart) {
		VBO.Bind();
		glVertexAttribPointer(layout, compsize, GL_FLOAT, GL_FALSE, vertexsize * sizeof(float), (void*)(fromstart * sizeof(float)));
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
		VertexSize = vertexsize;
	}
	// Binds the VAO
	void Bind() {
		glBindVertexArray(ID);
	}
	// Unbinds the VAO
	void Unbind() {
		glBindVertexArray(0);
	}
	// Deletes the VAO
	void Delete() {
		glDeleteVertexArrays(1, &ID);
	}
};