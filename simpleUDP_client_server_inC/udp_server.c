/* simple UDP socket server in C - Stéphane adam garnier 2012 */
/* to compile : ' cc udp_server.c -o udp_server.out ' */
/* to run: ' ./udp_server.out <portNumber>' */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
// note: the following include is not present in the 'tcp_server.c' program (> but is in the 'tcp_client.c program' (..) )
#include <netdb.h>

// helper fcn(s)
void error( char *message ){
	perror( message );
	exit(0); // exit with no error (..) // nb: other change compairing to our programs using TCP, here we exit with an 'O' (Nb: no correlation between the return value & the chosen protocol (..) )
}


// 'main' loop
int main( int argc, char *argv[] ){

	int sock, length, fromlen, n; // socket, length, from length, 'n' is a var used to read&write from/to the socket & also used handle errors, if any (..)
	char buf[1024]; // a 1024 chars buffer ( I guess suffiscient for 4 simultaneous clients ? (..) )
	struct sockaddr_in server; // to test > 'add' ", from;" // the server adress
	struct sockaddr_in from; // a client adress
	
	// check if all necessary command line argument are provided
	if( argc < 2 ){
		fprintf( stderr, "Error: no port provided \n" );
		exit(0); // exit with no error (..) // nb: other change, here we exit with an 'O'
	}
	
	
	// create a socket
	sock = socket( AF_INET, SOCK_DGRAM, 0 ); // args: IP adresse concept, Type of socket communication (here UDP (aka 'User Datagram') ), default3rd param ( O )
	
	// check if the socket was successfully created
	if( sock < 0 ){
		error( "Error while opening the socket ..." ); // use our custom error fcn (..)
	}
	
	
	// setting some server stuff
	length = sizeof(server); // holds the value return by sizeof
	bzero(&server, length); // and use it to specifi the length of the memory area to fill with 0s ? ( > thus, only guessing >> DIGG! ;p (..) )
	// Note: in the 'tcp_server.c' program, it was done using the following:		// I guess this acts the same, the only difference being an explicit casting to 'char*' for the '&server' variable (> wich points to a memory address ?)
	// Note 2: if 'server' holds the actual server adress, then the 'length' var holds the amount of memory taken by the 'server' var ... CQFD ? ;p ( > thus, I may [as well] be wrong (..) )
	//   bzero( (char *) &serv_addr, sizeof(serv_addr) ); // seems like we're casting it to a char pointer to do so (..)
	
	// continue setting server stuff (..)
	// SETS ' <adress>.sin_family ' //
	server.sin_family = AF_INET; // IP adress concept
	// SETS ' <adress>.sin_addr.s_addr ' //
	server.sin_addr.s_addr = INADDR_ANY; //get 'own' adress ( > localhost-like ? )
	server.sin_port = htons( atoi( argv[1] ) ); // use the first command line argument value as port, passing it through necessary fcns ( 'atoi' for chars to int, and 'htons' for ?? > DIGG!! ;p (..) )
	
	// binding (Nb: if anything goes wrong, it 'll equals less than 0 (..) )
	// Note: in the 'tcp_server.c' program, the first following uncommented line is written like the following:
	// 	 if( bind( sockfd, (struct sockaddr *) &serv_addr, sizeof( serv_addr ) ) < 0 ){
	if( bind( sock, (struct sockaddr *) &server, length ) < 0 ){
		error( "Error while binding the socket ..." );
	}
	
	// no listening mode nor accepting stuff here since we are working with UDP sockets (..)
	// we just set the 'fromlen' var to hold a number representing the sum of memory taken by all the connected clients (> thus I came with this half guessing/testing/thnkng? ;p (..) )
	fromlen = sizeof(struct sockaddr_in);
	
	
	// here we start a loop (> so that multiple users can connect) (R: quit the looping server program with 'CTRL + C')
	while(1){
		
		// receive from the socket to the buffer
		n = recvfrom( sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen );
		
		// check for errors while trying to receive from the socket
		if( n < 0 ){
			error( "Error while trying to receive from the socket" );
		}
		
		// print out the content of the buffer ( > what actually came from the socket)
		// Note: here I we use an alternative to the 'printf()' fcn used in the following
		//    printf( "Received an incoming message from the socket: %s \n", buffer ); // ' "%variable_type", variable ' syntax
		write( 1, "Received an incoming datagram:", 30 ); // '1' stands [THIS IS A GUESS, TO DIGG!] for "stdout", and so maybe '2' would stand for 'stderr' and so on ?  , '30' is the number of chars of the sent 'sentence' (..)
		
		// print the actual buffer content
		write( 1, buf, n ); // print content of the buffer using the 'n' var as length ( I guess (..) )
		
		
		// > TO DO: >> considered 'good practice' >> clear the buffer before writing to it > ' bzero(<bufferVar>, <bufferLength>) '
		//    bzero( buf, n ); // thus this should work
		
		// now we received a user datagram from a client , we gonna send something to him
		n = sendto( sock, "The message was received by the udp server\n", 43, 0, (struct sockaddr *)&from, fromlen ); // 43 chars in total, R: the '\n' count as 1 char (..) 
		
		// check if we successfully sent our message to the socket
		if( n < 0 ){
			error( "Error while trying to send to the socket ..." );
		}
		 
		
	} // end 'while(1)'


	// the server is now free to have a rest, so we finish its execution
	//return 0; // ( successfull end of the 'main loop' (..) ) // commented cause absent of the original tutorial> but as the 'while(1)' maintains the loop, I guess it may not b that bad to leave it , just in case of further additions (..)
}
