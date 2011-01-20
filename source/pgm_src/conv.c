/* 

Copyright (c) 1995  McGill University and Lee Iverson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including the rights to use, copy,
modify, merge, publish, and distribute copies of the Software without fee, and
to permit persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Any sale of this software or any work derived from this software shall be
prohibited without written agreement from the copyright holders.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
MCGILL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "llconfig.h"

#include "image.h"
#include "conv.h"

#define iconvolve CONCAT(iconvolve_,type)
#define fconvolve CONCAT(fconvolve_,type)

image_float *
DEFUN (fconvolve, (in, kern, out),
       image_type const *in AND
       fkernel const *kern AND
       image_float *out)
{
  u_int w = in->width, h = in->height, len = w*h;

  u_int kw = kern->width, kh = kern->height;
  int kx = kern->origin_x, ky = kern->origin_y;
  float *kdata = kern->data;

  type *ipstart = in->data;
  float *opstart = out->data, *opend, *op = opstart;
  type *kip = ipstart - kx - ky*w;
  
  /* This loop runs near the top boundary. */
  for (opend = opstart+ky*w; op < opend; op += w, kip += w) {
    float *op2 = op, *op2end;
    type *kip2 = kip;
    float *kp2 = kdata;
    u_int kh2 = kh, klen2;

    /* Adjust height of kernel near boundaries. */
    {
      int adj = ky-(op-opstart)/w;
      kp2 += adj*kw; kip2 += adj*w; kh2 -= adj;

      adj = kh-ky-(opstart+len-op)/w;
      if (adj > 0) kh2 -= adj;
    }
    klen2 = kh2*kw;

    /* This loop runs near the left boundary. */
    for (op2end = op+kx; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	kp3 += adj; kip3 += adj; kw3 -= adj;

	adj = kw3-kx-(op+w-op2);
	if (adj > 0) kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }

    /* This loop runs in the center (away from left or right boundaries). */
    for (op2end = op+w-(kw-kx)+1; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }

    /* This loop runs near the right boundary. */
    for (op2end = op+w; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	if (adj > 0) { kp3 += adj; kip3 += adj; kw3 -= adj; }

	adj = kw3-kx-(op2end-op2);
	kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }
  }
  
  /* This loop runs in the center (away from top or bottom boundaries). */
  for (opend = opstart+(h-(kh-ky)+1)*w; op < opend; op += w, kip += w) {
    float *op2 = op, *op2end;
    type *kip2 = kip;
    float *kp2 = kdata;
    u_int kh2 = kh, klen2 = kh2*kw;

    /* This loop runs near the left boundary. */
    for (op2end = op+kx; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	kp3 += adj; kip3 += adj; kw3 -= adj;

	adj = kw3-kx-(op+w-op2);
	if (adj > 0) kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }

    /* This loop runs in the center (away from left or right boundaries). */
    for (op2end = op+w-(kw-kx)+1; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }

    /* This loop runs near the right boundary. */
    for (op2end = op+w; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	if (adj > 0) { kp3 += adj; kip3 += adj; kw3 -= adj; }

	adj = kw3-kx-(op2end-op2);
	kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }
  }
  
  /* This loop runs near the bottom boundary. */
  for (opend = opstart+len; op < opend; op += w, kip += w) {
    float *op2 = op, *op2end;
    type *kip2 = kip;
    float *kp2 = kdata;
    u_int kh2 = kh, klen2;

    /* Adjust height of kernel near boundaries. */
    {
      int adj = ky-(op-opstart)/w;
      if (adj > 0) { kp2 += adj*kw; kip2 += adj*w; kh2 -= adj; }

      adj = kh-ky-(opstart+len-op)/w;
      kh2 -= adj;

      klen2 = kh2*kw;
    }

    /* This loop runs near the left boundary. */
    for (op2end = op+kx; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	kp3 += adj; kip3 += adj; kw3 -= adj;

	adj = kw3-kx-(op+w-op2);
	if (adj > 0) kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }

    /* This loop runs in the center (away from left or right boundaries). */
    for (op2end = op+w-(kw-kx)+1; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }

    /* This loop runs near the right boundary. */
    for (op2end = op+w; op2 < op2end; ++op2, ++kip2) {
      float sum = 0;
      type *kip3 = kip2;
      float *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	if (adj > 0) { kp3 += adj; kip3 += adj; kw3 -= adj; }

	adj = kw3-kx-(op2end-op2);
	kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	float *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum;
    }
  }

  return out;
}

#if (defined(COMPILE_GRAY8) \
     || defined(COMPILE_GRAY16) \
     || defined(COMPILE_GRAY32))
#define sum_t long
#else
#define sum_t type
#endif

image_type *
DEFUN (iconvolve, (in, kern, out),
       image_type const *in AND
       ikernel const *kern AND
       image_type *out)
{
  u_int w = in->width, h = in->height, len = w*h;
  
  u_int kw = kern->width, kh = kern->height;
  int kx = kern->origin_x, ky = kern->origin_y;
  int *kdata = kern->data;
  int divisor = kern->divisor;

  type *ipstart = in->data;
  type *opstart = out->data, *opend, *op = opstart;
  type *kip = ipstart - kx - ky*w;

  /* This loop runs near the top boundary. */
  for (opend = opstart+ky*w; op < opend; op += w, kip += w) {
    type *op2 = op, *op2end;
    type *kip2 = kip;
    int *kp2 = kdata;
    u_int kh2 = kh, klen2;

    /* Adjust height of kernel near boundaries. */
    {
      int adj = ky-(op-opstart)/w;
      kp2 += adj*kw; kip2 += adj*w; kh2 -= adj;

      adj = kh-ky-(opstart+len-op)/w;
      if (adj > 0) kh2 -= adj;
    }
    klen2 = kh2*kw;

    /* This loop runs near the left boundary. */
    for (op2end = op+kx; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	kp3 += adj; kip3 += adj; kw3 -= adj;

	adj = kw3-kx-(op+w-op2);
	if (adj > 0) kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }

    /* This loop runs in the center (away from left or right boundaries). */
    for (op2end = op+w-(kw-kx)+1; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }

    /* This loop runs near the right boundary. */
    for (op2end = op+w; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	if (adj > 0) { kp3 += adj; kip3 += adj; kw3 -= adj; }

	adj = kw3-kx-(op2end-op2);
	kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }
  }
  
  /* This loop runs in the center (away from top or bottom boundaries). */
  for (opend = opstart+(h-(kh-ky)+1)*w; op < opend; op += w, kip += w) {
    type *op2 = op, *op2end;
    type *kip2 = kip;
    int *kp2 = kdata;
    u_int kh2 = kh, klen2 = kh2*kw;

    /* This loop runs near the left boundary. */
    for (op2end = op+kx; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	kp3 += adj; kip3 += adj; kw3 -= adj;

	adj = kw3-kx-(op+w-op2);
	if (adj > 0) kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }

    /* This loop runs in the center (away from left or right boundaries). */
    for (op2end = op+w-(kw-kx)+1; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }

    /* This loop runs near the right boundary. */
    for (op2end = op+w; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	if (adj > 0) { kp3 += adj; kip3 += adj; kw3 -= adj; }

	adj = kw3-kx-(op2end-op2);
	kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }
  }
  
  /* This loop runs near the bottom boundary. */
  for (opend = opstart+len; op < opend; op += w, kip += w) {
    type *op2 = op, *op2end;
    type *kip2 = kip;
    int *kp2 = kdata;
    u_int kh2 = kh, klen2;

    /* Adjust height of kernel near boundaries. */
    {
      int adj = ky-(op-opstart)/w;
      if (adj > 0) { kp2 += adj*kw; kip2 += adj*w; kh2 -= adj; }

      adj = kh-ky-(opstart+len-op)/w;
      kh2 -= adj;

      klen2 = kh2*kw;
    }

    /* This loop runs near the left boundary. */
    for (op2end = op+kx; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	kp3 += adj; kip3 += adj; kw3 -= adj;

	adj = kw3-kx-(op+w-op2);
	if (adj > 0) kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }

    /* This loop runs in the center (away from left or right boundaries). */
    for (op2end = op+w-(kw-kx)+1; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }

    /* This loop runs near the right boundary. */
    for (op2end = op+w; op2 < op2end; ++op2, ++kip2) {
      sum_t sum = 0;
      type *kip3 = kip2;
      int *kp3 = kp2, *kp3end;
      u_int kw3 = kw;

      /* Adjust width of kernel near boundaries. */
      {
	int adj = kx-(op2-op);
	if (adj > 0) { kp3 += adj; kip3 += adj; kw3 -= adj; }

	adj = kw3-kx-(op2end-op2);
	kw3 -= adj;
      }

      for (kp3end = kp3+klen2; kp3 < kp3end; kip3 += w, kp3 += kw) {
	type *kip4 = kip3;
	int *kp4 = kp3, *kp4end = kp4+kw3;
	for ( ; kp4 < kp4end; ++kp4, ++kip4)
	  sum += kp4[0] * kip4[0];
      }

      op2[0] = sum/divisor;
    }
  }

  return out;
}
