/* simple TCP socket client in C - Stéphane adam garnier 2012 */
/* to compile : ' cc tcp_client.c -o tcp_client.out ' */
/* to run: ' ./tcp_client.out <host(example: 'localhost')> <portNumber>' */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


// helper fcn(s)
void error( char *message ){
	perror( message );
	exit(1); // exit with an error (..)
}


// 'main' loop
int main( int argc, char *argv[] ){
	
	// necessary variables declaration
	int sockfd, portno; // socket, port number
	char buffer[256]; // a 256 chars buffer
	struct sockaddr_in serv_addr; // the IP adress of the server
	struct hostent *server;
	int n; // will be used to read&write from/to the socket & also used handle errors, if any (..)
	
	
	// check if all necessary command line argument are provided
	if( argc < 3 ){
		fprintf( stderr, "Error: usage %s hostname port \n", argv[0] );
		exit(0);
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
	portno = atoi( argv[2] ); // 'atoi' > char to int (..)
	
	// set the hostname
	server = gethostbyname( argv[1] );
	
	// check if server exists
	if( server == NULL ){
		fprintf( stderr, "Error: no such host \n" );	
		exit(0);
	}
	
	// continue setting server stuff (..)
	serv_addr.sin_family = AF_INET; // IP adress concept
	//serv_addr.sin_addr.s_addr = INADDR_ANY; //get 'own' adress ( > localhost-like ? ) // [ CODE FROM SERVER TO SEE THE DIFFERENCE HERE (..) ]
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length ); // set the server adress
	serv_addr.sin_port = htons( portno );
	
	
	// connecting (Nb: if anything goes wrong, it 'll be less than 0 (..) )
	if( connect(sockfd, &serv_addr, sizeof(serv_addr) ) < 0 ){
		error( "Error while connecting the socket ..." );
	}
	
	// by now, socket connection should be established: in that particular case, we prompot the user ( running the client, this file ) to enter some value to be sent to the server throught the socket
	printf( "Please enter a message:" );
	
	// clear the buffer before further data handling ( reading & writing )
	bzero( buffer, 256 );
	
	// get what the user typed (Nb: we could use the 'scanf()' fcn (..) )
	fgets( buffer, 255, stdin );
	
	// now we fetched what the user typed, we can try to write that to the socket
	//n = write( newsockfd, "The send message was received by the server", 43 ); // '43' is the number of chars of the sent 'sentence' (..) // [ CODE FROM SERVER TO SEE ANOTHER WAY OF DOING IT (..) ]
	n = write( sockfd, buffer, strlen(buffer) ); // thanks to 'strlen()' the length is auto calculated ;p
	
	// check if we wrote successfully to the socket
	if( n < 0 ){
		error( "Error while writing to the socket ..." );
	}
	
	
	// now before reading data that surely has been sent by the server in return to our message, we gotta clean the buffer first ;D
	bzero( buffer, 256 );
	
	// now we can read from the socket to the buffer ( read from the socket to the buffer with a length of 255 ) [ SAME CODE IS USED BY SERVER ]
	n = read( sockfd, buffer, 255 );
	
	// check for errors while trying to read from the socket
	if( n < 0 ){
		error( "Error while reading from the socket" );
	}
	
	// finally print out the content of the buffer ( > what actually came from the server through the socket)
	printf( "Received an incoming message from the socket: %s \n", buffer ); // ' "%variable_type", variable ' syntax .... just like in Objective-C ? ^^	
	
	
	// the client is now free to have a rest, so we finish its execution
	return 0; // ( successfull end of the 'main loop' (..) ) , and thus end of the program (..)
}