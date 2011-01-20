/* llconfig.h.  Generated automatically by configure.  */
/* @TOP@ */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if using alloca.c.  */
/* #undef C_ALLOCA */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
   This function is required for alloca.c support on those systems.  */
/* #undef CRAY_STACKSEG_END */

/* Define if you have alloca, as a function or macro.  */
#define HAVE_ALLOCA 1

/* Define if you have <alloca.h> and it should be used (not on Ultrix).  */
#define HAVE_ALLOCA_H 1

/* Define if your C compiler doesn't accept -c and -o together.  */
/* #undef NO_MINUS_C_MINUS_O */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown
 */
/* #undef STACK_DIRECTION */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you have the expf function.  */
#define HAVE_EXPF 1

/* Define if you have the sinf function.  */
#define HAVE_SINF 1

/* Define if you have the strdup function.  */
#define HAVE_STRDUP 1

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the m library (-lm).  */
#define HAVE_LIBM 1

/* @BOTTOM@ */

#ifndef CONCAT
#ifdef __STDC__
#define _CONCAT(a,b) a ## b
#define CONCAT(a,b) _CONCAT(a,b)
#else /* !__STDC__ */
#define CONCAT(a,b) a/**/b
#endif /* !__STDC__ */
#endif /* !CONCAT */
