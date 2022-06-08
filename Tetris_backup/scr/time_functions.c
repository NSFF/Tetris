/*
 * time_functions.c
 *
 *  Created on: 7 Dec 2015
 *      Author: robin
 */

#include "time_functions.h"

/*
 * stops the program for an amount of time (in milliseconds)
 */
void sleep(int nr_of_seconds, int nr_of_milliseconds) {
	struct timespec *sleep_time = malloc(sizeof(struct timespec));
	sleep_time->tv_sec = nr_of_seconds;
	sleep_time->tv_nsec = nr_of_milliseconds * 1000 * 1000;
	struct timespec *remainder_sleep_time = malloc(sizeof(struct timespec));
	nanosleep(sleep_time, remainder_sleep_time);

	free(sleep_time);
	free(remainder_sleep_time);
}

/*
 * calculates timedifference, used in main()
 */
float timedifference_msec(struct timeval t0, struct timeval t1){

    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

/* returns amount of time between frames in milliseconds */
float fps(unsigned int n){
	return (1.0/n)*1000.0;
}
