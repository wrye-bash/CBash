import pytest

@pytest.fixture
def lz4():
    from cint import lz4
    return lz4


def testVersion(lz4):
    assert lz4.version() == 10702
