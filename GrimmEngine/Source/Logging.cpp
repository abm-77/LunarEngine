#include "System/Logging.h"

void Logger::PrintMessage(const std::string& message, int messageIndentLevel)
{
    std::string indent = "";

    for (int i = 0; i < messageIndentLevel; i++)
        indent += "\t";

    std::cout << std::endl << indent << "Message: " << message << std::endl;
}

void Logger::PrintError(const std::string& error)
{
    std::cout << std::endl << "Error: %s" << error << std::endl;
}
