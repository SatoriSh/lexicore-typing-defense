#pragma once

#include <SFML/Graphics.hpp>

class Timer
{
public:
    sf::Clock& getClock() { return clock; };
    void setDuration(sf::Time t) { duration = t; };
    sf::Time getDuration() { return duration; };
    sf::Time getLeftTime() { return duration - clock.getElapsedTime(); };

    bool autoRestart = false;

    bool timeout()
    {
        if (duration.asMilliseconds() <= 0)
            return false;

        if (clock.getElapsedTime() >= duration)
        {
            if (autoRestart)
                clock.restart();

            return true;
        }

        return false;
    }
private:
    sf::Clock clock;
    sf::Time duration;
};
