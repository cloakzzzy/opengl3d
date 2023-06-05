#pragma once
#include <glfw3.h>
#include <iostream>
#include <functional>
#include <Windows.h>

using namespace std;

void glfwSetVersion(int majorversion, int minorversion) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorversion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorversion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

class Window
{
private:
	float LastFrame = 0.0;
	int Frames = 0.0;
	float s = 0.0;
public:
	GLFWwindow* Object;
	float DeltaTime = 0.0;
	float FPS = 0.0;
	
	void Create(int width, int height, const char* title) {
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		Object = glfwCreateWindow(width, height, title, NULL, NULL);
		if (Object == NULL)
		{
			cout << "Failed to create GLFW window" << '\n';
			glfwTerminate();
		}
		glfwMakeContextCurrent(Object);

	}


	void MainLoop(function<void()> func, float r,float g,float b) {
		while (!glfwWindowShouldClose(Object))
		{
			s = round(glfwGetTime());
			Frames += 1;
			Sleep(1);
			float currentFrame = static_cast<float>(glfwGetTime());
			DeltaTime = currentFrame - LastFrame;
			LastFrame = currentFrame;

			glClearColor(r,g,b, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			func();
			
			if (round(glfwGetTime()) != s) {
				FPS = Frames;
				Frames = 0;
			}
			
			glfwSwapBuffers(Object);
			glfwPollEvents();
		}
	}
};