/*
 * dsp.h
 *
 *  Created on: 1. 12. 2025
 *      Author: Student
 */

#ifndef DSP_H_
#define DSP_H_

#include <math.h>

#define SAMPLING_FREQ 44100 // sampling frequency of the signal
#define SEGMENT_LENGTH 1764 // segment length corresponds to 40 ms when fs = 44100
#define SHIFT 441 // 75% overlap
#define NUMBER_OF_SEGMENTS 97 
#define K_MIN 110 // fs/400 (maximum expected fundamental freq is 400 Hz)
#define K_MAX 882// fs/50 (minimum expected fundamental freq is 50 Hz)

void initHammingWin();
void removeDC(const Int16* segment, Int16* output);
void applyHammingWin(Int16* segment);
void compute_sum(Int16* segment, Int16 k, Int32* acum);
void autoCorrelation(Int16* segment);
void quadrInterpolation(Int16* segment, Int32 maximum, Int16 k_max);


#endif /* DSP_H_ */
