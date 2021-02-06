from __future__ import absolute_import, division, print_function
import unittest
from time import sleep, time
from freebsd import *
from freebsd.const import *

from _util import getprocoutput

def genload(period):
    sleep(period / 2)
    btime = time()
    while time() < btime + (period / 2):
        continue

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

    def test_get_cpu_times(self):
        self.do_cp_time_test(get_cpu_times, 0.0)

    def test_get_kern_cp_time(self):
        ctimes = self.do_cp_time_test(get_kern_cp_time, 0)
        ctimes1 = [int(x) for x in getprocoutput('sysctl -qn kern.cp_time').split()]
        self.check_monot(ctimes, ctimes1)

    def do_cp_time_test(self, func, zer0):
        ctimes = func()
        for i in (CP_USER, CP_SYS, CP_INTR, CP_IDLE):
            self.assertTrue(ctimes[i] > zer0)
        self.assertTrue(ctimes[CP_NICE] >= zer0)
        genload(0.25)
        ctimes1 = func()
        self.check_monot(ctimes, ctimes1)
        return ctimes

    def check_monot(self, ct0, ct1):
        for i in (CP_USER, CP_IDLE):
           self.assertTrue(ct0[i] < ct1[i])
        for i in (CP_SYS, CP_NICE, CP_INTR):
           self.assertTrue(ct0[i] <= ct1[i])

if __name__ == "__main__":
    unittest.main()
