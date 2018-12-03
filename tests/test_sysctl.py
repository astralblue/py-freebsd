from __future__ import absolute_import, division, print_function
import unittest
from test import test_support
import sys, os
from freebsd import *
from freebsd.const import *

def getprocoutput(cmd):
    return os.popen(cmd, 'r').read()

class Test_sysctl(unittest.TestCase):

    def test_getosreldate(self):
        self.assertEqual(str(getosreldate()),
                         getprocoutput('sysctl kern.osreldate').split()[-1])

    def test_getloadavg(self):
        # can't test with exact value because even test code affects L/A.
        lavg = getloadavg()
        self.assertEqual(type(lavg), tuple)
        self.assertEqual(len(lavg), 3)
        for i in range(3):
            self.assertTrue(0 <= lavg[i] <= 1)

if __name__ == "__main__":
    unittest.main()
