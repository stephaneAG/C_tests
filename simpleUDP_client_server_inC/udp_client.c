/* simple UDP socket client in C - Stéphane adam garnier 2012 */
/* to compile : ' cc udp_client.c -o udp_client.out ' */
/* to run: ' ./udp_client.out <host(example: 'localhost')> <portNumber>' */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
// note: the following include is not present in the 'tcp_server.c' program, nor in the 'tcp_client.c' or 'udp_server.c' programs neither (..) (> how many negations in the previous sentence ? ;p (> we could switch the last two ? ;D ) )
#include <arpa/inet.h>

// helper fcn(s)
void error( char *message ){
	perror( message );
	exit(0); // exit with no error (..) // nb: other change compairing to our programs using TCP, here we exit with an 'O' (Nb: no correlation between the return value & the chosen protocol (..) )
}


// 'main' loop
int main( int argc, char *argv[] ){

	int sock, length, fromlen, n; // socket, length, from length, 'n' is a var used to read&write from/to the socket & also used handle errors, if any (..)
	char buffer[256]; // a 256 chars buffer ( I guess suffiscient for the type of message we are sending to the server (..) )
	struct sockaddr_in server, from; // to test > 'add' ", from;" // the server/clients adresses // shorthand version compared to the 'udp_server.c' file : here we combine multiple declarations on one line using ',' (..)
	struct hostent *hp; // >DIGG!
	
	
	// check if all necessary command line argument are provided
	if( argc != 3 ){ // I guess another manner of writing ' if( argc < 3 ){ '
		printf( "Error: usage server port\n" ); // other way of doing it, isntead of writing to 'stderr' & 'fprintf' like in " fprintf( stderr, "Error: no port provided \n" ); "
		exit(1); // exit with no error (..) // nb: other change, here we exit with an 'O'
	}
	
	
	// create a socket
	sock = socket( AF_INET, SOCK_DGRAM, 0 ); // args: IP adresse concept, Type of socket communication (here UDP (aka 'User Datagram') ), default3rd param ( O )
	
	// check if the socket was successfully created
	if( sock < 0 ){
		error( "Error while opening the socket ..." ); // use our custom error fcn (..)
	}
	
	
	// setting some server stuff
	length = sizeof(struct sockaddr_in); // oooook ? I guess , 'prepare/hold memory for stuff (struct content >> struct length) that is as big as the passed 'prototype'[< righ term ? (..) ] struct ?? ' ( > DIGG FOR THE MEANING ! ;p )
	// Note: ' fromlen = sizeof(struct sockaddr_in); ' in the 'udp_server.c' program , as it seems to do exactly the same jobs (> so same purpose |> as same goal >> May I be right on my guess in the above statement ?(..)
	
	// SETS ' <adress>.sin_family ' //
	server.sin_family = AF_INET; // IP adress concept
	// SETS ' <adress>.sin_addr.s_addr ' //
	hp = gethostbyname( argv[1] ); // get the hostname from the host adress provided as command line argument
	if( hp == 0 ){
		error( "Error: unknown host" );
	}
	bcopy( (char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length ); // this line actually sets the '<host>.sin_addr.s_addr' (..) // > different than 'server.sin_addr.s_addr = INADDR_ANY; ', used in 'udp_server.c' for localhost (..)
	
	// continue setting server stuff (..)
	server.sin_port = htons( atoi( argv[2] ) ); // use the first command line argument value as port, passing it through necessary fcns ( 'atoi' for chars to int, and 'htons' for ?? > DIGG!! ;p (..) )
	
	
	// Here we actually setup the message we will be sending to the server
	// for that particular example, we ask the user to enter a string & we then fetch it from 'stdin' to be able to send it to the server through the socket (..)
	
	// we fist clear the buffer to empty it from glitches of old data ( > good practice anyway before using a buffer ( > even better practice on embedded microsystems ? ( I thnk 'Arduino' & 'Raspberry Pi') ;p )
	bzero( buffer, 256 ); // clear the buffer before further data handling ( reading & writing )
	
	// get what the user typed (Nb: we could use the 'scanf()' fcn (..) )
	fgets( buffer, 255, stdin );
	
	// now we fetched what the user typed, we can try to write that to the socket
	//n = sendto( sock, "The message was received by the udp server\n", 43, 0, (struct sockaddr *)&from, fromlen ); // 43 chars in total, R: the '\n' count as 1 char (..) // [ CODE FROM SERVER TO SEE ANOTHER WAY OF DOING IT (..) ]
	n = sendto( sock, buffer, strlen(buffer), 0, &server, length ); // here we make use of the 'strlen()' fcn to get the length of the buffer, and It seems that 'implicit casting' to a '(struct sockaddr *)' is done for '&server' (..)
		
	// check if we successfully sent our message to the socket
	if( n < 0 ){
		error( "Error while trying to send to the socket ..." );
	}
	
	
	// now before reading data that surely has been sent by the server in return to our message, we gotta clean the buffer first ;D
	bzero( buffer, 256 ); // good practiiiiiiice ;D
	
	// receive from the socket to the buffer
	n = recvfrom( sock, buffer, 256, 0, &from, &length ); // note the use of '&' before 'length' > dereferencing ? (..)
	
	// check for errors while trying to read from the socket
	if( n < 0 ){
		error( "Error while reading from the socket" );
	}
	
	
	
	// print out the content of the buffer ( > what actually came from the socket)
		// Note: here I we use an alternative to the 'printf()' fcn used in the following
		//    printf( "Received an incoming message from the socket: %s \n", buffer ); // ' "%variable_type", variable ' syntax
	write( 1, "Received an incoming datagram ( ACK ):", 38 ); // '1' stands [THIS IS A GUESS, TO DIGG!] for "stdout", and so maybe '2' would stand for 'stderr' and so on ?  , '38' is the number of chars of the sent 'sentence' (..)
		
	// print the actual buffer content
	write( 1, buffer, n ); // print content of the buffer using the 'n' var as length ( I guess (..) )
	


	// the client is now free to have a rest, so we finish its execution
	//return 0; // ( successfull end of the 'main loop' (..) ) , and thus end of the program (..) // commented cause absent of the original tutorial
}