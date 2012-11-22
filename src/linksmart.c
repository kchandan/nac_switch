/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/
#include "globle_var.h"
#include "link_macro.h"
#include "display_mod.h"
#define PORT 2000  

#define OUTBUFF 4096 /* max number of bytes we can get at once */
#define INBUFF  4096
#define WAIT_MODEM_RESPONSE 1



void
link_connect(int file)
{
    struct hostent 		*he;
    struct sockaddr_in 	    	their_addr; 
    fd_set 			rfds;
    short                       server_port;
    int                         sockfd;
    struct timeval 		tv;
    
    unsigned char              	read_buffer[2048],
                                write_buffer[2048];
    char                        *check,
                                link_layer_connect=0;                            
    int                         numbytes=0,retval=0;
    
    
    FD_ZERO(&rfds);
    FD_SET(file, &rfds);
    tv.tv_sec = 300;
    tv.tv_usec = 0;
    
    retval = select(file+1, &rfds, NULL,    NULL, &tv);
    if(retval)
    {
        fprintf(stderr,"Data from MODEM\n");
    }
    else
    {
        fprintf(stderr,"Time out\n");
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }        
    fprintf(stderr,"Connect\n");
    their_addr.sin_family = AF_INET;      /* host byte order */
    their_addr.sin_port = htons(server_port);    /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */
    retval=connect(sockfd, (struct sockaddr *)&their_addr, \
                          sizeof(struct sockaddr)) ;
    if(retval==-1)	
    {
        perror("Unable to connect host\n" \
            "Please check IP addr");
        PRINT_MACRO(host_name);
        
    }
    //console_message(FINAL_DISPLAY,0,gdisplay_msg[CONNECT_HOST]);
    do
    {
        bzero(read_buffer, sizeof(read_buffer));
        bzero(write_buffer, sizeof(write_buffer));
        numbytes=read(file, read_buffer, sizeof(read_buffer));
        if(numbytes > 0)
        {
            check=NULL;
            check=strstr(read_buffer,"NO CARRIER");
            if(check!=NULL)
            {
                //console_message(USER_DEBUGGING,0,gdisplay_msg[NO_CARRIER]);
                break;
            }
            check=strstr(read_buffer,"CONNECT");
            if(check!=NULL)
            {
                //console_message(FINAL_DISPLAY,2,gdisplay_msg[LINK_LAYER_CONNECT],gdisplay_msg[SENDING_PACKET_HOST]);
                link_layer_connect=1;
            }	
            fprintf(stderr, "--> %s\n",read_buffer);
            if(link_layer_connect)	/* if connected then only send the packet */
            {
                PRINT_MACRO("\nAbout to send\n");
                send(sockfd, read_buffer, numbytes, MSG_DONTWAIT);
            }
        }
        numbytes=recv(sockfd,write_buffer,2048, MSG_DONTWAIT);
        if(numbytes>0)
        {
            write(file,write_buffer,numbytes);
        }
        else
        {
            if(numbytes != EAGAIN && numbytes != -1)
            {
                fprintf(stderr, "ERR->%d\n", numbytes);
                perror("recv");
                break;
            }
        }
    sleep(1);
   } while(1);/* while(1) inner*/

    bzero(write_buffer,sizeof(write_buffer));	
    close(sockfd);
    return ;
}
