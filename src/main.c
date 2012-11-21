#include "sys_include.h"
#include "local_include.h"
#include "main.h"

void* 
test(void* arg)
{
	printf("%s\n\n",arg);
	sleep(10);
	while(1);
	fprintf(stderr,"It should never reach here\n");
}

int
main(int argc, char* argv[])
{
	
    int			    num[10]={0,1,2,3,4,5,6,7,8,9};
    int  			thread_return[10],
                    retval=0; 
    short           icount;
    int             hsf[8]={0};
    
    unsigned char  modem_response[64]={0};
    char            *check;    
    char            *modem_init_string="ats0=1\r\nat+ms=v32,0,4800,9600,4800,9600";
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
    #if 0
    for(icount=0;icount <8;icount++)
    {/* Converting each file to be non-blocking type*/
        retval=fcntl(hsf[icount],O_RDWR | O_NOCTTY | O_NDELAY);
        if(retval<0)
        {
            perror("FCNTL:");
        }
    }
    #endif
    do
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
    }while(1);
    
    
    return 0;
}
	
		
