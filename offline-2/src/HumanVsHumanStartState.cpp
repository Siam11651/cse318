#include <iostream>
#include "HumanVsHumanStartState.hpp"
#include "HumanState.hpp"

HumanVsHumanStartState::HumanVsHumanStartState(MancalaState *mancalaState) : State(mancalaState)
{
    
}

State *HumanVsHumanStartState::Execute()
{
    std::cout << "Shall black start first? [y/n]" << std::endl;

    char c;

    std::cin >> c;

    if(c == 'y' || c == 'Y')
    {
        return new HumanState(true, Player::BLACK, mancalaState);
    }
    else if(c == 'n' || c == 'N')
    {
        return new HumanState(true, Player::WHITE, mancalaState);
    }
    else
    {
        return new HumanVsHumanStartState(mancalaState);
    }
}