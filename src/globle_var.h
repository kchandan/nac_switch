/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/
#ifndef GLOBLE_VAR_H
 #define GLOBLE_VAR_H
#include "sys_include.h"
static unsigned short	    size_of_file=1;
unsigned short		        gtimer,
            			    gtime_out;
short			            gserver_port[8];

unsigned char		        global_file_buf[10240];
unsigned char		        ginit_string[512];
unsigned char		        ghost_name[10][128];
unsigned char		        gmodem_name[10][32];
unsigned char		        gwatch_dog[10];

FILE                        *glog_filp;


typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

static char gdisplay_msg[][64]=
{
	"Connected to Host",
	"Link Layer conneted",
	"Sending Packets to host",
	"usage: hostname  device_name server_port",
	"NO CARRIER",
	"No line connected to Modem",
    "Cant open FILE :",
};

enum CONSOLE_MSG
{
	DEVELOPER_TESTING=0,
	FINAL_DISPLAY,
	USER_DEBUGGING,
	PROTOCOL_MSG,
	ONLINE_DATA,
	ONLINE_STATUS,
    LOG_MESSAGE
};

enum MODEM_STATUS
{
    MODEM_NOT_RESPONDING,
    MODEM_RESPONDING,
    MODEM_LINE_NOTCONNECTED    
};
enum MESSAGE_INDEX
{
	CONNECT_HOST,
	LINK_LAYER_CONNECT,
	SENDING_PACKET_HOST,
	USAGE_HOSTNAME,
	NO_CARRIER,
	NO_LINE_CONNECTED,
    CANT_OPEN_FILE
};

enum RETURN_STATUS
{
    FILE_OPEN_ERROR=-1,
};
#endif // ifndef GLOBAL_VAR_H
