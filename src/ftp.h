/* Declarations for FTP support.
   Copyright (C) 1996-2005 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#ifndef FTP_H
#define FTP_H

#include "host.h"

/* System types. */
enum stype
{
  ST_UNIX,
  ST_VMS,
  ST_WINNT,
  ST_MACOS,
  ST_OS400,
  ST_OTHER
};

extern char ftp_last_respline[];

uerr_t ftp_response (int, char **);
uerr_t ftp_login (int, const char *, const char *);
uerr_t ftp_port (int, int *);
uerr_t ftp_pasv (int, ip_address *, int *);
#ifdef ENABLE_IPV6
uerr_t ftp_lprt (int, int *);
uerr_t ftp_lpsv (int, ip_address *, int *);
uerr_t ftp_eprt (int, int *);
uerr_t ftp_epsv (int, ip_address *, int *);
#endif
uerr_t ftp_type (int, int);
uerr_t ftp_cwd (int, const char *);
uerr_t ftp_retr (int, const char *);
uerr_t ftp_rest (int, wgint);
uerr_t ftp_list (int, const char *);
uerr_t ftp_syst (int, enum stype *);
uerr_t ftp_pwd (int, char **);
uerr_t ftp_size (int, const char *, wgint *);

#ifdef ENABLE_OPIE
const char *skey_response (int, const char *, const char *);
#endif

struct url;

/* File types.  */
enum ftype
{
  FT_PLAINFILE,
  FT_DIRECTORY,
  FT_SYMLINK,
  FT_UNKNOWN
};


/* Globbing (used by ftp_retrieve_glob).  */
enum
{
  GLOB_GLOBALL, GLOB_GETALL, GLOB_GETONE
};

/* Information about one filename in a linked list.  */
struct fileinfo
{
  enum ftype type;		/* file type */
  char *name;			/* file name */
  wgint size;			/* file size */
  long tstamp;			/* time-stamp */
  int perms;			/* file permissions */
  char *linkto;			/* link to which file points */
  struct fileinfo *prev;	/* previous... */
  struct fileinfo *next;	/* ...and next structure. */
};

/* Commands for FTP functions.  */
enum wget_ftp_command
{
  DO_LOGIN      = 0x0001,	/* Connect and login to the server.  */
  DO_CWD        = 0x0002,	/* Change current directory.  */
  DO_RETR       = 0x0004,	/* Retrieve the file.  */
  DO_LIST       = 0x0008,	/* Retrieve the directory list.  */
  LEAVE_PENDING = 0x0010	/* Do not close the socket.  */
};

enum wget_ftp_fstatus
{
  NOTHING       = 0x0000,	/* Nothing done yet.  */
  ON_YOUR_OWN   = 0x0001,	/* The ftp_loop_internal sets the
				   defaults.  */
  DONE_CWD      = 0x0002	/* The current working directory is
				   correct.  */
};

struct fileinfo *ftp_parse_ls (const char *, const enum stype);
uerr_t ftp_loop (struct url *, int *, struct url *);

uerr_t ftp_index (const char *, struct url *, struct fileinfo *);

char ftp_process_type (const char *);


#endif /* FTP_H */
