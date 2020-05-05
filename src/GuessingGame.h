#pragma once

#include <iostream>
#include <memory>

#include "GuessingGameState.h"

enum class GameType
{
    INT = 0,
    FLOAT
};

class GuessingGame
{
protected:
    std::unique_ptr<GuessingGameState> m_state;

public:
    virtual void handleQuestion() = 0;
    virtual void handleInput(const std::string &input) = 0;

    void setState(std::unique_ptr<GuessingGameState> state)
    {
        m_state = std::move(state);
    }

    bool finished() { return m_state->m_finished; }

    GuessingGame()
    {
        m_state = std::make_unique<GameStartingState>();
        m_state->start(*this);
    }

    void finish()
    {
        m_state->finish(*this);
    }
};

class IntGuessingGame : public GuessingGame
{

public:
    virtual void handleQuestion()
    {
        std::cout << "Asking a question from IntGuessingGame\n";
    }
    virtual void handleInput(const std::string &input)
    {
        std::cout << "Handling input " << input << " from IntGuessingGame\n";
        finish();
    }
};

class FloatGuessingGame : public GuessingGame
{
public:
    virtual void handleQuestion()
    {
        std::cout << "Asking a question from FloatGuessingGame\n";
    }
    virtual void handleInput(const std::string &input)
    {
        std::cout << "Handling input " << input << " from FloatGuessingGame\n";
        finish();
    }
};

inline std::unique_ptr<GuessingGame> guessingGameFactory(GameType gameType)
{
    if (gameType == GameType::INT)
    {
        auto ret = std::make_unique<IntGuessingGame>();
        return ret;
    }
    else
    {
        auto ret = std::make_unique<FloatGuessingGame>();
        return ret;
    }
}