/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/

#ifndef FUNCDEF_H
 #define FUNCDEF_H
#include "local_include.h"
                                    /*      Thread related funcs  */
void*   master_thread(pthread_t* thread_id);
                                    /* Comms functions  */    
void* 		linksmart(void *);
void        link_connect(int file);
                                    /* Config module    */
void 		get_whole_line(unsigned char ch,int j,unsigned char *temp);
unsigned char 	*Get_Mti_Bits_File(unsigned char *fieldname1,unsigned char *fieldname2,unsigned short int Mti,unsigned char which);
unsigned char	*get_init_value(char* fieldname,unsigned char*);
int 		copy_file_inarray(unsigned char * filename,  unsigned char * buffer);
void 		load_config(void);
                                    /* Display and log module */
void console_message(int,short,...);
void display_status(int ithread_id,int arg2,int imodem_state);
void init_win_params(WIN *p_win,int);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);
void print_curser(int y,int x,char* msg);
void print_leftwin(int y,int x,char* msg);
void print_rightwin(int y,int x,char* msg);

#endif // FUNCDEF_H 


