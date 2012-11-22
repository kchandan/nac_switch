/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/
#include "master_thread.h"

/* chandan kumar 1sept06
 *      This function is to kill modem threads, which are not resetting the watchdog flag within
 *      WATCHDOG_TIMER seconds.
 */
void*
master_thread(pthread_t* thread_id)
{
    int             icount=0,
                    ithread_state=0,
                    temp=0;
    time_t          current_time=0;
    unsigned char  slog_buffer[32]={0}; 
    
    printf("I am master thread\n");
    
    do
    {
        for(;icount<10;icount++)
        {
            if(gwatch_dog[icount])
            {
                if(ithread_state ^ (temp|=1<< icount))
                {
                    ithread_state |= 1<< icount;
                }
                else
                {
                    #ifdef _DEBUG
                        fprintf(stderr,"Not Resetting the watchdog kill %d\n In 5 seconds",icount);
                    #endif
                    pthread_kill(thread_id[icount],SIGINT);
                    sprintf(slog_buffer,"Killed Thread::%d",icount);
                    console_message(LOG_MESSAGE,1,slog_buffer);
                }
            }
        }
        sleep(WATCHDOG_TIMER);        
    }while(1);
}
