/*
 * modulecontents.h
 *
 * FreeBSD Platform Library - All Modules
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/07/01 00:12:14 $
 * Created : 13 June 2002
 *
 * $Revision: 1.17 $
 */

/*#include "cd.c"*/             /* cd (cdcontrol(1) and cdda facility) */
#include "fstab.c"          /* getfsent(3), getfsspec(3), getfsfile(3) */
#include "jail.c"           /* jail(2) */
#include "ktrace.c"         /* ktrace(2) */
#include "login.c"          /* getlogin(2), setlogin(2) */
#include "netstat.c"        /* ipstats, tcpstats (netstat(1)) */
#include "priority.c"       /* setpriority(2), getpriority(2) */
#include "process.c"        /* setproctitle(2), getprogname(3), setprogname(3) */
#include "pwdb.c"           /* getpwuid(3), getpwnam(3), getpwent(3) */
#include "quota.c"          /* quotaon, quotaoff, getquota, setquota, quotasync (quotactl(2)) */
#include "reboot.c"         /* reboot(2) */
#include "rlimit.c"         /* getrlimit(2), setrlimit(2) */
#include "rusage.c"         /* getrusage(2) */
#include "sendfile.c"       /* sendfile(2) */
#include "statfs.c"         /* statfs(2), fstatfs(2), getfsstat(2) */
#include "sysctl.c"         /* getloadavg(3), getosreldate(3) */
