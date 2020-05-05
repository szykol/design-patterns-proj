#include "GuessingGame.h"
#include <iostream>

int main()
{
    std::unique_ptr<GuessingGame> guessingGame = guessingGameFactory(GameType::INT);

    guessingGame->handleQuestion();
    guessingGame->handleInput(std::string("eldo"));
}