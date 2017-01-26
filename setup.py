#! /usr/bin/env python
#
# setup.py
#
# py-freebsd distutil setup
#
# Author  : Hye-Shik Chang <perky@fallin.lv>
# Date    : $Date: 2002/07/01 00:03:08 $
# Created : 12 June 2002
#
# $Revision: 1.4 $
#

from distutils.core import setup, Extension
import sys

if not sys.platform.startswith('freebsd'):
    print >> sys.stdout, "==> This package is for FreeBSD only."
    raise SystemExit

setup(name = "py-freebsd",
      version = "0.2",
      description = "Python Interface to FreeBSD Platform Library",
      author = "Hye-Shik Chang",
      author_email = "perky@fallin.lv",
      license = "BSD",
      ext_modules = [
          Extension(
            "freebsd",
            ["src/freebsdmodule.c"],
            #libraries=['util'],
          )
      ]
)
