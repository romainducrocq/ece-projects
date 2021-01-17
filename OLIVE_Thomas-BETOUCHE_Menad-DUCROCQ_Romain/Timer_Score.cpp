#include "Timer_Score.h"
#include <ctime>

timer_score::timer_score()
: m_chrono(0), m_tdepart(60), m_t1(time(NULL)), m_tdiff(true), m_tdiffsec(0)
{
}

timer_score::timer_score(int tdepart, time_t t1)
: m_chrono(0), m_tdepart(tdepart), m_t1(t1), m_tdiff(true), m_tdiffsec(0)
{
}

timer_score::~timer_score()
{

}

///GETTERS
int timer_score::gettecoule() const
{
    return m_tecoule;
}
int timer_score::getchrono() const
{
    return m_chrono;
}

///SETTERS
void timer_score::settdiffsec()
{
    m_tdiffsec=difftime(m_t2, m_t1);
}

void timer_score::settecoule()
{
    m_tecoule=static_cast<int>(m_tdiffsec);
}

void timer_score::setchrono()
{
    m_chrono=m_tdepart-m_tecoule;
}

void timer_score::setChronoPlus ()
{
    m_tdepart=m_tdepart+11;
}

void timer_score::sett2()
{
    m_t2=time(NULL);
}

void timer_score::settmp()
{
    m_tmp=m_t2;
}

void timer_score::timer(Console* pConsole)
{
        sett2();
        if (m_tdiff==false)
        {
            if(m_t2>m_tmp)
                m_tdiff=true;
        }
        else
        {
        settdiffsec();
        settecoule();
        setchrono();
         pConsole->gotoLigCol(6,62);
            if(getchrono()<10)
                std::cout << "Time left : 0" << getchrono() << std::endl;
            else
                std::cout << "Time left : " << getchrono() << std::endl;
        settmp();
        m_tdiff=false;
        }
}
