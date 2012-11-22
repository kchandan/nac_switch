/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/
#include "globle_var.h"
#include "load_config.h"	
#include "link_macro.h"


/*
 * Input : A whole line and fieldname from file.
 *
 * Get the value correspoding to that fieldname from file.
 *
 * Output : value.
 * Owner  : Sujit Jadhav
 * Editor : Chandan kumar
 */


unsigned char*
get_init_value(char* fieldname,unsigned char* conf_buffer)
	
{
	FILE *fp;
	char ch;
	int i;
	char *buf;
	char *temp;
	int j=0;
	unsigned char	*value;	
	
	if(size_of_file == 0 || strlen(conf_buffer)==0 ){
		fprintf(stderr,"File not populated in to array so returning \n");
		memcpy(value,"\00",1);
		return value;
	}
	memcpy(&ch,conf_buffer+j,1);
	j++;

//	fprintf(stderr,"%c",ch);
	while(j<size_of_file)
	{
		value=calloc(1, 500);
		buf=calloc(1, 500);
		temp=calloc(1, 500);

		if(ch=='['){
		
			do
			{
				memcpy(&ch,conf_buffer+j,1);
				j++;
#ifdef PRINT_DEBUG
				fprintf(stderr,"%c",ch);
#endif
			}while(ch!='\n');
		
			memcpy(&ch,conf_buffer+j,1);
			j++;
#ifdef PRINT_DEBUG
			fprintf(stderr,"%c",ch);
#endif
			continue;
		}
	
		i=0;
		for(;((ch==' ') || (ch=='\t') || (ch=='\n'));)
		{
			memcpy(&ch,conf_buffer+j,1);
			j++;
#ifdef PRINT_DEBUG
			fprintf(stderr,"%c",ch);
#endif
		}

		while(ch!='\n')
		{
			temp[i]=ch;
			i++;
			memcpy(&ch,conf_buffer+j,1);
			j++;
#ifdef PRINT_DEBUG
			fprintf(stderr,"%c",ch);
#endif
			
		}
		
		sscanf(temp,"%[^ =]",buf);
		
		if(strcmp(buf,fieldname)==0){
			value=strchr(temp,'=');
			value++;
	
			for(;*value==' ';)
				value++;
			
			sscanf(value,"%[^'#']",value);
#ifdef PRINT_DEBUG
			printf("\n%s\n",value);
#endif
			break;
			
			
#ifdef PRINT_DEBUG	
			printf("\n%s\n",value);
#endif
		}
		else {
			memcpy(&ch,conf_buffer+j,1);
			j++;
#ifdef PRINT_DEBUG	
			fprintf(stderr,"%c",ch);
#endif
		}
		
		free(value);
		free(buf);
		free(temp);
		
	}
	
	if(j>=size_of_file)
		memcpy(value,"\00",1);

#ifdef PRINT_DEBUG	
	fprintf(stderr,"\nj=%d\n",j);
#endif
	return value;
}



int 
copy_file_inarray(unsigned char * filename,  unsigned char * buffer)
{
	FILE * fp;
	int no=0;
	int i=0;
	char ch=0;
	
	fp=fopen(filename,"r");
	
	if(fp==NULL){
		fprintf(stderr,"error opening");
		return 0;
	}
	
	while(1)
	{

		
		ch=fgetc(fp);
		
		if(ch==EOF)
			break; 
		
		memcpy(buffer+i,&ch,1);

#ifdef PRINT_DEBUG
		fprintf(stderr,"%c",ch);
#endif
		no++;
		i++;
		
		
	}

#ifdef PRINT_DEBUG
	fprintf(stderr,"no=%d\n",no);

	for(i=0;i<no;i++)
	fprintf(stderr,"%c",buffer[i]);
#endif
	return no;
}

void 
load_config(void)
{
	unsigned char		temp_buf[2048],*buf_ptr;
	int			        file_descriptor;
	FILE			    *file_ptr;
	
	file_descriptor=open(CONFIG_FILE,O_RDWR);	
	if(file_descriptor < 0)
	{
		perror("nac_config.ini:");
	}
	file_ptr=fdopen(file_descriptor,"r");
	if(!file_ptr)
	{
		perror("file_ptr:");
	}
	do
	{
		size_of_file+=fread(temp_buf,1,2048,file_ptr);	
	}while(!feof(file_ptr));

	buf_ptr=(unsigned char*)calloc(size_of_file,1);
	if(!buf_ptr)
	{
		perror("calloc:");
	}

	buf_ptr=mmap(buf_ptr,size_of_file,PROT_EXEC,MAP_PRIVATE,file_descriptor,0);
	bzero(temp_buf,sizeof(temp_buf));
    strcpy(ghost_name[0],get_init_value("HOST_NAME",buf_ptr));
    strcpy(gmodem_name[0],get_init_value("MODEM0",buf_ptr));
    strcpy(gmodem_name[1],get_init_value("MODEM1",buf_ptr));
    strcpy(gmodem_name[2],get_init_value("MODEM2",buf_ptr));
    strcpy(gmodem_name[3],get_init_value("MODEM3",buf_ptr));
    strcpy(gmodem_name[4],get_init_value("MODEM4",buf_ptr));
    strcpy(gmodem_name[5],get_init_value("MODEM5",buf_ptr));
    strcpy(gmodem_name[6],get_init_value("MODEM6",buf_ptr));
    strcpy(gmodem_name[7],get_init_value("MODEM7",buf_ptr));
    strcpy(temp_buf,get_init_value("PORT0",buf_ptr));
    fprintf(stderr,"\nInloadconfig::Host name %s Modems:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n:%s\n",ghost_name[0],
    gmodem_name[0],gmodem_name[1],gmodem_name[2],gmodem_name[3],gmodem_name[4],gmodem_name[5],gmodem_name[6],gmodem_name[7]);
    console_message(DEVELOPER_TESTING,0,ghost_name[0]);
	gserver_port[0]=(short)atoi(temp_buf);
	munmap(buf_ptr,size_of_file);	
//	(void)free(buf_ptr);	/* As usual free was creating some problem */
	close(file_descriptor);
 	return ;
}

