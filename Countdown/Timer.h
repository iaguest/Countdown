//
//  timer.h
//  countdown
//
//  Created by Ian Guest on 17/01/2020.
//  Copyright © 2020 Ian Guest. All rights reserved.
//

#ifndef timer_h
#define timer_h

#include <iostream>
#include <chrono>

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

#endif /* timer_h */
