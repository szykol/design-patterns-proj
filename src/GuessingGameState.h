#pragma once

class GuessingGame;

class GuessingGameState
{
public:
    bool m_finished;

public:
    GuessingGameState()
    {
        m_finished = false;
    }
    virtual ~GuessingGameState() {}

    virtual void start(GuessingGame &game) = 0;
    virtual void finish(GuessingGame &game) = 0;
};

class GameStartingState : public GuessingGameState
{
    virtual void start(GuessingGame &game)
    {
        m_finished = false;
    }
    virtual void finish(GuessingGame &game);

public:
    virtual ~GameStartingState() {}
};

class GameFinishingState : public GuessingGameState
{
    virtual void start(GuessingGame &game);

    virtual void finish(GuessingGame &game)
    {
        m_finished = true;
    }

public:
    virtual ~GameFinishingState() {}
    GameFinishingState()
    {
        m_finished = true;
    }
};