#include "GuessingGame.h"
#include <iostream>

int main()
{
    std::unique_ptr<GuessingGame> guessingGame = guessingGameFactory(GameType::FLOAT);

    while (!guessingGame->finished())
    {
        guessingGame->handleQuestion();

        std::string input;
        std::getline(std::cin, input);

        guessingGame->handleInput(input);
    }
}