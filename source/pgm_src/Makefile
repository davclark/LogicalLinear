# Generated automatically from Makefile.in by configure.
     prefix = /usr/local
exec_prefix = ${prefix}

     srcdir = .

     BINDIR = $(exec_prefix)/bin
     LIBDIR = $(exec_prefix)/lib
     INCDIR = $(prefix)/include

         CC = gcc
     CFLAGS = -g -O

 ALL_CFLAGS = -I. -I$(srcdir) $(CFLAGS)

    LDFLAGS = -L$(LIBDIR) -L$(HOME)/$(ARCH)/lib
       LIBS = $(LIBIMAGE) -lm 

     RANLIB = ranlib

PROGS = \
  make-kern \
  pgmcxconv \
  pgmloglin \

LIBIMAGE = libimage.a

OBJS = \
  image.o basis.o timer.o pgm.o kern.o label.o loglin.o \
  conv-gray8.o conv-gray16.o conv-gray32.o conv-float.o \
  cxconv-gray8.o cxconv-gray16.o cxconv-gray32.o cxconv-float.o \
  llimage-gray8.o llimage-gray16.o llimage-gray32.o llimage-float.o \

INCS = llconfig.h image.h \
  basis.h basis-inlines.h \
  label.h label-inlines.h \
  loglin.h loglin-inlines.h

all: $(PROGS) $(LIBIMAGE) $(INCS)

%: %.c $(LIBIMAGE)
	@-$(RM) -f $@
	$(CC) -o $@ $(ALL_CFLAGS) $< $(LDFLAGS) $(LIBS)

%: %.o $(LIBIMAGE)
	@-$(RM) -f $@
	$(CC) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 

%-bit.o: %.c
	$(CC) -c -DCOMPILE_BIT $(ALL_CFLAGS) $< -o $@ 

%-gray8.o: %.c
	$(CC) -c -DCOMPILE_GRAY8 $(ALL_CFLAGS) $< -o $@ 

%-gray16.o: %.c
	$(CC) -c -DCOMPILE_GRAY16 $(ALL_CFLAGS) $< -o $@ 

%-gray32.o: %.c
	$(CC) -c -DCOMPILE_GRAY32 $(ALL_CFLAGS) $< -o $@ 

%-float.o: %.c
	$(CC) -c -DCOMPILE_FLOAT $(ALL_CFLAGS) $< -o $@ 

%-double.o: %.c
	$(CC) -c -DCOMPILE_DOUBLE $(ALL_CFLAGS) $< -o $@ 

$(PROGS): $(LIBIMAGE)

$(LIBIMAGE): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?
	$(RANLIB) $@

clean:
	-rm -f *.o *.a *~
	-rm -f $(PROGS)

realclean: clean
	-rm -f .depend
	-rm -f ${srcdir}/stamp-h ${srcdir}/stamp-h.in

${srcdir}/configure: configure.in
	cd ${srcdir} && autoconf
     
# autoheader might not change config.h.in, so touch a stamp file.
${srcdir}/config.h.in: stamp-h.in
${srcdir}/stamp-h.in: configure.in config.h.in
	cd ${srcdir} && autoheader
	echo timestamp > ${srcdir}/stamp-h.in
     
llconfig.h: stamp-h
stamp-h: llconfig.h.in config.status
	./config.status; echo timestamp > ${srcdir}/stamp-h

Makefile: Makefile.in config.status
	./config.status; echo timestamp > ${srcdir}/stamp-h
     
config.status: configure
	./config.status --recheck

# This calculates dependencies and then uses them
depend:
	$(CC) -M $(ALL_CFLAGS) *.c > .depend

ifeq (.depend, $(wildcard .depend*))
include .depend
endif
