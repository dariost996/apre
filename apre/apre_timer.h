#if defined _APRE_H_
#ifndef _APRE_TIMER_H_
#define _APRE_TIMER_H_

/**
    A class for timing
*/

class apreTimer
{
    protected:
    std::chrono::high_resolution_clock::time_point __ap_start;
    public:
    void start(void);                               ///< Start the timer
    void restart(void);                             ///< An alias of start()
    bool isPassedMilliSecPeriod(int64_t checkTime); ///< Check if a period of milliseconds is passed
    bool isPassedMicroSecPeriod(int64_t checkTime); ///< Check if a period of microseconds is passed
    int64_t getMilliSecPeriod();                    ///< Get milliseconds passed
    int64_t getMicroSecPeriod();                    ///< Get microseconds passed
    apreTimer();                                    ///< The constructor (calls start())
};

apreTimer::apreTimer()
{
    this->start();
}

void apreTimer::start(void)
{
    __ap_start=std::chrono::high_resolution_clock::now();
    return;
}

void apreTimer::restart(void)
{
    this->start();
    return;
}

bool apreTimer::isPassedMilliSecPeriod(int64_t checkTime)
{
    std::chrono::high_resolution_clock::time_point __ap_end=std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long int, std::milli> __timer = std::chrono::duration_cast<std::chrono::duration<long long int, std::milli>>(__ap_end-__ap_start);
    int64_t __tO=__timer.count();
    if(__tO<checkTime) return false;
    else return true;
}

bool apreTimer::isPassedMicroSecPeriod(int64_t checkTime)
{
    std::chrono::high_resolution_clock::time_point __ap_end=std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long int, std::micro> __timer = std::chrono::duration_cast<std::chrono::duration<long long int, std::micro>>(__ap_end-__ap_start);
    int64_t __tO=__timer.count();
    if(__tO<checkTime) return false;
    else return true;
}

int64_t apreTimer::getMicroSecPeriod()
{
    std::chrono::high_resolution_clock::time_point __ap_end=std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long int, std::micro> __timer = std::chrono::duration_cast<std::chrono::duration<long long int, std::micro>>(__ap_end-__ap_start);
    int64_t __tO=__timer.count();
    return __tO;
}

int64_t apreTimer::getMilliSecPeriod()
{
    std::chrono::high_resolution_clock::time_point __ap_end=std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long int, std::milli> __timer = std::chrono::duration_cast<std::chrono::duration<long long int, std::milli>>(__ap_end-__ap_start);
    int64_t __tO=__timer.count();
    return __tO;
}

#endif
#endif
