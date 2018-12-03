from __future__ import absolute_import, division, print_function
import unittest
from test import test_support
import sys, os
from freebsd import *
from freebsd.const import *

def getprocoutput(cmd):
    return os.popen(cmd, 'r').read()

class Test_getlogin(unittest.TestCase):

    def test_getlogin(self):
        self.assertEqual(str(getlogin()),
                         getprocoutput('whoami').strip())

if __name__ == "__main__":
    unittest.main()
