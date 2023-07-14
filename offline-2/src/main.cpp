#include "Window.hpp"
#include "HumanVsAiWindow.hpp"
#include "AiVsAiWindow.hpp"
#include "HumanVsHumanWindow.hpp"
#include "HumanVsAiGameWindow.hpp"
#include "AiVsAiGameWindow.hpp"
#include "HumanVsHumanGameWindow.hpp"

Window *currentWindow;
Window *mainWindow;
HumanVsAiWindow *humanVsAiWindow;
AiVsAiWindow *aiVsAiWindow;
HumanVsHumanWindow *humanVsHumanWindow;
HumanVsAiGameWindow *humanVsAiGameWindow;
AiVsAiGameWindow *aiVsAiGameWindow;
HumanVsHumanGameWindow *humanVsHumanGameWindow;

int main()
{
    mainWindow = new Window();
    humanVsAiWindow = new HumanVsAiWindow();
    aiVsAiWindow = new AiVsAiWindow();
    humanVsHumanWindow = new HumanVsHumanWindow();
    humanVsAiGameWindow = new HumanVsAiGameWindow();
    aiVsAiGameWindow = new AiVsAiGameWindow();
    humanVsHumanGameWindow = new HumanVsHumanGameWindow();
    currentWindow = mainWindow;

    while(currentWindow)
    {
        currentWindow->ProcessInput();
    }

    delete mainWindow;
    delete humanVsAiWindow;
    delete aiVsAiWindow;
    delete humanVsHumanWindow;
    delete humanVsAiGameWindow;
    delete aiVsAiGameWindow;
    delete humanVsHumanGameWindow;

    return 0;
}