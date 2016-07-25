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

char* readInt(char* c, int* val) {
	int value = 0, sign = 1;

	while (*c && !isdigit(*c)) {
		if (c[0] == '-') {
			sign = -1;
		}
		c++;
	}
	if (!*c) {
		fprintf(stderr, "Rows or cols are wrong\n");
		exit(1);
	}
	while (*c && isdigit(*c)) {
		value = 10*value + *c - '0';
		c++;
	}
	printf("%d \n", value);
	*val = sign*value;
	return c;
}

unsigned long long tna11hau_fm(char* aname, char* cname, int seconds)
{
	char helpStr[BUFSIZ], *line;
	int rows, cols, k, n;
	rational *A, *c;

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
	line = readInt(line, &rows);
	line = readInt(line, &cols);

	// Initialize the correct data structure

	A = calloc(rows*cols, sizeof(rational));

	for (k = 0; k < rows; k++) {
		fgets(helpStr, BUFSIZ, afile);
		line = helpStr;
		for (n = 0; n < cols; n++) {
			line = readInt(line, &(A[k*n + n].enu));
			A[k*n + n].den = 1;
			//printf("%d ", A[k*n + n].enu);
		}
		printf("\n");
	}

	if (!fgets(helpStr, BUFSIZ, cfile)) {
		fprintf(stderr, "Something is wrong in file C\n");
		exit(1);
	}

	readInt(helpStr, &k);

	if (k != rows) {
		fprintf(stderr, "A and C files do not match\n");
		exit(1);
	}

	c = calloc(rows, sizeof(rational));

	for(k = 0;  k < rows; k++) {
		fgets(helpStr, BUFSIZ, cfile);
		line = helpStr;
		line = readInt(line, &(c[k].enu));
		c[k].den = 1;
	}

	fclose(afile);
	fclose(cfile);

	printf("The contents of A is: \n rows = %d, cols = %d \n", rows, cols);

	for (k = 0; k < rows; k++) {
		for (n = 0; n < cols; n++) {
			printf("%d ", A[k*n + n].enu);
		}
		printf("\n");
	}

	printf("The contents of C is: \n");

	for(k = 0; k < rows; k++) {
		printf("%d \n", c[k].enu);
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
