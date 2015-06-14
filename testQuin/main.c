/*
** ceci est mon header de fichier a la norme 42
*/

#include <stdio.h>

int main(void)
{
	int x;
	int y;
	int *x_ptr = &x;
	int *y_ptr;
	
	x = 2;
	y = 10;
	y_ptr = &y;
	
	printf("x est a ladresse : %p\n", x_ptr);
	printf("x vaut : %d\n", *x_ptr);
	printf("y est a ladresse : %p\n", y_ptr);
	printf("y vaut : %d\n", *y_ptr);
	return (0);
	
}
