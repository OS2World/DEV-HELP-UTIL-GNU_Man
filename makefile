# Makefile for man and manpath

MANPATH_CONFIG_FILE=manpath.cfg

# Add these to DEFS if...
#
# -DHAS_TROFF		if you have troff installed
# -DSUPPORT_CAT_DIRS	if you have directories of preformatted man pages
# -DCHARSPRINTF		if your sprintf returns char *
# -DSTD_HEADERS		if you have standard headers installed
# -DALT_SYSTEMS		if you have system specific subdirectories in
#			your manpath (i.e. /usr/man/sunos/...)
# -DSTRDUP_MISSING	if your system lacks strdup()
#
# Edit and add any of the defs below if you want to override the
# defaults in config.h.
#
# -DMAXPATHLEN=512	maximum number of characters in an absolute filename
# -DBUFSIZ=1024		input buffers and some other things have this length
# -DMAXDIRS=64		something more than the maximum number of
#			directories in the config file

CC = gcc -Zomf -Zmt -O
O = .obj
#CC = gcc -g
#O = .o


DEFS = -DSTD_HEADERS -DSUPPORT_CAT_DIRS -DHAS_TROFF
CFLAGS = $(DEFS)

.c$O:
	$(CC) $(CFLAGS) -c $<

all: man.exe manpath.exe

manpath.exe: manpathmain$O config.h manpath.h gripes$O util$O strdup$O
	$(CC) $(CFLAGS) -o $@ manpathmain$O gripes$O util$O strdup$O

man.exe: man$O config.h gripes.h manpath$O manpath.h gripes$O glob$O \
	util$O strdup$O
	$(CC) $(CFLAGS) -o $@ man$O manpath$O gripes$O glob$O util$O strdup$O

manpathmain$O: manpath.c
	$(CC) $(CFLAGS) -DMAIN -o $@ -c $<

gripes$O: gripes.h
util$O: gripes.h

apropos: apropos.sh
	sed -e 's,LIBDIR,$(LIBDIR),' -e 's,BINDIR,$(BINDIR),' \
		apropos.sh > apropos

whatis: whatis.sh
	sed -e 's,LIBDIR,$(LIBDIR),' -e 's,BINDIR,$(BINDIR),' \
		whatis.sh > whatis

makewhatis: makewhatis.sh
	cp makewhatis.sh makewhatis

manpages: man.$(MANEXT) manpath.$(MANEXT) apropos.$(MANEXT) whatis.$(MANEXT)

man.$(MANEXT): man.man
	sed -e 's,MANPATH_CONFIG_FILE,$(MANPATH_CONFIG_FILE),' \
	man.man > man.$(MANEXT)

manpath.$(MANEXT): manpath.man
	sed -e 's,MANPATH_CONFIG_FILE,$(MANPATH_CONFIG_FILE),' \
	manpath.man > manpath.$(MANEXT)

apropos.$(MANEXT): apropos.man
	sed -e 's,MANPATH_CONFIG_FILE,$(MANPATH_CONFIG_FILE),' \
	apropos.man > apropos.$(MANEXT)

whatis.$(MANEXT): whatis.man
	sed -e 's,MANPATH_CONFIG_FILE,$(MANPATH_CONFIG_FILE),' \
	whatis.man > whatis.$(MANEXT)

clean:
	rm -f *$O *~ core
