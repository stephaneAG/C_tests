/* simple TCP socket server in C - Stéphane adam garnier 2012 */
/* to compile : ' cc tcp_server.c -o tcp_server.out ' */
/* to run: ' ./tcp_server.out <portNumber>' */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


// helper fcn(s)
void error( char *message ){
	perror( message );
	exit(1); // exit with an error (..)
}


// 'main' loop
int main( int argc, char *argv[] ){
	
	// necessary variables declaration
	int sockfd, newsockfd, portno, clilen; // socket, newsocket, port number, clients length
	char buffer[256]; // a 256 chars buffer
	struct sockaddr_in serv_addr, cli_addr; // the IP adresses
	int n; // will be used to read&write from/to the socket & also used handle errors, if any (..)
	
	
	// check if all necessary command line argument are provided
	if( argc < 2 ){
		fprintf( stderr, "Error: no port provided \n" );
		exit(1);
	}
	
	// create a socket
	sockfd = socket( AF_INET, SOCK_STREAM, 0 ); // args: IP adresse concept, Type of socket communication (here TCP), default3rd param ( O )
	
	// check if the socket was successfully created
	if( sockfd < 0 ){
		error( "Error while opening the socket ..." ); // use our custom error fcn (..)
	}
	
	
	// before setting up the address(es), we clean the 'holding struct'
	bzero( (char *) &serv_addr, sizeof(serv_addr) ); // seems like we're casting it to a char pointer to do so (..)
	
	// store the port number from the provided command line argument
	portno = atoi( argv[1] ); // 'atoi' > char to int (..)
	
	// continue setting server stuff (..)
	serv_addr.sin_family = AF_INET; // IP adress concept
	serv_addr.sin_addr.s_addr = INADDR_ANY; //get 'own' adress ( > localhost-like ? )
	serv_addr.sin_port = htons( portno );
	
	
	// binding (Nb: if anything goes wrong, it 'll equals less than 0 (..) )
	if( bind( sockfd, (struct sockaddr *) &serv_addr, sizeof( serv_addr ) ) < 0 ){
		error( "Error while binding the socket ..." );
	}
	
	
	// listening ( > listen mode (..) )
	listen( sockfd, 5 ); // args > socket to put in 'listen mode', how many clients it can accept ( here, 5 )
	clilen = sizeof( cli_addr ); // hold the number of clients (..)
	
	
	// when accepting a request, create a socket for the particular client that initiated the request (..)
	newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, &clilen );
	
	// check if the new 'dedicated' socket was created successfully
	if( newsockfd < 0 ){
		error( "Error on accepting a request ..." );
	}
	
	
	// clear the buffer before further data handling ( reading & writing )
	bzero( buffer, 256 );
	
	// read from the socket to the buffer with a length of 255
	n = read( newsockfd, buffer, 255 ); // I guess the last element left in the buffer is the 'classical line ending' ('\0') (..)
	
	// check for errors while trying to read from the socket
	if( n < 0 ){
		error( "Error while reading from the socket" );
	}
	
	// print out the content of the buffer ( > what actually came from the socket)
	printf( "Received an incoming message from the socket: %s \n", buffer ); // ' "%variable_type", variable ' syntax .... just like in Objective-C ? ^^
	
	
	// send a message back to the client
	n = write( newsockfd, "The message was received by the tcp server", 43 ); // '43' is the number of chars of the sent 'sentence' (..)
	
	// check if we wrote successfully to the socket
	if( n < 0 ){
		error( "Error while writing to the socket ..." );
	}
	
	
	
	// the server is now free to have a rest, so we finish its execution
	return 0; // ( successfull end of the 'main loop' (..) )
}