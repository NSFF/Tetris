/*
 * time_functions.h
 *
 *  Created on: 7 Dec 2015
 *      Author: robin
 */

#ifndef TIME_FUNCTIONS_H_
#define TIME_FUNCTIONS_H_

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>//used to calculate timedifference, could also use <time.h> for this
#include <stdio.h>

void sleep(int, int);

float timedifference_msec(struct timeval, struct timeval);

float fps(unsigned int);

#endif /* TIME_FUNCTIONS_H_ */
