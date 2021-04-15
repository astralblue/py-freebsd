#! /usr/bin/env python

from __future__ import absolute_import, division, print_function
from distutils.core import setup, Extension
import sys, glob, os, os.path, time
try:
    set
except:
    from sets import Set as set

if not sys.platform.startswith('freebsd'):
    print("==> This package is for FreeBSD only.", file=sys.stdout)
    raise SystemExit

DEPENDS = glob.glob('src/*.c') + glob.glob('src/*.h')
DEPENDS.remove('src/freebsdmodule.c')
DEFFILES = ('src/.const.def', 'src/.methods.def', 'src/.sources.def',
            'src/.types.def', 'src/.libraries.def')
sys.path.append('tools') # for source generators :)

def isoutdated(fname):
    if not os.access(fname, os.R_OK):
        return True

    srcmtime = max(list(map(os.path.getmtime, DEPENDS)))
    genmtime = os.path.getmtime(fname)
    return (genmtime < srcmtime)

def update_deffiles():
    if [_f for _f in map(isoutdated, DEFFILES) if _f]:
        print("==> Generating definition files..")
        import gendefs
        gendefs.main()

# update *.def files if sources are newer over them.
update_deffiles()

# get effective libraries in this system
libs = os.popen('unifdef -D__FreeBSD_version=`sysctl -n kern.osreldate` ' +
                'src/.libraries.def', 'r').read().split()
libs = list(set([_f for _f in libs if _f]))

setup(name = "py-freebsd",
      version = "0.9.4",
      description = "Python Interface to FreeBSD Platform Library",
      author = "Hye-Shik Chang",
      author_email = "perky@FreeBSD.org",
      license = "BSD",
      platforms = ['freebsd4', 'freebsd5', 'freebsd6'],
      py_modules = ['freebsd_compat02'],
      ext_modules = [
          Extension(
            "freebsd",
            ["src/freebsdmodule.c"],
            libraries=libs,
            library_dirs=['/lib', '/usr/lib'],
            depends=DEPENDS,
          )
      ],
)
