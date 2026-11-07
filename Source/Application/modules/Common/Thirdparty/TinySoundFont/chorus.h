/* Chorus adapted from Sox chorus */
/*
 * August 24, 1998
 * Copyright (C) 1998 Juergen Mueller And Sundry Contributors
 * This source code is freely redistributable and may be used for
 * any purpose.  This copyright notice must be maintained.
 * Juergen Mueller And Sundry Contributors are not responsible for
 * the consequences of using this software.
 */

/*
 * 	Chorus effect.
 *
 * Flow diagram scheme for n delays ( 1 <= n <= MAX_CHORUS ):
 *
 *        * gain-in                                           ___
 * ibuff -----+--------------------------------------------->|   |
 *            |      _________                               |   |
 *            |     |         |                   * decay 1  |   |
 *            +---->| delay 1 |----------------------------->|   |
 *            |     |_________|                              |   |
 *            |        /|\                                   |   |
 *            :         |                                    |   |
 *            : +-----------------+   +--------------+       | + |
 *            : | Delay control 1 |<--| mod. speed 1 |       |   |
 *            : +-----------------+   +--------------+       |   |
 *            |      _________                               |   |
 *            |     |         |                   * decay n  |   |
 *            +---->| delay n |----------------------------->|   |
 *                  |_________|                              |   |
 *                     /|\                                   |___|
 *                      |                                      |
 *              +-----------------+   +--------------+         | * gain-out
 *              | Delay control n |<--| mod. speed n |         |
 *              +-----------------+   +--------------+         +----->obuff
 *
 *
 * The delay i is controled by a sine or triangle modulation i ( 1 <= i <= n).
 *
 * Usage:
 *   chorus gain-in gain-out delay-1 decay-1 speed-1 depth-1 -s1|t1 [
 *       delay-2 decay-2 speed-2 depth-2 -s2|-t2 ... ]
 *
 * Where:
 *   gain-in, decay-1 ... decay-n :  0.0 ... 1.0      volume
 *   gain-out :  0.0 ...      volume
 *   delay-1 ... delay-n :  20.0 ... 100.0 msec
 *   speed-1 ... speed-n :  0.1 ... 5.0 Hz       modulation 1 ... n
 *   depth-1 ... depth-n :  0.0 ... 10.0 msec    modulated delay 1 ... n
 *   -s1 ... -sn : modulation by sine 1 ... n
 *   -t1 ... -tn : modulation by triangle 1 ... n
 *
 * Note:
 *   when decay is close to 1.0, the samples can begin clipping and the output
 *   can saturate!
 *
 * Hint:
 *   1 / out-gain < gain-in ( 1 + decay-1 + ... + decay-n )
 *
*/

/*
 * Sound Tools chorus effect file.
 */

#ifndef CHORUS_H
#define CHORUS_H
#include <stdint.h>
#include <stdlib.h> /* Harmless, and prototypes atof() etc. --dgc */

#ifdef __cplusplus
extern "C" {
#endif

#define MOD_SINE	0
#define MOD_TRIANGLE 1

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

typedef struct _chorus_t {
	int	modulation;
	int	counter;
	int32_t	phase;
	int16_t	*chorusbuf;
	float	delay;
	int16_t decay;
	float	speed, depth;
	int32_t	length;
	int	depth_samples, samples;
	int	maxsamples, fade_out;
} chorus_t;

int chorus_init(chorus_t *chorus, int rate, float delay, float decay, float speed, float depth, int mod);
int chorus_process(chorus_t *chorus, int32_t *in, int32_t *out, uint32_t samples);
#ifdef __cplusplus
}
#endif
#endif
