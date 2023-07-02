#include "HumanVsAiGameWindow.hpp"
#include "MancalaState.hpp"
#include "HumanVsAiStartState.hpp"

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
}