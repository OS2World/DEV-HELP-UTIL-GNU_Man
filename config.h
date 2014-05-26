/*
 * config.h
 *
 * Edit this file to match your site.
 *
 * Copyright (c) 1991, John W. Eaton.
 *
 * You may distribute under the terms of the GNU General Public
 * License as specified in the README file that comes with the man 1.0
 * distribution.
 *
 * John W. Eaton
 * jwe@che.utexas.edu
 * Department of Chemical Engineering
 * The University of Texas at Austin
 * Austin, Texas  78712
 */

#ifndef BUFSIZ
#define BUFSIZ 5120
#endif

#ifndef MAXPATHLEN
#define MAXPATHLEN 254
#endif

#ifndef MAXDIRS
#define MAXDIRS 64
#endif

/*
 * These are the programs man(1) execs with the -k and -f options.
 */

#define APROPOS "apropos"
#define WHATIS  "whatis"

/*
 * This might also be "/usr/ucb/more -s", though I prefer less(1)
 * because it allows one to backup even when reading from pipes.
 */

#define PAGER   "less"

static char config_file[] = "manpath.cfg";

/*
 * These might also be something like
 *
 *  nroff_command[] = "groff -man"
 *  troff_command[] = "groff -Tps -man"
 */

static char nroff_command[] = "groff -man";

#ifdef HAS_TROFF
static char troff_command[] = "groff -Tps -man";
#endif

/*
 * Define the valid manual sections.  For example, if your man
 * directory tree has subdirectories man1, man2, man3, mann,
 * and man3foo, valid_sections[] would have "1", "2", "3", "n", and
 * "3foo".  Directories are searched in the order they appear.  Having
 * extras isn't fatal, it just slows things down a bit.
 *
 * Note that this is just for directories to search.  If you have
 * files like .../man3/foobar.3Xtc, you don't need to have "3Xtc" in
 * the list below -- this is handled separately, so that `man 3Xtc foobar',
 * `man 3 foobar', and `man foobar' should find the file .../man3/foo.3Xtc,
 * (assuming, of course, that there isn't a .../man1/foo.1 or somesuch
 * that we would find first).
 *
 * Note that this list should be in the order that you want the
 * directories to be searched.  Is there a standard for this?  What is
 * the normal order?  If anyone knows, please tell me!
 */

static char *valid_sections[] =
{
  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  NULL
};

/*
 * Not all systems define these in stat.h.
 */

#ifndef S_IRUSR
#define	S_IRUSR	00400		/*  read permission: owner */
#endif
#ifndef S_IWUSR
#define	S_IWUSR	00200		/*  write permission: owner */
#endif
#ifndef S_IRGRP
#define	S_IRGRP	00040		/*  read permission: group */
#endif
#ifndef S_IWGRP
#define	S_IWGRP	00020		/*  write permission: group */
#endif
#ifndef S_IROTH
#define	S_IROTH	00004		/*  read permission: other */
#endif
#ifndef S_IWOTH
#define	S_IWOTH	00002		/*  write permission: other */
#endif

/*
 * This is the mode used for formatted pages that we create.
 */

#ifndef CATMODE
#define CATMODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#endif

#ifdef SUPPORT_CAT_DIRS
static int cat_support = 1;
#else
static int cat_support = 0;
#endif
