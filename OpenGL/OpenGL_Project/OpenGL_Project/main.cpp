#include <iostream>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FileUtils/stb_image.hpp"
#include "FileUtils/Path.h"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Constants.h"
#include "LightSource.hpp"

#define FILE_PATH __FILE__

// settings
constexpr uint SCR_WIDTH = 800;
constexpr uint SCR_HEIGHT = 600;

struct Time {
    Time() {
        update();
    }
    
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    
    void update() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
};

struct MouseInfo {
    float lastX = SCR_WIDTH / 2;
    float lastY = SCR_HEIGHT / 2;
    bool notOnWindow = true;
};
// need to make these global :(
MouseInfo mouseInfo;
Camera mainCamera( /*position*/ Constants::Camera::POSITION);
Time globalTime;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void genTexture(uint& tex, const char* texturePath, GLenum CHANNELS, GLenum texture_enum);
GLFWwindow* initWindow();
void generateSceneLights(std::vector<std::shared_ptr<LightSource>>& sceneLights);

uint CURR_WIDTH = SCR_WIDTH;
uint CURR_HEIGHT = SCR_HEIGHT;

int main()
{
    const Infrastructure::PathFinder pathFinder(FILE_PATH);
    GLFWwindow* window = initWindow();
    if (!window) return -1;

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    uint stride = sizeof(float) * 8;
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texCoord0 attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    stbi_set_flip_vertically_on_load(true);

    Shader objectShader(pathFinder.getPath("/shader.vs"), pathFinder.getPath("/shader.fs"));
    objectShader.use();
    SurfaceProperties surfaceProperties;
    
    // set diffuse tex
    genTexture(surfaceProperties.diffuseTex, pathFinder.getPath("/Resources/container2.png").c_str(), GL_RGBA, GL_TEXTURE0);
    objectShader.setUniform("surfaceProperties.diffuseTex", (int) 0); // 0 is dependent on GL_TEXTURE0 enum
    
    // set specular tex
    genTexture(surfaceProperties.specularTex, pathFinder.getPath("/Resources/container2_specular.png").c_str(), GL_RGBA, GL_TEXTURE1);
    objectShader.setUniform("surfaceProperties.specularTex", (int) 1); // 1 is dependent on GL_TEXTURE1 enum
    
    surfaceProperties.shininess = 32.0f;
    objectShader.setUniform("surfaceProperties", surfaceProperties);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    objectShader.setUniform("modelMatrix", model);
    objectShader.setUniform("viewMatrix", mainCamera.getViewMatrix());
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    objectShader.setUniform("projectionMatrix", projection);

    glEnable(GL_DEPTH_TEST);
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    std::vector<std::shared_ptr<LightSource>> sceneLights;
    generateSceneLights(sceneLights);
    
    Shader lightShader(pathFinder.getPath("/shader.vs"), pathFinder.getPath("/shader_LightSource.fs"));
    lightShader.use();
    lightShader.setUniform("viewMatrix", mainCamera.getViewMatrix());
    lightShader.setUniform("projectionMatrix", projection);
    
    objectShader.use();
    for (auto lightSource : sceneLights) {
        objectShader.setUniform(lightSource->getInfo());
        
    }
    objectShader.setUniform("viewPos", mainCamera.getPosition());
    
    // disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window))
    {
        globalTime.update();
        processInput(window);
        
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(mainCamera.getZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
        
        objectShader.use();
        objectShader.setUniform("viewMatrix", mainCamera.getViewMatrix());
        objectShader.setUniform("projectionMatrix", projection);
        objectShader.setUniform("viewPos", mainCamera.getPosition());

        glClearColor(0.1f, 0.2f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(VAO);
        for(unsigned int i = 1; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle) + (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
            objectShader.setUniform("modelMatrix", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        lightShader.use();
        lightShader.setUniform("viewMatrix", mainCamera.getViewMatrix());
        lightShader.setUniform("projectionMatrix", projection);
        // draw LightSources
        for(auto lightSource : sceneLights) {
            auto info = lightSource->getInfo();
            
            glm::vec3 myColor = info->specular;
            lightShader.setUniform("myColor", myColor);
            
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, info->position);
            model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
            lightShader.setUniform("modelMatrix", model);
            
            glBindVertexArray(*lightSource->getVAO());
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    using namespace Constants::Camera;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.processKeyboard(Movement::FORWARD, globalTime.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.processKeyboard(Movement::BACKWARD, globalTime.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.processKeyboard(Movement::LEFT, globalTime.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.processKeyboard(Movement::RIGHT, globalTime.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        mainCamera.processKeyboard(Movement::UP, globalTime.deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    CURR_WIDTH = width;
    CURR_HEIGHT = width;
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (mouseInfo.notOnWindow)
    {
        mouseInfo.lastX = xpos;
        mouseInfo.lastY = ypos;
        mouseInfo.notOnWindow = false;
    }

    float xoffset = xpos - mouseInfo.lastX;
    float yoffset = mouseInfo.lastY - ypos; // reversed since y-coordinates go from bottom to top

    mouseInfo.lastX = xpos;
    mouseInfo.lastY = ypos;

    mainCamera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    mainCamera.processMouseScroll(yoffset);
}

void genTexture(uint& tex, const char* texturePath, GLenum CHANNELS, GLenum texture_enum) {
    glActiveTexture(texture_enum);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    
    // load image, create texture and generate mipmaps
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, CHANNELS, width, height, 0, CHANNELS, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

GLFWwindow* initWindow() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    
    return window;
}

void generateSceneLights(std::vector<std::shared_ptr<LightSource>>& sceneLights) {
    using namespace glm;
    using namespace std;
    std::array<glm::vec3, 4> pointLightPositions = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    
    std::array<glm::vec3, 4> pointLightColors = {
        glm::vec3( 0.7f,  0.2f,  0.3f),
        glm::vec3( 1.0f,  0.8f,  0.9f),
        glm::vec3( 0.7f,  0.7f,  0.3f),
        glm::vec3( 0.1f,  0.2f,  0.7f)
    };
    
    for (int i = 0; i < pointLightPositions.size(); ++i) {
        unique_ptr<LightInfo::Generic> gen = make_unique<LightInfo::Point>(
                                                                             pointLightColors[i] * 0.5f,
                                                                             pointLightColors[i] * 0.5f,
                                                                             pointLightColors[i],
                                                                             pointLightPositions[i],
                                                                             Constants::LightSource::Defaults::POLYNOM_MAP.at(Constants::LightSource::Defaults::SPAN_RADIUS::D_50)
                                                                             );
        sceneLights.emplace_back(make_shared<LightSource>(move(gen)));
    }
    
    std::array<glm::vec3, 1> directionalLightPositions = {
        glm::vec3( 0.7f,  5.0f,  2.0f)
    };
    
    std::array<glm::vec3, 1> directionalLightColors = {
        glm::vec3( 1.0f,  1.0f,  1.0f)
    };
    
    std::array<glm::vec3, 1> directionalLightDirections = {
        glm::vec3( 0.0f,  -1.0f,  -0.1f)
    };
    for (int i = 0; i < directionalLightPositions.size(); ++i) {
        unique_ptr<LightInfo::Generic> gen = make_unique<LightInfo::Directional>(
                                                                                   directionalLightColors[i] * 0.5f,
                                                                                   directionalLightColors[i] * 0.5f,
                                                                                   directionalLightColors[i],
                                                                                   directionalLightPositions[i],
                                                                                   directionalLightDirections[i]
                                                                                   );
        sceneLights.emplace_back(make_shared<LightSource>(move(gen)));
    }
    
    std::array<glm::vec3, 1> spotLightPositions = {
        glm::vec3( 0.0f,  0.0f,  3.0f)
    };
    
    std::array<glm::vec3, 1> spotLightColors = {
        glm::vec3( 0.0f,  1.0f,  0.0f)
    };
    
    std::array<glm::vec3, 1> spotLightDirections = {
        glm::vec3( 0.0f,  0.0f,  -1.0f)
    };
    
    for (int i = 0; i < directionalLightPositions.size(); ++i) {
        unique_ptr<LightInfo::Generic> gen = make_unique<LightInfo::Spot>(
                                                                          spotLightColors[i] * 0.5f,
                                                                          spotLightColors[i] * 0.5f,
                                                                          spotLightColors[i],
                                                                          spotLightPositions[i],
                                                                          spotLightDirections[i],
                                                                          Constants::LightSource::Defaults::POLYNOM_MAP.at(Constants::LightSource::Defaults::SPAN_RADIUS::D_50),
                                                                          glm::cos(glm::radians(16.5f)),
                                                                          glm::cos(glm::radians(20.5f))
                                                                          );
        sceneLights.emplace_back(make_shared<LightSource>(move(gen)));
    }
}
