#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "fm_elim.c"
#include "rational.c"

static unsigned long long	fm_count;
static volatile bool		proceed = false;

static void done(int unused)
{
	proceed = false;
	unused = unused;
}

unsigned long long tna11hau_fm(char* aname, char* cname, int seconds)
{
	char helpStr[BUFSIZ], *line;
	int rows, cols, k, n;
	int *A, *c;

	FILE*		afile = fopen(aname, "r");
	FILE*		cfile = fopen(cname, "r");

	fm_count = 0;

	if (afile == NULL) {
		fprintf(stderr, "could not open file A\n");
		exit(1);
	}

	if (cfile == NULL) {
		fprintf(stderr, "could not open file c\n");
		exit(1);
	}

	// Read the right number of numbers in each row
	if(!fgets(helpStr, BUFSIZ, afile)) {
		fprintf(stderr, "Something is wrong in file A\n");
		exit(1);
	}

	line = helpStr;
	rows = strtol(line, &line, 0);
	cols = strtol(line, &line, 0);
	// Initialize the correct data structure

	A = calloc(rows*cols, sizeof(long int));

	for(k = 0; k < rows; k++) {
		fgets(helpStr, BUFSIZ, afile);
		line = helpStr;
		for (n=0; n < cols; n++) {
			A[k*cols + n] = strtol(line, &line, 0);
			//A[k*n + n].den = 1;
			printf("%d%d %d ", k, n, k*n+n);
		}
		printf("\n");
	}

	if (!fgets(helpStr, BUFSIZ, cfile)) {
		fprintf(stderr, "Something is wrong in file C\n");
		exit(1);
	}

	line = helpStr;

	if (strtol(line, &line, 0) != rows) {
		fprintf(stderr, "A and C files do not match\n");
		exit(1);
	}

	c = calloc(rows, sizeof(long int));

	for (k=0; k < rows; k++) {
		fgets(helpStr, BUFSIZ, cfile);
		line = helpStr;
		c[k] = strtol(line, &line, 0);
		//c[k].den = 1;
	}

	fclose(afile);
	fclose(cfile);

	printf("The contents of A is: \n rows = %d, cols = %d \n", rows, cols);

	for (k = 0; k < rows; k++) {
		for (n = 0; n < cols; n++) {
			printf("%d ", A[k*cols + n]);
		}
		printf("\n");
	}

	printf("The contents of C is: \n");

	for(k = 0; k < rows; k++) {
		printf("%d \n", c[k]);
	}

	if (seconds == 0) {
		/* Just run once for validation. */

		// Uncomment when your function and variables exist...
		// return fm_elim(rows, cols, a, c);
		return 1; // return one, i.e. has a solution for now...
	}

	/* Tell operating system to call function DONE when an ALARM comes. */
	signal(SIGALRM, done);
	alarm(seconds);

	/* Now loop until the alarm comes... */
	proceed = true;
	while (proceed) {
		// Uncomment when your function and variables exist...
		// fm_elim(rows, cols, A, c);

		fm_count++;
	}
	free(A);
	free(c);
	return fm_count;
}
