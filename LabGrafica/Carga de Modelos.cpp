// Previo 6 Modificado: Llamas Naranja-Rojizo y más Grandes
// Cornejo Gonzalez Mauricio
// Fecha de entrega 21/09/2026 (Modificado)
// 319274233

#include <iostream>
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 10.0f));

bool keys[1024];

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Colores del fuego (Naranja-Rojizo)
glm::vec3 fireColorCore(1.0f, 0.4f, 0.0f); // Naranja brillante
glm::vec3 fireColorEdge(0.8f, 0.1f, 0.0f); // Rojo oscuro


int main()
{
    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Previo 6 Modificado - Perro en llamas rojas y grandes",
        nullptr,
        nullptr
    );

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(
        window,
        &SCREEN_WIDTH,
        &SCREEN_HEIGHT
    );

    // Set callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define viewport
    glViewport(
        0,
        0,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    // Depth test
    glEnable(GL_DEPTH_TEST);

    // Shader
    // Se asume que estos shaders manejan colores base de material o uniformes
    Shader shader(
        "Shader/modelLoading.vs",
        "Shader/modelLoading.frag"
    );


    // =========================================================
    // CARGA DE LOS MODELOS
    // =========================================================

    Model dog((char*)"Models/RedDog.obj");

    Model chair((char*)"Models/Chair.obj");

    Model table((char*)"Models/Table.obj");

    Model cup((char*)"Models/Cup.obj");

    Model windowModel((char*)"Models/Window.obj");

    Model fire((char*)"Models/Fire.obj");


    // =========================================================
    // PROJECTION
    // =========================================================

    glm::mat4 projection = glm::perspective(
        camera.GetZoom(),
        (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
        0.1f,
        100.0f
    );


    // =========================================================
    // GAME LOOP
    // =========================================================

    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check events
        glfwPollEvents();

        // Camera movement
        DoMovement();


        // =====================================================
        // FONDO (Se mantiene igual)
        // =====================================================

        glClearColor(
            0.15f,
            0.08f,
            0.04f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );


        shader.Use();

        // Establecer colores de fuego por defecto para objetos que no son fuego
        glUniform3f(glGetUniformLocation(shader.Program, "materialColor"), 1.0f, 1.0f, 1.0f);


        // =====================================================
        // VIEW
        // =====================================================

        glm::mat4 view = camera.GetViewMatrix();

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "projection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "view"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );


        // =====================================================
        // 1. PERRO
        // =====================================================

        glm::mat4 model(1.0f);

        model = glm::translate(
            model,
            glm::vec3(-0.8f, -0.8f, 0.0f)
        );

        model = glm::scale(
            model,
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        dog.Draw(shader);


        // =====================================================
        // 2. SILLA
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(-0.8f, -1.0f, 0.5f)
        );

        model = glm::scale(
            model,
            glm::vec3(0.8f, 0.8f, 0.8f)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        chair.Draw(shader);


        // =====================================================
        // 3. MESA
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(2.5f, -1.0f, 0.0f)
        );

        model = glm::scale(
            model,
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        table.Draw(shader);


        // =====================================================
        // 4. TAZA
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(2.5f, 0.8f, 0.0f)
        );

        model = glm::scale(
            model,
            glm::vec3(0.5f, 0.5f, 0.5f)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        cup.Draw(shader);


        // =====================================================
        // 5. VENTANA
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(0.0f, 2.5f, -4.0f)
        );

        model = glm::scale(
            model,
            glm::vec3(1.5f, 1.5f, 1.0f)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        windowModel.Draw(shader);


        // =====================================================
        // CONFIGURACIÓN PARA EL FUEGO (Naranja/Rojo y Escala)
        // =====================================================

        // Se asume que el fragment shader tiene un uniforme para color
        GLint materialColorLoc = glGetUniformLocation(shader.Program, "materialColor");

        // Usar color naranja brillante para el núcleo del fuego
        glUniform3fv(materialColorLoc, 1, glm::value_ptr(fireColorCore));

        // Escala aumentada para el fuego (proporcionada a la imagen)
        glm::vec3 fireScale(4.0f, 5.0f, 2.0f);


        // =====================================================
        // 6. FUEGO - IZQUIERDA (Grande y Naranja/Rojo)
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(-3.5f, 0.5f, -2.5f) // Elevado un poco para compensar la escala
        );

        model = glm::scale(
            model,
            fireScale // Usando escala aumentada
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        fire.Draw(shader);


        // =====================================================
        // 7. FUEGO - DERECHA (Grande y Naranja/Rojo)
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(4.0f, 1.0f, -2.5f) // Elevado para compensar
        );

        // Opcional: Variar un poco el color o escala
        glUniform3fv(materialColorLoc, 1, glm::value_ptr(fireColorEdge));
        glm::vec3 fireScaleRight(4.2f, 6.0f, 2.0f);

        model = glm::scale(
            model,
            fireScaleRight // Escala aumentada
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        fire.Draw(shader);


        // =====================================================
        // 8. FUEGO - TRASERA IZQUIERDA (Grande y Naranja/Rojo)
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(-3.0f, 3.0f, -3.5f) // Ajustada posición
        );

        glUniform3fv(materialColorLoc, 1, glm::value_ptr(fireColorCore));

        model = glm::scale(
            model,
            glm::vec3(4.0f, 4.0f, 2.0f) // Escala aumentada
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        fire.Draw(shader);


        // =====================================================
        // 9. FUEGO - TRASERA DERECHA (Grande y Naranja/Rojo)
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(3.5f, 3.0f, -3.5f) // Ajustada posición
        );

        model = glm::scale(
            model,
            glm::vec3(4.0f, 4.0f, 2.0f) // Escala aumentada
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        fire.Draw(shader);


        // =====================================================
        // 10. FUEGO - PARTE SUPERIOR (Grande y Naranja/Rojo)
        // =====================================================

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(0.0f, 5.0f, -3.5f) // Ajustada posición
        );

        glUniform3fv(materialColorLoc, 1, glm::value_ptr(fireColorEdge));

        model = glm::scale(
            model,
            glm::vec3(9.0f, 3.0f, 2.0f) // Escala MUY aumentada a lo ancho
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        fire.Draw(shader);


        // Swap buffers
        glfwSwapBuffers(window);
    }


    glfwTerminate();

    return 0;
}


// =============================================================
// MOVIMIENTO DE LA CÁMARA (Se mantiene igual)
// =============================================================

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(
            FORWARD,
            deltaTime
        );
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(
            BACKWARD,
            deltaTime
        );
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(
            LEFT,
            deltaTime
        );
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(
            RIGHT,
            deltaTime
        );
    }
}


// =============================================================
// TECLADO (Se mantiene igual)
// =============================================================

void KeyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mode
)
{
    if (
        GLFW_KEY_ESCAPE == key &&
        GLFW_PRESS == action
        )
    {
        glfwSetWindowShouldClose(
            window,
            GL_TRUE
        );
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}


// =============================================================
// MOUSE (Se mantiene igual)
// =============================================================

void MouseCallback(
    GLFWwindow* window,
    double xPos,
    double yPos
)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(
        xOffset,
        yOffset
    );
}