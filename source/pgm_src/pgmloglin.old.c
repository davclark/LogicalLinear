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

#include "image.h"
#include "conv.h"
#include "basis.h"
#include "label.h"
#include "alloc.h"

#include <string.h>
#include <stdio.h>
#include <values.h>

#ifndef M_PI
#define M_PI (3.14159265535)
#endif

static char *argv0;
static char usage[] = 
  "Usage: %s [-ENP] [-n<ndirs>] [-d<degree>] [-t<thresh>] [pgmin] [out]\n";

float line2_sx   = 2.5;
float line2_xn   = 4;
float line2_deg  = 2.0;
float line2_stab = 0.2;
float line2_sy   = 1.4;
float line2_sep  = 0.8;

float edge2_sx   = 2.5;
float edge2_xn   = 4;
float edge2_deg  = 2.0;
float edge2_stab = 0.2;
float edge2_sy   = 1.4;  /* Original value was 1.4 */
float edge2_sep  = 0.8;  /* Original value was 0.8 */

typedef struct {
  FILE *file;
  float thresh;
  float range;
  u_short ndirs;
  u_short label;
  u_short do_edge;
  u_short do_line;
  u_short do_dark;
} cbdata;

static image_float *
image_gray8_to_float PARAMS((image_gray8 *grayim));

static void
write_row_edges PARAMS((int line, int w, void *cbp,
			float const *o1, float const *o2));

static void
write_row_lines PARAMS((int line, int w, void *cbp,
			float const *o1, float const *o2));

int
main (argc, argv)
  int argc;
  char **argv;
{
  char *in = 0, *out = 0;
  FILE *inf = stdin;
  FILE *outf = stdout;

  image_gray8 *im_in = 0;
  image_float *im_in_f = 0;
  image_float *im_out = 0, *im_outc = 0;
  unsigned int width, height;

  float degree = 32;
  float thresh = 0.01;
  int do_edges = 0;
  int do_lines = 0;
  int do_dark_lines = 0;
  int ndirs = 8;

  cbdata cb;

  argv0 = argv[0];

  for (--argc, ++argv; argc; --argc, ++argv) {
    if (**argv == '-') {
      while (*++*argv) {
	switch (**argv) {
	case 'd':
	  degree = atof ( *(*argv+1)? ++*argv: (--argc, *++argv) );
	  goto next_arg;

	case 'E':
	  do_edges = 1;
	  break;

	case 'N':
	  do_dark_lines = 1;
	  break;

	case 'P':
	  do_lines = 1;
	  break;

	case 't':
	  thresh = atof ( *(*argv+1)? ++*argv: (--argc, *++argv) );
	  goto next_arg;
	  
	case 's':
	  edge2_sy = atof( *(*argv+1)? ++*argv: (--argc, *++argv) );
	  line2_sy = edge2_sy;
	  goto next_arg;

	case 'e':
	  edge2_sep = atof( *(*argv+1)? ++*argv: (--argc, *++argv) );
	  line2_sep = edge2_sep;
	  goto next_arg;

	default:
	  fprintf (stderr, usage, argv0);
	  exit (1);
	}
      }
      next_arg:;
     
    } else if (! in) {
      /* Open input file appropriately. */
      if (! (inf = fopen (in = *argv, "r"))) {
	fprintf (stderr, "%s: Cannot open image %s\n", argv0, in);
	exit (1);
      }

    } else if (! out) {
      out = *argv;
    }
  }
  
  /* Read file from input. */
  if (! in) in = "<stdin>";
  im_in = read_pgm (inf);
  fclose (inf);

  /* Can't work without input. */
  if (! im_in) {
    fprintf (stderr, "%s: %s not an image.\n", argv0, in);
    exit (1);
  }

  /* Convert to a float image for speed on RISCy processors. */
  im_in_f = image_gray8_to_float (im_in);
  free_image_gray8 (im_in);

  /* Assume that no specifier means just edges. */
  if (! do_lines && ! do_dark_lines && ! do_edges)
    do_edges = 1;

  /* Get image size. */
  width  = image_width (im_in_f);
  height = image_height (im_in_f);

  if (out)
    outf = fopen (out, "w");

  im_out = new_image_float (width, height);
  if (do_edges || do_dark_lines) im_outc = new_image_float (width, height);

  {
    char desc[128], *p;
    if ((p = strrchr(in, '/'))) ++p;
    sprintf (desc, "%s %s%s%s", p ? p : in,
	     do_edges ? "E" : "", 
	     do_lines ? "P" : "", 
	     do_dark_lines ? "N" : "");
    write_label_head (outf, desc, width, height, ndirs,
		      do_edges, do_lines, do_dark_lines);
  }

  /* Fill in callback data structure. */
  cb.file = outf;
  cb.ndirs = ndirs;
  cb.thresh = thresh;
  cb.range = im_in_f->max;
  cb.do_edge = do_edges;
  cb.do_line = do_lines;
  cb.do_dark = do_dark_lines;

  if (do_lines || do_dark_lines) {
    int i;

    for (i = 0; i < ndirs; ++i) {
      cxkernel *line2 =
	make_line2_cxkern (i * M_PI/ndirs, 
			   line2_sx, line2_xn, line2_deg, line2_stab,
			   line2_sy, line2_sep);
      cb.label = i;
      cxconvolve_float (im_in_f, degree, line2, 
			im_out,
			do_dark_lines ? im_outc : 0,
			write_row_lines, &cb);
      if (0) {
	label_list *labs;

	if (do_lines) {
	  labs = collect_labels (im_out, im_in_f->max, thresh, i);
	  write_labels (outf, labs, "plin");
	  free_label_list (labs);
	}

	if (do_dark_lines) {
	  labs = collect_labels (im_outc, im_in_f->max, thresh, i);
	  write_labels (outf, labs, "nlin");
	  free_label_list (labs);
	}
      }
    }
  }

  if (do_edges) {
    int i;

    for (i = 0; i < ndirs; ++i) {
      cxkernel *edge2 =
	make_edge2_cxkern (i * M_PI/ndirs, 
			   edge2_sx, edge2_xn, edge2_deg, edge2_stab,
			   edge2_sy, edge2_sep);
      cb.label = i;
      cxconvolve_float (im_in_f, degree, edge2, 
			im_out, im_outc,
			write_row_edges, &cb);

      if (0) {
	label_list *labs;

	labs = collect_labels (im_out, im_in_f->max, thresh, i);
	write_labels (outf, labs, "edge");
	free_label_list (labs);

	labs = collect_labels (im_outc, im_in_f->max, thresh, i+ndirs);
	write_labels (outf, labs, "edge");
	free_label_list (labs);
      }
    }
  }

  write_label_tail (outf);

  fclose (outf);

  return 0;
}

static image_float *
image_gray8_to_float (grayim)
  image_gray8 *grayim;
{
  image_float *fim = new (image_float);
  u_int w = grayim->width, h = grayim->height, len = w*h;
  gray8 const *gp, *gpend;
  float *fp;
  float const gmax = grayim->max;

  fim->width = w;
  fim->height = h;
  fim->min = 0.0;
  fim->max = 1.0;
  fim->data = fp = newv (float, len);

  for (gp = grayim->data, gpend = gp+len; gp < gpend; ++gp, ++fp)
    fp[0] = gp[0]/gmax;

  return fim;
}

extern double rint PARAMS((double));

static void
write_row_edges (line, w, cbp, o1, o2)
  int line, w;
  void *cbp;
  float const *o1;
  float const *o2;
{
  cbdata *cb = (cbdata *) cbp;
  FILE *outf = cb->file;
  float thresh = cb->thresh;
  float range = cb->range;
  u_short ndirs = cb->ndirs;
  u_short lbl = cb->label;

  float const *op, *opend;
  
  if (o1)
    for (op = o1, opend = op+w; op < opend; ++op) {
      float v = op[0]/range;
      if (v > thresh)
	write_label (outf, op-o1, line, lbl,
		     (u_short) rint (v * CONF_MAX),
		     "edge");
    }

  if (o2)
    for (op = o2, opend = op+w; op < opend; ++op) {
      float v = op[0]/range;
      if (v > thresh)
	write_label (outf, op-o2, line, lbl+ndirs,
		     (u_short) rint (v * CONF_MAX),
		     "edge");
    }
}

static void
write_row_lines (line, w, cbp, o1, o2)
  int line, w;
  void *cbp;
  float const *o1;
  float const *o2;
{
  cbdata *cb = (cbdata *) cbp;
  FILE *outf = cb->file;
  float thresh = cb->thresh;
  float range = cb->range;
  u_short lbl = cb->label;
  int do_line = cb->do_line;
  int do_dark = cb->do_dark;

  float const *op, *opend;
  
  if (do_line && o1)
    for (op = o1, opend = op+w; op < opend; ++op) {
      float v = op[0]/range;
      if (v > thresh)
	write_label (outf, op-o1, line, lbl,
		     (u_short) rint (v * CONF_MAX),
		     "plin");
    }

  if (do_dark && o2)
    for (op = o2, opend = op+w; op < opend; ++op) {
      float v = op[0]/range;
      if (v > thresh)
	write_label (outf, op-o2, line, lbl,
		     (u_short) rint (v * CONF_MAX),
		     "nlin");
    }
}
