from __future__ import unicode_literals
from distutils import dir_util
from pytest import fixture
from os import path


@fixture
def datadir(tmpdir, request):
    '''
    Fixture responsible for searching a folder with the same name of test
    module and, if available, moving all contents to a temporary directory so
    tests can use them freely.
    '''
    filename = request.module.__file__
    test_dir, _ = path.splitext(filename)

    if path.isdir(test_dir):
        dir_util.copy_tree(test_dir, bytes(tmpdir))

    return tmpdir

@fixture
def lz4():
    from cint import lz4
    return lz4


def testVersion(lz4):
    assert lz4.VERSION_NUMBER() == 10702
    assert lz4.VERSION() == (1, 7, 2)
    assert lz4.__version__() == "1.7.2"


def testCompress(lz4, datadir):
    uncompressed_data = datadir.join("testdata.txt").read_binary()
    compressed_data = datadir.join("testdata-1.txt.lz4").read_binary()
       
    output = lz4.compress(uncompressed_data)
    assert len(output) == len(compressed_data)
    assert output == compressed_data

