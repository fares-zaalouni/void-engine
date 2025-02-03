#include <GLFW/glfw3.h>
#include <iostream>
class InputManager {
public:
    InputManager(GLFWwindow* window);
    void handleKeyPress(int key, int action);
    void handleMouseButton(int button, int action);
    void handleCursorPos(double xpos, double ypos);
    
    int IsKeyPressed(int key);
    bool IsMousePressed(int button);
    double GetMouseX();
    double GetMouseY();
private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    int _keyStates[GLFW_KEY_LAST + 1];
    bool _mouseButtonStates[GLFW_MOUSE_BUTTON_LAST + 1];
    double _mouseX, _mouseY;
};
