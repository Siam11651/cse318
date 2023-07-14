#include "HumanVsHumanGameWindow.hpp"
#include "MancalaState.hpp"
#include "HumanVsHumanStartState.hpp"

extern Window *currentWindow;

HumanVsHumanGameWindow::HumanVsHumanGameWindow() : Window()
{
    MancalaState *mancalaState = new MancalaState();
    state = new HumanVsHumanStartState(mancalaState);
}

void HumanVsHumanGameWindow::ProcessInput()
{
    while(state)
    {
        State *toDelete = state;
        state = state->Execute();

        delete toDelete;
    }

    currentWindow = nullptr;
}