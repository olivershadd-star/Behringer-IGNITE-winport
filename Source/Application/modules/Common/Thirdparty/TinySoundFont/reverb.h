#ifndef REVERB_H
#define REVERB_H
/* Reverb adapted from https://github.com/gordonjcp/reverb */

/*
Copyright (c) 2015 Gordon JC Pearce <gordonjcp@gjcp.net>

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
*/
#include <stdint.h>
#include <math.h>


/* note that buffers need to be a power of 2 */
/* if we scale the tap sizes for higher sample rates, this will need to be larger */

#define COMB_SIZE 4096
#define AP_SIZE 2048

#define NUM_COMBS 4
#define NUM_APS 3

#define COMB_MASK (COMB_SIZE-1)
#define AP_MASK (AP_SIZE-1)

#define MAX_NUM_COMBS 4
#define MAX_NUM_APS 3

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

typedef struct {
    /* structure for reverb parameters */
    /* controls */
    float decay;
    float size;
    float colour;

    int16_t lpo;
    int16_t a0, b1;
    int16_t gl, gh;
    int16_t d1, d2;

    uint32_t tap[MAX_NUM_COMBS];
    uint32_t ap_tap[MAX_NUM_APS];

    int16_t comp_gain[MAX_NUM_COMBS];
    int16_t ap_gain;

    uint32_t comb_pos;             /* position within comb filter */
    uint32_t ap_pos;               /* position within allpass filter */

    int16_t comb[NUM_COMBS][COMB_SIZE];   /* buffers for comb filters */
    int16_t ap[NUM_APS][AP_SIZE];        /* buffers for ap filters */
} reverb_t;

void reverb_set_colour(reverb_t *rev, float colour);
void reverb_set_size(reverb_t *rev, float size);
void reverb_set_decay(reverb_t *rev, float decay);
void reverb_init(reverb_t *rev);
void reverb_process(reverb_t *rev, int32_t *in, int32_t *out, unsigned int samples);
#endif