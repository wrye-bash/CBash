import unittest

class Test_ImportCint(unittest.TestCase):
    def test_import(self):
        import cint
        help(cint)

class Test_Submodule(unittest.TestCase):
    def test_submodule(self):
        from cint import submodule


if __name__ == '__main__':
    unittest.main()
