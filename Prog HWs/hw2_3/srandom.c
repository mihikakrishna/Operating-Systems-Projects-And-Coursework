/*
 * example of how to use srandom()
 * it uses that to seed the PRNG
 * and prints the first NR numbers generated
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * convert a string to a number
 * if an error occurs,, return -1 after setting *err to non-zero
 */
int tonum(char *str, int *err)
{
	int n = 0;	/* accumulates number */

	/* convert to number in the usal way */
	while(*str){
		if (isdigit(*str))	n = n * 10 + *str - '0';
		else{	/* oops . . . error */ *err = 1; return(-1); }
		str++;
	}
	/* done -- return integer */
	return(n);
}

/*
 * main program
 */
int main(int argc, char *argv[])
{
	int i;			/* temp used as error flag, counter */
	int r;			/* random number */
	int n = 20;		/* how many random numbers to generate */

	/* process argument */
	if (argc == 1)
		n = 20;
	else if (argc > 2){
		fprintf(stderr, "Usage: %s [ count ]\n", argv[0]);
		return(1);
	}
	else{
		/* single arg -- convert to integer or report error */
		i = 0;
		n = tonum(argv[1], &i);
		if (i != 0 || n < 1){
			fprintf(stderr, "count must be a positive integer\n");
			return(0);
		}
	}

	/* seed the PRNG */
	(void) srandom(12345);

	/* generate the random numbers */
	for(i = 0; i < n; i++){
		r = random();
		printf("%d\n", r);
	}

	/* done! */
	return(0);
}
