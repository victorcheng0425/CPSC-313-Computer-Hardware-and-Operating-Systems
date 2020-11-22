#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Basically identical to the Aaron/Emery problem but with a 2D array. */

#define NTREES	100

/* Measurements are taken every 5 minutes */
#define	M_PER_DAY	24 * (60/5)

#define DAYS		365

#define tv_ms_diff(tv1, tv2) \
        ((tv2)->tv_sec * 1000) + ((double)(tv2)->tv_usec / 1000) - \
        (((tv1)->tv_sec * 1000) + ((double)(tv1)->tv_usec / 1000))

/*
 * Make this have 1 row for each measurement. All measurements for
 * tree T, will be in column T.
 */
double ecodata[DAYS * M_PER_DAY][NTREES];

void timing_info(struct timeval *tv, struct rusage *ru) {
	int r = getrusage(RUSAGE_SELF, ru);
	assert(r >= 0);

	r = gettimeofday(tv, 0);
	assert(r >= 0);
}

void timing_output(struct timeval *tv_start, struct timeval *tv_end,
    struct rusage *ru_begin, struct rusage *ru_end) {

	// Compute elapsed time in ms
	printf("Elapsed time (ms): %7.2f\n", tv_ms_diff(tv_start, tv_end));
	printf("User time (ms)   : %7.2f\n",
	tv_ms_diff(&(ru_begin->ru_utime), &(ru_end->ru_utime)));
	printf("System time (ms) : %7.2f\n",
	tv_ms_diff(&(ru_begin->ru_stime), &(ru_end->ru_stime)));
}

/*
 * We assume that we place data in the array in real time. So, every
 * five minutes, we generate 100 readings, one for each tree. We assume
 * trees are numbered 0-99 and that collection starts precisely at midnight.
 */

/*
 * Emery wants the average sensor value for tree number 7.
 * Tree number 7 is the 8th tree, so within each
 * set of measurements, we want the 8th sample.
 */
double emery(void) {
	struct timeval tv_start, tv_end;
	struct rusage ru_start, ru_end;

	printf("Emery's analysis\n");
	timing_info(&tv_start, &ru_start);

	double val = 0;
	int bytes = 0;
	for (int i = 0; i < DAYS * M_PER_DAY; i++) {
		if (!isnan(ecodata[i][7]))
			val += ecodata[i][7];
		bytes += 8;
	}

	timing_info(&tv_end, &ru_end);
	timing_output(&tv_start, &tv_end, &ru_start, &ru_end);
	printf("Read %d bytes\n", bytes);

	return val;
}

/*
 * Aaron wants to analyze data from 9-10 every morning
 * If we collect data at 5 minute intervals, then we collect
 * 12 samples / hour and each sample is 100 trees worth. So
 * the interval from 9:00 - 10:00 AM starts at the (12 * 9 * 100)th
 * sample and we want to collect 12 sets of samples and then go to the
 * next day. Now, the interval between two chunks of data we care
 * about is 24 hours: 12 samples per hour * 24 hours * 100 trees/sample.
 */
double aaron(void) {
	struct timeval tv_start, tv_end;
	struct rusage ru_start, ru_end;

	double val = 0;
	int bytes = 0;

	int rows_per_hour = 12;
	int start_row = 9 * rows_per_hour;
	int gap_rows = 24 * rows_per_hour;

	printf("Aaron's analysis\n");
	timing_info(&tv_start, &ru_start);

	for (int i = start_row; i < DAYS * M_PER_DAY; i += gap_rows)
		for (int j = i; j < i + 12; j++)
			for (int k = 0; k < NTREES; k++) {
				if (!isnan(ecodata[j][k]))
					val += ecodata[j][k];
				bytes += 8;
			}

	timing_info(&tv_end, &ru_end);
	timing_output(&tv_start, &tv_end, &ru_start, &ru_end);
	printf("Read %d bytes\n", bytes);

	return val;
}

int main(int argc, char *argv[]) {

	/* We're going to create data by reading /dev/urandom. */
	int fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) {
		perror("Unable to open /dev/urandom");
		exit(1);
	}
	for (int i = 0; i < M_PER_DAY * DAYS; i++) {
		ssize_t bytes = read(fd, ecodata[i], NTREES * sizeof(double));
		if (bytes  != NTREES * sizeof(double)) {
			perror("Read failed");
			exit(1);
		}
	}	

	/*
	   So, now we have a large chunk-o-data. Let's simulate Emery and
	   Aaron's analyses. Note: Emery and Aaron are both real live ecologists
	   with whom I work.
	*/

	(void)emery();
	(void)aaron();
}

