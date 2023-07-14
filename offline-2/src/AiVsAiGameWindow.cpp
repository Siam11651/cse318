#include "AiVsAiGameWindow.hpp"
#include "AiVsAiStartState.hpp"

extern Window *currentWindow;

AiVsAiGameWindow::AiVsAiGameWindow() : Window()
{
    MancalaState *mancalaState = new MancalaState();
    state = new AiVsAiStartState(mancalaState);
}

void AiVsAiGameWindow::ProcessInput()
{
    while(state)
    {
        State *toDelete = state;
        state = state->Execute();

        delete toDelete;
    }

    currentWindow = nullptr;
}