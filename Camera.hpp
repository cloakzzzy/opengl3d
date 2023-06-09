#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"
#include <string>

using namespace std;

const float DEG = 180 / 3.14159;


class Camera
{
private:
    bool firstMouse = true;
    float yaw = -90.0f;	
    float pitch = 0.0f;
    float lastX;
    float lastY;
    float nea;
    float fa;
    
public:
    float fov = 45.0f;
    float aspect;
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec2 yawdir = glm::vec2(0.0f, -1.0);


    Camera(float windowwidth, float windowheight ,float Fov, float Aspect, float Near, float Far) {
        lastX = windowwidth / 2;
        lastY = windowheight / 2;
        fov = Fov;
        aspect = Aspect;
        nea = Near;
        fa = Far;
	}
	void Mouse_SetLookAt(float xposIn, float yposIn, float sensitivity) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; 
        lastX = xpos;
        lastY = ypos;

        xoffset *= 1 / sensitivity;
        yoffset *= 1 / sensitivity;

        yaw += xoffset ;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        yawdir.x = cos(glm::radians(yaw));
        yawdir.y = sin(glm::radians(yaw));

        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction = glm::normalize(direction);
	}

    void Controller_HandleRightStick(float SensitivityX, float SensitivityY,float Xdegrees,float Ydegrees, float deadzone) {
        
        float x = Xdegrees;
        float y = Ydegrees;
    
        if ((x < deadzone and x > -deadzone)) {
            x = 0;
        }
        if (y < deadzone and y > -deadzone) {
            y = 0;
        }
        yaw += x * SensitivityX;
        pitch -= y * SensitivityY;
      
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        yawdir.x = cos(glm::radians(yaw));
        yawdir.y = sin(glm::radians(yaw));

        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction = glm::normalize(direction);
    }
   
    void Controller_HandleLeftStick(float Xdegrees, float Ydegrees, float speed, float deadzone, float dt) {
        float x = Xdegrees;
        float y = Ydegrees;

        if ((x < deadzone and x > -deadzone)) {
            x = 0;
        }
        if (y < deadzone and y > -deadzone) {
            y = 0;
        }
        position.x -= speed * dt * y  * yawdir.x;
        position.z -= speed * dt * y * yawdir.y;
        position += speed * dt * x * glm::normalize(glm::cross(direction, up));
    }
 
    glm::mat4 GetView() {
        glm::mat4 view = glm::lookAt(position, position + direction, up);
        return view;
    }

    glm::mat4 GetProjection() {
        glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, nea, fa);
        return projection;
    }
};