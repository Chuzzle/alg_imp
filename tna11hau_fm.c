#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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
		return NULL;
	}
	while (*c && isidigit(*c)) {
		value = 10*value + *c - '0';
		c++;
	}
	return value;
}

unsigned long long tna11hau_fm(char* aname, char* cname, int seconds)
{
	char* helpStr[BUFSIZ];
	int x, rows, cols;

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

//	while(fgets(helpStr, BUFSIZ, afile)) {

	}
	/* read A and c files. */


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
		// fm_elim(rows, cols, a, c);

		fm_count++;
	}

	return fm_count;
}
