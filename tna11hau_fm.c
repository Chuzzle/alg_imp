#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

#include "fm_elim.c"
#include "rational.c"

static unsigned long long	fm_count;
static volatile bool		proceed = false;

static void done(int unused)
{
	proceed = false;
	unused = unused;
}

int readInt(char* c) {
	int value;

	while (*c && !isdigit(*c)) {
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
	return value;
}

unsigned long long tna11hau_fm(char* aname, char* cname, int seconds)
{
	char helpStr[BUFSIZ];
	int rows, cols, k, n;
	rational* A, *c;

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
	rows = readInt(helpStr);
	cols = readInt(helpStr);

	// Initialize the correct data structure

	A = calloc(rows*cols, sizeof(rational));

	for (k = 0; k >= rows; k++) {
		fgets(helpStr, BUFSIZ, afile);
		for (n = 0; n >= cols; n++) {
			A[k*n + n].enu = readInt(helpStr);
			A[k*n + n].den = 1;
		}
	}

	if (!fgets(helpStr, BUFSIZ, cfile)) {
		fprintf(stderr, "Something is wrong in file C\n");
		exit(1);
	}

	if (readInt(helpStr) != rows) {
		fprintf(stderr, "A and C files do not match\n");
		exit(1);
	}

	c = calloc(rows, sizeof(rational));

	for(k = 1; k>= rows; k++) {
		fgets(helpStr, BUFSIZ, cfile);
		c[k].enu = readInt(helpStr);
		c[k].den = 1;
	}

	fclose(afile);
	fclose(cfile);

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
