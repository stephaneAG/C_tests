/* simple threads in C - Stéphane adam garnier 2012 */

#include <stdio.h>
#include <pthread.h>

// a fcn that 'll be 'threaded' ( or used as thread )
void* thread_fcn(void* parameter){
	int i = 0;
	for(i = 0; i < 5; i++){
		printf("[thread] >i currently equals %d \n", i); // '%d' to print a decimal
		sleep(1); // wait a little bit to see the thread(s) in action ..
	}
	return 0; // return stg > 0 = success ?
}

// 'infinite thread' fcn
void* infinite_thread_fcn(void* parameter){
	int i = 0;
	while(1){ // while true > 'loop bidon' ;p
		printf("[infinite thread] > i currently equals %d \n", i); // '%d' to print a decimal
		sleep(1); // wait a little bit to see the thread(s) in action ..
		i++; // increment manually an int 'i'
	}
	return 0; // return stg > 0 = success ?
}


// the 'main' loop
int main(int argc, char** argv){
	
	//create a 'pthread handle'
	pthread_t thread_handle;
	
	// create another handle for the 'infinite thread'
	pthread_t inf_thread_handle;
	
	// start and save the result of the thread
	int returnVal = pthread_create( &thread_handle, 0, thread_fcn, 0 ); // seen > 'NULL's in place(s) of the '0's
	
	// same as above, as I guess the fact being 'saving' the result is actually a way to check the thread for any error
	// > so if the thread is doing its 'looping stuff', it won't return anything (as infinite), but if some error happens, then it will return 1 and that 'll be catched using the 'saved return value' (..)
	// nb: that's kind of 'cleverly nice' ;p
	int infReturnVal = pthread_create( &inf_thread_handle, 0, infinite_thread_fcn, 0 );
	
	// once the thread has finisehd, it should return
	// we check that to ensure the thread was created correctly
	if( returnVal != 0 ){
		printf("The thread creation failed: %d", returnVal); // validate the result
		sleep(1);
		return 1; // stop ?
	}
	
	// same error checking for the 'infinite thread'
	if( infReturnVal != 0 ){
		printf("The infinite thread creation failed: %d", infReturnVal); // validate the result
		sleep(1);
		return 1; // stop ?
	}
	
	// wait until the thread ends ( i guess we should always wait for threads just before the 'final return' of the 'main' loop (..) )
	pthread_join( thread_handle, 0);
	
	//wait until ... oups, sorry, 'wait forever' ;p
	pthread_join( inf_thread_handle, 0);
	
	return 0; // success ( 1 = error (..) )
}