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
#include "loglin.h"
#include "alloc.h"

#define lland2 CONCAT(lland2_,type)
#define lland3 CONCAT(lland3_,type)
#define lland4 CONCAT(lland4_,type)
#define lland5 CONCAT(lland5_,type)
#define lland6 CONCAT(lland6_,type)
#define lland_n CONCAT(lland_n_,type)

#define llor2 CONCAT(llor2_,type)
#define llor3 CONCAT(llor3_,type)
#define llor4 CONCAT(llor4_,type)
#define llor5 CONCAT(llor5_,type)
#define llor6 CONCAT(llor6_,type)
#define llor_n CONCAT(llor_n_,type)

image_type *
DEFUN (lland2, (degree, im0, im1, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1)
      op[0] = abs_lland2 (p0[0], p1[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1)
      op[0] = contin_lland2 (degree, p0[0], p1[0]);

  return out;
}

image_type *
DEFUN (lland3, (degree, im0, im1, im2, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2)
      op[0] = abs_lland3 (p0[0], p1[0], p2[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2)
      op[0] = contin_lland3 (degree, p0[0], p1[0], p2[0]);

  return out;
}

image_type *
DEFUN (lland4, (degree, im0, im1, im2, im3, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *im3 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *p3 = im3->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3)
      op[0] = abs_lland4 (p0[0], p1[0], p2[0], p3[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3)
      op[0] = contin_lland4 (degree, p0[0], p1[0], p2[0], p3[0]);

  return out;
}

image_type *
DEFUN (lland5, (degree, im0, im1, im2, im3, im4, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *im3 AND
       image_type *im4 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *p3 = im3->data;
  type *p4 = im4->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4)
      op[0] = abs_lland5 (p0[0], p1[0], p2[0], p3[0], p4[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4)
      op[0] = contin_lland5 (degree, p0[0], p1[0], p2[0], p3[0], p4[0]);

  return out;
}

image_type *
DEFUN (lland6, (degree, im0, im1, im2, im3, im4, im5, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *im3 AND
       image_type *im4 AND
       image_type *im5 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *p3 = im3->data;
  type *p4 = im4->data, *p5 = im5->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4, ++p5)
      op[0] = abs_lland6 (p0[0], p1[0], p2[0], p3[0], p4[0], p5[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4, ++p5)
      op[0] = contin_lland6 (degree, p0[0], p1[0], p2[0], p3[0], p4[0], p5[0]);

  return out;
}

image_type *
DEFUN (lland_n, (degree, ims, n, out),
       float degree AND
       image_type **ims AND
       int n AND
       image_type *out)
{
  switch (n) {
  case 2:
    lland2 (degree, ims[0], ims[1], out);
    break;

  case 3:
    lland3 (degree, ims[0], ims[1], ims[2], out);
    break;

  case 4:
    lland4 (degree, ims[0], ims[1], ims[2], ims[3], out);
    break;

  case 5:
    lland5 (degree, ims[0], ims[1], ims[2], ims[3], ims[4], out);
    break;

  case 6:
    lland6 (degree, ims[0], ims[1], ims[2], ims[3], ims[4], ims[5], out);
    break;

  default: {
    int w = out->width, h = out->height, len = w*h;
    type *ostart = out->data, *oend = ostart + len, *op;

    type **ptrs = anewv (type *, n);
    float *args = anewv (float, n);
    int i;

    for (i = n; i >= 0; --i)
      ptrs[i] = ims[i]->data;
    
    if (degree <= 0)
      for (op = ostart; op < oend; ++op) {
	for (i = n; i >= 0; --i) args[i] = *ptrs[i];
	op[0] = abs_lland_n (args, n);
	for (i = n; i >= 0; --i) ++ptrs[i];
      }
    else
      for (op = ostart; op < oend; ++op) {
	for (i = n; i >= 0; --i) args[i] = *ptrs[i];
	op[0] = contin_lland_n (degree, args, n);
	for (i = n; i >= 0; --i) ++ptrs[i];
      }

    break;
  }
  }

  return out;
}

image_type *
DEFUN (llor2, (degree, im0, im1, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1)
      op[0] = abs_llor2 (p0[0], p1[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1)
      op[0] = contin_llor2 (degree, p0[0], p1[0]);

  return out;
}

image_type *
DEFUN (llor3, (degree, im0, im1, im2, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2)
      op[0] = abs_llor3 (p0[0], p1[0], p2[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2)
      op[0] = contin_llor3 (degree, p0[0], p1[0], p2[0]);
    
  return out;
}

image_type *
DEFUN (llor4, (degree, im0, im1, im2, im3, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *im3 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *p3 = im3->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3)
      op[0] = abs_llor4 (p0[0], p1[0], p2[0], p3[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3)
      op[0] = contin_llor4 (degree, p0[0], p1[0], p2[0], p3[0]);

  return out;
}

image_type *
DEFUN (llor5, (degree, im0, im1, im2, im3, im4, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *im3 AND
       image_type *im4 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *p3 = im3->data;
  type *p4 = im4->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4)
      op[0] = abs_llor5 (p0[0], p1[0], p2[0], p3[0], p4[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4)
      op[0] = contin_llor5 (degree, p0[0], p1[0], p2[0], p3[0], p4[0]);

  return out;
}

image_type *
DEFUN (llor6, (degree, im0, im1, im2, im3, im4, im5, out),
       float degree AND
       image_type *im0 AND
       image_type *im1 AND
       image_type *im2 AND
       image_type *im3 AND
       image_type *im4 AND
       image_type *im5 AND
       image_type *out)
{
  int w = im0->width, h = im0->height, len = w*h;

  type *ostart = out->data, *oend = ostart + len;
  type *p0 = im0->data, *p1 = im1->data, *p2 = im2->data, *p3 = im3->data;
  type *p4 = im4->data, *p5 = im5->data, *op;

  if (degree <= 0)
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4, ++p5)
      op[0] = abs_llor6 (p0[0], p1[0], p2[0], p3[0], p4[0], p5[0]);
  else
    for (op = ostart; op < oend; ++op, ++p0, ++p1, ++p2, ++p3, ++p4, ++p5)
      op[0] = contin_llor6 (degree, p0[0], p1[0], p2[0], p3[0], p4[0], p5[0]);

  return out;
}

image_type *
DEFUN (llor_n, (degree, ims, n, out),
       float degree AND
       image_type **ims AND
       int n AND
       image_type *out)
{
  switch (n) {
  case 2:
    llor2 (degree, ims[0], ims[1], out);
    break;

  case 3:
    llor3 (degree, ims[0], ims[1], ims[2], out);
    break;

  case 4:
    llor4 (degree, ims[0], ims[1], ims[2], ims[3], out);
    break;

  case 5:
    llor5 (degree, ims[0], ims[1], ims[2], ims[3], ims[4], out);
    break;

  case 6:
    llor6 (degree, ims[0], ims[1], ims[2], ims[3], ims[4], ims[5], out);
    break;

  default: {
    int w = out->width, h = out->height, len = w*h;
    type *ostart = out->data, *oend = ostart + len, *op;

    type **ptrs = anewv (type *, n);
    float *args = anewv (float, n);
    int i;

    for (i = n; i >= 0; --i)
      ptrs[i] = ims[i]->data;
    
    if (degree <= 0)
      for (op = ostart; op < oend; ++op) {
	for (i = n; i >= 0; --i) args[i] = *ptrs[i];
	op[0] = abs_llor_n (args, n);
	for (i = n; i >= 0; --i) ++ptrs[i];
      }
    else
      for (op = ostart; op < oend; ++op) {
	for (i = n; i >= 0; --i) args[i] = *ptrs[i];
	op[0] = contin_llor_n (degree, args, n);
	for (i = n; i >= 0; --i) ++ptrs[i];
      }

    break;
  }
  }

  return out;
}
