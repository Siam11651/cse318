#include "Window.hpp"
#include "HumanVsAiWindow.hpp"
#include "AiVsAiWindow.hpp"
#include "HumanVsAiGameWindow.hpp"
#include "AiVsAiGameWindow.hpp"

Window *currentWindow;
Window *mainWindow;
HumanVsAiWindow *humanVsAiWindow;
AiVsAiWindow *aiVsAiWindow;
HumanVsAiGameWindow *humanVsAiGameWindow;
AiVsAiGameWindow *aiVsAiGameWindow;

int main()
{
    mainWindow = new Window();
    humanVsAiWindow = new HumanVsAiWindow();
    aiVsAiWindow = new AiVsAiWindow();
    humanVsAiGameWindow = new HumanVsAiGameWindow();
    aiVsAiGameWindow = new AiVsAiGameWindow();
    currentWindow = mainWindow;

    while(currentWindow)
    {
        currentWindow->ProcessInput();
    }

    delete mainWindow;
    delete humanVsAiWindow;
    delete aiVsAiWindow;
    delete humanVsAiGameWindow;
    delete aiVsAiGameWindow;

    return 0;
}