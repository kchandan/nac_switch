/*  Initial Creation 
*   Chandan Kumar 2006
*   http://about.me/chandank
*/
#include "thread_data.h"

void
init_thread_data(void)
{
	/* this variable will be used to store return codes of pthread functions */
    int                 iwatchdog;

	/* define a variable into which we'll store some data */
	/* for example, and integer.                          */
	int* p_num = (int*)calloc(10,sizeof(int));
	if (!p_num) 
	{
	    fprintf(stderr, "malloc: out of memory\n");
		exit(1);
	}
	/* initialize our variable to some value */
	(*p_num) = 4;

	/* now lets store this value in our TSD key.    */
	/* note that we don't store 'p_num' in our key. */
	/* we store the value that p_num points to.     */
/*	iwatchdog= pthread_setspecific(watchdog_key, (void*)p_num);

    int* pwatchdog_keyval = (int*)pthread_getspecific(watchdog_key);

    if (pwatchdog_keyval != NULL) 
    {
        printf("value of 'a_key' is: %d\n", *pwatchdog_keyval);
    }
    */
}
