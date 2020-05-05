#pragma once

#include <iostream>
#include <memory>

enum class GameType
{
    INT = 0,
    FLOAT
};

class GuessingGame
{
public:
    virtual void handleQuestion() = 0;
    virtual void handleInput(const std::string &input) = 0;
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
    }
};

std::unique_ptr<GuessingGame> guessingGameFactory(GameType gameType)
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