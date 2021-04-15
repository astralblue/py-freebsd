from __future__ import absolute_import, division, print_function
import unittest
from freebsd import *
from freebsd.const import *

from _util import getprocoutput

class Test_getlogin(unittest.TestCase):

    def test_getlogin(self):
        self.assertEqual(str(getlogin()),
                         getprocoutput('whoami').strip())

if __name__ == "__main__":
    unittest.main()
