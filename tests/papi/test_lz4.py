import pytest

@pytest.fixture
def lz4():
    from cint import lz4
    return lz4


def testVersion(lz4):
    assert lz4.versionNumber() == 10702
    assert lz4.version() == (1, 7, 2)
    assert lz4.versionString() == "1.7.2"
