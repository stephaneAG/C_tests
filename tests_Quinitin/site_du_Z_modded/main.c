#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Tef Edit: the following may be necessary for 'write()' to work (..)
#include <sys/types.h>
#include <string.h>
// the following is THE one for 'read()' & 'write()'
#include <unistd.h>

// Tef Edit: Fcn qui utilise 'write()' pour afficher du stuff sur stdout (..)
void writeThat( char *theStringToWrite ){
	char buf[40]; // reserve space for te buffer
	size_t nbytes;
	ssize_t bytes_written;
	int fd; // the 'file descriptor', an int

	fd = 1; // set the file descriptor to stdout
	
	//strcpy(buf, "This is a test\n");
	strcpy(buf, theStringToWrite); // copy the string passed in the buffer
	nbytes = strlen(buf);
	
	//bytes_written = write(fd, buf, nbytes);
	bytes_written = write(fd, buf, nbytes); // actually write the stuff to stdout
	
	bzero(buf, 40);// clear the buffer
}
 
// Fonction d'affichage
void affichage (int grille[9][9])
{
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            //printf( ((j+1)%3) ? "%d " : "%d|", grille[i][j]); // old one from SdZ
            char someStuffToWrite[40]; // create a hlder for the stuff to write
  			int formatedStuff;
  			formatedStuff = sprintf (someStuffToWrite, ((j+1)%3) ? "%d " : "%d|", grille[i][j]);
  			//printf ("[%s] is a string %d chars long\n",someStuffToWrite,formatedStuff);
            
            writeThat( someStuffToWrite );
        }
        //putchar('\n'); // old one from SdZ
        writeThat("\n");
        //writeThat( (char[]){'\n'} );
        //write(socket, (char[]){40,0,0,0}, 4);
        
        if (!((i+1)%3)){
            //puts("------------------"); // old one from SdZ
            writeThat("------------------");
            writeThat( (char[]){'\n','\0'} );
        }
            
    }
    //puts("\n\n"); // old one from SdZ
    writeThat("\n\n");
    writeThat( (char[]){'\0'} );
}
 
bool absentSurLigne (int k, int grille[9][9], int i)
{
    for (int j=0; j < 9; j++)
        if (grille[i][j] == k)
            return false;
    return true;
}
 
bool absentSurColonne (int k, int grille[9][9], int j)
{
    for (int i=0; i < 9; i++)
        if (grille[i][j] == k)
            return false;
    return true;
}
 
bool absentSurBloc (int k, int grille[9][9], int i, int j)
{
    int _i = i-(i%3), _j = j-(j%3);  // ou encore : _i = 3*(i/3), _j = 3*(j/3);
    for (i=_i; i < _i+3; i++)
        for (j=_j; j < _j+3; j++)
            if (grille[i][j] == k)
                return false;
    return true;
}
 
bool estValide (int grille[9][9], int position)
{
    if (position == 9*9)
        return true;
 
    int i = position/9, j = position%9;
 
    if (grille[i][j] != 0)
        return estValide(grille, position+1);
 
    for (int k=1; k <= 9; k++)
    {
        if (absentSurLigne(k,grille,i) && absentSurColonne(k,grille,j) && absentSurBloc(k,grille,i,j))
        {
            grille[i][j] = k;
 
            if ( estValide (grille, position+1) )
                return true;
        }
    }
    grille[i][j] = 0;
 
    return false;
}
 
//int main (void)
int main (int argc, char **argv)
{
	
	
	int otherGrid[9][9]; // grid that will get filled with the params
	if ( argc != 10 ) // we need correct sudoku parameters
    {
        /* We print argv[0] assuming it is the program name */
        writeThat("Need more parameters!\n"); // argv[0] is the program name
        //exit(1); // exit
    } else {
    	int argX = 0;
    	int argY = 0;
    	int argcX2 = argc * 2; // as it may contain commas or dots between the 0's of the sudoku grid (..)
    	for (argX = 0; argX < argc; argX++){
    		
    		//writeThat("yup! one more\n");
    		for(argY = 0; argY < ( argc ); argY++){
    			//writeThat("here! ");
    			if( (int)argY%2 ==0 ){ // if PAIR number & different than 10
    				//writeThat("Not a comma ");
    				
    				// construct the otherGrid array with the data
    				// TO IMPLEMENT
    				
    				// testing ( ..)
    				char stuffToWrite[4]; // create a holder for the stuff to write
  					int formatedStuff;
  					formatedStuff = sprintf (stuffToWrite, "%d", (int)argY ); // this displays the current index ( nice test ;p ) 
  					//formatedStuff = sprintf (stuffToWrite, "%s", (char[]){ argv[argX+1][argY], '\0'} );
  					//writeThat( stuffToWrite );
    				
    			} else {
    				//writeThat(" ");
    			}
    		}
    		//writeThat("\n"); 
    	}
    }
	
	// Tef Edit: passed arguments into the array ;p
	/*
	int otherGrid[9][9];
	int arg_i = 0;
	int arg_j = 0;
	for( i=0; i < argc; i++ ){
		j = 0;
		while( argv[i][j] != '\0')
			if( argv[i][j] != ','){
				otherGrid[i][j] = argv[i][j];
				j++;
			}
	}
	*/
	
	writeThat("\n\n");
	
	
    int grille[9][9] =
    {
        {9,0,0,1,0,0,0,0,5},
        {0,0,5,0,9,0,2,0,1},
        {8,0,0,0,4,0,0,0,0},
        {0,0,0,0,8,0,0,0,0},
        {0,0,0,7,0,0,0,0,0},
        {0,0,0,0,2,6,0,0,9},
        {2,0,0,3,0,0,0,0,6},
        {0,0,0,2,0,0,9,0,0},
        {0,0,1,9,0,4,5,7,0}
    };
 
    //printf("Grille avant\n"); // old one from SdZ
    writeThat("Grille avant\n");
    affichage(grille);
 
    estValide(grille,0);
 
    //printf("Grille apres\n"); // old one from SdZ
    writeThat("Grille apres\n");
    affichage(grille);
    
    writeThat("Like it ? Loving it! \n");
}