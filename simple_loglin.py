#!/usr/bin/env python

# This function simply walks through the lines of a file, leaving only those
# that are not comments

# Standard libs

import sys
import os
import traceback
# import pdb

# Installed libs

from PIL import Image

# parameters

long_edge_length = 1000
pgmloglin_path = os.path.join(sys.exec_prefix, 'pgmloglin')
gs_path = '/sw/bin/gs'

# code - no touch unless programmer!

def pil_image_rescale(infile, outfile):
    """pil_image_to_pgm(infile, outfile) - convert any image readable by PIL to pgm

    the function will work with any formats that PIL supports implicitly"""
    im = Image.open(infile)
    im = im.convert('L')
    scale = float(long_edge_length) / max(im.size)
    im = im.resize([int(d * scale) for d in im.size])
    im.save(outfile)


if __name__ == '__main__':
    print "NOTE: Ghostscript must be installed to run this program properly!\n"

    for f in sys.argv[1:]:
        basename = f.rsplit('.', 1)[0]
        pgm_name = basename + '.pgm'
        ps_name = basename + '.ps' 
        out_name = basename + '-lines.png'

        pil_image_rescale(f, pgm_name)

        print 'simple_loglin: generating', out_name
        os.system(pgmloglin_path + ' %s %s' % (pgm_name, ps_name))
        os.remove(pgm_name)

        if os.path.exists(gs_path):
            os.system(gs_path + ' -dSAFER -dBATCH -dNOPAUSE'
                    ' -dEPSFitPage -sDEVICE=pnggray -sOutputFile=%s %s' \
                            % (out_name, ps_name) )

            os.remove(ps_name)
            print out_name + ' done'

            # The following would allow more control, but PIL won't open
            # postscript files unless attached to a tty... or something like
            # that
            # im = Image.open(ps_name)
            # im.save(out_name)
        else:
            print "can't find gs!"
            print "You'll have to convert %s by hand" % ps_name
