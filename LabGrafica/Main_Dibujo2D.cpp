#include <iostream>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800;
const GLint HEIGHT = 600;


int main()
{
    glfwInit();
    //Verificaci�n de compatibilidad 
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/
   

    GLFWwindow* window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Trofeo - Dibujo de primitivas 2D",
        NULL,
        NULL
    );

    glfwSetFramebufferSizeCallback(window, resize);

    // Verificacion de errores de creacion de ventana
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    // Verificacion de errores de inicializacion de GLEW
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialise GLEW" << std::endl;

        return EXIT_FAILURE;
    }


   
    // Imprimimos informacin de OpenGL del sistema

    std::cout << "> Version: "
        << glGetString(GL_VERSION)
        << std::endl;

    std::cout << "> Vendor: "
        << glGetString(GL_VENDOR)
        << std::endl;

    std::cout << "> Renderer: "
        << glGetString(GL_RENDERER)
        << std::endl;

    std::cout << "> SL Version: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION)
        << std::endl;


    // Define las dimensiones del viewport
     //glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader(
        "Shader/core.vs",
        "Shader/core.frag"
    );


    // =========================================================
    // VERTICES
    //
    // Cada vertice tiene 6 datos:
    //
    // x, y, z, r, g, b
    //
    // x,y,z = posicion
    // r,g,b = color
    // =========================================================

    float vertices[] =
    {

        // =====================================================
        // 0 - 3
        // BORDE SUPERIOR NEGRO
        // =====================================================

        -0.32f,  0.62f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.32f,  0.62f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.32f,  0.52f, 0.0f,    0.08f, 0.08f, 0.12f,
        -0.32f,  0.52f, 0.0f,    0.08f, 0.08f, 0.12f,


        // =====================================================
        // 4 - 7
        // PARTE SUPERIOR AMARILLA
        // =====================================================

        -0.27f,  0.52f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.27f,  0.52f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.27f,  0.42f, 0.0f,    0.95f, 0.68f, 0.08f,
        -0.27f,  0.42f, 0.0f,    0.95f, 0.68f, 0.08f,


        // =====================================================
        // 8 - 11
        // PARTE SUPERIOR AMARILLO
        // =====================================================

        -0.40f,  0.42f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.40f,  0.42f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.40f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,
        -0.40f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,


        // =====================================================
        // 12 - 15
        // PARTE CENTRAL AMARILLO
        // =====================================================

        -0.32f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.32f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.22f, -0.05f, 0.0f,    0.95f, 0.68f, 0.08f,
        -0.22f, -0.05f, 0.0f,    0.95f, 0.68f, 0.08f,


        // =====================================================
        // 16 - 19
        // PARTE INFERIOR / CUELLO
        // =====================================================

        -0.22f, -0.05f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.22f, -0.05f, 0.0f,    0.95f, 0.68f, 0.08f,
         0.12f, -0.27f, 0.0f,    0.95f, 0.68f, 0.08f,
        -0.12f, -0.27f, 0.0f,    0.95f, 0.68f, 0.08f,


        // =====================================================
        // 20 - 23
        // BORDE NEGRO PARTE MEDIA
        // =====================================================

        -0.14f, -0.27f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.14f, -0.27f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.14f, -0.36f, 0.0f,    0.08f, 0.08f, 0.12f,
        -0.14f, -0.36f, 0.0f,    0.08f, 0.08f, 0.12f,


        // =====================================================
        // 24 - 27
        // BASE CAFE
        // =====================================================

        -0.20f, -0.34f, 0.0f,    0.55f, 0.35f, 0.24f,
         0.20f, -0.34f, 0.0f,    0.55f, 0.35f, 0.24f,
         0.20f, -0.47f, 0.0f,    0.55f, 0.35f, 0.24f,
        -0.20f, -0.47f, 0.0f,    0.55f, 0.35f, 0.24f,


        // =====================================================
        // 28 - 31
        // BORDE NEGRO INFERIOR DE LA BASE
        // =====================================================

        -0.22f, -0.47f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.22f, -0.47f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.22f, -0.55f, 0.0f,    0.08f, 0.08f, 0.12f,
        -0.22f, -0.55f, 0.0f,    0.08f, 0.08f, 0.12f,


        // =====================================================
        // 32 - 35
        // BORDE PARTE IZQUIERDA
        // =====================================================

        -0.40f,  0.43f, 0.0f,    0.08f, 0.08f, 0.12f,
        -0.63f,  0.43f, 0.0f,    0.08f, 0.08f, 0.12f,
        -0.63f,  0.08f, 0.0f,    0.08f, 0.08f, 0.12f,
        -0.40f,  0.08f, 0.0f,    0.08f, 0.08f, 0.12f,


        // =====================================================
        // 36 - 39
        // PARTE IZQUIERDA AMARILLA
        // =====================================================

        -0.40f,  0.36f, 0.0f,    0.95f, 0.68f, 0.08f,
        -0.55f,  0.36f, 0.0f,    0.95f, 0.68f, 0.08f,
        -0.55f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,
        -0.40f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,


        // =====================================================
        // 40 - 43
        // HUECO BLANCO PARTE IZQUIERDA
        // =====================================================

        -0.46f,  0.31f, 0.0f,    1.0f, 1.0f, 1.0f,
        -0.52f,  0.31f, 0.0f,    1.0f, 1.0f, 1.0f,
        -0.52f,  0.20f, 0.0f,    1.0f, 1.0f, 1.0f,
        -0.46f,  0.20f, 0.0f,    1.0f, 1.0f, 1.0f,


        // =====================================================
        // 44 - 47
        // BORDE PARTE DERECHA
        // =====================================================

         0.40f,  0.43f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.63f,  0.43f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.63f,  0.08f, 0.0f,    0.08f, 0.08f, 0.12f,
         0.40f,  0.08f, 0.0f,    0.08f, 0.08f, 0.12f,


         // =====================================================
         // 48 - 51
         // PARTE DERECHA AMARILLA
         // =====================================================

          0.40f,  0.36f, 0.0f,    0.95f, 0.68f, 0.08f,
          0.55f,  0.36f, 0.0f,    0.95f, 0.68f, 0.08f,
          0.55f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,
          0.40f,  0.15f, 0.0f,    0.95f, 0.68f, 0.08f,


          // =====================================================
          // 52 - 55
          // HUECO BLANCO PARTE DERECHA
          // =====================================================

           0.46f,  0.31f, 0.0f,    1.0f, 1.0f, 1.0f,
           0.52f,  0.31f, 0.0f,    1.0f, 1.0f, 1.0f,
           0.52f,  0.20f, 0.0f,    1.0f, 1.0f, 1.0f,
           0.46f,  0.20f, 0.0f,    1.0f, 1.0f, 1.0f,


           // =====================================================
           // 56 - 59
           // BORDE NEGRO IZQUIERDO
           // =====================================================

           -0.40f,  0.15f, 0.0f,    0.08f, 0.08f, 0.12f,
           -0.32f,  0.15f, 0.0f,    0.08f, 0.08f, 0.12f,
           -0.22f, -0.05f, 0.0f,    0.08f, 0.08f, 0.12f,
           -0.30f, -0.05f, 0.0f,    0.08f, 0.08f, 0.12f,


           // =====================================================
           // 60 - 63
           // BORDE NEGRO DERECHO 
           // =====================================================

            0.32f,  0.15f, 0.0f,    0.08f, 0.08f, 0.12f,
            0.40f,  0.15f, 0.0f,    0.08f, 0.08f, 0.12f,
            0.30f, -0.05f, 0.0f,    0.08f, 0.08f, 0.12f,
            0.22f, -0.05f, 0.0f,    0.08f, 0.08f, 0.12f
    };


    // =========================================================
    // INDICES
    //
    // Cada 3 indices forman un triangulo.
    // Cada rectangulo tiene 2 triangulos.
    // =========================================================

    unsigned int indices[] =
    {
        // -----------------------------------------------------
        // PARTE SUPERIOR
        // -----------------------------------------------------

        0, 1, 2,
        0, 2, 3,

        4, 5, 6,
        4, 6, 7,


        // -----------------------------------------------------
        // CENTRO
        // -----------------------------------------------------

        8, 9, 10,
        8, 10, 11,

        12, 13, 14,
        12, 14, 15,

        16, 17, 18,
        16, 18, 19,


        // -----------------------------------------------------
        // CUELLO
        // -----------------------------------------------------

        20, 21, 22,
        20, 22, 23,


        // -----------------------------------------------------
        // BASE
        // -----------------------------------------------------

        24, 25, 26,
        24, 26, 27,

        28, 29, 30,
        28, 30, 31,


        // -----------------------------------------------------
        // PARTE IZQUIERDA
        // -----------------------------------------------------

        32, 33, 34,
        32, 34, 35,

        36, 37, 38,
        36, 38, 39,

        40, 41, 42,
        40, 42, 43,


        // -----------------------------------------------------
        // PARTE DERECHA
        // -----------------------------------------------------

        44, 45, 46,
        44, 46, 47,

        48, 49, 50,
        48, 50, 51,

        52, 53, 54,
        52, 54, 55,


        // -----------------------------------------------------
        // BORDES LATERALES
        // -----------------------------------------------------

        56, 57, 58,
        56, 58, 59,

        60, 61, 62,
        60, 62, 63
    };




    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);



    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );


  

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        EBO
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );


    // =========================================================
    // POSICION
    //
    // Cada vertice tiene:
    //
    // x y z r g b
    //
    // 6 valores en total.
    // =========================================================

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)0
    );

    glEnableVertexAttribArray(0);


    // =========================================================
    // COLOR
    // =========================================================

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


   

    while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();


       

        // Fondo blanco
        glClearColor(
            1.0f,
            1.0f,
            1.0f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.Use();
        glBindVertexArray(VAO);


        // =====================================================
        // DIBUJAR
        //
        // GL_TRIANGLES:
        // cada 3 indices forman un triangulo.
        //
        // sizeof(indices) / sizeof(indices[0]):
        // cantidad total de indices.
        //
        // GL_UNSIGNED_INT:
        // el tipo de dato de indices[].
        //
        // 0:
        // comenzar desde el primer indice.
        // =====================================================

        glDrawElements(
            GL_TRIANGLES,
            sizeof(indices) / sizeof(indices[0]),
            GL_UNSIGNED_INT,
            0
        );


        glBindVertexArray(0);



        glfwSwapBuffers(window);
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return EXIT_SUCCESS;
}


void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
    //glViewport(0, 0, screenWidth, screenHeight);
}