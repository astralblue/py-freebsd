from __future__ import absolute_import, division, print_function
import unittest
from freebsd import *
from freebsd.const import *

from _util import getprocoutput

class Test_gethostname(unittest.TestCase):

    def test_gethostname(self):
        self.assertEqual(str(gethostname()),
                         getprocoutput('hostname').strip())

if __name__ == "__main__":
    unittest.main()
