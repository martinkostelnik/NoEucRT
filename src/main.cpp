#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        printf("ERROR");
    }
    else
    {
        printf("SUCCESS");
    }

    glfwTerminate();
    return 0;
}
