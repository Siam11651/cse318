#include "Window.hpp"
#include "HumanVsAiWindow.hpp"
#include "AiVsAiWindow.hpp"
#include "HumanVsHumanWindow.hpp"
#include "HumanVsAiGameWindow.hpp"
#include "AiVsAiGameWindow.hpp"
#include "HumanVsHumanGameWindow.hpp"

int main()
{
    Window *currentWindow = new Window();

    while(currentWindow)
    {
        Window *toDelete = currentWindow;

        currentWindow = currentWindow->ProcessInput();

        delete toDelete;
    }

    return 0;
}