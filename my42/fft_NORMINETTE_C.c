/*******************************************************************************/
/*                                                                             */
/*                                                       :::       ::::::::    */
/*   NORMINETTE_C__main.c                               :+:       :+:   :+:    */
/*                                                    +:+ +:+          +:+     */
/*   by: NORMINETTE_C                               +#+  +:+        +#+        */
/*                                                +#+#+#+#+#+    +#+           */
/*   Created: yyyy/mm/dd hh:mm:ss by NORMINETTE_C      #+#     #+#             */
/*   Updated: yyyy/mm/dd hh:mm:ss by NORMINETTE_C      ###   ########.fr       */
/*                                                                             */
/*******************************************************************************/

/**************************************/
/*
** FORBIDDEN STUFF : 
** .for				.switch			.goto
** .do ... while	.case			.embedd-ternairs/ternairs used for something else than setting a value ( thus, " a = ( a == 42 ? fun1() : fun2() ); " is allowed )
**
** ALLOWED STUFF : 
** .while			.if/else		.ternairs
*/
/**************************************/

/* includes ( example of available .h files (...) ) -> NEVER include a .c ! */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

/* macros and preprocessor */
/* only macros name in upper-case */
#define FOO "bar"

/* indented characters after #if, #ifdef & #ifndef with a space at each level/layer */
/* & here, double inclusion prevention ( -> we use #ifndef before doing our stuff ) */
#ifndef NORMINETTE_C_MAIN_C
# define NORMINETTE_C_MAIN_C
# ifdef __WIN32
#  define FOO "beer"
# endif /* !__WIN32 */

/* NO #if, #ifdef or #ifndef after the 1st fcn definition in a .c file ! */

/* denomination */

/* struct -> s_ */
/* typedef -> t_ */
typedef int    myint;
typedef struct	s_buff
{
	/* some stuff */
}				t_buff;
/* union -> u_ */
/* enum -> e_ */
/* globale -> g_ */

/* example fts -> 4 parameters max, 25 lines max, NO comments in the body of a fct ! */
void 			ft_print_char (void);

void 			ft_testing_function (void)
{
	int counter;
	int user_input_size;
	char *user_input;
}

int 			ft_calculator_function (void);

/* formatting */
void 			ft_correct_format_calculator (int a)
{
	if ( a == 42)
		a =0;
	
	if ( a == 42)
	{
		a = 0;
	}
	
	if ( a == 42)
	{
		if ( b ==42)
			a = 0;
	}
}

void 			ft_correct_return (int test, int value)
{
	if ( test == 0)
	{
		return (value);
	}
}

/* correct overall setup */

int 			fct (void)
{
	/* some stuff */
}

int 			fct_with_arguments (int arg1, int arg2, int arg3, int arg4)
{
	/* some stuff */
}

/* struct declaration */
struct	s_info	get_info (void)
{
	/* some stuff */
}

int 			main (void)
{
	char letter; // only declaration -> valid
	double current_value;
	char *words;
	struct s_info	toto; /* structure variable declaration */
	
	letter = 'c'; // only initialization -> valid
	current_value = 0.2;
	
	fct();
	fct_with_arguments(0, 4, 2, 3);
	return (0);
}

#endif /* !NORMINETTE_C_MAIN_C */