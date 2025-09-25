#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "constants/constants.h"
#include "utils/camera.h"

#include "models/watch_body.h"
#include "models/watch_face.h"
#include "models/watch_holder.h"
#include "models/watch_band.h"
#include "models/watch_hour.h"
#include "models/watch_minute.h"
#include "models/watch_pivot.h"
#include "models/watch_screw.h"
#include "models/watch_miniscrew.h"
#include "models/watch_hourmarker.h"
#include "models/watch_bighourmarker.h"
#include "models/watch_button.h"
#include "models/watch_lock.h"

#include "animation/watch_animation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0,1,0));
bool lightEnabled = false;
bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keys[key] = true;
            if (key == GLFW_KEY_F) lightEnabled = !lightEnabled;
        } else if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}

void do_movement(float deltaTime) {
    if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(GLFW_KEY_W, deltaTime);
    if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(GLFW_KEY_S, deltaTime);
    if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(GLFW_KEY_A, deltaTime);
    if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(GLFW_KEY_D, deltaTime);
    if (keys[GLFW_KEY_E]) camera.RotateYaw(-90.0f * deltaTime);
    if (keys[GLFW_KEY_Q]) camera.RotateYaw( 90.0f * deltaTime);
}

std::string loadShaderSource(const char* filepath) {
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int compileShader(const char* source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    int success; char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) { glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl; }
    return shader;
}

unsigned int createShaderProgram(const char* vPath, const char* fPath) {
    auto vCode = loadShaderSource(vPath);
    auto fCode = loadShaderSource(fPath);
    unsigned int vShader = compileShader(vCode.c_str(), GL_VERTEX_SHADER);
    unsigned int fShader = compileShader(fCode.c_str(), GL_FRAGMENT_SHADER);
    unsigned int program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    int success; char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) { glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl; }
    glDeleteShader(vShader); glDeleteShader(fShader);
    return program;
}

int main() {
    // GLFW + GLAD init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGl Watch", nullptr, nullptr);
    if (!window) { std::cerr<<"Failed to create window"; return -1; }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cerr<<"Failed to init GLAD"; return -1; }
    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(window, key_callback);

    // models
    WatchBody    watchBody;
    WatchFace    watchFace;
    WatchHolder  watchHolder;
    WatchBand    watchBand;
    WatchHour    watchHour;
    WatchMinute  watchMinute;
    WatchPivot  watchPivot;
    WatchScrew  watchScrew1;
    WatchScrew  watchScrew2;
    WatchScrew  watchScrew3;
    WatchScrew  watchScrew4;
    WatchScrew  watchScrew5;
    WatchScrew  watchScrew6;
    WatchMiniScrew  watchMiniScrew1;
    WatchMiniScrew  watchMiniScrew2;
    WatchMiniScrew  watchMiniScrew3;
    WatchMiniScrew  watchMiniScrew4;
    WatchHourMarker  watchHourMarker;
    WatchBigHourMarker  watchBigHourMarker;
    WatchButton  watchButton1;
    WatchButton  watchButton2;
    WatchButton  watchButton3;
    WatchLock  watchLock;

    WatchAnimation animation;

    unsigned int shaderProgram = createShaderProgram("shaders/vertex_shader.glsl","shaders/fragment_shader.glsl");
    glUseProgram(shaderProgram);
    auto modelLoc = glGetUniformLocation(shaderProgram, "model");
    auto viewLoc  = glGetUniformLocation(shaderProgram, "view");
    auto projLoc  = glGetUniformLocation(shaderProgram, "projection");
    auto lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    auto viewPosLoc  = glGetUniformLocation(shaderProgram, "viewPos");
    auto lightEnabledLoc = glGetUniformLocation(shaderProgram, "lightEnabled");

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        do_movement(deltaTime);
        animation.Update(deltaTime);

        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // view & proj
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(CAMERA_FOV), float(WINDOW_WIDTH)/WINDOW_HEIGHT,0.1f,1000.0f);
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(projLoc,1,GL_FALSE,glm::value_ptr(proj));
        glUniform3fv(lightPosLoc,1,glm::value_ptr(camera.Position));
        glUniform3fv(viewPosLoc,1,glm::value_ptr(camera.Position));
        glUniform1i(lightEnabledLoc,lightEnabled);

        // draw static
        glm::mat4 identity(1.0f);
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(identity));
        watchBody.Draw(); watchFace.Draw(); watchHolder.Draw(); watchPivot.Draw();

        // band
        glm::mat4 bandModel = glm::translate(identity, glm::vec3(0,0,-3.2f));
        bandModel = glm::rotate(bandModel,glm::radians(90.0f),glm::vec3(0,1,0));
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(bandModel));
        watchBand.Draw();

        // hour hand
        glm::mat4 hourModel = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.14f));
        hourModel = glm::rotate(hourModel, glm::radians(animation.hourAngle), glm::vec3(0, 0, 1));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(hourModel));
        watchHour.Draw();

        // minute hand
        glm::mat4 minModel = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.13f));
        minModel = glm::rotate(minModel, glm::radians(animation.minuteAngle), glm::vec3(0, 0, 1));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(minModel));
        watchMinute.Draw();

        // screw
        glm::mat4 screwModel1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.125f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(screwModel1));
        watchScrew1.Draw();
        glm::mat4 screwModel2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.97427857925f, 0.5625f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(screwModel2));
        watchScrew2.Draw();
        glm::mat4 screwModel3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.97427857925f, -0.5625f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(screwModel3));
        watchScrew3.Draw();
        glm::mat4 screwModel4 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.125f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(screwModel4));
        watchScrew4.Draw();
        glm::mat4 screwModel5 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.97427857925f, -0.5625f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(screwModel5));
        watchScrew5.Draw();
        glm::mat4 screwModel6 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.97427857925f, 0.5625f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(screwModel6));
        watchScrew6.Draw();

        // mini screw
        glm::mat4 miniScrewModel1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 1.35f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(miniScrewModel1));
        watchMiniScrew1.Draw();
        glm::mat4 miniScrewModel2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -1.35f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(miniScrewModel2));
        watchMiniScrew2.Draw();
        glm::mat4 miniScrewModel3 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -1.35f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(miniScrewModel3));
        watchMiniScrew3.Draw();
        glm::mat4 miniScrewModel4 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 1.35f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(miniScrewModel4));
        watchMiniScrew4.Draw();

        // hour marker
        for (int i = 1; i < 12; ++i) {
            float angle = glm::radians(i * 30.0f); 
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1)); 
            transform = glm::translate(transform, glm::vec3(0.0f, 0.9f, 0.005f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
            watchHourMarker.Draw();
        }

        // big hour marker
        glm::mat4 bigHourMarkerModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.9f, 0.005f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(bigHourMarkerModel));
        watchBigHourMarker.Draw();

        // watch button
        glm::mat4 watchButtonModel1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.3f, 0.0f, 0.0f));
        watchButtonModel1 = glm::rotate(watchButtonModel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(watchButtonModel1));
        watchButton1.Draw();

        glm::mat4 watchButtonModel2 = glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, 0.7f, 0.0f));
        watchButtonModel2 = glm::rotate(watchButtonModel2, glm::radians(90.0f), glm::vec3(0, 1, 0));
        watchButtonModel2 = glm::rotate(watchButtonModel2, glm::radians(-30.0f), glm::vec3(1, 0, 0));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(watchButtonModel2));
        watchButton2.Draw();

        glm::mat4 watchButtonModel3 = glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, -0.7f, 0.0f));
        watchButtonModel3 = glm::rotate(watchButtonModel3, glm::radians(90.0f), glm::vec3(0, 1, 0));
        watchButtonModel3 = glm::rotate(watchButtonModel3, glm::radians(30.0f), glm::vec3(1, 0, 0));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(watchButtonModel3));
        watchButton3.Draw();

        // watch lock
        glm::mat4 lockModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -6.20f));
        lockModel = glm::rotate(lockModel, glm::radians(-10.0f), glm::vec3(1, 0, 0));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lockModel));
        watchLock.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
