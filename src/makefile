
#		COMPILER		#
CC        =     gcc -g  
#CC       =     gcc32 -g  -DDEBUG
FLAGS     =     -fpack-struct
#		PROJECT DIRECTORY	#
ROOT_DIR  =	/root/Programs/nac_rep
INCLUDES  =    
LIBS      = -lpthread -lncurses	    

GNU_OBJ   = $(ROOT_DIR)/gnu_obj/main.o \
	$(ROOT_DIR)/gnu_obj/linksmart.o \
	$(ROOT_DIR)/gnu_obj/load_config.o\
	$(ROOT_DIR)/gnu_obj/display_mod.o\
	$(ROOT_DIR)/gnu_obj/thread_data.o\
	$(ROOT_DIR)/gnu_obj/master_thread.o\

#		MAIN MAKE RULES		#
main:	$(GNU_OBJ)		
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) $(GNU_OBJ) -o $(ROOT_DIR)/gnu_obj/output
	rm  $(ROOT_DIR)/src/output
	cp  $(ROOT_DIR)/gnu_obj/output  $(ROOT_DIR)/src/output
	
$(ROOT_DIR)/gnu_obj/main.o: $(ROOT_DIR)/src/main.c $(ROOT_DIR)/src/main.h 
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) -c $(ROOT_DIR)/src/main.c
	mv main.o  $(ROOT_DIR)/gnu_obj/

$(ROOT_DIR)/gnu_obj/linksmart.o: $(ROOT_DIR)/src/linksmart.c $(ROOT_DIR)/src/linksmart.h 
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) -c $(ROOT_DIR)/src/linksmart.c
	mv linksmart.o  $(ROOT_DIR)/gnu_obj/

$(ROOT_DIR)/gnu_obj/load_config.o: $(ROOT_DIR)/src/load_config.c $(ROOT_DIR)/src/load_config.h  
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) -c $(ROOT_DIR)/src/load_config.c
	mv load_config.o  $(ROOT_DIR)/gnu_obj/

$(ROOT_DIR)/gnu_obj/display_mod.o: $(ROOT_DIR)/src/display_mod.c $(ROOT_DIR)/src/display_mod.h 
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) -c $(ROOT_DIR)/src/display_mod.c
	mv display_mod.o  $(ROOT_DIR)/gnu_obj/

$(ROOT_DIR)/gnu_obj/thread_data.o: $(ROOT_DIR)/src/thread_data.c $(ROOT_DIR)/src/thread_data.h 
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) -c $(ROOT_DIR)/src/thread_data.c
	mv thread_data.o  $(ROOT_DIR)/gnu_obj/
	
$(ROOT_DIR)/gnu_obj/master_thread.o: $(ROOT_DIR)/src/master_thread.c $(ROOT_DIR)/src/master_thread.h 
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) -c $(ROOT_DIR)/src/master_thread.c
	mv master_thread.o  $(ROOT_DIR)/gnu_obj/	
clean :
	        -rm  $(ROOT_DIR)/gnu_obj/*.o
	
