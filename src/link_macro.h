/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/
#ifndef LINK_MACRO_H
 #define LINK_MARCO_H

#ifdef DEBUG
 #define PRINT_MACRO(str) \
	fprintf(stderr,str);
 #else
    #define PRINT_MACRO(str)
#endif // #ifdef DEBUG
#define CONFIG_FILE	"nac_config.ini"
#define LOG_FILE    "log_file"
#define MODEM_DISPLAY_X	20
#define MODEM_DISPLAY_Y	20
#define memclr(arg1,arg2) memset(arg1,0x00,arg2)
#define WATCHDOG_TIMER 5
#endif // ifndef LINK_MACRO_H
