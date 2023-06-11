#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>

#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"

#include "Macros.hpp"
#include "OtherAbstractions.hpp"
#include "Utillities.hpp"

#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"

#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

#include <cstdarg>
#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
unsigned int Frames = 0;
Camera cam(SCR_WIDTH, SCR_HEIGHT, 90, float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1, 100);
Window win;
const unsigned char* buttons;
Shader shader;

int main()
{
    glfwSetVersion(3, 3);
    win.Create(SCR_WIDTH, SCR_HEIGHT, "some aim trainer");

    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(win.Object, framebuffer_size_callback);
    glfwSetCursorPosCallback(win.Object, mouse_callback);
    glfwSetInputMode(win.Object, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewInit();
    glEnable(GL_DEPTH_TEST);
    shader.SetFiles("default.vert", "default.frag");

    float x = 0.05;
    float y = 0.05;

    float s = 0.01f;
    float th = 0.005;


    vector<float> vertices = {
        /*
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        */

    };

    //crosshair
    Gen_Quad(vertices, -0.005, 0.005, s, s);
    Gen_Quad(vertices, 0.005, 0.005, s, s);
    Gen_Quad(vertices, -0.005, -0.005, s, s);
    Gen_Quad(vertices, -0.015, 0.005, s, s);
    Gen_Quad(vertices, -0.005, 0.015, s, s);

    // NOTE: shapes are in order of when i implemented the functions. Going from left to right.
    Gen_UVsphere(vertices, 50, 0.f, 0.f, 0.f, 2.0f);
    Gen_Cone(vertices, 50, 5.0f, -2.0f, 0.f, 2.0f, 4.0f);
    Gen_Doughnut(vertices, 50, 10.0f, 0.f, 0.f, 2.0f, 1.5f);
    Gen_Cylinder(vertices, 50, 15.0f, -2.0f, 0.f, 2.0f, 4.0f);
    
    VBO VBO1(vertices);
    VBO1.Bind();

    VAO VAO1;

    VAO1.Bind();
    VAO1.LinkVBO(VBO1, 6, 0, 3, 0);
    VAO1.LinkVBO(VBO1, 6, 1, 2, 3);
    VAO1.LinkVBO(VBO1, 6, 2, 1, 5);

    Texture texture("grey.jpg");
    shader.SetInt("texture1", 0);

    shader.Use();
    int axesCount;
    const float* axes;
    int buttonCount;
    const float speed = 3.f;
    shader.SetVec2("change", 1.0f, float(SCR_WIDTH) / float(SCR_HEIGHT));

    float xoff = 0.f;

    win.MainLoop([&] {
        //cout << win.FPS << '\n';
        processInput(win.Object);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.ID);
        
        shader.Use();
        
        if (glfwJoystickPresent(GLFW_JOYSTICK_1) == 1) {
            axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
            cam.Controller_HandleRightStick(3.0f, 2.0f, axes[CONTROLLER_AXES_ANALOGSTICK_RIGHT_X], axes[CONTROLLER_AXES_ANALOGSTICK_RIGHT_Y], 0.07f);
            cam.Controller_HandleLeftStick(axes[CONTROLLER_AXES_ANALOGSTICK_LEFT_X], axes[CONTROLLER_AXES_ANALOGSTICK_LEFT_Y], speed, 0.07f, win.DeltaTime);
            if (buttons[CONTROLLER_BUTTON_CROSS] == GLFW_PRESS) {
                cam.position.y += speed * win.DeltaTime;
            }
            if (buttons[CONTROLLER_BUTTON_CIRCLE] == GLFW_PRESS) {
                cam.position.y -= speed * win.DeltaTime;
            }
            if (buttons[CONTROLLER_BUTTON_PLAYSTATIION] == GLFW_PRESS) {
                glfwTerminate();
                exit(0);
            }


        }

        shader.SetMat4("projection", glm::value_ptr(cam.GetProjection()));
        shader.SetMat4("view", glm::value_ptr(cam.GetView()));


        VAO1.Bind();

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / VAO1.VertexSize);
        }, 0.53, 0.81, 0.92);

    VBO1.Delete();
    VAO1.Delete();

    glfwTerminate();
    return 0;
}

double monoa = 0;
bool toggle = true;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        monoa += 0.000000001;
        if (monoa == 0.000000001) {
            toggle = !toggle;
            if (toggle == false) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
        monoa = 0;

    float cameraSpeed = static_cast<float>(3.0f) * win.DeltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam.position.x += cameraSpeed * cam.yawdir.x;
        cam.position.z += cameraSpeed * cam.yawdir.y;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam.position.x -= cameraSpeed * cam.yawdir.x;
        cam.position.z -= cameraSpeed * cam.yawdir.y;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.position -= glm::normalize(glm::cross(cam.direction, cam.up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.position += glm::normalize(glm::cross(cam.direction, cam.up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.position.y += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.position.y -= cameraSpeed;


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    cam.aspect = float(width) / float(height);
    shader.SetVec2("change", float(SCR_WIDTH) / float(width), float(SCR_WIDTH) / float(height));

}
double sxpos;
double sypos;
bool set = true;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (toggle == true) {
        cam.Mouse_SetLookAt(xposIn, yposIn, 10);
    }
}
