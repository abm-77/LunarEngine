#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
// Todo: Make more robust
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) Logger::GLClearError();\
    x;\
    ASSERT(Logger::GLLogCall())

class Logger
{

public:
    static void PrintMessage(const std::string& message, int messageIndentLevel = 0);

    static void PrintError(const std::string& error);

};
