#ifndef TIMER_SCORE_H_INCLUDED
#define TIMER_SCORE_H_INCLUDED

#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include "console.h"


class timer_score
{
private :
    int m_chrono, m_tdepart, m_tecoule;
    time_t m_t1, m_t2, m_tmp;
    bool m_timer, m_tdiff;
    double m_tdiffsec;


public :
    timer_score();
    timer_score(int tdepart, time_t t1);
    ~timer_score();

    int gettecoule() const;
    int getchrono() const;

    void settdiffsec();
    void settecoule();
    void setchrono();
    void setChronoPlus();
    void sett2();
    void settmp();


    void timer(Console* pConsole);
    /// void score
};

#endif // TIMER_SCORE_H_INCLUDED
