/*
 * dsp.c
 *
 *  Created on: 29.10.2025
 *      Author: Zikan
 */
#include <std.h>

#include "dsp.h"


#define PI acos(-1.0)

#define FLOAT2FIXED(x)  ((x) >= 0 ? ((Int16)((x)*32768+0.5)) : ((Int16)((x)*32768-0.5)))

#define INVERT_SEGMENT_LEN  (FLOAT2FIXED(0.00056689)) // inverted length of the segment (i.e 1/SEGMENT_LENGTH)

Int16 hamming[SEGMENT_LENGTH] = {0}; // array for the coefficients of Hamming Window

/**
* @brief compute the coefficients of the Hamming Window and save them to an array
 */
void initHammingWin()
{
   int k;

   for(k = 0; k < SEGMENT_LENGTH; k++)
   {
       hamming[k] = FLOAT2FIXED(-(0.54 - 0.46 * cosf ((2 * PI * k) / (SEGMENT_LENGTH - 1))));
   }
}

/*** 
    @brief remove the DC bias of the signal by subtracting 
        the mean of the signal from each sample
    @param segment pointer to the first sample of the current segment
    @param output pointer to the array for saving the result
 */
void removeDC(const Int16* segment, Int16* output)
{
	Int32 acum = 0;
	Int16 i;
    // compute mean value of the signal
	for (i = 0; i < SEGMENT_LENGTH; i++) // 
    {
        acum = _sadd(acum, _smpy(*(segment + i), INVERT_SEGMENT_LEN));
    }
    // subtract the mean from each sample and save to output array
    for (i = 0; i < SEGMENT_LENGTH; i++)
    {
        Int16 result = _ext( _ssub(_sshl(*(segment + i), 16), acum), 0, 16);
        *(output + i) = result;
    }
}

/** 
    @brief multiply each sample of the signal by the corresponding hamming window coefficient
    @param segment pointer to the first sample of the input segment
 */
void applyHammingWin(Int16* segment)
{
    Int16 i;
	for (i = 0; i < SEGMENT_LENGTH; i++)
	{

		*(segment + i) = _smpylh(*(segment + i), _smpy(hamming[i],0x8000)) >> 16;
	}
}

/** 
    @brief function used in autocorrelation to compute that computes the value of autocorrelation function at the given index k
    @param segment pointer to the first sample of the input segment
    @param k the delay of the signal. This signal is multiplied by the undelayed version of itself
    @param acum acumulator (the output of this function)
 */
void compute_sum(Int16* segment, Int16 k, Int32* acum)
{
    *acum = 0;
    Int16 n;
	for (n = 0; n < SEGMENT_LENGTH - k; n++)
	{
		Int32 product = _smpy(segment[n], segment[k + n]);
		*acum = _sadd(*acum, product >> 11);
	}
}

/** 
    @brief compute the value of the autocorrelation function for k's determined by K_MIN and K_MAX
            K_MIN and K_MAX corresponds to the range of frequencies where the result is expected
            store the maximum value of the autocorrelation function in k_max
            find the maximum of the quadratic function that interpolates values at k_max and the neighboring indexes
            (quadrInterpolation function)
    @param segment pointer to the first sample of the input segment
 */
void autoCorrelation(Int16* segment)
// autokorelace pro k od 20 do 160
{
	Int32 maximum = 0;
	Int32 acum = 0;

	Int16 k, k_max;

	for ( k = K_MIN - 1; k < K_MAX - 1; k++)
	{
		acum = 0;

		compute_sum(segment, k, &acum);

		if (acum > maximum)
		{
			maximum = acum;
			k_max = k;
		}
	}

	quadrInterpolation(segment, maximum, k_max);

}

/** 
    @brief takes the found maximum of the function and inteprolates this maximum and the neighboring function values using quadratic function
            then finds the maximum of this quadratic function
    @param segment pointer to the first sample of the input segment
    @param maximum the value of the autocorrelation function at k_max
    @param k_max the index of the autocorrelation function where maximum was found
 */
void quadrInterpolation(Int16* segment, Int32 maximum, Int16 k_max)
{
   Int32 acum = 0;
   // INDEX K+1
   compute_sum(segment, k_max + 1, &acum); // compute autocorrelation value at neighboring indexes (k+1 and k-1)
   Int32 maximum_plus1 = acum >> 5; // get the correct Q15 value

   maximum = maximum >> 5;// get the correct Q15 value

   // INDEX K-1
   compute_sum(segment, k_max - 1, &acum);
   Int32 maximum_minus1 = acum >> 5; // get the correct Q15 value

   Int32 num = _ssub(maximum_minus1, maximum_plus1); // numerator
   Int32 den = _ssub(maximum_minus1, _sadd((_sshl(maximum, 1)), maximum_plus1)); // denumerator
   den = _sshl(den, 1); // multiply by two

   Int32 den_invert = ((1 << 30)/den); //>> 16;

   Int32 k_max_q15 = _sshl(k_max, 15);

   Int32 k_interp = _sadd( k_max_q15, _smpy(den_invert, num) >> 16);

   Int16 freq = _ext(_sshl((_sshl(SAMPLING_FREQ, 15) / (k_interp)), 15), 0, 15);

   *(segment) = freq;
}

