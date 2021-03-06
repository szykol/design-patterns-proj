#pragma once

#include <iostream>
#include <memory>

#include "GuessingGameState.h"
#include "Random.h"

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
    const int guess_number = Random::Instance().get<int>(1, 100);

public:
    virtual void handleQuestion()
    {
        std::cout << "Guess a number between 1 and 100\n";
    }
    virtual void handleInput(const std::string &input)
    {
        try
        {
            auto inputInt = std::stoi(input);

            if (inputInt > guess_number)
            {
                std::cout << "Lower!\n";
            }
            else if (inputInt < guess_number)
            {
                std::cout << "Higher!\n";
            }
            else
            {
                std::cout << "Correct!\n";
                finish();
            }
        }
        catch (std::invalid_argument const &e)
        {
            std::cout << "Please provide a number" << '\n';
        }
        catch (std::out_of_range const &e)
        {
            std::cout << "Please provide a number that fits into " << sizeof(int) << "bytes" << '\n';
        }
    }
};

class FloatGuessingGame : public GuessingGame
{
    const float guess_number = Random::Instance().get<float>(1.0, 10.0);

public:
    virtual void handleQuestion()
    {
        std::cout << "Guess a float number between 1.0 and 10.0\n";
    }
    virtual void handleInput(const std::string &input)
    {
        try
        {
            auto inputFloat = std::stof(input);
            auto miss = std::abs(inputFloat - guess_number);
            if (miss > 0.15)
                if (inputFloat > guess_number)
                {
                    std::cout << "Lower!\n";
                }
                else
                {
                    std::cout << "Higher!\n";
                }
            else
            {
                std::cout << "Correct!\nYou've missed the number(" << guess_number << ") by " << miss << std::endl;
                finish();
            }
        }
        catch (std::invalid_argument const &e)
        {
            std::cout << "Please provide a number" << '\n';
        }
        catch (std::out_of_range const &e)
        {
            std::cout << "Please provide a number that fits into " << sizeof(float) << "bytes" << '\n';
        }
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