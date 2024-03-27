#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

//My favorite equation that I have encountered during Aerospace so far is the Archimedes spiral. I have chose to plot
//this as my favorite equation using OpenGL library.

const float a = 0.1f; // Initial distance from the origin
const float b = 0.1f; // Rate of expansion

int main() {
  if ( !glfwInit() ) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow( 800, 800, "Archimedes Spiral using OpenGL with GLEW and GLFW", NULL, NULL );
  if ( !window ) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent( window );

  if ( glewInit() != GLEW_OK ) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

  while ( !glfwWindowShouldClose( window ) ) {
    glClear( GL_COLOR_BUFFER_BIT );

    glBegin( GL_LINES );
    // Draw X and Y axis
    glColor3f( 1.0, 1.0, 1.0 );
    glVertex2f( -1.0, 0.0 );
    glVertex2f( 1.0, 0.0 );
    glVertex2f( 0.0, 1.0 );
    glVertex2f( 0.0, -1.0 );

    //Plot archimedes spiral equation
    glColor3f(0.0, 1.0, 0.0);
    for (float theta = 0; theta < 10 * 3.14159; theta += 0.1) {
        float r = a + b * theta;
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glfwSwapBuffers( window );
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}