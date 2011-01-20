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

#ifndef _image_h_
#define _image_h_

#include <sys/types.h>

#include <ansidecl.h>
#include <stdio.h>

#if !defined(_PBM_H_) && !defined(_imdefs_h_)
typedef u_char bit;
#endif

typedef u_char byte;

typedef u_char gray8;
typedef short gray16;
typedef int gray32;

#ifndef BIT
#define BIT(n) (1 << (n))
#endif

typedef struct {
  u_int width, height;
} image_header;

#define image_width(im)  (((image_header *) (im))->width)
#define image_height(im) (((image_header *) (im))->height)

typedef struct {
  u_int width, height;
  bit *data;
} image_bit;

extern image_bit *new_image_bit PARAMS((int width, int height));
extern void free_image_bit PARAMS((image_bit *im));

typedef struct {
  u_int width, height;
  gray8 *data;
  gray8 max;
} image_gray8;

extern image_gray8 *new_image_gray8 PARAMS((int width, int height));
extern void free_image_gray8 PARAMS((image_gray8 *im));

typedef struct {
  u_int width, height;
  gray16 *data;
  gray16 min, max;
} image_gray16;

extern image_gray16 *new_image_gray16 PARAMS((int width, int height));
extern void free_image_gray16 PARAMS((image_gray16 *im));

typedef struct {
  u_int width, height;
  gray32 *data;
  gray32 min, max;
} image_gray32;

extern image_gray32 *new_image_gray32 PARAMS((int width, int height));
extern void free_image_gray32 PARAMS((image_gray32 *im));

typedef struct {
  u_int width, height;
  float *data;
  float min, max;
} image_float;

extern image_float *new_image_float PARAMS((int width, int height));
extern void free_image_float PARAMS((image_float *im));

typedef struct {
  u_int width, height;
  double *data;
  double min, max;
} image_double;

extern image_double *new_image_double PARAMS((int width, int height));
extern void free_image_double PARAMS((image_double *im));

extern image_gray8 *
read_pgm PARAMS((FILE *));

extern void 
write_pgm PARAMS((FILE *, image_gray8 *));

extern long
timer_elapsed PARAMS((void *timer, char *s));

extern long
timer_elapsed_n PARAMS((void *timer, char *s, int n));

/*
 * This is a simple trick for a trivial kind of template expansion in the
 * C code.  If a file is compiled with any of the #defines below specified on
 * the command line (e.g. -DCOMPILE_BIT), then type gets appropriately set.
 */

#ifdef COMPILE_BIT
#define type bit
#endif

#ifdef COMPILE_GRAY8
#define type gray8
#endif

#ifdef COMPILE_GRAY16
#define type gray16
#endif

#ifdef COMPILE_GRAY32
#define type gray32
#endif

#ifdef COMPILE_FLOAT
#define type float
#endif

#ifdef COMPILE_DOUBLE
#define type double
#endif

#ifndef image_type
#define image_type CONCAT(image_,type)
#endif

#endif /* _image_h_ */
