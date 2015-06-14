#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// From JS
// '\033' + '[1;36m' + getRandomGlyphValue() + '\033' + '[1;0m';
 
int main (int argc, char *argv[])
{
    char buf[] = "\033[1;36mI liki shit \033[1;0mand pussy whosies\n";
    //char buffer[256];
 	
    //write(1, buf, strlen(buf));
 	
 	char *bufPtr = "\033[1;36mI liki shit \033[1;0mand pussy whosies\n";
 	
 	char myBuffer[3];
 	char (*myBufferPtr)[3];
 	
 	myBuffer[0] = 'a';
 	myBuffer[1] = 'b';
 	myBuffer[2] = 'c';
 	myBuffer[3] = '\0';
 	
 	myBufferPtr = &myBuffer;
 	printf("buffer size using sizeof: %d \n", (int)sizeof(myBuffer) );
 	printf("buffer size using strlen: %d \n", (int)strlen(myBuffer) );
 	printf("buffer content: %s \n", myBuffer );
 	printf("buffer content using Ptr: %s \n", *myBufferPtr ); // a l'air de passer -> devrait passer ds une boucle (..)
 	printf("buffer address: %s \n", (char*)&myBuffer ); // getting the obj, not the adress of it
 	printf("buffer address using Ptr: %s \n", (char*)myBufferPtr ); // getting the obj, not the adress of it
 	printf("buffer address 2nd try: %d \n", *myBuffer ); // 97 ??!
 	printf("buffer address 2nd try using Ptr: %p \n", (char*)&myBufferPtr ); // seems to get the mesmory address of obj
 	printf("buffer address 2nd try: %p \n", (void*)myBuffer ); // 97 ??!
 	
 	write(1, myBufferPtr, strlen(*myBufferPtr) ); // est passé 
 	write(1, myBufferPtr[1], (int*)strlen(*myBufferPtr[1]) );
 	
 	//int i = 0;
 	//for (i=0; i < sizeof(myBuffer); i++){
 		//write(1, "Hello\n", strlen("Hello\n") );
 		//write(1, myBufferPtr[i], sizeof(myBufferPtr[i]) );
 	//}
 	
 	
 	/*
 	int i = 0;
 	for (i=0; i< sizeof(buf); i++){
 		//write(1, &bufPtr[i], strlen(&bufPtr[i]+1) ); // passes
 		//write(1, &buf[i], strlen(&buf[i]) ); // passe
 		write(1, "lol\n", strlen("lol\n") );
 		
 	}
 	*/
 	
 	/** Coooool ;D
 	int i = 0;
 	for (i=0; i< strlen(buf); i++){
 		write(1, &bufPtr[i], strlen(&bufPtr[i]) );
 	}
 	*/
 	
    return 0;
}