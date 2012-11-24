/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/
#include "display_mod.h"

/*  chandan kumar 31/08/06
 *      This module is all about to display all the messages(log,debug and status messages)
 */
void
console_message(int debug_level,short imsg_count,...)
{

	va_list 		    arguments;
	int			        icount,
                        ival=0;
    short               ithread_id=0,
                        iline_state=0,
                        imodem_state=0;
	unsigned char		*pstring;
    FILE                *filp;
    time_t              current_time=0;
    
	va_start(arguments,imsg_count);

	switch(debug_level)
	{

#ifdef DEVELOPMENT
	case DEVELOPER_TESTING:
        fprintf(stderr,"\n Test Printing block\n");
		for(icount=0;icount <=imsg_count;icount++)
		{
			pstring=va_arg(arguments,unsigned char*);
			print_leftwin()
			fprintf(stderr,"\n");
		}
        fprintf(stderr,"End block\n");
		break;

#endif // DEVELOPMENT
	case FINAL_DISPLAY:
		for(icount=0;icount <=imsg_count;icount++)
		{
			pstring=va_arg(arguments,unsigned char*);
			fprintf(stderr,pstring);
			fprintf(stderr,"\n");
		}
		break;
	case USER_DEBUGGING:
		break;
	case PROTOCOL_MSG:
		break;
	case ONLINE_DATA:
		break;
	case ONLINE_STATUS:
        ithread_id=va_arg(arguments,int); // Thread number
	/* This msg type will tell wheather only modem is not responding or only line is not there */
        ival=va_arg(arguments,int); // Msg number, 
        imodem_state=va_arg(arguments,int); // modem/line state
        //display_status(ithread_id,ival,imodem_state); 
		break;
    case LOG_MESSAGE:
        for(icount=0;icount <=imsg_count;icount++)
		{
			pstring=va_arg(arguments,unsigned char*);
			fprintf(glog_filp,pstring);
			
		}
        time(&current_time);
        fprintf(glog_filp,"%s\n",ctime(&current_time));
        break;
	default:
		break;
	}
	return;
}


inline void 
display_status(int ithread_id,int arg2,int imodem_state)
{
    unsigned char       msg[64]={0};
    static char		    cprevious_error_flag; 
    move(MODEM_DISPLAY_Y,MODEM_DISPLAY_Y);
    attron(A_BOLD);
    attron(A_STANDOUT); 
    printw("Modem number        Line status     Modem status");
    move(MODEM_DISPLAY_Y+ithread_id+2,MODEM_DISPLAY_X);
    sprintf(msg,"%2d                OK              OK",ithread_id);
    printw(msg);
    if(imodem_state==MODEM_NOT_RESPONDING)
    {
        memclr(msg,sizeof(msg));
    	move(MODEM_DISPLAY_Y+ithread_id+2,MODEM_DISPLAY_X);
        sprintf(msg,"%2d             OK             KO",ithread_id);
        printw(msg);
        refresh();
    }
    if(imodem_state==MODEM_LINE_NOTCONNECTED)
    {
    	move(MODEM_DISPLAY_Y+ithread_id+2,MODEM_DISPLAY_X);
        memclr(msg,sizeof(msg));
        sprintf(msg,"%2d              KO            OK",ithread_id);
        printw(msg);
        refresh();
    }
    if(imodem_state==MODEM_LINE_NOTCONNECTED)
    {
    	move(MODEM_DISPLAY_Y+ithread_id+2,MODEM_DISPLAY_X);
        memclr(msg,sizeof(msg));
        sprintf(msg,"%2d              KO            OK",ithread_id);
        printw(msg);
        refresh();
    
    }
    return;
}

