#include "GuessingGame.h"
#include <iostream>

int main()
{
    auto range = Random::Instance().get_range(1, 10, 5);

    for(const auto item: range) {
        std::cout<<item;
    }

    std::cout<<"\n";

    int choice;
    std::cout << "Select game type:\n1) IntGuessingGame\n2) FloatGuessingGame\nSelect: ";
    std::cin >> choice;
    std::cin.get();

    std::unique_ptr<GuessingGame> guessingGame = guessingGameFactory(choice == 1 ? GameType::INT : GameType::FLOAT);
    while (!guessingGame->finished())
    {
        guessingGame->handleQuestion();

        std::string input;
        std::getline(std::cin, input);

        guessingGame->handleInput(input);
    }
}