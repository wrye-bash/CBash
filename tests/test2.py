import unittest
from cintold import *
from helpers import printRecord

class Test_test2(unittest.TestCase):
    def test_A(self):
        collection = ObCollection()
        collection.addMod('Oblivion.esm', Saveable = False)
        collection.addMod('DupedRecord.esp', LoadMasters = True)
        collection.load()

if __name__ == '__main__':
    unittest.main()
