#include "HumanVsAiGameWindow.hpp"
#include "MancalaState.hpp"
#include "HumanVsAiStartState.hpp"

extern Window *currentWindow;

HumanVsAiGameWindow::HumanVsAiGameWindow() : Window()
{
    MancalaState *mancalaState = new MancalaState();
    state = new HumanVsAiStartState(mancalaState);
}

void HumanVsAiGameWindow::ProcessInput()
{
    while(state)
    {
        State *toDelete = state;
        state = state->Execute();

        delete toDelete;
    }

    currentWindow = nullptr;
}