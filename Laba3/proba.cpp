
#include <iostream>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
using namespace std;
//void signalhandler(int sign);
void signalhandler(int sign)
{
    cout<<"RABOTAI MATI VASHY"<<endl;
}
  int main()
  {
    struct itimerval nval, oval;
    signal(SIGALRM,signalhandler);
    nval.it_interval.tv_sec  = 2;
    nval.it_value.tv_sec  = 2;
    //raise(SIGALRM);
    setitimer (ITIMER_REAL, &nval, &oval);
    /* Запускаем таймер */
      return 0;
  }