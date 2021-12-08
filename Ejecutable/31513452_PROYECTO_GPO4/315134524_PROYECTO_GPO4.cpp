// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
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
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
float rotropero = 0.0f;
float rotventana = 0.0f;
float rotlibro = 0.0f; 
float rotpuerta = 0.0f;
float movCa = 0.0f;
float movRe = 0.0f;
float rotRe = 0.0f;
float movTa = 0.0;
float rotTa = 0.0;
bool ropero = false;
bool roperoA = false;
bool roperoC = false;
bool ventana = false;
bool ventanaA = false;
bool ventanaC = false;
bool libro = false;
bool libroA = false;
bool libroC = false;
bool puerta = false;
bool puertaA = false;
bool puertaC = false;
bool abrir = false;
bool cerrar = false;
bool cajon = false;
bool reloj = false;
bool der = false;
bool izq = false;
bool caja = false;
bool arriba = false;
bool abajo = false;

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader lampshader( "Shaders/lamp.vs", "Shaders/lamp.frag" );
    
    // Load models
    Model Casa((char*)"Models/Casa/casa.obj");
    Model Puerta((char*)"Models/Casa/puertaCasa.obj");
    Model Repisa((char*)"Models/Repisa/repisa.obj");
    Model Libro((char*)"Models/Repisa/libro.obj");
    Model Cortina((char*)"Models/Ventana/cortina.obj");
    Model Ventana((char*)"Models/Ventana/ventana.obj");
    Model Ropero((char*)"Models/Ropero/ropero.obj");
    Model PuertaDer((char*)"Models/Ropero/puertaDer.obj");
    Model PuertaIzq((char*)"Models/Ropero/puertaIzq.obj");
    Model Tapa((char*)"Models/Ropero/tapa.obj");
    Model Comoda((char*)"Models/Comoda/comoda.obj");
    Model Cajon((char*)"Models/Comoda/cajon.obj");
    Model Reloj((char*)"Models/Comoda/reloj.obj");
    Model Buro((char*)"Models/Buro/buro.obj");
    Model Cama((char*)"Models/Cama/cama.obj");
    Model Refri((char*)"Models/Refrigerador/Refri.obj");
    Model Estufa((char*)"Models/Estufa/Estufa.obj");
    Model Campana((char*)"Models/Campana/Campana.obj");
    Model Micro((char*)"Models/Microondas/Microondas.obj");
    Model Mueble1((char*)"Models/Mueble/MuebleCentro.obj");
    Model Mueble2((char*)"Models/Mueble/MuebleIzq.obj");
    Model Mueble3((char*)"Models/Mueble/Mueble.obj");

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    GLfloat vertices[] =
    {
        // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 

    };

    GLuint indices[] =
    {  // Note that we start from 0!
        0,1,3,
        1,2,3

    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load textures
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  
    image = stbi_load("images/goku.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.698f, 0.921f, 0.909f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        //Dibujando Casa
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Casa.Draw(shader);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(-rotpuerta), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta.Draw(shader);

        //Dibujando habitacion
        //Dibujando comoda
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Comoda.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.25f, -0.36f, -5.45));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, movCa));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cajon.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.5f, -0.07f, -5.5f));
        model = glm::translate(model, glm::vec3(0.0f, movRe, 0.0f));
        model = glm::rotate(model, glm::radians(rotRe), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Reloj.Draw(shader);

        //Dibujando Buro con taza
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Buro.Draw(shader);

        //Dibujando Cama
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cama.Draw(shader);
        
        //Dibujando Repisa y libro
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Repisa.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.64f, 0.688f, -5.542f));
        model = glm::rotate(model, glm::radians(-rotlibro), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Libro.Draw(shader);

        //Dibujando ventana y cortina
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cortina.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.098f, 0.741f, -5.76f));
        model = glm::rotate(model, glm::radians(rotventana), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventana.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.33f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Cortina.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.0f, 0.741f, -5.76f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rotventana), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventana.Draw(shader);

        //Dibujando el ropero y puertas
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ropero.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.556f, 0.17f, -5.32f));
        model = glm::rotate(model, glm::radians(rotropero), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PuertaDer.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.24f, 0.146f, -5.3f));
        model = glm::rotate(model, glm::radians(-rotropero), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        PuertaIzq.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.88f, 1.258f, -5.509f));
        model = glm::translate(model, glm::vec3(0.0f, movTa, 0.0f));
        model = glm::rotate(model, glm::radians(rotTa), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Tapa.Draw(shader);

        //Dibujando cocina
        //Dibujando Refrigerador
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Refri.Draw(shader);

        //Dibujando Estufa
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Estufa.Draw(shader);

        //Dibujando Campana
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Campana.Draw(shader);

        //Dibujando Microondas
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Micro.Draw(shader);

        //Dibujando Muebles
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mueble1.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mueble2.Draw(shader);

        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Mueble3.Draw(shader);


        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        lampshader.Use();
        //glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
    if (ropero)
    {
        if (roperoA)
        {
            roperoC = false;
            if (rotropero <= 125.0f)
                rotropero += 0.5;
            else
                roperoC = true;
        }
        if (roperoC)
        {
            roperoA = false;
            if (rotropero >= 0.1f)
                rotropero -= 0.5;
        }
    }
    if (ventana)
    {
        if (ventanaA)
        {
            ventanaC = false;
            if (rotventana <= 130.0f)
                rotventana += 1.0;
            else
                ventanaC = true;
        }
        if (ventanaC)
        {
            ventanaA = false;
            if (rotventana >= 0.1f)
                rotventana -= 1.0;
        }
    }
    if (libro)
    {
        if (libroA)
        {
            libroC = false;
            if (rotlibro <= 35.0f)
                rotlibro += 0.5;
            else
                libroC = true;
        }
        if (libroC)
        {
            libroA = false;
            if (rotlibro >= 0.0f)
                rotlibro -= 0.5;
        }
    }
    if (puerta)
    {
        if (puertaA)
        {
            puertaC = false;
            if (rotpuerta <= 90.0f)
                rotpuerta += 1.0;
            else
                puertaC = true;
        }
        if (puertaC)
        {
            puertaA = false;
            if (rotpuerta >= 0.1f)
                rotpuerta -= 1.0;
        }
    }
    if (cajon)
    {
        if (abrir)
        {
            cerrar = false;
            if (movCa < 0.3f)
                movCa += 0.01;
            else
                cerrar = true;
        }
        if (cerrar)
        {
            abrir = false;
            if (movCa > 0.001)
              movCa -= 0.01;
            else
                cerrar = false;
        }
    }
    if (reloj)
    {
        movRe = 0.1f;
        if (der)
        {
            izq = false;
            if (rotRe > -45.0f)
                rotRe -= 8.0f;
            else
               izq = true;
        }
        if (izq)
        {
            der = false;
            if (rotRe < 45.0f)
                rotRe += 8.0f;
            else
                der = true;
        }
    }
    if (caja)
    {
       
        if (arriba)
        {
            abajo = false;
            movTa = 0.1f;
            if (rotTa < 180.0f)
                rotTa += 20.0f;
            else
                abajo = true;
        }
        if (abajo)
        {
            arriba = false;
            if (movTa > -0.21f)
                movTa -= 0.01f;
            else
                abajo = false;
                
        }
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
    if (keys[GLFW_KEY_P])
    {
        puertaA = true;
        puerta = !puerta;
    }
    if (keys[GLFW_KEY_L])
    {
        libroA = true;
        libro = !libro;
    }
    if (keys[GLFW_KEY_V])
    {
        ventanaA = true;
        ventana = !ventana;
    }
    if (keys[GLFW_KEY_K])
    {
        roperoA = true;
        ropero = !ropero;
    }
    if (keys[GLFW_KEY_N])
    {
        abrir = true;
        cajon = !cajon;
    }
    if (keys[GLFW_KEY_M])
    {
        der = true;
        reloj = !reloj;
        movRe = 0.0f;
        rotRe = 0.0f;
    }
    if (keys[GLFW_KEY_C])
    {
        arriba = true;
        caja = !caja;
        rotTa = 0.0f;
        movTa = 0.0;
     }
 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}