/* Initial creation Chandan Kumar 2007 */

#include "sys_include.h"
#include "local_include.h"
#include "main.h"

#define MODEM_INIT_CMD  "ats0=1\r\nat+ms=v32,0,4800,9600,4800,9600"

int
main(int argc, char* argv[])
{
    int  			thread_return[10],
                    retval=0; 
    short           icount;
    int             hsf[8]={0};
    unsigned char  modem_response[64]={0};
    char            *check;    
    char            *modem_init_string=MODEM_INIT_CMD;
    pid_t           new_process;
    
    load_config();
	//init_thread_data();
    glog_filp=fopen(LOG_FILE,"a");
    if(!glog_filp)
    {
        fprintf(stderr,"Cant open log file");
        perror("");
        exit(FILE_OPEN_ERROR);
    }
    /*          Opening all files       */
    for(icount=0;icount <1;icount++)
    {
        hsf[icount]=open(gmodem_name[icount], O_RDWR | O_NOCTTY | O_NDELAY);
        if(hsf[icount]<0)
        {
            fprintf(stderr,"Error opening::%s",gmodem_name[icount]);
        }
        write(hsf[icount],modem_init_string,strlen(modem_init_string));
        usleep(10);
        read(hsf[icount],modem_response,sizeof(modem_response));
        if(strstr(modem_response,"OK")==NULL)
        {
            fprintf(stderr,"No response from modem::%s",gmodem_name[icount]);
        }
    }
    
    for (;;)
    {
        for(icount=0;icount <8;icount++)
        {
            memclr(modem_response,sizeof(modem_response));
            retval=read(hsf[0],modem_response,sizeof(modem_response));
            if(retval>0)
            {
                check=strstr(modem_response,"RING");
                if(check!=NULL) // Got RING on modem
                {
                    if(fork()==0)
                    {/* Create a new process to handle the incomming request */
                        link_connect(hsf[icount]);
                    }
                    else
                        continue;
                }
            }
        }
    }
    return 0;
}
