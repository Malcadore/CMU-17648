import unittest
import ctypes
import _ctypes
from ctypes import CFUNCTYPE
from ctypes import c_void_p
from ctypes import POINTER
from ctypes import c_int
from ctypes import cdll


class Harness(unittest.TestCase):
    
    def setUp(self):
        """ setUp
        `setUp` is called before every test method below.  The
        library should be reloaded, pointer redefined, callback
        buffer reallocated and the init function called in the 
        library.
        """
        self.clib = cdll.LoadLibrary('./libtpms.so')
        self.clib.get_pressure_log.argtype = POINTER(ctypes.c_ubyte)
        self.clib.get_pressure_log.restype = None
        self.clib.get_event_log.argtype = POINTER(ctypes.c_uint32)
        self.clib.get_event_log.restype = None

    def tearDown(self):
        _ctypes.dlclose(self.clib._handle)
        del self.clib

    def test_pressurelog(self):
        """ test_pressurelog
        1. set up a range from 0..99
        2. create a list big enough to fit the pressure log (126 bytes)
        3. put those values through the process function (see tpms.c)
        4. calling get_pressure_log will copy the internal array to the one from step 2
        5. print the content of the list we gave to tpms.c to fill
        """

        test_case = list(range(99))
        for i in test_case:
           self.clib.process(i)
        plog = (ctypes.c_ubyte*126)()
        self.clib.get_pressure_log(plog)
        print(list(plog))

    def test_eventlog(self):
        """ test_eventlog
        1. set up a range from 0..99
        2. create a list big enough to fit the event log (10 integers)
        3. put those values through the process function (see tpms.c)
        4. calling get_event_log will copy the internal array to the one from step 2
        5. print the content of the list we gave to tpms.c to fill
        """        
        
        test_case = list(range(99))
        
        for i in test_case:
            self.clib.process(i)

        elog = (ctypes.c_uint32*10)()
        self.clib.get_event_log(elog)
        print(list(elog))

        
# Use this block to run as pytest
# Usage: python3 harness.py
if __name__ == '__main__':
    unittest.main()

