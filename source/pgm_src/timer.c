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

#include <sys/time.h>
#include <sys/resource.h>

#include <alloc.h>

void *
DEFUN_VOID (timer_start)
{
  struct rusage *usagep = new (struct rusage);

  getrusage (RUSAGE_SELF, usagep);

  return (void *) usagep;
}

long
DEFUN (timer_elapsed, (p, s),
       void *p AND
       char *s)
{
  long long udiff, sdiff;
  struct rusage *old_usage, new_usage;

  getrusage (RUSAGE_SELF, &new_usage);

  old_usage = (struct rusage *) p;

  udiff = ((long long) new_usage.ru_utime.tv_sec) * 1000000LL
    + ((long long) new_usage.ru_utime.tv_usec);
  udiff -= ((long long) old_usage->ru_utime.tv_sec) * 1000000LL
    + ((long long) old_usage->ru_utime.tv_usec);

  sdiff = ((long long) new_usage.ru_stime.tv_sec) * 1000000LL
    + ((long long) new_usage.ru_stime.tv_usec);
  sdiff -= ((long long) old_usage->ru_stime.tv_sec) * 1000000LL
    + ((long long) old_usage->ru_stime.tv_usec);

  if (s)
    printf ("%s: ", s);
  printf ("Elapsed %.1f ms [USER %.1f, SYS %.1f]\n",
	  (udiff+sdiff)/(1000.0F), udiff/(1000.0F), sdiff/(1000.0F));

  return (long) udiff;
}

long
DEFUN (timer_elapsed_n, (p, s, n),
       void *p AND
       char *s AND
       int n)
{
  long long udiff, sdiff;
  struct rusage *old_usage, new_usage;

  getrusage (RUSAGE_SELF, &new_usage);

  old_usage = (struct rusage *) p;

  udiff = ((long long) new_usage.ru_utime.tv_sec) * 1000000LL
    + ((long long) new_usage.ru_utime.tv_usec);
  udiff -= ((long long) old_usage->ru_utime.tv_sec) * 1000000LL
    + ((long long) old_usage->ru_utime.tv_usec);

  sdiff = ((long long) new_usage.ru_stime.tv_sec) * 1000000LL
    + ((long long) new_usage.ru_stime.tv_usec);
  sdiff -= ((long long) old_usage->ru_stime.tv_sec) * 1000000LL
    + ((long long) old_usage->ru_stime.tv_usec);

  if (s)
    printf ("%s: ", s);
  printf ("Elapsed %.2f ms [USER %.2f, SYS %.2f]\n",
	  (udiff+sdiff)/(n*1000.0F), udiff/(n*1000.0F), sdiff/(n*1000.0F));

  return (long) udiff;
}


