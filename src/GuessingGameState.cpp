#include "GuessingGame.h"
#include "GuessingGameState.h"

#include <memory>

void GuessingGameState::start(GuessingGame &game) {}
void GuessingGameState::finish(GuessingGame &game) {}

void GameStartingState::finish(GuessingGame &game)
{
    game.setState(std::make_unique<GameFinishingState>());
}

void GameFinishingState::start(GuessingGame &game)
{
    game.setState(std::make_unique<GameStartingState>());
}
