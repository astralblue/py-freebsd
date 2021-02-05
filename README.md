# Py-FreeBSD version 0.9.4

## Introduction

This package provides Python Interface to FreeBSD-Specific
C library functions.

## Supported Functions

  * Newly supported functions and extension types from 0.9.3

    Access content of the kern.cp_time sysctl:

    o get_cpu_times(): get breakdown of time spent in different states
      in seconds;
    o get_kern_cp_time(): get breakdown of time spent in different
      states in ticks.

    Jail(8) management:

    o jail_attach(): attach the current process to an existing jail, identified
      by jid;
    o jail_remove(): Kill all processes belonging to the jail, and remove any
      children of that jail.

  * Newly supported functions and extension types from 0.9

    chflags fchflags geom_getxml gethostname kevent kqueue lchflags
    sethostname sysctl sysctldescr sysctlmibtoname sysctlnametomib

  * Supported since 0.2

    ifstats ipstats tcpstats udpstats

  * Supported since 0.1

    fstatfs getfsent getfsfile getfsspec getfsstat getloadavg
    getlogin getosreldate getpriority getprogname getpwent getpwnam
    getpwuid getquota getrlimit getrusage jail ktrace quotaoff
    quotaon quotasync reboot sendfile setlogin setpriority setproctitle
    setprogname setquota setrlimit statfs

## Feedback

Any comments, suggestions, and/or patches are very welcome. Just file an Issue
or Pull Request on GitHub or bug report in the FreeBSD Bug Tracking system and
we'll get back to it.

## Authors

Some part of this software is based on Doug White's py-kqueue.

Hye-Shik Chang <perky@FreeBSD.org> added bulk of it.

Maksym Sobolyev <sobomax@FreeBSD.org> has brought this package into the
wonderful world of the Python 3.x.

## Thank you for using Py-FreeBSD!
