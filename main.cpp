#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <GL/glew.h>
#include <glfw3.h>
#include <CL/opencl.h>

#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"
#include "libs/stb_image_write.h"

#include "Macros.hpp"
#include "OtherAbstractions.hpp"
#include "Depthshapes.hpp"
#include "Flatshapes.hpp"

#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"

#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

#include <cstdarg>
#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include<algorithm> // for copy() and assign() 
#include<iterator> // for back_inserter 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);

static std::string read_file(const char* fileName) {
    std::fstream f;
    f.open(fileName, std::ios_base::in);
    assert(f.is_open());

    std::string res;
    while (!f.eof()) {
        char c;
        f.get(c);
        res += c;
    }

    f.close();

    return std::move(res);
}

const unsigned long SCR_WIDTH = 800;
const unsigned long SCR_HEIGHT = 600;

float s = 0.01f;

void Crosshair(vector<float> &vertices) {
    Gen_Quad(vertices, -0.005, 0.005, s, s);
    Gen_Quad(vertices, 0.005, 0.005, s, s);
    Gen_Quad(vertices, -0.005, -0.005, s, s);
    Gen_Quad(vertices, -0.015, 0.005, s, s);
    Gen_Quad(vertices, -0.005, 0.015, s, s);
}

unsigned int Frames = 0;
Camera cam(SCR_WIDTH, SCR_HEIGHT, 90, float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1, 100);
Window win;
const unsigned char* buttons;
Shader shader;

int main()
{
    

//=====================================================================

    glfwSetVersion(3, 3);
    win.Create(SCR_WIDTH, SCR_HEIGHT, "some aim trainer");

    glfwSwapInterval(0);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwSetFramebufferSizeCallback(win.Object, framebuffer_size_callback);
    glfwSetCursorPosCallback(win.Object, mouse_callback);
    glfwSetMouseButtonCallback(win.Object, mouse_button_callback);
    glfwSetInputMode(win.Object, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    

    glewInit();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_MULTISAMPLE); 
    shader.SetFiles("default.vert", "default.frag");

    float x = 0.05;
    float y = 0.05;
    float th = 0.005;

    vector <float> vertices;

    //Crosshair(vertices);

    int acc = 40 ;

    // NOTE: shapes are placed in order of when i implemented the functions. Going from left to right.

    //Gen_Ngonxy(vertices, acc, 0.f, 0.f, 0.0f, 2.0f);
    Gen_UVsphere(vertices, acc, 5.0f, 0.f, 0.f, 2.0f);
    //Gen_Cone(vertices, acc, 10.0f, -2.0f, 0.f, 2.0f, 4.0f);
    //Gen_Doughnut(vertices, acc, 15.0f, 0.f, 0.f, 2.0f, 1.5f);
    //Gen_Cylinder(vertices, acc, 20.0f, -2.0f, 0.f, 2.0f, 4.0f);
    //Gen_Ngonxy(vertices, acc, 24.0f, 0.f, 0.0f, 1.0f, 2.0f);


    VBO VBO1(vertices);
    VBO1.Bind();

    VAO VAO1;

    VAO1.Bind();
    VAO1.LinkVBO(VBO1, 6, 0, 3, 0);
    VAO1.LinkVBO(VBO1, 6, 1, 2, 3);
    VAO1.LinkVBO(VBO1, 6, 2, 1, 5);

    Texture texture("checkgrid.png");
    shader.SetInt("texture1", texture.ID);

    shader.Use();
    int axesCount;
    const float* axes;
    int buttonCount;
    const float speed = 3.f;
    shader.SetVec2("change", 1.0f, float(SCR_WIDTH) / float(SCR_HEIGHT));

    float xoff = 0.f;
    processInput(win.Object);

    cam.position.z += 3.0f;
    int gd = 2;

    int n = 0;

    const unsigned int h = 50;

    win.MainLoop([&] {
        
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

        /*
        n++;
        string num = to_string(n);
        string s = "frames/frames" + num + ".png";
       
        char const* name = s.c_str();  
      
        uint8_t* pixels = new uint8_t[SCR_WIDTH * SCR_HEIGHT * 3];

        glReadPixels(0,0,SCR_WIDTH, SCR_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        
        stbi_write_png(name, SCR_WIDTH, SCR_HEIGHT, 3, pixels, SCR_WIDTH * 3);
        
        
        */
   
 
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

    float cameraSpeed = static_cast<float>(5.0f) * win.DeltaTime;
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

double monob = 0;
bool toggleb = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        monob += 0.000000001;
        if (monob == 0.000000001) {
            toggleb = !toggleb;
            if (toggleb == false) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        monob = 0;

        
}