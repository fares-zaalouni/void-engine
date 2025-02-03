#include "pch.h"
#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window)
{
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetWindowUserPointer(window, this);
    std::fill(std::begin(_keyStates), std::end(_keyStates), GLFW_RELEASE);
    std::fill(std::begin(_mouseButtonStates), std::end(_mouseButtonStates), false);
    _mouseX = 0;
    _mouseY = 0;
}
void InputManager::handleKeyPress(int key, int action)
{
    _keyStates[key] = action;
}

void InputManager::handleMouseButton(int button, int action) {
    _mouseButtonStates[button] = (action == GLFW_PRESS);
}

void InputManager::handleCursorPos(double xpos, double ypos) {
    _mouseX = xpos;
    _mouseY = ypos;
}

int InputManager::IsKeyPressed(int key)
{
    return _keyStates[key];
}

bool InputManager::IsMousePressed(int button)
{
    return _mouseButtonStates[button];
}

double InputManager::GetMouseX()
{
    return _mouseX;
}

double InputManager::GetMouseY()
{
    return _mouseY;
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    input->handleKeyPress(key, action);
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    input->handleMouseButton(button, action);
}

void InputManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    input->handleCursorPos(xpos, ypos);
}

