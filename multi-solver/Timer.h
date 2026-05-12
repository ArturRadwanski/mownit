//
// Created by valleron on 5/12/26.
//

#ifndef MULTI_SOLVER_TIMER_H
#define MULTI_SOLVER_TIMER_H


#include <chrono> // for std::chrono functions

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
    void reset()
    {
        m_beg = Clock::now();
    }

    [[nodiscard]] double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};


#endif //MULTI_SOLVER_TIMER_H