from cintold import *
from helpers import d, printRecord

def regressionTests():
    with ObCollection() as Current:
        Current.addMod("Oblivion.esm")
        newMod = Current.addMod("RegressionTests.esp")
        Current.load()
        print Current.Debug_DumpModFiles()

        assertTES4(Current, newMod)
        assertGMST(Current, newMod)
        assertGLOB(Current, newMod)
        assertCLAS(Current, newMod)
        assertFACT(Current, newMod)
        assertHAIR(Current, newMod)
        assertEYES(Current, newMod)
        assertRACE(Current, newMod)

##    assertSOUN(Current, newMod)
##    assertSKIL(Current, newMod)

def assertTES4(Current, newMod):
    record = Current.LoadOrderMods[0].TES4

    assert record.IsESM
    assert record.flags1 == 0x00000001
    assert record.flags2 == 0
    assert record.version == 1.0
    assert record.numRecords == 1252095
    assert record.nextObject == 0xFF09764D
    assert record.ofst_p == [0, 2, 0, 0, 78, 79, 78, 69, 0, 0, 0, 0, 1, 233, 142, 87,
                             84, 69, 83, 52, 0, 0, 0, 0, 2, 235, 195, 1, 71, 82, 85,
                             80, 0, 0, 0, 0, 3, 0, 0, 0, 71, 77, 83, 84, 0, 0, 0, 0,
                             4, 105, 111, 110, 71, 76, 79, 66, 0, 0, 0, 0, 5, 0, 0,
                             0, 67, 76, 65, 83, 0, 0, 0, 0, 6, 0, 0, 0, 70, 65, 67,
                             84, 0, 0, 0, 0, 7, 0, 0, 0, 72, 65, 73, 82, 0, 0, 0, 0,
                             8, 0, 0, 0, 69, 89, 69, 83, 0, 0, 0, 0, 9, 0, 0, 0, 82,
                             65, 67, 69, 0, 0, 0, 0, 10, 0, 0, 0, 83, 79, 85, 78, 0,
                             0, 0, 0, 11, 0, 0,0, 83, 75, 73, 76, 0, 0, 0, 0, 12, 0,
                             0, 0, 77, 71, 69, 70, 0, 0, 0, 0, 13, 0, 0, 0, 83, 67,
                             80, 84, 0, 0, 0, 0, 14, 0,0, 0, 76, 84, 69, 88, 0, 0,
                             0, 0, 15, 0, 0, 0, 69, 78, 67, 72, 0, 0, 0, 0, 16, 0,
                             0, 0, 83, 80, 69, 76, 0, 0, 0, 0, 17,0, 0, 0, 66, 83,
                             71, 78, 0, 0, 0, 0, 18, 0, 0, 0, 65, 67, 84, 73, 0, 0,
                             0, 0, 19, 0, 0, 0, 65, 80, 80, 65, 0, 0, 0, 0, 20, 0,
                             0, 0, 65, 82, 77, 79, 0, 0, 0, 0, 21, 0, 0, 0, 66, 79,
                             79, 75, 0, 0, 0, 0, 22, 0, 0, 0, 67, 76, 79, 84, 0, 0,
                             0, 0, 23, 0, 0, 0, 67, 79, 78, 84, 0, 0, 0, 0, 24, 68,
                             249, 119, 68, 79, 79, 82, 0, 0, 0, 0, 25, 19, 20, 0,
                             73, 78, 71, 82,0, 0, 0, 0, 26, 138, 245, 119, 76, 73,
                             71, 72, 0, 0, 0, 0, 27, 0, 0, 0, 76, 79, 67, 75, 0, 0,
                             0, 0, 28, 0, 0, 0, 77, 73, 83, 67, 0, 0, 0, 0, 29, 0,
                             0, 0, 82, 69, 80, 65, 0, 0, 0, 0, 30, 194, 245, 119,
                             83, 84, 65, 84, 0, 0, 0, 0, 31, 245, 18, 0, 84, 82,
                             69, 69, 0, 0, 0, 0, 32, 0, 0, 0, 70, 76, 79, 82, 0, 0,
                             0, 0, 33, 0, 0, 0, 70, 85, 82, 78, 0, 0, 0, 0, 34, 0,
                             0, 0, 87, 69, 65, 80, 0, 0, 0, 0, 35, 2, 0, 0, 65, 77,
                             77, 79, 0, 0, 0, 0, 36, 0, 0, 0, 78, 80, 67, 95, 0, 0,
                             0, 0, 37, 219, 111, 0, 67, 82, 69, 65, 0, 0, 0, 0, 38,
                             0, 0, 0, 76, 86, 76, 67, 0, 0, 0, 0, 39, 162, 112, 0,
                             83, 76, 71, 77, 0,0, 0, 0, 40, 0, 0, 0, 75, 69, 89, 77,
                             0, 0, 0, 0, 41, 107, 143, 0, 65, 76, 67, 72, 0, 0, 0,
                             0, 42, 245, 18, 0, 76, 86, 76, 73, 0, 0, 0, 0, 43, 167,
                             111, 0, 83, 78, 68, 71, 0, 0, 0, 0, 44, 220, 111, 0,
                             67, 76, 77, 84, 0, 0, 0, 0, 45, 222, 111, 0, 82, 69,
                             71, 78, 0, 0, 0, 0, 46, 217, 111, 0, 67, 69, 76, 76,
                             65, 254, 121, 17, 47, 107, 143, 0, 82, 69, 70, 82, 0,
                             0, 0, 0, 48, 29, 228, 1, 65, 67, 72, 82, 0, 0, 0, 0,
                             49, 0, 0, 0, 65, 67, 82, 69, 0, 0, 0, 0, 50, 0, 0, 0,
                             80, 71, 82,68, 0, 0, 0, 0, 51, 0, 0, 0, 87, 82, 76, 68,
                             0, 0, 0, 0, 52, 184, 218, 1, 76, 65, 78, 68, 0, 0, 0,
                             0, 53, 180, 218, 1, 84, 76, 79, 68, 0, 0, 0, 0, 54, 0,
                             0, 0, 68, 73, 65, 76, 0, 0, 0, 0, 55, 0, 218, 1, 73,
                             78, 70, 79, 0, 0, 0, 0, 56, 184, 218, 1, 81, 85, 83,
                             84, 0, 0, 0, 0]
    assert record.dele_p == [101, 84, 43, 226, 70, 177, 196, 1]
    assert record.author == "mlipari"
    assert record.description == " "
    assert record.masters == []

    record = newMod.TES4
    record.flags1 = 5
    record.flags2 = 12
    record.version = 1.2
    record.numRecords = 10
    record.nextObject = 0x00001000
    record.ofst_p = [0, 1, 2, 3]
    record.dele_p = [10, 11, 12, 13]
    record.author = "Waruddar"
    record.description = "This is a test string\nand only a test string."
##    record.masters = ["Oblivion.esm"] #For now, masters shouldn't be set directly. More coding needs to be done to make it safe
    assert record.flags1 ==  5
    assert record.flags2 == 12
    assert record.version == 1.2
    assert record.numRecords == 10
    assert record.nextObject == 0x00001000
    assert record.ofst_p == [0, 1, 2, 3]
    assert record.dele_p == [10, 11, 12, 13]
    assert record.author == "Waruddar"
    assert record.author != "WAruddar"
    assert record.description == "This is a test string\nand only a test string."
    assert record.description != "This is A test string\nand only a test string."
##    assert record.masters == ["Oblivion.esm"]
##    assert record.masters == ["oblivion.esm"] #Masters are case-insensitive

    print "TES4:Finished testing"

def assertGMST(Current, newMod):
    record = Current.LoadOrderMods[0].GMST[0]

    assert record.fid == ('Oblivion.esm', 0x045D2F)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1583621
    assert record.eid == "sMiscSEBounty"
    assert record.eid == "sMiscSEbounty"
    assert record.value == "Shivering Isles Bounty:"
    assert record.value != "ShiVering Isles Bounty:"

    srecord = newMod.create_GMST("sWarString")
    irecord = newMod.create_GMST("iWarString")
    frecord = newMod.create_GMST("fWarString")

    srecord.flags1 = 10
    srecord.flags2 = 15
    srecord.value = "It works!"
    assert srecord.value == "It works!"
    assert srecord.value != "IT works!"
    srecord.value = 1
    assert srecord.value == "1"
    srecord.value = 1.0
    assert srecord.value == "1.0"

    assert srecord.fid == ('RegressionTests.esp', 0x001001)
    assert srecord.flags1 == 10
    assert srecord.flags2 == 15
    assert srecord.eid == "sWarString"
    assert srecord.eid == "sWaRString"

    irecord.flags1 = 11
    irecord.flags2 = 16
    irecord.value = 2
    assert irecord.value == 2
    irecord.value = "It works!"  #Shouldn't work
    assert irecord.value == 2
    irecord.value = 5.9
    assert irecord.value == 5

    assert irecord.fid == ('RegressionTests.esp', 0x001002)
    assert irecord.flags1 == 11
    assert irecord.flags2 == 16
    assert irecord.eid == "iWarString"
    assert irecord.eid == "IWarString"

    frecord.flags1 = 12
    frecord.flags2 = 17
    frecord.value = 3.0
    assert frecord.value == 3.0
    frecord.value = "It works!"  #Shouldn't work
    assert frecord.value == 3.0
    frecord.value = 5
    assert frecord.value == 5.0

    assert frecord.fid == ('RegressionTests.esp', 0x001003)
    assert frecord.flags1 == 12
    assert frecord.flags2 == 17
    assert frecord.eid == "fWarString"
    assert frecord.eid == "fWarSTRing"

    record = Current.LoadOrderMods[0].GMST[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('Oblivion.esm', 0x045D2F)
    assert newrecord.flags1 == 0x00000000
    assert newrecord.flags2 == 1583621
    assert newrecord.eid == "sMiscSEBounty"
    assert newrecord.eid == "SMiscSEBounty"
    assert newrecord.value == "Shivering Isles Bounty:"
    assert newrecord.value != "ShiverinG Isles Bounty:"

    newrecord.flags1 = 0
    newrecord.flags2 = 5
    newrecord.eid = "sTestWar"
    newrecord.eid = "" #Shouldn't work
    newrecord.value = "Test:"

    assert newrecord.fid == FormID('Oblivion.esm', 0x045D2F)
    assert newrecord.flags1 == 0x00000000
    assert newrecord.flags2 == 5
    assert newrecord.eid == "sTestWar"
    assert newrecord.eid == "sTEstWar"
    assert newrecord.value == "Test:"
    assert newrecord.value != "TeSt:"

    assert record.fid == ('Oblivion.esm', 0x045D2F)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1583621
    assert record.eid == "sMiscSEBounty"
    assert record.eid == "sMiscSEBounTy"
    assert record.value == "Shivering Isles Bounty:"
    assert record.value != "Shivering Isles BounTy:"

    print "GMST:Finished testing"

def assertGLOB(Current, newMod):
    record = Current.LoadOrderMods[0].GLOB[0]

    assert record.fid == ('Oblivion.esm', 0x08D9DA)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1584398
    assert record.eid == "SEKnightSpawnTime"
    assert record.eid == "SEKnighTSpawnTime"
    assert record.format == 's'
    assert record.format != 'S'
    assert record.value == 4.0

    record = newMod.create_GLOB()
    record.flags1 = 0x0102
    record.flags2 = 0x0201
    record.eid = "WarGlobalTest"
    record.format = 'f'
    record.value = 12.2

    assert record.fid == ('RegressionTests.esp', 0x001004)
    assert record.flags1 == 0x0102
    assert record.flags2 == 0x0201
    assert record.eid == "WarGlobalTest"
    assert record.eid == "WArGlobalTest"
    assert record.format == 'f'
    assert record.format != 'F'
    assert record.value == 12.2

    record = Current.LoadOrderMods[0].GLOB[0]
    newrecord = record.CopyAsOverride(newMod)

    assert newrecord.fid == ('Oblivion.esm', 0x08D9DA)
    assert newrecord.flags1 == 0x00000000
    assert newrecord.flags2 == 1584398
    assert newrecord.eid == "SEKnightSpawnTime"
    assert newrecord.eid == "SEKnighTSpawnTime"
    assert newrecord.format == 's'
    assert newrecord.format != 'S'
    assert newrecord.value == 4.0

    newrecord.flags1 = 2
    newrecord.flags2 = 3
    newrecord.eid = "WarGlobalCopyTest"
    newrecord.format = 'f'
    newrecord.value = 16.0

    assert newrecord.flags1 == 2 #CBash sets 0x80000000 for internal use
    assert newrecord.flags2 == 3
    assert newrecord.eid == "WarGlobalCopyTest"
    assert newrecord.eid == "WArGlobalCopyTest"
    assert newrecord.format == 'f'
    assert newrecord.format != 'F'
    assert newrecord.value == 16.0

    assert record.fid == ('Oblivion.esm', 0x08D9DA)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1584398
    assert record.eid == "SEKnightSpawnTime"
    assert record.eid == "SEKnighTSpawnTime"
    assert record.format == 's'
    assert record.format != 'S'
    assert record.value == 4.0

    newrecord = record.CopyAsNew(newMod)

    assert newrecord.fid == ('RegressionTests.esp', 0x001005)
    assert newrecord.flags1 == 0x00000000
    assert newrecord.flags2 == 1584398
    assert newrecord.eid == "SEKnightSpawnTime"
    assert newrecord.eid == "SEKnighTSpawnTime"
    assert newrecord.format == 's'
    assert newrecord.format != 'S'
    assert newrecord.value == 4.0

    newrecord.flags1 = 4
    newrecord.flags2 = 8
    newrecord.eid = "WarGlobalCopyNew"
    newrecord.format = 's'
    newrecord.value = 9.0

    assert newrecord.flags1 == 4 #CBash sets 0x80000000 for internal use
    assert newrecord.flags2 == 8
    assert newrecord.eid == "WarGlobalCopyNew"
    assert newrecord.eid == "WArGlobalCopyNew"
    assert newrecord.format == 's'
    assert newrecord.format != 'S'
    assert newrecord.value == 9.0

    print "GLOB:Finished testing"

def assertCLAS(Current, newMod):
    record = Current.LoadOrderMods[0].CLAS[0]

    assert record.fid == ('Oblivion.esm', 0x09712F)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 7024151
    assert record.eid == "SE32Smith"
    assert record.eid == "SE32SmiTh"
    assert record.full == "Vitharn Smith"
    assert record.full != "Vitharn SmiTh"
    assert record.description == None
    assert record.iconPath == None
    assert record.primary1 == 0
    assert record.primary2 == 5
    assert record.specialization == 0
    assert record.major1 == 12
    assert record.major2 == 30
    assert record.major3 == 14
    assert record.major4 == 15
    assert record.major5 == 16
    assert record.major6 == 29
    assert record.major7 == 18
    assert record.flags == 0
    assert record.services == 0
    assert record.trainSkill == 0
    assert record.trainLevel == 0
    assert record.unused1 == [0,0]

    record = newMod.create_CLAS()

    record.flags1 = 0x0102
    record.flags2 = 0x0201
    record.eid = "WarCLASTest"
    record.full = "Waruddar! RARGH!"
    record.description = "This is just a very long and quick test of a string that is absolutely pointless for the vast majority of cases.!!!"
    record.iconPath = r"ICON\asdf.ico"
    record.primary1 = 8
    record.primary2 = 9
    record.specialization = 1
    record.major1 = 1
    record.major2 = 2
    record.major3 = 3
    record.major4 = 4
    record.major5 = 5
    record.major6 = 6
    record.major7 = 7
    record.flags = 0x07
    record.services = 0x08
    record.trainSkill = 13
    record.trainLevel = 60
    record.unused1 = [0x01, 0xFF]

    assert record.fid == ('RegressionTests.esp', 0x001006)
    assert record.flags1 == 0x0102
    assert record.flags2 == 0x0201
    assert record.eid == "WarCLASTest"
    assert record.eid == "WarCLAsTest"
    assert record.full == "Waruddar! RARGH!"
    assert record.full != "Waruddar! RaRGH!"
    assert record.description == "This is just a very long and quick test of a string that is absolutely pointless for the vast majority of cases.!!!"
    assert record.description != "This is just A very long and quick test of a string that is absolutely pointless for the vast majority of cases.!!!"
    assert record.iconPath == r"ICON\asdf.ico"
    assert record.iconPath == r"iCoN\asDf.ico" #should be case insensitive
    assert record.primary1 == 8
    assert record.primary2 == 9
    assert record.specialization == 1
    assert record.major1 == 1
    assert record.major2 == 2
    assert record.major3 == 3
    assert record.major4 == 4
    assert record.major5 == 5
    assert record.major6 == 6
    assert record.major7 == 7
    assert record.flags == 0x07
    assert record.services == 0x08
    assert record.trainSkill == 13
    assert record.trainLevel == 60
    assert record.unused1 == [0x01, 0xFF]

    record = Current.LoadOrderMods[0].CLAS[0]
    record = record.CopyAsOverride(newMod)

    assert record.fid == ('Oblivion.esm', 0x09712F)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 7024151
    assert record.eid == "SE32Smith"
    assert record.eid == "SE32SmiTh"
    assert record.full == "Vitharn Smith"
    assert record.full != "Vitharn SmiTh"
    assert record.description == None
    assert record.iconPath == None
    assert record.primary1 == 0
    assert record.primary2 == 5
    assert record.specialization == 0
    assert record.major1 == 12
    assert record.major2 == 30
    assert record.major3 == 14
    assert record.major4 == 15
    assert record.major5 == 16
    assert record.major6 == 29
    assert record.major7 == 18
    assert record.flags == 0
    assert record.services == 0
    assert record.trainSkill == 0
    assert record.trainLevel == 0
    assert record.unused1 == [0,0]

    record.flags1 = 0x0103
    record.flags2 = 0x0202
    record.eid = "WarCLASCopy"
    record.full = "War! RARGH!"
    record.description = "This is just a very short test"
    record.iconPath = r"ICON2\asdf.ico"
    record.primary1 = 10
    record.primary2 = 11
    record.specialization = 5
    record.major1 = 12
    record.major2 = 13
    record.major3 = 14
    record.major4 = 15
    record.major5 = 16
    record.major6 = 17
    record.major7 = 18
    record.flags = 0x10
    record.services = 0x11
    record.trainSkill = 20
    record.trainLevel = 30
    record.unused1 = [0x50, 0x0F]

    assert record.fid == ('Oblivion.esm', 0x09712F)
    assert record.flags1 == 0x0103
    assert record.flags2 == 0x0202
    assert record.eid == "WarCLASCopy"
    assert record.eid == "WarCLaSCopy"
    assert record.full == "War! RARGH!"
    assert record.full != "War! RaRGH!"
    assert record.description == "This is just a very short test"
    assert record.description != "This is just A very short test"
    assert record.iconPath == r"ICON2\asdf.ico"
    assert record.iconPath == r"iCoN2\asDf.ico" #should be case insensitive
    assert record.primary1 == 10
    assert record.primary2 == 11
    assert record.specialization == 5
    assert record.major1 == 12
    assert record.major2 == 13
    assert record.major3 == 14
    assert record.major4 == 15
    assert record.major5 == 16
    assert record.major6 == 17
    assert record.major7 == 18
    assert record.flags == 0x10
    assert record.services == 0x11
    assert record.trainSkill == 20
    assert record.trainLevel == 30
    assert record.unused1 == [0x50, 0x0F]

    record = Current.LoadOrderMods[0].CLAS[0]
    assert record.fid == ('Oblivion.esm', 0x09712F)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 7024151
    assert record.eid == "SE32Smith"
    assert record.eid == "SE32SmiTh"
    assert record.full == "Vitharn Smith"
    assert record.full != "Vitharn SmiTh"
    assert record.description == None
    assert record.iconPath == None
    assert record.primary1 == 0
    assert record.primary2 == 5
    assert record.specialization == 0
    assert record.major1 == 12
    assert record.major2 == 30
    assert record.major3 == 14
    assert record.major4 == 15
    assert record.major5 == 16
    assert record.major6 == 29
    assert record.major7 == 18
    assert record.flags == 0
    assert record.services == 0
    assert record.trainSkill == 0
    assert record.trainLevel == 0
    assert record.unused1 == [0,0]

    record = record.CopyAsNew(newMod)

    assert record.fid == ('RegressionTests.esp', 0x001007)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 7024151
    assert record.eid == "SE32Smith"
    assert record.eid == "SE32SmiTh"
    assert record.full == "Vitharn Smith"
    assert record.full != "Vitharn SmiTh"
    assert record.description == None
    assert record.iconPath == None
    assert record.primary1 == 0
    assert record.primary2 == 5
    assert record.specialization == 0
    assert record.major1 == 12
    assert record.major2 == 30
    assert record.major3 == 14
    assert record.major4 == 15
    assert record.major5 == 16
    assert record.major6 == 29
    assert record.major7 == 18
    assert record.flags == 0
    assert record.services == 0
    assert record.trainSkill == 0
    assert record.trainLevel == 0
    assert record.unused1 == [0,0]

    record.flags1 = 0x0103
    record.flags2 = 0x0202
    record.eid = "WarCLASAsNew"
    record.full = "War3! RARGH!"
    record.description = "This is a very short test"
    record.iconPath = r"ICON21\asdf.ico"
    record.primary1 = 101
    record.primary2 = 111
    record.specialization = 51
    record.major1 = 121
    record.major2 = 131
    record.major3 = 141
    record.major4 = 151
    record.major5 = 161
    record.major6 = 171
    record.major7 = 181
    record.flags = 0x101
    record.services = 0x111
    record.trainSkill = -1
    record.trainLevel = 233
    record.unused1 = [0x80, 0x2F]

    assert record.fid == ('RegressionTests.esp', 0x001007)
    assert record.flags1 == 0x0103
    assert record.flags2 == 0x0202
    assert record.eid == "WarCLASAsNew"
    assert record.eid == "WarCLaSAsNew"
    assert record.full == "War3! RARGH!"
    assert record.full != "War3! RaRGH!"
    assert record.description == "This is a very short test"
    assert record.description != "This is A very short test"
    assert record.iconPath == r"ICON21\asdf.ico"
    assert record.iconPath == r"iCoN21\asDf.ico" #should be case insensitive
    assert record.primary1 == 101
    assert record.primary2 == 111
    assert record.specialization == 51
    assert record.major1 == 121
    assert record.major2 == 131
    assert record.major3 == 141
    assert record.major4 == 151
    assert record.major5 == 161
    assert record.major6 == 171
    assert record.major7 == 181
    assert record.flags == 0x101
    assert record.services == 0x111
    assert record.trainSkill == -1
    assert record.trainLevel == 233
    assert record.unused1 == [0x80, 0x2F]

    record = Current.LoadOrderMods[0].CLAS[0]
    assert record.fid == ('Oblivion.esm', 0x09712F)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 7024151
    assert record.eid == "SE32Smith"
    assert record.eid == "SE32SmiTh"
    assert record.full == "Vitharn Smith"
    assert record.full != "Vitharn SmiTh"
    assert record.description == None
    assert record.iconPath == None
    assert record.primary1 == 0
    assert record.primary2 == 5
    assert record.specialization == 0
    assert record.major1 == 12
    assert record.major2 == 30
    assert record.major3 == 14
    assert record.major4 == 15
    assert record.major5 == 16
    assert record.major6 == 29
    assert record.major7 == 18
    assert record.flags == 0
    assert record.services == 0
    assert record.trainSkill == 0
    assert record.trainLevel == 0
    assert record.unused1 == [0,0]

    print "CLAS:Finished testing"

def assertFACT(Current, newMod):
    record = Current.LoadOrderMods[0].FACT[9]

    assert record.fid == ('Oblivion.esm', 0x080D18)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 2829337
    assert record.eid == "SERooftopClubFaction"
    assert record.eid == "SERoofTopClubFaction"
    assert record.full == "Rooftop Club"
    assert record.full != "RoofTop Club"
    assert record.flags == 1
    assert record.crimeGoldMultiplier == 1.0
    assert len(record.relations) == 1
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x080D18)
    assert relation.mod == 15
    assert len(record.ranks) == 1
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'Fighter'
    assert rank.male != 'FiGhter'
    assert rank.female == 'Fighter'
    assert rank.female != 'FigHter'
    assert rank.insigniaPath == None

    record = newMod.create_FACT()

    record.flags1 = 0x0106
    record.flags2 = 0x0207
    record.eid = "WarFACTTest"
    record.full = "RARGH!111!1!"
    record.flags = 0x4
    record.crimeGoldMultiplier = 16.1

    relation = record.create_relation()
    relation.faction = FormID('Oblivion.esm', 0x123456)
    relation.mod = 20

    relation = record.create_relation()
    relation.faction = FormID('Oblivion.esm', 0x789123)
    relation.mod = 16

    rank = record.create_rank()
    rank.rank = 0
    rank.male = "male_name0"
    rank.female = "female_name0"
    rank.insigniaPath = r"insignia\asdf.ico"

    rank = record.create_rank()
    rank.rank = 1
    rank.male = "male_name1"
    rank.female = "female_name1"
    rank.insigniaPath = r"insignia1\asdf.ico"

    assert record.fid == ('RegressionTests.esp', 0x001008)
    assert record.flags1 == 0x0106
    assert record.flags2 == 0x0207
    assert record.eid == "WarFACTTest"
    assert record.eid == "WarFACtTest"
    assert record.full == "RARGH!111!1!"
    assert record.full != "RaRGH!111!1!"
    assert record.flags == 0x4
    assert record.crimeGoldMultiplier == 16.1

    assert len(record.relations) == 2
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x123456)
    assert relation.mod == 20
    relation = record.relations[1]
    assert relation.faction == ('Oblivion.esm',0x789123)
    assert relation.mod == 16

    assert len(record.ranks) == 2
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'male_name0'
    assert rank.male != 'male_nAme0'
    assert rank.female == 'female_name0'
    assert rank.female != 'female_nAme0'
    assert rank.insigniaPath == r"insignia\asdf.ico"
    assert rank.insigniaPath == r"insigniA\asdf.ico"
    rank = record.ranks[1]
    assert rank.rank == 1
    assert rank.male == 'male_name1'
    assert rank.male != 'mAle_name1'
    assert rank.female == 'female_name1'
    assert rank.female != 'femAle_name1'
    assert rank.insigniaPath == r"insignia1\asdf.ico"
    assert rank.insigniaPath == r"insIgnia1\asdf.ico"

    record = Current.LoadOrderMods[0].FACT[9]
    record = record.CopyAsOverride(newMod)

    assert record.fid == ('Oblivion.esm', 0x080D18)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 2829337
    assert record.eid == "SERooftopClubFaction"
    assert record.eid == "SERoofTopClubFaction"
    assert record.full == "Rooftop Club"
    assert record.full != "RoofTop Club"
    assert record.flags == 1
    assert record.crimeGoldMultiplier == 1.0
    assert len(record.relations) == 1
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x080D18)
    assert relation.mod == 15
    assert len(record.ranks) == 1
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'Fighter'
    assert rank.male != 'FiGhter'
    assert rank.female == 'Fighter'
    assert rank.female != 'FigHter'
    assert rank.insigniaPath == None

    record.flags1 = 0x0101
    record.flags2 = 0x0201
    record.eid = "WarFACTCopy"
    record.full = "RARGH!"
    record.flags = 0x6
    record.crimeGoldMultiplier = 13.1

    relation = record.create_relation()
    relation.faction = FormID('Oblivion.esm', 0x133456)
    relation.mod = 20

    relation = record.create_relation()
    relation.faction = FormID('Oblivion.esm', 0x799123)
    relation.mod = 16

    rank = record.create_rank()
    rank.rank = 0
    rank.male = "male_name0"
    rank.female = "female_name0"
    rank.insigniaPath = r"insignia\asdf.ico"

    rank = record.create_rank()
    rank.rank = 1
    rank.male = "male_name1"
    rank.female = "female_name1"
    rank.insigniaPath = r"insignia1\asdf.ico"

    assert record.fid == ('Oblivion.esm', 0x080D18)
    assert record.flags1 == 0x0101
    assert record.flags2 == 0x0201
    assert record.eid == "WarFACTCopy"
    assert record.eid == "WaRFACTCopy"
    assert record.full == "RARGH!"
    assert record.full != "RaRGH!"
    assert record.flags == 0x6
    assert record.crimeGoldMultiplier == 13.1
    assert len(record.relations) == 3
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x080D18)
    assert relation.mod == 15
    relation = record.relations[1]
    assert relation.faction == ('Oblivion.esm',0x133456)
    assert relation.mod == 20
    relation = record.relations[2]
    assert relation.faction == ('Oblivion.esm',0x799123)
    assert relation.mod == 16
    assert len(record.ranks) == 3
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'Fighter'
    assert rank.male != 'FiGhter'
    assert rank.female == 'Fighter'
    assert rank.female != 'FigHter'
    assert rank.insigniaPath == None
    rank = record.ranks[1]
    assert rank.rank == 0
    assert rank.male == 'male_name0'
    assert rank.male != 'male_nAme0'
    assert rank.female == 'female_name0'
    assert rank.female != 'female_nAme0'
    assert rank.insigniaPath == r"insignia\asdf.ico"
    assert rank.insigniaPath == r"insigniA\asdf.ico"
    rank = record.ranks[2]
    assert rank.rank == 1
    assert rank.male == 'male_name1'
    assert rank.male != 'mAle_name1'
    assert rank.female == 'female_name1'
    assert rank.female != 'femAle_name1'
    assert rank.insigniaPath == r"insignia1\asdf.ico"
    assert rank.insigniaPath == r"insIgnia1\asdf.ico"

    record = Current.LoadOrderMods[0].FACT[9]
    assert record.fid == ('Oblivion.esm', 0x080D18)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 2829337
    assert record.eid == "SERooftopClubFaction"
    assert record.eid == "SERoofTopClubFaction"
    assert record.full == "Rooftop Club"
    assert record.full != "RoofTop Club"
    assert record.flags == 1
    assert record.crimeGoldMultiplier == 1.0
    assert len(record.relations) == 1
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x080D18)
    assert relation.mod == 15
    assert len(record.ranks) == 1
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'Fighter'
    assert rank.male != 'FiGhter'
    assert rank.female == 'Fighter'
    assert rank.female != 'FigHter'
    assert rank.insigniaPath == None

    record = record.CopyAsNew(newMod)

    assert record.fid == ('RegressionTests.esp', 0x001009)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 2829337
    assert record.eid == "SERooftopClubFaction"
    assert record.eid == "SERoofTopClubFaction"
    assert record.full == "Rooftop Club"
    assert record.full != "RoofTop Club"
    assert record.flags == 1
    assert record.crimeGoldMultiplier == 1.0
    assert len(record.relations) == 1
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x080D18)
    assert relation.mod == 15
    assert len(record.ranks) == 1
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'Fighter'
    assert rank.male != 'FiGhter'
    assert rank.female == 'Fighter'
    assert rank.female != 'FigHter'
    assert rank.insigniaPath == None

    record.flags1 = 0x0101
    record.flags2 = 0x0201
    record.eid = "WarFACTCopy2"
    record.full = "RARGH2!"
    record.flags = 0x6
    record.crimeGoldMultiplier = 13.1

    relation = record.create_relation()
    relation.faction = FormID('Oblivion.esm', 0x133456)
    relation.mod = 20

    relation = record.create_relation()
    relation.faction = FormID('Oblivion.esm', 0x799123)
    relation.mod = 16

    rank = record.create_rank()
    rank.rank = 0
    rank.male = "male_name0"
    rank.female = "female_name0"
    rank.insigniaPath = r"insignia\asdf.ico"

    rank = record.create_rank()
    rank.rank = 1
    rank.male = "male_name1"
    rank.female = "female_name1"
    rank.insigniaPath = r"insignia1\asdf.ico"

    assert record.fid == ('RegressionTests.esp', 0x001009)
    assert record.flags1 == 0x0101
    assert record.flags2 == 0x0201
    assert record.eid == "WarFACTCopy2"
    assert record.eid == "WaRFACTCopy2"
    assert record.full == "RARGH2!"
    assert record.full != "RaRGH2!"
    assert record.flags == 0x6
    assert record.crimeGoldMultiplier == 13.1
    assert len(record.relations) == 3
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x080D18)
    assert relation.mod == 15
    relation = record.relations[1]
    assert relation.faction == ('Oblivion.esm',0x133456)
    assert relation.mod == 20
    relation = record.relations[2]
    assert relation.faction == ('Oblivion.esm',0x799123)
    assert relation.mod == 16
    assert len(record.ranks) == 3
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'Fighter'
    assert rank.male != 'FiGhter'
    assert rank.female == 'Fighter'
    assert rank.female != 'FigHter'
    assert rank.insigniaPath == None
    rank = record.ranks[1]
    assert rank.rank == 0
    assert rank.male == 'male_name0'
    assert rank.male != 'male_nAme0'
    assert rank.female == 'female_name0'
    assert rank.female != 'female_nAme0'
    assert rank.insigniaPath == r"insignia\asdf.ico"
    assert rank.insigniaPath == r"insigniA\asdf.ico"
    rank = record.ranks[2]
    assert rank.rank == 1
    assert rank.male == 'male_name1'
    assert rank.male != 'mAle_name1'
    assert rank.female == 'female_name1'
    assert rank.female != 'femAle_name1'
    assert rank.insigniaPath == r"insignia1\asdf.ico"
    assert rank.insigniaPath == r"insIgnia1\asdf.ico"

    record = Current.LoadOrderMods[0].FACT[9]
    assert record.fid == ('Oblivion.esm', 0x080D18)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 2829337
    assert record.eid == "SERooftopClubFaction"
    assert record.eid == "SERoofTopClubFaction"
    assert record.full == "Rooftop Club"
    assert record.full != "RoofTop Club"
    assert record.flags == 1
    assert record.crimeGoldMultiplier == 1.0
    assert len(record.relations) == 1
    relation = record.relations[0]
    assert relation.faction == ('Oblivion.esm',0x080D18)
    assert relation.mod == 15
    assert len(record.ranks) == 1
    rank = record.ranks[0]
    assert rank.rank == 0
    assert rank.male == 'Fighter'
    assert rank.male != 'FiGhter'
    assert rank.female == 'Fighter'
    assert rank.female != 'FigHter'
    assert rank.insigniaPath == None

    print "FACT:Finished testing"

def assertHAIR(Current, newMod):
    record = Current.LoadOrderMods[0].HAIR[0]

    assert record.fid == ('Oblivion.esm', 0x0C4821)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1712643
    assert record.eid == "KhajiitWisps"
    assert record.eid == "KhAjiitWisps"
    assert record.full == "Wisps"
    assert record.full != "WiSps"
    assert record.modPath == r"Characters\Hair\KhajiitWisps.NIF"
    assert record.modPath == r"ChaRactErs\HAir\KhajIitWisps.NiF" #Should be case insensitive
    assert record.modb == 0.0
    assert record.modt_p == []
    assert record.iconPath == r"Characters\Hair\Mane.dds"
    assert record.iconPath == r"ChAraCterS\HaIr\ManE.dDs" #Should be case insensitive
    assert record.flags == 8

    record = newMod.create_HAIR()
    record.flags1 = 0x0102
    record.flags2 = 0x0201
    record.eid = "HAIRWarTest"
    record.full = "Fancy HAIR"
    record.modPath = r"Blah\hay\1.nif"
    record.modb = 2.56
    record.modt_p = [0x00, 0xFF, 0xFF]
    record.iconPath = r"hair\path\test.dds"
    record.flags = 15

    assert record.fid == ('RegressionTests.esp', 0x00100A)
    assert record.flags1 == 0x0102
    assert record.flags2 == 0x0201
    assert record.eid == "HAIRWarTest"
    assert record.eid == "HaIRWarTest"
    assert record.full == "Fancy HAIR"
    assert record.full != "Fancy HaIR"
    assert record.modPath == r"Blah\hay\1.nif"
    assert record.modPath == r"BlAh\hAy\1.Nif" #Should be case insensitive
    assert record.modb == 2.56
    assert record.modt_p == [0x00, 0xFF, 0xFF]
    assert record.iconPath == r"hair\path\test.dds"
    assert record.iconPath == r"hAiR\pATh\tEst.ddS" #Should be case insensitive
    assert record.flags == 15

    record = Current.LoadOrderMods[0].HAIR[0]
    record = record.CopyAsOverride(newMod)

    assert record.fid == ('Oblivion.esm', 0x0C4821)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1712643
    assert record.eid == "KhajiitWisps"
    assert record.eid == "KhAjiitWisps"
    assert record.full == "Wisps"
    assert record.full != "WiSps"
    assert record.modPath == r"Characters\Hair\KhajiitWisps.NIF"
    assert record.modPath == r"ChaRactErs\HAir\KhajIitWisps.NiF" #Should be case insensitive
    assert record.modb == 0.0
    assert record.modt_p == []
    assert record.iconPath == r"Characters\Hair\Mane.dds"
    assert record.iconPath == r"ChAraCterS\HaIr\ManE.dDs" #Should be case insensitive
    assert record.flags == 8

    record.flags1 = 0x0103
    record.flags2 = 0x0202
    record.eid = "HAIRWarTest2"
    record.full = "Fancy2 HAIR"
    record.modPath = r"Blah\hay\2.nif"
    record.modb = 2.16
    record.modt_p = [0x0F, 0x1F, 0xF4]
    record.iconPath = r"path\test2.dds"
    record.flags = 17

    assert record.fid == ('Oblivion.esm', 0x0C4821)
    assert record.flags1 == 0x0103
    assert record.flags2 == 0x0202
    assert record.eid == "HAIRWarTest2"
    assert record.eid == "HaIRWarTest2"
    assert record.full == "Fancy2 HAIR"
    assert record.full != "Fancy2 HaIR"
    assert record.modPath == r"Blah\hay\2.nif"
    assert record.modPath == r"BlAh\hAy\2.Nif" #Should be case insensitive
    assert record.modb == 2.16
    assert record.modt_p == [0x0F, 0x1F, 0xF4]
    assert record.iconPath == r"path\test2.dds"
    assert record.iconPath == r"paTH\teST2.dds" #Should be case insensitive
    assert record.flags == 17

    record = Current.LoadOrderMods[0].HAIR[0]

    assert record.fid == ('Oblivion.esm', 0x0C4821)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1712643
    assert record.eid == "KhajiitWisps"
    assert record.eid == "KhAjiitWisps"
    assert record.full == "Wisps"
    assert record.full != "WiSps"
    assert record.modPath == r"Characters\Hair\KhajiitWisps.NIF"
    assert record.modPath == r"ChaRactErs\HAir\KhajIitWisps.NiF" #Should be case insensitive
    assert record.modb == 0.0
    assert record.modt_p == []
    assert record.iconPath == r"Characters\Hair\Mane.dds"
    assert record.iconPath == r"ChAraCterS\HaIr\ManE.dDs" #Should be case insensitive
    assert record.flags == 8

    record = record.CopyAsNew(newMod)

    assert record.fid == ('RegressionTests.esp', 0x00100B)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1712643
    assert record.eid == "KhajiitWisps"
    assert record.eid == "KhAjiitWisps"
    assert record.full == "Wisps"
    assert record.full != "WiSps"
    assert record.modPath == r"Characters\Hair\KhajiitWisps.NIF"
    assert record.modPath == r"ChaRactErs\HAir\KhajIitWisps.NiF" #Should be case insensitive
    assert record.modb == 0.0
    assert record.modt_p == []
    assert record.iconPath == r"Characters\Hair\Mane.dds"
    assert record.iconPath == r"ChAraCterS\HaIr\ManE.dDs" #Should be case insensitive
    assert record.flags == 8

    record.flags1 = 0x0303
    record.flags2 = 0x0102
    record.eid = "HAIRWarTest2CopyNew"
    record.full = "Fancy2 CopyNew"
    record.modPath = r"Blah\CopyNew\2.nif"
    record.modb = 3.16
    record.modt_p = [0x0F, 0x1F, 0xF4]
    record.iconPath = r"CopyNew\test2.dds"
    record.flags = 27

    assert record.fid == ('RegressionTests.esp', 0x00100B)
    assert record.flags1 == 0x0303
    assert record.flags2 == 0x0102
    assert record.eid == "HAIRWarTest2CopyNew"
    assert record.eid == "HaIRWarTest2CopyNew"
    assert record.full == "Fancy2 CopyNew"
    assert record.full != "FAncy2 CopyNew"
    assert record.modPath == r"Blah\CopyNew\2.nif"
    assert record.modPath == r"BlAh\CoPyNew\2.Nif" #Should be case insensitive
    assert record.modb == 3.16
    assert record.modt_p == [0x0F, 0x1F, 0xF4]
    assert record.iconPath == r"CopyNew\test2.dds"
    assert record.iconPath == r"COPyNew\test2.dds" #Should be case insensitive
    assert record.flags == 27

    print "HAIR:Finished testing"

def assertEYES(Current, newMod):
    record = Current.LoadOrderMods[0].EYES[0]

    assert record.fid == ('Oblivion.esm', 0x05FA43)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1714717
    assert record.eid == "eyeOrdered"
    assert record.eid == "eYeOrdered"
    assert record.full == "Order"
    assert record.full != "ORder"
    assert record.iconPath == r"Characters\Eyes\EyeOrder.dds"
    assert record.iconPath == r"Characters\EyEs\EyeOrder.dDs" #Should be case insensitive
    assert record.flags == 0

    record = newMod.create_EYES()

    record.flags1 = 0x0102
    record.flags2 = 0x0201
    record.eid = "EYESWarTest"
    record.full = "Fancy EYES"
    record.iconPath = r"EYES\p\nath\test.dds"
    record.flags = 15

    assert record.fid == ('RegressionTests.esp', 0x00100C)
    assert record.flags1 == 0x0102
    assert record.flags2 == 0x0201
    assert record.eid == "EYESWarTest"
    assert record.eid == "EYeSWarTest"
    assert record.full == "Fancy EYES"
    assert record.full != "FAncy EYES"
    assert record.iconPath == r"EYES\p\nath\test.dds"
    assert record.iconPath == r"EYES\p\nath\tEst.dds" #Should be case insensitive
    assert record.flags == 15

    record = Current.LoadOrderMods[0].EYES[0]
    record = record.CopyAsOverride(newMod)

    assert record.fid == ('Oblivion.esm', 0x05FA43)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1714717
    assert record.eid == "eyeOrdered"
    assert record.eid == "eYeOrdered"
    assert record.full == "Order"
    assert record.full != "ORder"
    assert record.iconPath == r"Characters\Eyes\EyeOrder.dds"
    assert record.iconPath == r"Characters\EyEs\EyeOrder.dDs" #Should be case insensitive
    assert record.flags == 0

    record.flags1 = 0x0104
    record.flags2 = 0x0206
    record.eid = "EYESWarTest2"
    record.full = "Fancy EYES2"
    record.iconPath = r"EYES2\p\nath\test.dds"
    record.flags = 17

    assert record.fid == ('Oblivion.esm', 0x05FA43)
    assert record.flags1 == 0x0104
    assert record.flags2 == 0x0206
    assert record.eid == "EYESWarTest2"
    assert record.eid == "EYeSWarTest2"
    assert record.full == "Fancy EYES2"
    assert record.full != "FAncy EYES2"
    assert record.iconPath == r"EYES2\p\nath\test.dds"
    assert record.iconPath == r"EYES2\p\nath\tEst.dds" #Should be case insensitive
    assert record.flags == 17

    record = Current.LoadOrderMods[0].EYES[0]

    assert record.fid == ('Oblivion.esm', 0x05FA43)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1714717
    assert record.eid == "eyeOrdered"
    assert record.eid == "eYeOrdered"
    assert record.full == "Order"
    assert record.full != "ORder"
    assert record.iconPath == r"Characters\Eyes\EyeOrder.dds"
    assert record.iconPath == r"Characters\EyEs\EyeOrder.dDs" #Should be case insensitive
    assert record.flags == 0


    record = record.CopyAsNew(newMod)

    assert record.fid == ('RegressionTests.esp', 0x00100D)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1714717
    assert record.eid == "eyeOrdered"
    assert record.eid == "eYeOrdered"
    assert record.full == "Order"
    assert record.full != "ORder"
    assert record.iconPath == r"Characters\Eyes\EyeOrder.dds"
    assert record.iconPath == r"Characters\EyEs\EyeOrder.dDs" #Should be case insensitive
    assert record.flags == 0

    record.flags1 = 0x0107
    record.flags2 = 0x0203
    record.eid = "EYESWarTest3"
    record.full = "Fancy EYES3"
    record.iconPath = r"EYES3\p\nath\test.dds"
    record.flags = 19

    assert record.fid == ('RegressionTests.esp', 0x00100D)
    assert record.flags1 == 0x0107
    assert record.flags2 == 0x0203
    assert record.eid == "EYESWarTest3"
    assert record.eid == "EYeSWarTest3"
    assert record.full == "Fancy EYES3"
    assert record.full != "FAncy EYES3"
    assert record.iconPath == r"EYES3\p\nath\test.dds"
    assert record.iconPath == r"EYES3\p\nath\tEst.dds" #Should be case insensitive
    assert record.flags == 19

    print "EYES:Finished testing"

def assertRACE(Current, newMod):
    record = Current.LoadOrderMods[0].RACE[13]

    assert record.fid == ('Oblivion.esm', 0x000D43)
    assert record.flags1 == 0x00000000
    assert record.flags2 == 1712664
    assert record.eid == "Redguard"
    assert record.eid == "REdguard"
    assert record.full == "Redguard"
    assert record.full != "REdguard"
    assert record.text == "The most naturally talented warriors in Tamriel.  In addition to their cultural affinities for many weapon and armor styles, they also have a hardy constitution and a natural resistance to disease and poison."
    assert record.text != "ThE most naturally talented warriors in Tamriel.  In addition to their cultural affinities for many weapon and armor styles, they also have a hardy constitution and a natural resistance to disease and poison."
    assert len(record.spells) == 3
    assert record.spells == [('Oblivion.esm', 0x047AE6), ('Oblivion.esm', 0x047AE5), ('Oblivion.esm', 0x047AE7)]
    assert len(record.relations) == 3
    assert record.relations_list == [(('Oblivion.esm',0x0224FC), -5), (('Oblivion.esm',0x000907), -5), (('Oblivion.esm',0x000D43), 5)]
    assert record.skill1 == 13
    assert record.skill1Boost == 10
    assert record.skill2 == 16
    assert record.skill2Boost == 10
    assert record.skill3 == 18
    assert record.skill3Boost == 5
    assert record.skill4 == 27
    assert record.skill4Boost == 5
    assert record.skill5 == 14
    assert record.skill5Boost == 10
    assert record.skill6 == 29
    assert record.skill6Boost == 5
    assert record.skill7 == -1
    assert record.skill7Boost == 0
    assert record.unused1 == [0,0]
    assert record.maleHeight == 1.03
    assert record.femaleHeight == 1.0
    assert record.maleWeight == 1.03
    assert record.femaleWeight == 1.0
    assert record.flags == 1
    assert record.maleVoice == FormID(None,None)
    assert record.femaleVoice == None
    assert record.defaultHairMale == ('Oblivion.esm', 0x64215)
    assert record.defaultHairFemale == ('Oblivion.esm', 0x64210)
    assert record.defaultHairColor == 13
    assert record.mainClamp == None
    assert record.faceClamp == None
    assert record.maleStrength == 50
    assert record.maleIntelligence == 30
    assert record.maleWillpower == 30
    assert record.maleAgility == 40
    assert record.maleSpeed == 40
    assert record.maleEndurance == 50
    assert record.malePersonality == 30
    assert record.maleLuck == 50
    assert record.femaleStrength == 40
    assert record.femaleIntelligence == 30
    assert record.femaleWillpower == 30
    assert record.femaleAgility == 40
    assert record.femaleSpeed == 40
    assert record.femaleEndurance == 50
    assert record.femalePersonality == 40
    assert record.femaleLuck == 50
    assert record.head.modPath == r'Characters\Imperial\HeadHuman.nif'
    assert record.head.modPath == r'CharactErs\Imperial\HeadHuman.nif'
    assert record.head.modb == 0.0
    assert record.head.iconPath == r'Characters\Imperial\HeadHuman.dds'
    assert record.head.iconPath == r'CharactErs\Imperial\HeadHuman.dds'
    assert record.head.modt_p == []
    assert record.maleEars.modPath == r'Characters\Imperial\EarsHuman.nif'
    assert record.maleEars.modPath == r'CharactErs\Imperial\EarsHuman.nif'
    assert record.maleEars.modb == 0.0
    assert record.maleEars.iconPath == r'Characters\Imperial\EarsHuman.dds'
    assert record.maleEars.iconPath == r'CharactErs\Imperial\EarsHuman.dds'
    assert record.maleEars.modt_p == []
    assert record.femaleEars.modPath == r'Characters\Imperial\EarsHuman.nif'
    assert record.femaleEars.modPath == r'CharactErs\Imperial\EarsHuman.nif'
    assert record.femaleEars.modb == 0.0
    assert record.femaleEars.iconPath == r'Characters\Imperial\EarsHuman.dds'
    assert record.femaleEars.iconPath == r'CharactErs\Imperial\EarsHuman.dds'
    assert record.femaleEars.modt_p == []
    assert record.mouth.modPath == r'Characters\Imperial\MouthHuman.nif'
    assert record.mouth.modPath == r'CharactErs\Imperial\MouthHuman.nif'
    assert record.mouth.modb == 0.0
    assert record.mouth.iconPath == r'Characters\Imperial\MouthHuman.dds'
    assert record.mouth.iconPath == r'CharactErs\Imperial\MouthHuman.dds'
    assert record.mouth.modt_p == []
    assert record.teethLower.modPath == r'Characters\Imperial\TeethLowerHuman.nif'
    assert record.teethLower.modPath == r'CharactErs\Imperial\TeethLowerHuman.nif'
    assert record.teethLower.modb == 0.0
    assert record.teethLower.iconPath == r'Characters\Imperial\TeethLowerHuman.dds'
    assert record.teethLower.iconPath == r'CharactErs\Imperial\TeethLowerHuman.dds'
    assert record.teethLower.modt_p == []
    assert record.teethUpper.modPath == r'Characters\Imperial\TeethUpperHuman.nif'
    assert record.teethUpper.modPath == r'CharactErs\Imperial\TeethUpperHuman.nif'
    assert record.teethUpper.modb == 0.0
    assert record.teethUpper.iconPath == r'Characters\Imperial\TeethUpperHuman.dds'
    assert record.teethUpper.iconPath == r'CharactErs\Imperial\TeethUpperHuman.dds'
    assert record.teethUpper.modt_p == []
    assert record.tongue.modPath == r'Characters\Imperial\TongueHuman.nif'
    assert record.tongue.modPath == r'CharactErs\Imperial\TongueHuman.nif'
    assert record.tongue.modb == 0.0
    assert record.tongue.iconPath == r'Characters\Imperial\TongueHuman.dds'
    assert record.tongue.iconPath == r'CharactErs\Imperial\TongueHuman.dds'
    assert record.tongue.modt_p == []
    assert record.leftEye.modPath == r'Characters\Imperial\EyeLeftHuman.nif'
    assert record.leftEye.modPath == r'CharactErs\Imperial\EyeLeftHuman.nif'
    assert record.leftEye.modb == 0.0
    assert record.leftEye.iconPath == None
    assert record.leftEye.modt_p == []
    assert record.rightEye.modPath == r'Characters\Imperial\EyeRightHuman.nif'
    assert record.rightEye.modPath == r'CharactErs\Imperial\EyeRightHuman.nif'
    assert record.rightEye.modb == 0.0
    assert record.rightEye.iconPath == None
    assert record.rightEye.modt_p == []
    assert record.maleTail.modPath == None
    assert record.maleTail.modb == None
    assert record.maleTail.modt_p == []
    assert record.maleUpperBodyPath == r'Characters\Imperial\Male\UpperBodyMale.dds'
    assert record.maleUpperBodyPath == r'CharactErs\Imperial\Male\UpperBodyMale.dds'
    assert record.maleLowerBodyPath == r'Characters\Imperial\Male\LegMale.dds'
    assert record.maleLowerBodyPath == r'CharactErs\Imperial\Male\LegMale.dds'
    assert record.maleHandPath == r'Characters\Imperial\Male\HandMale.dds'
    assert record.maleHandPath == r'CharactErs\Imperial\Male\HandMale.dds'
    assert record.maleFootPath == r'Characters\Imperial\Male\FootMale.dds'
    assert record.maleFootPath == r'CharactErs\Imperial\Male\FootMale.dds'
    assert record.maleTailPath == None
    assert record.femaleTail.modPath == None
    assert record.femaleTail.modb == None
    assert record.femaleTail.modt_p == []
    assert record.femaleUpperBodyPath == r'Characters\Imperial\Female\UpperBodyFemale.dds'
    assert record.femaleUpperBodyPath == r'CharactErs\Imperial\Female\UpperBodyFemale.dds'
    assert record.femaleLowerBodyPath == r'Characters\Imperial\Female\LegFemale.dds'
    assert record.femaleLowerBodyPath == r'CharactErs\Imperial\Female\LegFemale.dds'
    assert record.femaleHandPath == r'Characters\Imperial\Female\HandFemale.dds'
    assert record.femaleHandPath == r'CharactErs\Imperial\Female\HandFemale.dds'
    assert record.femaleFootPath == r'Characters\Imperial\Female\FootFemale.dds'
    assert record.femaleFootPath == r'CharactErs\Imperial\Female\FootFemale.dds'
    assert record.femaleTailPath == None
    assert len(record.hairs) == 20
    assert record.hairs == [('Oblivion.esm', 0x064213), ('Oblivion.esm', 0x18A891), ('Oblivion.esm', 0x0690C2),
                            ('Oblivion.esm', 0x0690BB), ('Oblivion.esm', 0x01DA83), ('Oblivion.esm', 0x01DA82),
                            ('Oblivion.esm', 0x07B792), ('Oblivion.esm', 0x069474), ('Oblivion.esm', 0x069472),
                            ('Oblivion.esm', 0x064C7D), ('Oblivion.esm', 0x064211), ('Oblivion.esm', 0x090475),
                            ('Oblivion.esm', 0x027FF2), ('Oblivion.esm', 0x06420E), ('Oblivion.esm', 0x02C4D0),
                            ('Oblivion.esm', 0x0950EB), ('Oblivion.esm', 0x064215), ('Oblivion.esm', 0x064210),
                            ('Oblivion.esm', 0x064216), ('Oblivion.esm', 0x066F21)]
    assert len(record.eyes) == 3
    assert record.eyes == [('Oblivion.esm', 0x027306), ('Oblivion.esm', 0x027308), ('Oblivion.esm', 0x027309)]
    assert record.fggs_p == [98, 46, 20, 63, 9, 226, 81, 60, 20, 53, 65, 191, 58, 23, 125, 191, 179, 78, 204,
                             191, 25, 242, 74, 191, 32, 76, 30, 58, 49, 50, 113, 62, 203, 44, 247, 191, 240,
                             108, 97, 191, 152, 76, 225, 63, 205, 77, 34, 63, 73, 226, 178, 189, 32, 202, 130,
                             191, 247, 184, 212, 190, 113, 133, 131, 190, 46, 55, 245, 62, 52, 132, 239, 63,
                             136, 53, 57, 63, 182, 97, 116, 63, 112, 1, 138, 191, 92, 26, 220, 187, 24, 246,
                             5, 191, 43, 19, 119, 191, 132, 138, 68, 191, 24, 172, 163, 62, 252, 90, 1, 191,
                             140, 90, 188, 63, 65, 74, 206, 190, 207, 161, 55, 63, 2, 253, 230, 62, 160, 244,
                             224, 59, 41, 72, 149, 191, 219, 53, 5, 190, 0, 120, 180, 57, 180, 6, 175, 191,
                             170, 210, 163, 63, 50, 122, 142, 191, 166, 234, 92, 63, 126, 196, 214, 61, 36,
                             180, 113, 63, 202, 102, 118, 63, 223, 178, 29, 191, 13, 29, 139, 62, 85, 20, 145,
                             62, 47, 160, 50, 62, 147, 100, 145, 62, 215, 20, 189, 63, 81, 162, 165, 191, 228,
                             118, 100, 63]
    assert record.fgga_p == [64, 216, 0, 63, 222, 89, 196, 191, 173, 161, 97, 191, 181, 48, 43, 63, 189, 192,
                             12, 62, 65, 172, 209, 190, 197, 147, 79, 63, 176, 239, 94, 63, 207, 184, 103, 189,
                             165, 253, 131, 191, 176, 215, 137, 62, 76, 65, 149, 191, 189, 216, 9, 191, 150,
                             252, 27, 190, 50, 226, 21, 190, 43, 157, 77, 62, 6, 28, 191, 191, 223, 215, 125,
                             191, 58, 33, 231, 62, 80, 31, 15, 63, 160, 99, 113, 191, 206, 126, 160, 62, 168,
                             128, 40, 63, 29, 219, 152, 190, 192, 175, 21, 191, 160, 201, 103, 191, 43, 160,
                             226, 191, 112, 150, 239, 61, 105, 57, 246, 62, 218, 238, 251, 190]
    assert record.fgts_p == [20, 174, 71, 192, 143, 22, 240, 63, 113, 227, 64, 62, 28, 86, 22, 190, 144, 255,
                             41, 63, 229, 182, 12, 192, 205, 164, 132, 190, 108, 26, 159, 190, 196, 170, 193,
                             63, 230, 152, 55, 190, 165, 96, 4, 192, 141, 138, 35, 192, 81, 91, 157, 62, 63,
                             71, 21, 191, 186, 243, 154, 191, 42, 206, 31, 61, 163, 69, 103, 64, 23, 110, 79,
                             191, 182, 149, 64, 63, 75, 14, 219, 191, 162, 51, 10, 192, 22, 15, 38, 64, 229,
                             202, 204, 190, 204, 13, 205, 63, 196, 249, 144, 64, 76, 98, 164, 63, 50, 194,
                             247, 191, 162, 3, 121, 191, 104, 56, 146, 190, 70, 102, 136, 63, 219, 33, 234,
                             191, 67, 189, 174, 191, 227, 251, 17, 190, 141, 220, 93, 192, 7, 58, 41, 63, 247,
                             217, 210, 190, 42, 227, 131, 190, 2, 25, 83, 63, 50, 245, 167, 61, 182, 156, 145,
                             63, 148, 221, 149, 191, 230, 112, 200, 61, 24, 174, 69, 64, 42, 234, 11, 64, 52,
                             120, 54, 64, 183, 156, 50, 192, 105, 123, 23, 64, 20, 217, 52, 64, 223, 122, 162,
                             191, 101, 153, 48, 191]
    assert record.snam_p == [169, 97]

    record = newMod.create_RACE()
    record.flags1 = 0x0102
    record.flags2 = 0x0201
    record.eid = "RACEWarTest"
    record.full = "Fancy RACE"
    record.text = "BLAH BLAH BLHARGH"
    record.spells = [FormID(0x00000121), FormID(0x00000222)]
    relation = record.create_relation()
    relation.faction = FormID(0x00000800)
    relation.mod = 100
    relation = record.create_relation()
    relation.faction = FormID(0x00000801)
    relation.mod = 50
    relation = record.create_relation()
    relation.faction = FormID(0x00000802)
    relation.mod = 60
    relation = record.create_relation()
    relation.faction = FormID(0x00000803)
    relation.mod = 70
    relations = record.relations
    record.relations = [relations[1],relations[0],relations[2],relations[3]]
    relations_list = record.relations_list
    relations_list.append((FormID('Oblivion.esm', 0x001234),15))
    record.relations_list = relations_list
    record.skill1 = 1
    record.skill1Boost = 11
    record.skill2 = 2
    record.skill2Boost = 12
    record.skill3 = 3
    record.skill3Boost = 13
    record.skill4 = 4
    record.skill4Boost = 14
    record.skill5 = 5
    record.skill5Boost = 15
    record.skill6 = 6
    record.skill6Boost = 16
    record.skill7 = 7
    record.skill7Boost = 17
    record.unused1 = [0x00, 0xFF]
    record.maleHeight = 1.5
    record.femaleHeight = 1.6
    record.maleWeight = 2.1
    record.femaleWeight = 2.2
    record.flags = 0x00000010
    record.maleVoice = FormID(0x00000011)
    record.femaleVoice = FormID(0x00000012)
    record.defaultHairMale = FormID(0x00000013)
    record.defaultHairFemale = FormID(0x00000014)
    record.defaultHairColor = 1
    record.mainClamp = 10.1
    record.faceClamp = 1.2
    record.maleStrength = 25
    record.maleIntelligence = 26
    record.maleWillpower = 27
    record.maleAgility = 28
    record.maleSpeed = 29
    record.maleEndurance = 30
    record.malePersonality = 31
    record.maleLuck = 32
    record.femaleStrength = 51
    record.femaleIntelligence = 52
    record.femaleWillpower = 53
    record.femaleAgility = 54
    record.femaleSpeed = 55
    record.femaleEndurance = 56
    record.femalePersonality = 57
    record.femaleLuck = 58
    record.head.modPath = r"asdf"
    record.head.modb = 1.3
    record.head.iconPath = r"fqeasdf"
    record.head.modt_p = [0x01, 0x10]
    record.maleEars.modPath = r"maleEars"
    record.maleEars.modb = 1.4
    record.maleEars.iconPath = r"maleEarsP"
    record.maleEars.modt_p = [0x01, 0x11]
    record.femaleEars.modPath = r"femaleEars"
    record.femaleEars.modb = 1.5
    record.femaleEars.iconPath = r"femaleEarsP"
    record.femaleEars.modt_p = [0x01, 0x12]
    record.mouth.modPath = r"mouth"
    record.mouth.modb = 1.6
    record.mouth.iconPath = r"mouth\P"
    record.mouth.modt_p = [0x01, 0x13]
    record.teethLower.modPath = r"teeth\Lower"
    record.teethLower.modb = 1.7
    record.teethLower.iconPath = r"teeth\LowerP"
    record.teethLower.modt_p = [0x01, 0x14]
    record.teethUpper.modPath = r"teeth\Upper"
    record.teethUpper.modb = 1.8
    record.teethUpper.iconPath = r"teethUpper\P"
    record.teethUpper.modt_p = [0x01, 0x15]
    record.tongue.modPath = r"tongu\e"
    record.tongue.modb = 1.9
    record.tongue.iconPath = r"tongu\e"
    record.tongue.modt_p = [0x01, 0x16]
    record.leftEye.modPath = r"left\Eye"
    record.leftEye.modb = 2.0
    record.leftEye.iconPath = r"left\Eye"
    record.leftEye.modt_p = [0x01, 0x20]
    record.rightEye.modPath = r"right\Eye"
    record.rightEye.modb = 2.1
    record.rightEye.iconPath = r"right\Eye"
    record.rightEye.modt_p = [0x01, 0x17]
    record.maleTail.modPath = r"maleTail\Model"
    record.maleTail.modb = 2.2
    record.maleTail.modt_p = [0x01, 0x18]
    record.maleUpperBodyPath = r"maleUpperBody\Path"
    record.maleLowerBodyPath = r"maleLowerBody\Path"
    record.maleHandPath = r"maleHand\Path"
    record.maleFootPath = r"maleFoot\Path"
    record.maleTailPath = r"maleTail\Path"
    record.femaleTail.modPath = r"femaleTail\Model"
    record.femaleTail.modb = 2.3
    record.femaleTail.modt_p = [0x01, 0x19]
    record.femaleUpperBodyPath = ""
    record.femaleLowerBodyPath = r"female\Path"
    record.femaleHandPath = r"female\Hand\Path"
    record.femaleFootPath = r"female\Foot\Path"
    record.femaleTailPath = r"female\Tail\Path"
    record.hairs = [FormID(0x00000001), FormID(0x01000802)]
    record.eyes = [FormID(0x00000003), FormID(0x01000804)]
    record.fggs_p = [0x01, 0x20]
    record.fgga_p = [0x01, 0x21]
    record.fgts_p = [0x01, 0x22]
    record.snam_p = [0x01, 0x23]

##    assert record.fid == ('Oblivion.esm', 0x000D43)
##    assert record.flags1 == 0x00000000
##    assert record.flags2 == 1712664
##    assert record.eid == "Redguard"
##    assert record.eid == "REdguard"
##    assert record.full == "Redguard"
##    assert record.full != "REdguard"
##    assert record.text == "The most naturally talented warriors in Tamriel.  In addition to their cultural affinities for many weapon and armor styles, they also have a hardy constitution and a natural resistance to disease and poison."
##    assert record.text != "ThE most naturally talented warriors in Tamriel.  In addition to their cultural affinities for many weapon and armor styles, they also have a hardy constitution and a natural resistance to disease and poison."
##    assert len(record.spells) == 3
##    assert record.spells == [('Oblivion.esm', 0x047AE6), ('Oblivion.esm', 0x047AE5), ('Oblivion.esm', 0x047AE7)]
##    assert len(record.relations) == 3
##    assert record.relations_list == [[('Oblivion.esm',0x0224FC), -5], [('Oblivion.esm',0x000907), -5], [('Oblivion.esm',0x000D43), 5]]
##    assert record.skill1 == 13
##    assert record.skill1Boost == 10
##    assert record.skill2 == 16
##    assert record.skill2Boost == 10
##    assert record.skill3 == 18
##    assert record.skill3Boost == 5
##    assert record.skill4 == 27
##    assert record.skill4Boost == 5
##    assert record.skill5 == 14
##    assert record.skill5Boost == 10
##    assert record.skill6 == 29
##    assert record.skill6Boost == 5
##    assert record.skill7 == -1
##    assert record.skill7Boost == 0
##    assert record.unused1 == [0,0]
##    assert record.maleHeight == 1.03
##    assert record.femaleHeight == 1.0
##    assert record.maleWeight == 1.03
##    assert record.femaleWeight == 1.0
##    assert record.flags == 1
##    assert record.maleVoice == None
##    assert record.femaleVoice == None
##    assert record.defaultHairMale == ('Oblivion.esm', 0x64215)
##    assert record.defaultHairFemale == ('Oblivion.esm', 0x64210)
##    assert record.defaultHairColor == 13
##    assert record.mainClamp == None
##    assert record.faceClamp == None
##    assert record.maleStrength == 50
##    assert record.maleIntelligence == 30
##    assert record.maleWillpower == 30
##    assert record.maleAgility == 40
##    assert record.maleSpeed == 40
##    assert record.maleEndurance == 50
##    assert record.malePersonality == 30
##    assert record.maleLuck == 50
##    assert record.femaleStrength == 40
##    assert record.femaleIntelligence == 30
##    assert record.femaleWillpower == 30
##    assert record.femaleAgility == 40
##    assert record.femaleSpeed == 40
##    assert record.femaleEndurance == 50
##    assert record.femalePersonality == 40
##    assert record.femaleLuck == 50
##    assert record.head.modPath == r'Characters\Imperial\HeadHuman.nif'
##    assert record.head.modPath == r'CharactErs\Imperial\HeadHuman.nif'
##    assert record.head.modb == 0.0
##    assert record.head.iconPath == r'Characters\Imperial\HeadHuman.dds'
##    assert record.head.iconPath == r'CharactErs\Imperial\HeadHuman.dds'
##    assert record.head.modt_p == []
##    assert record.maleEars.modPath == r'Characters\Imperial\EarsHuman.nif'
##    assert record.maleEars.modPath == r'CharactErs\Imperial\EarsHuman.nif'
##    assert record.maleEars.modb == 0.0
##    assert record.maleEars.iconPath == r'Characters\Imperial\EarsHuman.dds'
##    assert record.maleEars.iconPath == r'CharactErs\Imperial\EarsHuman.dds'
##    assert record.maleEars.modt_p == []
##    assert record.femaleEars.modPath == r'Characters\Imperial\EarsHuman.nif'
##    assert record.femaleEars.modPath == r'CharactErs\Imperial\EarsHuman.nif'
##    assert record.femaleEars.modb == 0.0
##    assert record.femaleEars.iconPath == r'Characters\Imperial\EarsHuman.dds'
##    assert record.femaleEars.iconPath == r'CharactErs\Imperial\EarsHuman.dds'
##    assert record.femaleEars.modt_p == []
##    assert record.mouth.modPath == r'Characters\Imperial\MouthHuman.nif'
##    assert record.mouth.modPath == r'CharactErs\Imperial\MouthHuman.nif'
##    assert record.mouth.modb == 0.0
##    assert record.mouth.iconPath == r'Characters\Imperial\MouthHuman.dds'
##    assert record.mouth.iconPath == r'CharactErs\Imperial\MouthHuman.dds'
##    assert record.mouth.modt_p == []
##    assert record.teethLower.modPath == r'Characters\Imperial\TeethLowerHuman.nif'
##    assert record.teethLower.modPath == r'CharactErs\Imperial\TeethLowerHuman.nif'
##    assert record.teethLower.modb == 0.0
##    assert record.teethLower.iconPath == r'Characters\Imperial\TeethLowerHuman.dds'
##    assert record.teethLower.iconPath == r'CharactErs\Imperial\TeethLowerHuman.dds'
##    assert record.teethLower.modt_p == []
##    assert record.teethUpper.modPath == r'Characters\Imperial\TeethUpperHuman.nif'
##    assert record.teethUpper.modPath == r'CharactErs\Imperial\TeethUpperHuman.nif'
##    assert record.teethUpper.modb == 0.0
##    assert record.teethUpper.iconPath == r'Characters\Imperial\TeethUpperHuman.dds'
##    assert record.teethUpper.iconPath == r'CharactErs\Imperial\TeethUpperHuman.dds'
##    assert record.teethUpper.modt_p == []
##    assert record.tongue.modPath == r'Characters\Imperial\TongueHuman.nif'
##    assert record.tongue.modPath == r'CharactErs\Imperial\TongueHuman.nif'
##    assert record.tongue.modb == 0.0
##    assert record.tongue.iconPath == r'Characters\Imperial\TongueHuman.dds'
##    assert record.tongue.iconPath == r'CharactErs\Imperial\TongueHuman.dds'
##    assert record.tongue.modt_p == []
    assert record.leftEye.modPath == r'left\Eye'
    assert record.leftEye.modPath == r'lEft\Eye'
    assert record.leftEye.modb == 2.0
    assert record.leftEye.iconPath == r'left\Eye'
    assert record.leftEye.iconPath == r'lEft\Eye'
    assert record.leftEye.modt_p == [1, 32]
    assert record.rightEye.modPath == r'right\Eye'
    assert record.rightEye.modPath == r'rIght\Eye'
    assert record.rightEye.modb == 2.1
    assert record.rightEye.iconPath == r'right\Eye'
    assert record.rightEye.iconPath == r'rIght\Eye'
    assert record.rightEye.modt_p == [1, 23]
    assert record.maleTail.modPath == r'maleTail\Model'
    assert record.maleTail.modPath == r'mAleTail\Model'
    assert record.maleTail.modb == 2.2
    assert record.maleTail.modt_p == [1, 24]
    assert record.maleUpperBodyPath == r'maleUpperBody\Path'
    assert record.maleUpperBodyPath == r'mAleUpperBody\Path'
    assert record.maleLowerBodyPath == r'maleLowerBody\Path'
    assert record.maleLowerBodyPath == r'mAleLowerBody\Path'
    assert record.maleHandPath == r'maleHand\Path'
    assert record.maleHandPath == r'mAleHand\Path'
    assert record.maleFootPath == r'maleFoot\Path'
    assert record.maleFootPath == r'mAleFoot\Path'
    assert record.maleTailPath == r'maleTail\Path'
    assert record.maleTailPath == r'mAleTail\Path'
    assert record.femaleTail.modPath == r'femaleTail\Model'
    assert record.femaleTail.modPath == r'femAleTail\Model'
    assert record.femaleTail.modb == 2.3
    assert record.femaleTail.modt_p == [1, 25]
    assert record.femaleUpperBodyPath == None
    assert record.femaleLowerBodyPath == r'female\Path'
    assert record.femaleLowerBodyPath == r'femAle\Path'
    assert record.femaleHandPath == r'female\Hand\Path'
    assert record.femaleHandPath == r'femAle\Hand\Path'
    assert record.femaleFootPath == r'female\Foot\Path'
    assert record.femaleFootPath == r'femAle\Foot\Path'
    assert record.femaleTailPath == r'female\Tail\Path'
    assert record.femaleTailPath == r'femAle\Tail\Path'
    assert len(record.hairs) == 2
    assert record.hairs == [('Oblivion.esm', 0x1), ('RegressionTests.esp', 0x802)]
    assert len(record.eyes) == 2
    assert record.eyes == [('Oblivion.esm', 0x3), ('RegressionTests.esp', 0x804)]
    assert record.fggs_p == []
    assert record.fgga_p == []
    assert record.fgts_p == []
    assert record.snam_p == [0x01, 0x23]

    return
    print "RACE:Finished testing"


def assertSOUN(Current, newMod):
    record = Current.LoadOrderMods[0].SOUN[0]

    for record in Current.LoadOrderMods[0].SOUN:
        print
        print "fid     :", record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "soundPath      :", record.soundPath
        print "minDistance    :", record.minDistance
        print "maxDistance    :", record.maxDistance
        print "freqAdjustment :", record.freqAdjustment
        print "unused1        :", record.unused1
        print "flags          :", record.flags
        print "unused2        :", record.unused2
        print "staticAtten    :", record.staticAtten
        print "stopTime       :", record.stopTime
        print "startTime      :", record.startTime
        break
    return

    print "SOUN:Create Record Test"
    newRecord = newMod.create_SOUN()
    d(newRecord)

    print "SOUN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SOUNWarTest"
    print "soundPath..."
    newRecord.soundPath = "Fancy SOUN"
    newRecord.minDistance = 1
    newRecord.maxDistance = 55
    newRecord.freqAdjustment = -3
    newRecord.unused1 = 15
    newRecord.flags = 16
    newRecord.unused2 = [0x01, 0xFF]
    newRecord.staticAtten = 5
    newRecord.stopTime = 12
    newRecord.startTime = 24

    print "SOUN:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "soundPath      :", newRecord.soundPath
    print "minDistance    :", newRecord.minDistance
    print "maxDistance    :", newRecord.maxDistance
    print "freqAdjustment :", newRecord.freqAdjustment
    print "unused1        :", newRecord.unused1
    print "flags          :", newRecord.flags
    print "unused2        :", newRecord.unused2
    print "staticAtten    :", newRecord.staticAtten
    print "stopTime       :", newRecord.stopTime
    print "startTime      :", newRecord.startTime

    print "SOUN:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SOUN:
        record.CopyAsOverride(newMod)

    print "SOUN:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SOUN:
        record.CopyAsNew(newMod)

    print "SOUN:Save Test - TestSOUN.esp"
    newMod.save()
    print "SOUN:Finished testing"

def assertSKIL(Current, newMod):
    record = Current.LoadOrderMods[0].SKIL[0]

    for record in Current.LoadOrderMods[0].SKIL:
        print
        print "fid     :", record.fid
        print "flags1  :", record.flags1
        print "flags2  :", record.flags2
        print "eid     :", record.eid

        print "skill          :", record.skill
        print "description    :", record.description
        print "iconPath       :", record.iconPath
        print "action         :", record.action
        print "attribute      :", record.attribute
        print "specialization :", record.specialization
        print "use0           :", record.use0
        print "use1           :", record.use1
        print "apprentice     :", record.apprentice
        print "journeyman     :", record.journeyman
        print "expert         :", record.expert
        print "master         :", record.master
        break
    return
    print "SKIL:Create Record Test"
    newRecord = newMod.create_SKIL()
    d(newRecord)

    print "SKIL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SKILWarTest"
    print "skill..."
    newRecord.skill = 1
    newRecord.description = "Fancy SKIL"
    newRecord.iconPath = r"ICON\Path\1.dds"
    newRecord.action = 2
    newRecord.attribute = 28
    newRecord.specialization = 1
    newRecord.use0 = 1.0
    newRecord.use1 = 2.0
    newRecord.apprentice = "of nothing"
    newRecord.journeyman = "Little bit"
    newRecord.expert = "Jack of none"
    newRecord.master = "Master of all"

    print "SKIL:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "skill          :", newRecord.skill
    print "description    :", newRecord.description
    print "iconPath       :", newRecord.iconPath
    print "action         :", newRecord.action
    print "attribute      :", newRecord.attribute
    print "specialization :", newRecord.specialization
    print "use0           :", newRecord.use0
    print "use1           :", newRecord.use1
    print "apprentice     :", newRecord.apprentice
    print "journeyman     :", newRecord.journeyman
    print "expert         :", newRecord.expert
    print "master         :", newRecord.master

    print "SKIL:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SKIL:
        record.CopyAsOverride(newMod)

    print "SKIL:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SKIL:
        record.CopyAsNew(newMod)

    print "SKIL:Save Test - TestSKIL.esp"
    newMod.save()
    print "SKIL:Finished testing"

def TestAttrReport():
    Current = ObCollection()
    newMod = Current.addMod("Oblivion.esm")
##    newMod = Current.addMod("Oscuro's_Oblivion_Overhaul.esm")
##    newMod = Current.addMod("Oscuro's_Oblivion_Overhaul.esp")
    Current.load()
    healths = []
    enchantPointss = []
    weights = []
    values = []
    attacks = []
    reachs = []
    speeds = []
    vwratios = []
    infvwratios = []
    wvratios = []
    infwvratios = []
    mgef_fid = {}
    for modFile in Current.LoadOrderMods:
        for record in modFile.MGEF:
            mgef_fid[cast(record.eid, POINTER(c_ulong)).contents.value if record.recordVersion is None else record.mgefCode] = record.fid
    try:
        fMagicDurMagBaseCostMult = Current.LookupRecords('fMagicDurMagBaseCostMult')[0].value or 0.1
    except:
        fMagicDurMagBaseCostMult = 0.1
    try:
        fMagicCostScale = Current.LookupRecords('fMagicCostScale')[0].value or 1.28
    except:
        fMagicCostScale = 1.28
    try:
        fMagicAreaBaseCostMult = Current.LookupRecords('fMagicAreaBaseCostMult')[0].value or 0.15
    except:
        fMagicAreaBaseCostMult = 0.15
    try:
        fMagicRangeTargetCostMult = Current.LookupRecords('fMagicRangeTargetCostMult')[0].value or 1.5
    except:
        fMagicRangeTargetCostMult = 1.5
    from math import floor
    def getValue(record):
        enchantment = None
        if record._Type in ('INGR','ALCH'):
            if record.IsNoAutoCalc:
                value = record.value
            else:
                value = 0
                enchantment = record
        else:
            value = record.value
            if hasattr(record,'enchantment'):
                enchantment = record.enchantment
                if enchantment:
                    enchantment = Current.LookupRecords(enchantment)[0]
        if not enchantment:
            return floor(value)

        enchCost = 0
        for effect in enchantment.effects:
            mgefFid = mgef_fid[effect.name]
            modName = mgefFid[0]
            modFile = Current.LookupModFile(modName)
            mgef = modFile.LookupRecord(mgefFid)
            effectFactor = mgef.baseCost * fMagicDurMagBaseCostMult
            magFactor = pow(effect.magnitude,fMagicCostScale)
            durFactor = max(effect.duration,1)
            areaFactor = max(effect.area * fMagicAreaBaseCostMult,1)
            if effect.IsTarget: rangeFactor = fMagicRangeTargetCostMult
            else: rangeFactor = 1
            enchCost += floor(effectFactor * magFactor * durFactor * areaFactor * rangeFactor) or 1
        if record._Type in ('WEAP','AMMO'):
            enchCost = 0.4 * (enchCost + (record.enchantPoints or 0))
        elif record._Type in ('ARMO','CLOT'):
            if value:
                enchCost = record.enchantPoints or 0
                mod = 0
                for effect in enchantment.effects:
                    mgefFid = mgef_fid[effect.name]
                    modName = mgefFid[0]
                    modFile = Current.LookupModFile(modName)
                    mgef = modFile.LookupRecord(mgefFid)
                    if effect.name in ('WAWA','WABR','NEYE'):
                        mod += floor(mgef.cefBarter * 5)
                    else:
                        mod += mgef.cefBarter * effect.magnitude
                enchCost += mod
        elif record._Type == 'BOOK':
            enchCost = enchCost / 2.0
        value += enchCost
        return floor(value)

    for attr in pickupables:
        for record in getattr(newMod,attr):
            record = Current.LookupRecords(record.fid)[0]
            if hasattr(record,'IsPlayable'):
                if not record.IsPlayable:
                    continue
            if hasattr(record, 'health'):
                if record.health is not None:
                    healths.append(record.health)
            if hasattr(record, 'enchantPoints'):
                if record.enchantPoints is not None:
                    enchantPointss.append(record.enchantPoints)
            if hasattr(record, 'weight'):
                if record.weight is not None:
                    weights.append(record.weight)
            if hasattr(record, 'value'):
                if record.value is not None:
                    values.append(record.value)
            if hasattr(record, 'value') and hasattr(record, 'weight'):
                value = getValue(record)
                if value == 0:
                    vwratios.append(0.0)
                elif record.weight is None or record.weight == 0:
                    infvwratios.append(record.fid)
                else:
                    vwratio = round(value/record.weight,3)
                    vwratios.append(vwratio)
            if hasattr(record, 'weight') and hasattr(record, 'value'):
                value = getValue(record)
                if record.weight is None or record.weight == 0:
                    wvratios.append(0.0)
                elif value == 0:
                    infwvratios.append(record.fid)
                else:
                    wvratio = round(record.weight/value,3)
                    wvratios.append(wvratio)
            if hasattr(record, 'value'):
                if record.value is not None:
                    values.append(record.value)
            if hasattr(record, 'damage'):
                if record.damage is not None:
                    attacks.append(record.damage)
            if hasattr(record, 'reach'):
                if record.reach is not None:
                    reachs.append(record.reach)
            if hasattr(record, 'speed'):
                if record.speed is not None:
                    speeds.append(record.speed)

    print "Min health:", min(healths)
    print "Max health:", max(healths)
    print "Avg health:", sum(healths) / len(healths)

    print "Min enchantPoints:", min(enchantPointss)
    print "Max enchantPoints:", max(enchantPointss)
    print "Avg enchantPoints:", sum(enchantPointss) / len(enchantPointss)

    print "Min weight:", min(weights)
    print "Max weight:", max(weights)
    print "Avg weight:", sum(weights) / len(weights)

    print "Min value:", min(values)
    print "Max value:", max(values)
    print "Avg value:", sum(values) / len(values)

    print "Min attack:", min(attacks)
    print "Max attack:", max(attacks)
    print "Avg attack:", sum(attacks) / len(attacks)

    print "Min reach:", min(reachs)
    print "Max reach:", max(reachs)
    print "Avg reach:", sum(reachs) / len(reachs)

    print "Min Speed:", min(speeds)
    print "Max Speed:", max(speeds)
    print "Avg Speed:", sum(speeds) / len(speeds)

    print "Inf Value/Weight:", len(infvwratios)
    print "Min Value/Weight:", min(vwratios)
    print "Max Value/Weight:", max(vwratios)
    print "Avg Value/Weight:", sum(vwratios) / len(vwratios)

    print "Inf Weight/Value:", len(infwvratios)
    print "Min Weight/Value:", min(wvratios)
    print "Max Weight/Value:", max(wvratios)
    print "Avg Weight/Value:", sum(wvratios) / len(wvratios)
    Current.Close()

def TestCopyAttrs():
    Current = ObCollection()
    srcFile = Current.addMod("Oblivion.esm")
    Current.load()
    origFids = []
    newFids = []
    for armor in srcFile.ARMO:
        clothing = srcFile.create_CLOT()
        for attr in clothing.copyattrs:
            setattr(clothing, attr, getattr(armor, attr))
        origFids.append(armor.fid)
        newFids.append(clothing.fid)
        armor.DeleteRecord()
    print srcFile.UpdateReferences(origFids, newFids)
    srcFile.save()
    Current.Close()

def TestCleanMasters():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("Speedy Disrobe OBSE.esp")
    Current.load()
    print newMod.CleanMasters()
    newMod.save()
    Current.Close()

def TestLoadMasters():
    Current = ObCollection()
    Current.addMod("OOO Patch - Geomancy - Activator.esp")
    Current.load()
    Current.Close()

def TestDeleteRecord():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestDelete.esp")
    Current.load()
    print "Delete Test"
    for record in Current.LoadOrderMods[0].GMST:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].GLOB:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].CLAS:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].FACT:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].HAIR:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].EYES:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].RACE:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].SOUN:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].SKIL:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].MGEF:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].SCPT:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].LTEX:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].ENCH:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].SPEL:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].BSGN:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].ACTI:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].APPA:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].ARMO:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].BOOK:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].CLOT:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].CONT:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].DOOR:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].INGR:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].LIGH:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].MISC:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].STAT:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].GRAS:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].TREE:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].FLOR:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].FURN:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].WEAP:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].AMMO:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].NPC_:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].CREA:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].LVLC:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].SLGM:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].KEYM:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].ALCH:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].SBSP:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].SGST:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].LVLI:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].WTHR:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].CLMT:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].REGN:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].CELL:
        trgCellOver = record.CopyAsOverride(newMod)
        for npcRef in record.ACHR:
            newRecord = npcRef.CopyAsOverride(trgCellOver)
            newRecord.DeleteRecord()
        for creaRef in record.ACRE:
            newRecord = creaRef.CopyAsOverride(trgCellOver)
            newRecord.DeleteRecord()
        for objRef in record.REFR:
            newRecord = objRef.CopyAsOverride(trgCellOver)
            newRecord.DeleteRecord()
        Pgrd = record.PGRD
        if(Pgrd):
            newRecord = Pgrd.CopyAsOverride(trgCellOver)
            newRecord.DeleteRecord()
        trgCellOver.DeleteRecord()

    for record in Current.LoadOrderMods[0].WRLD:
        trgWrldOver = record.CopyAsOverride(newMod)
        road = record.ROAD
        if(road != None):
            newRecord = road.CopyAsOverride(trgWrldOver)
            newRecord.DeleteRecord()
        cell = record.WorldCELL
        if(cell != None):
            trgCellOver = cell.CopyAsOverride(trgWrldOver)
            cLand = cell.LAND
            if(cLand != None):
                newRecord = cLand.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            for npcRef in cell.ACHR:
                newRecord = npcRef.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            for creaRef in cell.ACRE:
                newRecord = creaRef.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            for objRef in cell.REFR:
                newRecord = objRef.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            Pgrd = cell.PGRD
            if(Pgrd != None):
                newRecord = Pgrd.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            trgCellOver.DeleteRecord()
        for wrldCell in record.CELLS:
            trgCellOver = wrldCell.CopyAsOverride(trgWrldOver)
            cLand = wrldCell.LAND
            if(cLand != None):
                newRecord = cLand.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            for npcRef in wrldCell.ACHR:
                newRecord = npcRef.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            for creaRef in wrldCell.ACRE:
                newRecord = creaRef.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            for objRef in wrldCell.REFR:
                newRecord = objRef.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            Pgrd = wrldCell.PGRD
            if(Pgrd != None):
                newRecord = Pgrd.CopyAsOverride(trgCellOver)
                newRecord.DeleteRecord()
            trgCellOver.DeleteRecord()
        trgWrldOver.DeleteRecord()

    for record in Current.LoadOrderMods[0].DIAL:
        newOver = record.CopyAsOverride(newMod)
        for info in record.INFO:
            newRecord = info.CopyAsOverride(newOver)
            newRecord.DeleteRecord()
        newOver.DeleteRecord()
    for record in Current.LoadOrderMods[0].QUST:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].IDLE:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].PACK:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].CSTY:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].LSCR:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].LVSP:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].ANIO:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].WATR:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()
    for record in Current.LoadOrderMods[0].EFSH:
        newRecord = record.CopyAsOverride(newMod)
        newRecord.DeleteRecord()

    print "Delete:Save Test - TestDelete.esp"
    newMod.save()
    Current.Close()

def TestMinimalLoad():
    Current = ObCollection()
    newMod = Current.addMod("Oblivion.esm", MinLoad=True)
    Current.load()
##    newMod.save()
    Current.Close()

def TestFullLoad():
    Current = ObCollection()
    newMod = Current.addMod("Oblivion.esm", MinLoad=False)
    Current.load()
##    newMod.save()
    Current.Close()

def TestReadWriteAll():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestALL.esp", CreateNew=True)
    ##Preloading seems to have almost no effect (~2ms on all simple, CopyAsNew) on speed when later reading...
    ##Not preloading would make it faster if not all records being iterated, and save memory...

    Current.load()

    for record in Current.LoadOrderMods[0].GMST:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod, record.eid + "WarCopy")
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].GLOB:
        record.CopyAsNew(newMod)
        record.CopyAsOverride(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].CLAS:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].FACT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].HAIR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].EYES:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].RACE:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].SOUN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].SKIL:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].MGEF:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod, record.eid + "WarCopy")
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].SCPT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].LTEX:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].ENCH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].SPEL:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].BSGN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].ACTI:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].APPA:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].ARMO:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].BOOK:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].CLOT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].CONT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].DOOR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].INGR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].LIGH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].MISC:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].STAT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].GRAS:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].TREE:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].FLOR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].FURN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].WEAP:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].AMMO:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].NPC_:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].CREA:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].LVLC:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].SLGM:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].KEYM:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].ALCH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].SBSP:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].SGST:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].LVLI:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].WTHR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].CLMT:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].REGN:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].CELL:
        trgCellOver = record.CopyAsOverride(newMod)
        trgCellNew = record.CopyAsNew(newMod)
        for npcRef in record.ACHR:
            npcRef.CopyAsOverride(trgCellOver)
            npcRef.CopyAsNew(trgCellNew)
            npcRef.DeleteRecord()
        for creaRef in record.ACRE:
            creaRef.CopyAsOverride(trgCellOver)
            creaRef.CopyAsNew(trgCellNew)
            creaRef.DeleteRecord()
        for objRef in record.REFR:
            objRef.CopyAsOverride(trgCellOver)
            objRef.CopyAsNew(trgCellNew)
            objRef.DeleteRecord()
        Pgrd = record.PGRD
        if(Pgrd):
            Pgrd.CopyAsOverride(trgCellOver)
            Pgrd.CopyAsNew(trgCellNew)
            Pgrd.DeleteRecord()
        record.DeleteRecord()

    for record in Current.LoadOrderMods[0].WRLD:
        trgWrldOver = record.CopyAsOverride(newMod)
        trgWrldNew = record.CopyAsNew(newMod)
        road = record.ROAD
        if(road != None):
            road.CopyAsOverride(trgWrldOver)
            road.CopyAsNew(trgWrldNew)
            road.DeleteRecord()
        cell = record.WorldCELL
        if(cell != None):
            trgCellOver = cell.CopyAsOverride(trgWrldOver)
            trgCellNew = cell.CopyAsNew(trgWrldNew)
            cLand = cell.LAND
            if(cLand != None):
                cLand.CopyAsOverride(trgCellOver)
                cLand.CopyAsNew(trgCellNew)
                cLand.DeleteRecord()
            for npcRef in cell.ACHR:
                npcRef.CopyAsOverride(trgCellOver)
                npcRef.CopyAsNew(trgCellNew)
                npcRef.DeleteRecord()
            for creaRef in cell.ACRE:
                creaRef.CopyAsOverride(trgCellOver)
                creaRef.CopyAsNew(trgCellNew)
                creaRef.DeleteRecord()
            for objRef in cell.REFR:
                objRef.CopyAsOverride(trgCellOver)
                objRef.CopyAsNew(trgCellNew)
                objRef.DeleteRecord()
            Pgrd = cell.PGRD
            if(Pgrd != None):
                Pgrd.CopyAsOverride(trgCellOver)
                Pgrd.CopyAsNew(trgCellNew)
                Pgrd.DeleteRecord()
            cell.DeleteRecord()
        for wrldCell in record.CELLS:
            trgCellOver = wrldCell.CopyAsOverride(trgWrldOver)
            trgCellNew = wrldCell.CopyAsNew(trgWrldNew)
            cLand = wrldCell.LAND
            if(cLand != None):
                cLand.CopyAsOverride(trgCellOver)
                cLand.CopyAsNew(trgCellNew)
                cLand.DeleteRecord()
            for npcRef in wrldCell.ACHR:
                npcRef.CopyAsOverride(trgCellOver)
                npcRef.CopyAsNew(trgCellNew)
                npcRef.DeleteRecord()
            for creaRef in wrldCell.ACRE:
                creaRef.CopyAsOverride(trgCellOver)
                creaRef.CopyAsNew(trgCellNew)
                creaRef.DeleteRecord()
            for objRef in wrldCell.REFR:
                objRef.CopyAsOverride(trgCellOver)
                objRef.CopyAsNew(trgCellNew)
                objRef.DeleteRecord()
            Pgrd = wrldCell.PGRD
            if(Pgrd != None):
                Pgrd.CopyAsOverride(trgCellOver)
                Pgrd.CopyAsNew(trgCellNew)
                Pgrd.DeleteRecord()
            wrldCell.DeleteRecord()
        record.DeleteRecord()

    for record in Current.LoadOrderMods[0].DIAL:
        newOver = record.CopyAsOverride(newMod)
        newNew = record.CopyAsNew(newMod)
        for info in record.INFO:
            info.CopyAsOverride(newOver)
            info.CopyAsNew(newNew)
            info.DeleteRecord()
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].QUST:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].IDLE:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].PACK:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].CSTY:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].LSCR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].LVSP:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].ANIO:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].WATR:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()
    for record in Current.LoadOrderMods[0].EFSH:
        record.CopyAsOverride(newMod)
        record.CopyAsNew(newMod)
        record.DeleteRecord()

    print "ALL:Save Test - TestALL.esp"

    phonenumber = raw_input(">")
    newMod.save()
    phonenumber = raw_input("!")
    print "ALL:Finished testing"
    Current.Close()

def TestTES4():
    Current = ObCollection()
##    CBash.SetLogging(Current._CollectionIndex, Logging2Callback, 0, 0)
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestTES4.esp")
    Current.load()
    print "TES4:Read Test"
    for modFile in Current.LoadOrderMods:
        record = modFile.TES4
        print
        print "ModName    :", modFile.ModName
        printRecord(record)
        break
    print "TES4:Set Test"
    print "version..."
    newMod.TES4.version = Current.LoadOrderMods[0].TES4.version
    print "numRecords..."
    newMod.TES4.numRecords = Current.LoadOrderMods[0].TES4.numRecords
    print "nextObject..."
    newMod.TES4.nextObject = Current.LoadOrderMods[0].TES4.nextObject
    print "ofst_p..."
    newMod.TES4.ofst_p = Current.LoadOrderMods[0].TES4.ofst_p
    print "dele_p..."
    newMod.TES4.dele_p = Current.LoadOrderMods[0].TES4.dele_p
    print "author..."
    newMod.TES4.author = Current.LoadOrderMods[0].TES4.author
    print "description..."
    newMod.TES4.description = Current.LoadOrderMods[0].TES4.description
    print "masters..."
##    newMod.TES4.masters = Current.LoadOrderMods[0].TES4.masters
    newMod.TES4.masters = ["Oblivion.esm"]
    print "TES4:Set Test Results"
    print "ModName   :", newMod.ModName
    d(newMod.TES4)

    print "TES4:Save Test - TestTES4.esp"
    newMod.save()
    print "TES4:Finished testing"
    Current.Close()

def TestGMST():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestGMST.esp")
    Current.load()
    print "GMST:Read Test"
    for record in Current.LoadOrderMods[0].GMST:
        print
        print "eid     :", record.eid
        printRecord(record)
        break

    print "GMST:Create Record Test"
    newRecord = newMod.create_GMST("sWarString")
    d(newRecord)

    print "GMST:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "value..."
    newRecord.value = "It works!"
    print "GMST:Set Test Results"
    print
    print "eid     :", newRecord.eid
    printRecord(newRecord)

    print "GMST:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].GMST:
        record.CopyAsOverride(newMod)
    print "GMST:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].GMST:
        rec = record.CopyAsNew(newMod, record.eid + 'WarCopy')

    print "GMST:Save Test - TestGMST.esp"
    newMod.save()
    print "GMST:Finished testing"
    Current.Close()

def TestGLOB():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestGLOB.esp")
    Current.load()
    print "GLOB:Read Test"
    for record in Current.LoadOrderMods[0].GLOB:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "GLOB:Create Record Test"
    newRecord = newMod.create_GLOB()
    d(newRecord)

    print "GLOB:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WarGlobalTest"
    print "format..."
    newRecord.format = 'f'
    print "value..."
    newRecord.value = 12.2
    print "GLOB:Set Test Results"
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "format :", newRecord.format
    print "value  :", newRecord.value
    print "GLOB:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].GLOB:
        record.CopyAsOverride(newMod)
    print "GLOB:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].GLOB:
        record.CopyAsNew(newMod)
    print "GLOB:Save Test - TestGLOB.esp"
    newMod.save()
    print "GLOB:Finished testing"
    Current.Close()

def TestCLAS():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCLAS.esp")
    Current.load()
    print "CLAS:Read Test"
    for record in Current.LoadOrderMods[0].CLAS:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "CLAS:Create Record Test"
    newRecord = newMod.create_CLAS()
    d(newRecord)

    print "CLAS:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WarCLASTest"

    print "full..."
    newRecord.full = "Waruddar! RARGH!"
    print "description..."
    newRecord.description = "This is just a very long and quick test of a string that is absolutely pointless for the vast majority of cases.!!!"
    print "iconPath..."
    newRecord.iconPath = r"ICON\asdf.ico"
    print "primary1..."
    newRecord.primary1 = 8
    print "primary2..."
    newRecord.primary2 = 9
    print "specialization..."
    newRecord.specialization = 1
    print "major1..."
    newRecord.major1 = 1
    print "major2..."
    newRecord.major2 = 2
    print "major3..."
    newRecord.major3 = 3
    print "major4..."
    newRecord.major4 = 4
    print "major5..."
    newRecord.major5 = 5
    print "major6..."
    newRecord.major6 = 6
    print "major7..."
    newRecord.major7 = 7
    print "flags...."
    newRecord.flags = 0x07
    print "services..."
    newRecord.services = 0x08
    print "trainSkill..."
    newRecord.trainSkill = 13
    print "trainLevel..."
    newRecord.trainLevel = 60
    print "unused1..."
    newRecord.unused1 = [0x01, 0xFF]

    print "CLAS:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full          :", newRecord.full
    print "description   :", newRecord.description
    print "iconPath      :", newRecord.iconPath
    print "primary1      :", newRecord.primary1
    print "primary2      :", newRecord.primary2
    print "specialization:", newRecord.specialization
    print "major1        :", newRecord.major1
    print "major2        :", newRecord.major2
    print "major3        :", newRecord.major3
    print "major4        :", newRecord.major4
    print "major5        :", newRecord.major5
    print "major6        :", newRecord.major6
    print "major7        :", newRecord.major7
    print "flags         :", newRecord.flags
    print "services      :", newRecord.services
    print "trainSkill    :", newRecord.trainSkill
    print "trainLevel    :", newRecord.trainLevel
    print "unused1       :", newRecord.unused1
    print "CLAS:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].CLAS:
        record.CopyAsOverride(newMod)
    print "CLAS:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].CLAS:
        record.CopyAsNew(newMod)
    print "CLAS:Save Test - TestCLAS.esp"
    newMod.save()
    print "CLAS:Finished testing"
    Current.Close()

def TestFACT():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestFACT.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].FACT:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "FACT:Create Record Test"
    newRecord = newMod.create_FACT()
    d(newRecord)

    print "FACT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "FACTWarTest"
    print "full..."
    newRecord.full = "Waruddar's Faction"
    print "relations..."
    newRelation = newRecord.create_relation()
    newRelation.faction = FormID(1)
    newRelation.mod = -69
    newRelation = newRecord.create_relation()
    newRelation.faction = FormID(2)
    newRelation.mod = 67
    newRelation = newRecord.create_relation()
    newRelation.faction = FormID(15)
    newRelation.mod = 100
    print "flags..."
    newRecord.flags = 15
    print "crimeGoldMultiplier..."
    newRecord.crimeGoldMultiplier = 1.5
    print "ranks..."
    newRank = newRecord.create_rank()
    newRank.rank = 0
    newRank.male = "HELP ME"
    newRank.female = "LOST MY MIND"
    newRank.insigniaPath = "WHERE is IT?"
    newRank = newRecord.create_rank()
    newRank.rank = 1
    newRank.male = "Is it here?"
    newRank.female = "Or, there?"
    newRank.insigniaPath = "Where?"
    newRank = newRecord.create_rank()
    newRank.rank = 2
    newRank.male = "Silly me"
    newRank.female = "Here it is"
    newRank.insigniaPath = "Found it"

    print "FACT:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full               :", newRecord.full
    print "relations          :"
    for relation in newRecord.relations:
        print "  %i: Faction: %s, Mod: %i" % (relation._ListIndex, relation.faction, relation.mod)
    print "flags              :", newRecord.flags
    print "crimeGoldMultiplier:", newRecord.crimeGoldMultiplier
    print "ranks              :"
    for rank in newRecord.ranks:
        print "  rank: %i\n    male:%s\n    female:%s\n    insigniaPath:%s" % (rank.rank, rank.male, rank.female, rank.insigniaPath)

    print "FACT:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].FACT:
        record.CopyAsOverride(newMod)

    print "FACT:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].FACT:
        record.CopyAsNew(newMod)

    print "FACT:Save Test - TestFACT.esp"
    newMod.save()
    print "FACT:Finished testing"
    Current.Close()

def TestHAIR():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestHAIR.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].HAIR:
        print
        print "fid     :", record.fid
        printRecord(record)
        break



    print "HAIR:Create Record Test"
    newRecord = newMod.create_HAIR()
    d(newRecord)

    print "HAIR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "HAIRWarTest"
    print "full..."
    newRecord.full = "Fancy HAIR"

    print "modPath..."
    newRecord.modPath = r"Blah\hay\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"hair\path\test.dds"

    print "flags..."
    newRecord.flags = 15


    print "HAIR:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "flags   :", newRecord.flags

    print "HAIR:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].HAIR:
        record.CopyAsOverride(newMod)

    print "HAIR:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].HAIR:
        record.CopyAsNew(newMod)

    print "HAIR:Save Test - TestHAIR.esp"
    newMod.save()
    print "HAIR:Finished testing"
    Current.Close()

def TestEYES():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestEYES.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].EYES:
        print
        print "fid     :", record.fid
        printRecord(record)
        break



    print "EYES:Create Record Test"
    newRecord = newMod.create_EYES()
    d(newRecord)

    print "EYES:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "EYESWarTest"
    print "full..."
    newRecord.full = "Fancy EYES"
    print "iconPath..."
    newRecord.iconPath = r"EYES\p\nath\test.dds"
    print "flags..."
    newRecord.flags = 15

    print "EYES:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full    :", newRecord.full
    print "iconPath:", newRecord.iconPath
    print "flags   :", newRecord.flags

    print "EYES:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].EYES:
        record.CopyAsOverride(newMod)

    print "EYES:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].EYES:
        record.CopyAsNew(newMod)

    print "EYES:Save Test - TestEYES.esp"
    newMod.save()
    print "EYES:Finished testing"
    Current.Close()

def TestRACE():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestRACE.esp")
    Current.load()
    for record in Current.LoadOrderMods[0].RACE:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "RACE:Create Record Test"
    newRecord = newMod.create_RACE()
    d(newRecord)

    print "RACE:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "RACEWarTest"
    print "full..."
    newRecord.full = "Fancy RACE"

    newRecord.text = "BLAH BLAH BLHARGH"
    newRecord.spells = [FormID(0xFF000121), FormID(0xFE000222)]
    newRelation = newRecord.create_relation()
    newRelation.faction = FormID(0x00000800)
    newRelation.mod = 100
    newRelation = newRecord.create_relation()
    newRelation.faction = FormID(0x00000801)
    newRelation.mod = 50
    newRelation = newRecord.create_relation()
    newRelation.faction = FormID(0x00000802)
    newRelation.mod = 60
    newRelation = newRecord.create_relation()
    newRelation.faction = FormID(0x00000803)
    newRelation.mod = 70
    nRelations = newRecord.relations
    newRecord.relations = [nRelations[1],nRelations[0],nRelations[2],nRelations[3]]

    newRecord.skill1 = 1
    newRecord.skill1Boost = 11
    newRecord.skill2 = 2
    newRecord.skill2Boost = 12
    newRecord.skill3 = 3
    newRecord.skill3Boost = 13
    newRecord.skill4 = 4
    newRecord.skill4Boost = 14
    newRecord.skill5 = 5
    newRecord.skill5Boost = 15
    newRecord.skill6 = 6
    newRecord.skill6Boost = 16
    newRecord.skill7 = 7
    newRecord.skill7Boost = 17

    newRecord.unused1 = [0x00, 0xFF]

    newRecord.maleHeight = 1.5
    newRecord.femaleHeight = 1.6
    newRecord.maleWeight = 2.1
    newRecord.femaleWeight = 2.2


    newRecord.flags = 0x00000010

    newRecord.maleVoice = FormID(0x00000011)
    newRecord.femaleVoice = FormID(0x00000012)

    newRecord.defaultHairMale = FormID(0x00000013)
    newRecord.defaultHairFemale = FormID(0x00000014)
    newRecord.defaultHairColor = 1

    newRecord.mainClamp = 10.1
    newRecord.faceClamp = 1.2

    newRecord.maleStrength = 25
    newRecord.maleIntelligence = 26
    newRecord.maleWillpower = 27
    newRecord.maleAgility = 28
    newRecord.maleSpeed = 29
    newRecord.maleEndurance = 30
    newRecord.malePersonality = 31
    newRecord.maleLuck = 32

    newRecord.femaleStrength = 51
    newRecord.femaleIntelligence = 52
    newRecord.femaleWillpower = 53
    newRecord.femaleAgility = 54
    newRecord.femaleSpeed = 55
    newRecord.femaleEndurance = 56
    newRecord.femalePersonality = 57
    newRecord.femaleLuck = 58

    newRecord.head.modPath = r"asdf"
    newRecord.head.modb = 1.3
    newRecord.head.iconPath = r"fqeasdf"
    newRecord.head.modt_p = [0x01, 0x20]

    newRecord.maleEars.modPath = "maleEars"
    newRecord.maleEars.modb = 1.4
    newRecord.maleEars.iconPath = "maleEarsP"
    newRecord.maleEars.modt_p = [0x01, 0x20]

    newRecord.femaleEars.modPath = "femaleEars"
    newRecord.femaleEars.modb = 1.5
    newRecord.femaleEars.iconPath = "femaleEarsP"
    newRecord.femaleEars.modt_p = [0x01, 0x20]

    newRecord.mouth.modPath = "mouth"
    newRecord.mouth.modb = 1.6
    newRecord.mouth.iconPath = "mouthP"
    newRecord.mouth.modt_p = [0x01, 0x20]

    newRecord.teethLower.modPath = "teethLower"
    newRecord.teethLower.modb = 1.7
    newRecord.teethLower.iconPath = "teethLowerP"
    newRecord.teethLower.modt_p = [0x01, 0x20]

    newRecord.teethUpper.modPath = "teethUpper"
    newRecord.teethUpper.modb = 1.8
    newRecord.teethUpper.iconPath = "teethUpperP"
    newRecord.teethUpper.modt_p = [0x01, 0x20]

    newRecord.tongue.modPath = "tongue"
    newRecord.tongue.modb = 1.9
    newRecord.tongue.iconPath = "tongue"
    newRecord.tongue.modt_p = [0x01, 0x20]

    newRecord.leftEye.modPath = "leftEye"
    newRecord.leftEye.modb = 2.0
    newRecord.leftEye.iconPath = "leftEye"
    newRecord.leftEye.modt_p = [0x01, 0x20]

    newRecord.rightEye.modPath = "rightEye"
    newRecord.rightEye.modb = 2.1
    newRecord.rightEye.iconPath = "rightEye"
    newRecord.rightEye.modt_p = [0x01, 0x20]

    newRecord.maleTail.modPath = "maleTail"
    newRecord.maleTail.modb = 2.2
    newRecord.maleTail.modt_p = [0x01, 0x20]

    newRecord.maleUpperBodyPath = "maleUpperBodyPath"
    newRecord.maleLowerBodyPath = "maleLowerBodyPath"
    newRecord.maleHandPath = "maleHandPath"
    newRecord.maleFootPath = "maleFootPath"
    newRecord.maleTailPath = "maleTailPath"

    newRecord.femaleTail.modPath = "femaleTail"
    newRecord.femaleTail.modb = 2.3
    newRecord.femaleTail.modt_p = [0x01, 0x20]

    newRecord.femaleUpperBodyPath = ""
    newRecord.femaleLowerBodyPath = "femaleLowerBodyPath"
    newRecord.femaleHandPath = "femaleHandPath"
    newRecord.femaleFootPath = "femaleFootPath"
    newRecord.femaleTailPath = "femaleTailPath"
    newRecord.hairs = [FormID(0x00000001), FormID(0x01000002)]
    newRecord.eyes = [FormID(0x00000003), FormID(0x01000004)]

    newRecord.fggs_p = [0x01, 0x20]
    newRecord.fgga_p = [0x01, 0x20]
    newRecord.fgts_p = [0x01, 0x20]

    newRecord.snam_p = [0x01, 0x20]

    print "RACE:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full      :", newRecord.full
    print "text      :", newRecord.text
    print "spells    :"
    for spell in newRecord.spells:
        print "  ", spell

    print "relations :"
    for relation in newRecord.relations:
        print "  %i: Faction: %s, Mod: %i" % (relation._ListIndex, relation.faction, relation.mod)

    print "  skill1:", newRecord.skill1, ", boost:", newRecord.skill1Boost
    print "  skill2:", newRecord.skill2, ", boost:", newRecord.skill2Boost
    print "  skill3:", newRecord.skill3, ", boost:", newRecord.skill3Boost
    print "  skill4:", newRecord.skill4, ", boost:", newRecord.skill4Boost
    print "  skill5:", newRecord.skill5, ", boost:", newRecord.skill5Boost
    print "  skill6:", newRecord.skill6, ", boost:", newRecord.skill6Boost
    print "  skill7:", newRecord.skill7, ", boost:", newRecord.skill7Boost

    print "unused1          :", newRecord.unused1

    print "maleHeight       :", newRecord.maleHeight
    print "femaleHeight     :", newRecord.femaleHeight
    print "maleWeight       :", newRecord.maleWeight
    print "femaleWeight     :", newRecord.femaleWeight
    print "flags            :", newRecord.flags

    print "maleVoice        :", newRecord.maleVoice
    print "femaleVoice      :", newRecord.femaleVoice

    print "defaultHairMale  :", newRecord.defaultHairMale
    print "defaultHairFemale:", newRecord.defaultHairFemale
    print "defaultHairColor :", newRecord.defaultHairColor

    print "mainClamp        :", newRecord.mainClamp
    print "faceClamp        :", newRecord.faceClamp

    print "maleStrength     :", newRecord.maleStrength
    print "maleIntelligence :", newRecord.maleIntelligence
    print "maleWillpower    :", newRecord.maleWillpower
    print "maleAgility      :", newRecord.maleAgility
    print "maleSpeed        :", newRecord.maleSpeed
    print "maleEndurance    :", newRecord.maleEndurance
    print "malePersonality  :", newRecord.malePersonality
    print "maleLuck         :", newRecord.maleLuck

    print "femaleStrength     :", newRecord.femaleStrength
    print "femaleIntelligence :", newRecord.femaleIntelligence
    print "femaleWillpower    :", newRecord.femaleWillpower
    print "femaleAgility      :", newRecord.femaleAgility
    print "femaleSpeed        :", newRecord.femaleSpeed
    print "femaleEndurance    :", newRecord.femaleEndurance
    print "femalePersonality  :", newRecord.femalePersonality
    print "femaleLuck         :", newRecord.femaleLuck

    print "head.modPath       :", newRecord.head.modPath
    print "head.modb          :", newRecord.head.modb
    print "head.iconPath      :", newRecord.head.iconPath
    print "head.modt_p        :", newRecord.head.modt_p

    print "maleEars.modPath   :", newRecord.maleEars.modPath
    print "maleEars.modb      :", newRecord.maleEars.modb
    print "maleEars.iconPath  :", newRecord.maleEars.iconPath
    print "maleEars.modt_p    :", newRecord.maleEars.modt_p

    print "femaleEars.modPath :", newRecord.femaleEars.modPath
    print "femaleEars.modb    :", newRecord.femaleEars.modb
    print "femaleEars.iconPath:", newRecord.femaleEars.iconPath
    print "femaleEars.modt_p  :", newRecord.femaleEars.modt_p

    print "mouth.modPath      :", newRecord.mouth.modPath
    print "mouth.modb         :", newRecord.mouth.modb
    print "mouth.iconPath     :", newRecord.mouth.iconPath
    print "mouth.modt_p       :", newRecord.mouth.modt_p

    print "teethLower.modPath :", newRecord.teethLower.modPath
    print "teethLower.modb    :", newRecord.teethLower.modb
    print "teethLower.iconPath:", newRecord.teethLower.iconPath
    print "teethLower.modt_p  :", newRecord.teethLower.modt_p

    print "teethUpper.modPath :", newRecord.teethUpper.modPath
    print "teethUpper.modb    :", newRecord.teethUpper.modb
    print "teethUpper.iconPath:", newRecord.teethUpper.iconPath
    print "teethUpper.modt_p  :", newRecord.teethUpper.modt_p

    print "tongue.modPath     :", newRecord.tongue.modPath
    print "tongue.modb        :", newRecord.tongue.modb
    print "tongue.iconPath    :", newRecord.tongue.iconPath
    print "tongue.modt_p      :", newRecord.tongue.modt_p

    print "leftEye.modPath    :", newRecord.leftEye.modPath
    print "leftEye.modb       :", newRecord.leftEye.modb
    print "leftEye.iconPath   :", newRecord.leftEye.iconPath
    print "leftEye.modt_p     :", newRecord.leftEye.modt_p

    print "rightEye.modPath   :", newRecord.rightEye.modPath
    print "rightEye.modb      :", newRecord.rightEye.modb
    print "rightEye.iconPath  :", newRecord.rightEye.iconPath
    print "rightEye.modt_p    :", newRecord.rightEye.modt_p

    print "maleTail.modPath :", newRecord.maleTail.modPath
    print "maleTail.modb    :", newRecord.maleTail.modb
    print "maleTail.modt_p  :", newRecord.maleTail.modt_p

    print "maleUpperBodyPath     :", newRecord.maleUpperBodyPath
    print "maleLowerBodyPath     :", newRecord.maleLowerBodyPath
    print "maleHandPath          :", newRecord.maleHandPath
    print "maleFootPath          :", newRecord.maleFootPath
    print "maleTailPath          :", newRecord.maleTailPath

    print "femaleTail.modPath :", newRecord.femaleTail.modPath
    print "femaleTail.modb    :", newRecord.femaleTail.modb
    print "femaleTail.modt_p  :", newRecord.femaleTail.modt_p

    print "femaleUpperBodyPath     :", newRecord.femaleUpperBodyPath
    print "femaleLowerBodyPath     :", newRecord.femaleLowerBodyPath
    print "femaleHandPath          :", newRecord.femaleHandPath
    print "femaleFootPath          :", newRecord.femaleFootPath
    print "femaleTailPath          :", newRecord.femaleTailPath

    print "hairs :"
    for hair in newRecord.hairs:
        print "  ", hair

    print "eyes :"
    for eye in newRecord.eyes:
        print "  ", eye

    print "fggs_p:", newRecord.fggs_p
    print "fgga_p:", newRecord.fgga_p
    print "fgts_p:", newRecord.fgts_p

    print "snam_p:", newRecord.snam_p

    print "RACE:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].RACE:
        record.CopyAsOverride(newMod)

    print "RACE:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].RACE:
        record.CopyAsNew(newMod)

    print "RACE:Save Test - TestRACE.esp"
    newMod.save()
    print "RACE:Finished testing"
    Current.Close()

def TestSOUN():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSOUN.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].SOUN:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "SOUN:Create Record Test"
    newRecord = newMod.create_SOUN()
    d(newRecord)

    print "SOUN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SOUNWarTest"
    print "soundPath..."
    newRecord.soundPath = "Fancy SOUN"
    newRecord.minDistance = 1
    newRecord.maxDistance = 55
    newRecord.freqAdjustment = -3
    newRecord.unused1 = [15]
    newRecord.flags = 16
    newRecord.unused2 = [0x01, 0xFF]
    newRecord.staticAtten = 5
    newRecord.stopTime = 12
    newRecord.startTime = 24

    print "SOUN:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "soundPath      :", newRecord.soundPath
    print "minDistance    :", newRecord.minDistance
    print "maxDistance    :", newRecord.maxDistance
    print "freqAdjustment :", newRecord.freqAdjustment
    print "unused1        :", newRecord.unused1
    print "flags          :", newRecord.flags
    print "unused2        :", newRecord.unused2
    print "staticAtten    :", newRecord.staticAtten
    print "stopTime       :", newRecord.stopTime
    print "startTime      :", newRecord.startTime

    print "SOUN:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SOUN:
        record.CopyAsOverride(newMod)

    print "SOUN:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SOUN:
        record.CopyAsNew(newMod)

    print "SOUN:Save Test - TestSOUN.esp"
    newMod.save()
    print "SOUN:Finished testing"
    Current.Close()

def TestSKIL():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSKIL.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].SKIL:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "SKIL:Create Record Test"
    newRecord = newMod.create_SKIL()
    d(newRecord)

    print "SKIL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SKILWarTest"
    print "skill..."
    newRecord.skill = 1
    newRecord.description = "Fancy SKIL"
    newRecord.iconPath = r"ICON\Path\1.dds"
    newRecord.action = 2
    newRecord.attribute = 28
    newRecord.specialization = 1
    newRecord.use0 = 1.0
    newRecord.use1 = 2.0
    newRecord.apprentice = "of nothing"
    newRecord.journeyman = "Little bit"
    newRecord.expert = "Jack of none"
    newRecord.master = "Master of all"

    print "SKIL:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "skill          :", newRecord.skill
    print "description    :", newRecord.description
    print "iconPath       :", newRecord.iconPath
    print "action         :", newRecord.action
    print "attribute      :", newRecord.attribute
    print "specialization :", newRecord.specialization
    print "use0           :", newRecord.use0
    print "use1           :", newRecord.use1
    print "apprentice     :", newRecord.apprentice
    print "journeyman     :", newRecord.journeyman
    print "expert         :", newRecord.expert
    print "master         :", newRecord.master

    print "SKIL:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SKIL:
        record.CopyAsOverride(newMod)

    print "SKIL:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SKIL:
        record.CopyAsNew(newMod)

    print "SKIL:Save Test - TestSKIL.esp"
    newMod.save()
    print "SKIL:Finished testing"
    Current.Close()

def TestMGEF():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestMGEF.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].MGEF:
        print
        print "eid     :", record.eid
        printRecord(record)
        break
    print "MGEF:Create Record Test"
    newRecord = newMod.create_MGEF("MGEFWarTest0")
    d(newRecord)

    print "MGEF:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "MGEFWarTest"
    newRecord.full = "Long winded and boring story"
    newRecord.text = "These can't be added anyway"
    newRecord.iconPath = "WHAT?"
    newRecord.modPath = "STILL?"
    newRecord.modb = 1.2
    newRecord.flags = 1
    newRecord.baseCost = 12
    newRecord.associated = FormID(7)
    newRecord.schoolType = 30
    newRecord.resistValue = 35
    newRecord.numCounters = 15
    newRecord.light = FormID(8)
    newRecord.projectileSpeed = 9
    newRecord.effectShader = FormID(10)
    newRecord.enchantEffect = FormID(11)
    newRecord.castingSound = FormID(12)
    newRecord.boltSound = FormID(13)
    newRecord.hitSound = FormID(14)
    newRecord.areaSound = FormID(15)
    newRecord.cefEnchantment = 16.0
    newRecord.cefBarter = 17.2
    newRecord.counterEffects = [MGEFCode("SEFF")]

    print "MGEF:Set Test Results"
    print
    print "eid     :", newRecord.eid
    printRecord(newRecord)

    print "MGEF:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].MGEF:
        record.CopyAsOverride(newMod)

    print "MGEF:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].MGEF:
        record.CopyAsNew(newMod, record.eid + 'WarCopy')

    print "MGEF:Save Test - TestMGEF.esp"
    newMod.save()
    print "MGEF:Finished testing"
    Current.Close()

def TestSCPT():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSCPT.esp")
    Current.load()
    x = 0
    for record in Current.LoadOrderMods[0].SCPT:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "SCPT:Create Record Test"
    newRecord = newMod.create_SCPT()
    d(newRecord)

    print "SCPT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SCPTWarTest"

    newRecord.unused1 = [0x0F, 0xFF]
    newRecord.numRefs = 0
    newRecord.compiledSize = 2
    newRecord.lastIndex = 1
    newRecord.scriptType = 1
    newRecord.compiled_p = [0x00, 0xFF]
    newRecord.scriptText = "scn WarTest\nshort Didit\nend"

    newVar = newRecord.create_var()
    newVar.index = 1
    newVar.unused1 = [0,1,2,3,4,5,6,7,8,9,10,11]
    newVar.flags = 1
    newVar.unused2 = [0,1,2,3,4,5,6]
    newVar.name = "Didit"

    newVar = newRecord.create_var()
    newVar.index = 2
    newVar.unused1 = [0,1,2,3,4,5,6,7,8,9,10,11]
    newVar.flags = 2
    newVar.unused2 = [0,1,2,3,4,5,6]
    newVar.name = "Did1it"

    newVar = newRecord.create_var()
    newVar.index = 3
    newVar.unused1 = [0,1,2,3,4,5,6,7,8,9,10,11]
    newVar.flags = 2
    newVar.unused2 = [0,1,2,3,4,5,6]
    newVar.name = "Did2it"

    newRecord.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]

    print "SCPT:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "unused1      :", newRecord.unused1
    print "numRefs      :", newRecord.numRefs
    print "compiledSize :", newRecord.compiledSize
    print "lastIndex    :", newRecord.lastIndex
    print "scriptType   :", newRecord.scriptType
    print "compiled_p   :", newRecord.compiled_p
    print "scriptText   :\n", newRecord.scriptText
    print "vars         :"
    for var in newRecord.vars:
        print
        print "  index   :", var.index
        print "  unused1 :", var.unused1
        print "  flags   :", var.flags
        print "  unused2 :", var.unused2
        print "  name    :", var.name
    print "references   :"
    for reference in newRecord.references:
        if isinstance(reference, FormID):
            print "  SCRO:", reference
        else:
            print "  SCRV:", reference

    print "SCPT:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SCPT:
        record.CopyAsOverride(newMod)

    print "SCPT:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SCPT:
        record.CopyAsNew(newMod)

    print "SCPT:Save Test - TestSCPT.esp"
    newMod.save()
    print "SCPT:Finished testing"
    Current.Close()

def TestLTEX():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLTEX.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].LTEX:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "LTEX:Create Record Test"
    newRecord = newMod.create_LTEX()
    d(newRecord)

    print "LTEX:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."

    newRecord.eid = "LTEXWarTest"
    newRecord.iconPath = r"LTEX\path\test.dds"
    newRecord.types = 156
    newRecord.friction = 111
    newRecord.restitution = 123
    newRecord.specular = 128

    newRecord.grass = [FormID(0xFF000121), FormID(0xFE000222)]


    print "LTEX:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "iconPath    :", newRecord.iconPath
    print "types       :", newRecord.types
    print "friction    :", newRecord.friction
    print "restitution :", newRecord.restitution
    print "specular    :", newRecord.specular
    print "grass    :"
    for grass in newRecord.grass:
        print "  ", grass

    print "LTEX:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].LTEX:
        record.CopyAsOverride(newMod)

    print "LTEX:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].LTEX:
        record.CopyAsNew(newMod)

    print "LTEX:Save Test - TestLTEX.esp"
    newMod.save()
    print "LTEX:Finished testing"
    Current.Close()

def TestENCH():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestENCH.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].ENCH:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "ENCH:Create Record Test"
    newRecord = newMod.create_ENCH()
    d(newRecord)

    print "ENCH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ENCHWarTest"

    newRecord.full = "Fancy ENCH"
    newRecord.itemType = 1
    newRecord.chargeAmount = 2
    newRecord.enchantCost = 3
    newRecord.flags = 4
    newRecord.unused1 = [0,1,2]

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.rangeType = 4
    newEffect.actorValue = ActorValue(5)
    newEffect.script = FormID(0xFF000007)
    newEffect.schoolType = 324
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "ENCH?"

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.rangeType = 9
    newEffect.actorValue = ActorValue(10)
    newEffect.script = FormID(0xFF00000A)
    newEffect.schoolType = 11
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "ENCH??"

    print "ENCH:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full         :", newRecord.full
    print "itemType     :", newRecord.itemType
    print "chargeAmount :", newRecord.chargeAmount
    print "enchantCost  :", newRecord.enchantCost
    print "flags        :", newRecord.flags
    print "unused1      :", newRecord.unused1
    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  rangeType  :", effect.rangeType
        print "  actorValue :", effect.actorValue
        print "  script     :", effect.script
        print "  schoolType :", effect.schoolType
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print
    print "ENCH:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].ENCH:
        record.CopyAsOverride(newMod)

    print "ENCH:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].ENCH:
        record.CopyAsNew(newMod)

    print "ENCH:Save Test - TestENCH.esp"
    newMod.save()
    print "ENCH:Finished testing"
    Current.Close()

def TestSPEL():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSPEL.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].SPEL:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "SPEL:Create Record Test"
    newRecord = newMod.create_SPEL()
    d(newRecord)

    print "SPEL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SPELWarTest"

    newRecord.full = "Fancy SPEL"
    newRecord.spellType = 1
    newRecord.cost = 2
    newRecord.levelType = 3
    newRecord.flags = 4
    newRecord.unused1 = [0,1,2]

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.rangeType = 4
    newEffect.actorValue = ActorValue(5)
    newEffect.script = FormID(0xFF000007)
    newEffect.schoolType = 324
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "SPEL?"

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.rangeType = 9
    newEffect.actorValue = ActorValue(10)
    newEffect.script = FormID(0xFF00000A)
    newEffect.schoolType = 11
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "SPEL??"
    print "SPEL:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full         :", newRecord.full
    print "spellType    :", newRecord.spellType
    print "cost         :", newRecord.cost
    print "levelType    :", newRecord.levelType
    print "flags        :", newRecord.flags
    print "unused1      :", newRecord.unused1
    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  rangeType  :", effect.rangeType
        print "  actorValue :", effect.actorValue
        print "  script     :", effect.script
        print "  schoolType :", effect.schoolType
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print
    print "SPEL:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SPEL:
        record.CopyAsOverride(newMod)

    print "SPEL:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SPEL:
        record.CopyAsNew(newMod)

    print "SPEL:Save Test - TestSPEL.esp"
    newMod.save()
    print "SPEL:Finished testing"
    Current.Close()

def TestBSGN():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestBSGN.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].BSGN:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "BSGN:Create Record Test"
    newRecord = newMod.create_BSGN()
    d(newRecord)

    print "BSGN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "BSGNWarTest"
    newRecord.full = "Fancy BSGN"

    newRecord.iconPath = r"BSGN\p\nath\test.dds"
    newRecord.text = "BLAH BLAH BLHARGH"
    newRecord.spells = [FormID(0xFF000121), FormID(0xFE000222)]
    print "BSGN:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full      :", newRecord.full
    print "iconPath  :", newRecord.iconPath
    print "text      :", newRecord.text
    print "spells    :"
    for spell in newRecord.spells:
        print "  ", spell
    print "BSGN:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].BSGN:
        record.CopyAsOverride(newMod)

    print "BSGN:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].BSGN:
        record.CopyAsNew(newMod)

    print "BSGN:Save Test - TestBSGN.esp"
    newMod.save()
    print "BSGN:Finished testing"
    Current.Close()

def TestACTI():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestACTI.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].ACTI:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "ACTI:Create Record Test"
    newRecord = newMod.create_ACTI()
    d(newRecord)

    print "ACTI:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ACTIWarTest"
    print "full..."
    newRecord.full = "Fancy ACTI"

    print "modPath..."
    newRecord.modPath = r"ACTI\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.script = FormID(7)
    newRecord.sound = FormID(0x0000000A)

    print "ACTI:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "script  :", newRecord.script
    print "sound   :", newRecord.sound

    print "ACTI:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].ACTI:
        record.CopyAsOverride(newMod)

    print "ACTI:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].ACTI:
        record.CopyAsNew(newMod)

    print "ACTI:Save Test - TestACTI.esp"
    newMod.save()
    print "ACTI:Finished testing"
    Current.Close()

def TestAPPA():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestAPPA.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].APPA:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "APPA:Create Record Test"
    newRecord = newMod.create_APPA()
    d(newRecord)

    print "APPA:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "APPAWarTest"
    print "full..."
    newRecord.full = "Fancy APPA"

    print "modPath..."
    newRecord.modPath = r"APPA\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"APPA\path\test.dds"
    newRecord.script = FormID(7)
    newRecord.apparatusType = 1
    newRecord.value = 150
    newRecord.weight = 3.56
    newRecord.quality = 3.0
    print "APPA:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full          :", newRecord.full
    print "modPath       :", newRecord.modPath
    print "modb          :", newRecord.modb
    print "modt_p        :", newRecord.modt_p
    print "iconPath      :", newRecord.iconPath
    print "script        :", newRecord.script
    print "apparatusType :", newRecord.apparatusType
    print "value         :", newRecord.value
    print "weight        :", newRecord.weight
    print "quality       :", newRecord.quality

    print "APPA:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].APPA:
        record.CopyAsOverride(newMod)

    print "APPA:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].APPA:
        record.CopyAsNew(newMod)

    print "APPA:Save Test - TestAPPA.esp"
    newMod.save()
    print "APPA:Finished testing"
    Current.Close()

def TestARMO():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestARMO.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].ARMO:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "ARMO:Create Record Test"
    newRecord = newMod.create_ARMO()
    d(newRecord)

    print "ARMO:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ARMOWarTest"

    newRecord.full =  "Fancy ARMO"
    newRecord.script = FormID(7)
    newRecord.enchantment = FormID(0x0000000A)
    newRecord.enchantPoints = 251
    newRecord.flags = 1
    newRecord.maleBody.modPath = r"maleBody\hay\1.nif"
    newRecord.maleBody.modb = 1.1
    newRecord.maleBody.modt_p = [0x00, 0xFF, 0xFE]
    newRecord.maleWorld.modPath = r"maleWorld\hay\1.nif"
    newRecord.maleWorld.modb = 1.2
    newRecord.maleWorld.modt_p = [0x00, 0xFF, 0xFD]
    newRecord.maleIconPath = r"maleIconPath\hay\1.dds"
    newRecord.femaleBody.modPath = r"femaleBody\hay\1.nif"
    newRecord.femaleBody.modb = 1.3
    newRecord.femaleBody.modt_p = [0x00, 0xFF, 0xFC]
    newRecord.femaleWorld.modPath = r"femaleWorld\hay\1.nif"
    newRecord.femaleWorld.modb = 1.4
    newRecord.femaleWorld.modt_p = [0x00, 0xFF, 0xFB]
    newRecord.femaleIconPath =  r"femaleIconPath\hay\1.dds"
    newRecord.strength = 15
    newRecord.value = 150
    newRecord.health = 155
    newRecord.weight = 5


    print "ARMO:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full          :", newRecord.full
    print "script        :", newRecord.script
    print "enchantment   :", newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "flags         :", newRecord.flags
    print "maleBody.modPath  :", newRecord.maleBody.modPath
    print "maleBody.modb     :", newRecord.maleBody.modb
    print "maleBody.modt_p   :", newRecord.maleBody.modt_p
    print "maleWorld.modPath :", newRecord.maleWorld.modPath
    print "maleWorld.modb    :", newRecord.maleWorld.modb
    print "maleWorld.modt_p  :", newRecord.maleWorld.modt_p
    print "maleIconPath      :", newRecord.maleIconPath
    print "femaleBody.modPath  :", newRecord.femaleBody.modPath
    print "femaleBody.modb     :", newRecord.femaleBody.modb
    print "femaleBody.modt_p   :", newRecord.femaleBody.modt_p
    print "femaleWorld.modPath :", newRecord.femaleWorld.modPath
    print "femaleWorld.modb    :", newRecord.femaleWorld.modb
    print "femaleWorld.modt_p  :", newRecord.femaleWorld.modt_p
    print "femaleIconPath      :", newRecord.femaleIconPath
    print "strength       :", newRecord.strength
    print "value          :", newRecord.value
    print "health         :", newRecord.health
    print "weight         :", newRecord.weight
    print "ARMO:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].ARMO:
        record.CopyAsOverride(newMod)

    print "ARMO:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].ARMO:
        record.CopyAsNew(newMod)

    print "ARMO:Save Test - TestARMO.esp"
    newMod.save()
    print "ARMO:Finished testing"
    Current.Close()

def TestBOOK():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestBOOK.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].BOOK:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "BOOK:Create Record Test"
    newRecord = newMod.create_BOOK()
    d(newRecord)

    print "BOOK:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "BOOKWarTest"
    print "full..."
    newRecord.full = "Fancy BOOK"

    print "modPath..."
    newRecord.modPath = r"BOOK\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"BOOK\path\test.dds"
    newRecord.text = "Now this is a story about...something. And an interesting thing happened to...something. But, unknown to...something..., there was opposition from...something else....\n<br>Hey!</br><herlmf></herlmf>\nJust a test\n"
    newRecord.script = FormID(7)
    newRecord.enchantment = FormID(0x0000000A)
    newRecord.enchantPoints = 251
    newRecord.flags = 1
    newRecord.teaches = -1
    newRecord.value = 152
    newRecord.weight = 3.56


    print "BOOK:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath      :", newRecord.iconPath
    print "text          :", newRecord.text
    print "script        :", newRecord.script
    print "enchantment   :", newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "flags         :", newRecord.flags
    print "teaches       :", newRecord.teaches
    print "value         :", newRecord.value
    print "weight        :", newRecord.weight
    print "BOOK:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].BOOK:
        record.CopyAsOverride(newMod)

    print "BOOK:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].BOOK:
        record.CopyAsNew(newMod)

    print "BOOK:Save Test - TestBOOK.esp"
    newMod.save()
    print "BOOK:Finished testing"
    Current.Close()

def TestCLOT():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCLOT.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].CLOT:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "CLOT:Create Record Test"
    newRecord = newMod.create_CLOT()
    d(newRecord)

    print "CLOT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CLOTWarTest"

    newRecord.full =  "Fancy CLOT"
    newRecord.script = FormID(7)
    newRecord.enchantment = FormID(0x0000000A)
    newRecord.enchantPoints = 251
    newRecord.flags = 1
    newRecord.maleBody.modPath = r"maleBody\hay\1.nif"
    newRecord.maleBody.modb = 1.1
    newRecord.maleBody.modt_p = [0x00, 0xFF, 0xFE]
    newRecord.maleWorld.modPath = r"maleWorld\hay\1.nif"
    newRecord.maleWorld.modb = 1.2
    newRecord.maleWorld.modt_p = [0x00, 0xFF, 0xFD]
    newRecord.maleIconPath = r"maleIconPath\hay\1.dds"
    newRecord.femaleBody.modPath = r"femaleBody\hay\1.nif"
    newRecord.femaleBody.modb = 1.3
    newRecord.femaleBody.modt_p = [0x00, 0xFF, 0xFC]
    newRecord.femaleWorld.modPath = r"femaleWorld\hay\1.nif"
    newRecord.femaleWorld.modb = 1.4
    newRecord.femaleWorld.modt_p = [0x00, 0xFF, 0xFB]
    newRecord.femaleIconPath =  r"femaleIconPath\hay\1.dds"
    newRecord.value = 151
    newRecord.weight = 6
    print "CLOT:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "full          :", newRecord.full
    print "script        :", newRecord.script
    print "enchantment   :", newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "flags         :", newRecord.flags
    print "maleBody.modPath  :", newRecord.maleBody.modPath
    print "maleBody.modb     :", newRecord.maleBody.modb
    print "maleBody.modt_p   :", newRecord.maleBody.modt_p
    print "maleWorld.modPath :", newRecord.maleWorld.modPath
    print "maleWorld.modb    :", newRecord.maleWorld.modb
    print "maleWorld.modt_p  :", newRecord.maleWorld.modt_p
    print "maleIconPath      :", newRecord.maleIconPath
    print "femaleBody.modPath  :", newRecord.femaleBody.modPath
    print "femaleBody.modb     :", newRecord.femaleBody.modb
    print "femaleBody.modt_p   :", newRecord.femaleBody.modt_p
    print "femaleWorld.modPath :", newRecord.femaleWorld.modPath
    print "femaleWorld.modb    :", newRecord.femaleWorld.modb
    print "femaleWorld.modt_p  :", newRecord.femaleWorld.modt_p
    print "femaleIconPath      :", newRecord.femaleIconPath
    print "value          :", newRecord.value
    print "weight         :", newRecord.weight
    print "CLOT:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].CLOT:
        record.CopyAsOverride(newMod)

    print "CLOT:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].CLOT:
        record.CopyAsNew(newMod)

    print "CLOT:Save Test - TestCLOT.esp"
    newMod.save()
    print "CLOT:Finished testing"
    Current.Close()

def TestCONT():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCONT.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].CONT:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "CONT:Create Record Test"
    newRecord = newMod.create_CONT()
    d(newRecord)

    print "CONT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CONTWarTest"
    print "full..."
    newRecord.full = "Fancy CONT"

    print "modPath..."
    newRecord.modPath = r"CONT\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.script = FormID(7)
    item = newRecord.create_item()
    item.item = FormID(0x0100000A)
    item.count = 50
    item = newRecord.create_item()
    item.item = FormID(0x0000000B)
    item.count = 1
    item = newRecord.create_item()
    item.item = FormID(0x0000000C)
    item.count = 2
    item = newRecord.create_item()
    item.item = FormID(0x0000000D)
    item.count = 3
    print newRecord.items
    printRecord(newRecord.items)
    print
    newRecord.items = [newRecord.items[3], newRecord.items[2], newRecord.items[0]]
    print 6
    newRecord.flags = 1
    print 7
    newRecord.weight = 3.56
    print 8
    newRecord.soundOpen  = FormID(0x00000007)
    print 9
    newRecord.soundClose = FormID(0x00000008)

    print "CONT:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "script     :", newRecord.script
    print "items      :"
    for item in newRecord.items:
        print "  %i: item: %s, count: %i" % (item._ListIndex, item.item, item.count)
    print "flags      :", newRecord.flags
    print "weight     :", newRecord.weight
    print "soundOpen  :", newRecord.soundOpen
    print "soundClose :", newRecord.soundClose

    print "CONT:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].CONT:
        record.CopyAsOverride(newMod)

    print "CONT:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].CONT:
        record.CopyAsNew(newMod)

    print "CONT:Save Test - TestCONT.esp"
    newMod.save()
    print "CONT:Finished testing"
    Current.Close()

def TestDOOR():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestDOOR.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].DOOR:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "DOOR:Create Record Test"
    newRecord = newMod.create_DOOR()
    d(newRecord)

    print "DOOR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "DOORWarTest"
    print "full..."
    newRecord.full = "Fancy DOOR"

    print "modPath..."
    newRecord.modPath = r"DOOR\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.1
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.script = FormID(8)
    newRecord.soundOpen  = FormID(0x00000007)
    newRecord.soundClose = FormID(0x00000008)
    newRecord.soundLoop = FormID(0x00000009)

    newRecord.flags = 1
    newRecord.destinations = [FormID(0xFF000121), FormID(0xFE000222)]
    print "DOOR:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "script     :", newRecord.script
    print "soundOpen  :", newRecord.soundOpen
    print "soundClose :", newRecord.soundClose
    print "soundLoop  :", newRecord.soundLoop

    print "flags   :", newRecord.flags
    print "destinations :"
    for destination in newRecord.destinations:
        print "  ", destination

    print "DOOR:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].DOOR:
        record.CopyAsOverride(newMod)

    print "DOOR:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].DOOR:
        record.CopyAsNew(newMod)

    print "DOOR:Save Test - TestDOOR.esp"
    newMod.save()
    print "DOOR:Finished testing"
    Current.Close()

def TestINGR():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestINGR.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].INGR:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "INGR:Create Record Test"
    newRecord = newMod.create_INGR()
    d(newRecord)

    print "INGR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "INGRWarTest"
    print "full..."
    newRecord.full = "Fancy INGR"

    print "modPath..."
    newRecord.modPath = r"INGR\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"INGR\path\test.dds"
    newRecord.script = FormID(7)
    newRecord.weight = 3.56
    newRecord.value = 150

    newRecord.flags = 1

    newRecord.unused1 = [0x00, 0xFE, 0xFD]

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.rangeType = 4
    newEffect.actorValue = ActorValue(5)
    newEffect.script = FormID(0xFF000007)
    newEffect.schoolType = 324
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "INGR?"

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.rangeType = 9
    newEffect.actorValue = ActorValue(10)
    newEffect.script = FormID(0xFF00000A)
    newEffect.schoolType = 11
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "INGR??"

    print "INGR:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script
    print "weight  :", newRecord.weight
    print "value   :", newRecord.value
    print "flags   :", newRecord.flags

    print "unused1 :", newRecord.unused1

    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  rangeType  :", effect.rangeType
        print "  actorValue :", effect.actorValue
        print "  script     :", effect.script
        print "  schoolType :", effect.schoolType
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print
    print "INGR:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].INGR:
        record.CopyAsOverride(newMod)

    print "INGR:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].INGR:
        record.CopyAsNew(newMod)

    print "INGR:Save Test - TestINGR.esp"
    newMod.save()
    print "INGR:Finished testing"
    Current.Close()

def TestLIGH():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLIGH.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].LIGH:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "LIGH:Create Record Test"
    newRecord = newMod.create_LIGH()
    d(newRecord)

    print "LIGH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LIGHWarTest"

    print "modPath..."
    newRecord.modPath = r"LIGH\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.26
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.script = FormID(7)

    print "full..."
    newRecord.full = "Fancy LIGH"
    print "iconPath..."
    newRecord.iconPath = r"LIGH\path\test.dds"

    newRecord.duration = -1
    newRecord.radius = 256

    newRecord.red = 70
    newRecord.green = 71
    newRecord.blue = 72
    newRecord.unused1 = [12]

    newRecord.flags = 1
    newRecord.falloff = 12.6
    newRecord.fov = 35.1
    newRecord.value = 70
    newRecord.weight = 5.2
    newRecord.fade = 6.9
    newRecord.sound = FormID(14)

    print "LIGH:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "script  :", newRecord.script
    print "full    :", newRecord.full
    print "iconPath:", newRecord.iconPath
    print "duration:", newRecord.duration
    print "radius  :", newRecord.radius

    print "red     :", newRecord.red
    print "green   :", newRecord.green
    print "blue    :", newRecord.blue
    print "unused1 :", newRecord.unused1

    print "flags   :", newRecord.flags
    print "falloff :", newRecord.falloff
    print "fov     :", newRecord.fov
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight
    print "fade    :", newRecord.fade
    print "sound   :", newRecord.sound

    print "LIGH:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].LIGH:
        record.CopyAsOverride(newMod)

    print "LIGH:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].LIGH:
        record.CopyAsNew(newMod)

    print "LIGH:Save Test - TestLIGH.esp"
    newMod.save()
    print "LIGH:Finished testing"
    Current.Close()

def TestMISC():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestMISC.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].MISC:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "MISC:Create Record Test"
    newRecord = newMod.create_MISC()
    d(newRecord)

    print "MISC:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "MISCWarTest"
    print "full..."
    newRecord.full = "Fancy MISC"

    print "modPath..."
    newRecord.modPath = r"Blah\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"MISC\path\test.dds"
    newRecord.script = FormID(7)
    newRecord.value = 150
    newRecord.weight = 3.56

    print "MISC:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight

    print "MISC:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].MISC:
        record.CopyAsOverride(newMod)

    print "MISC:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].MISC:
        record.CopyAsNew(newMod)

    print "MISC:Save Test - TestMISC.esp"
    newMod.save()
    print "MISC:Finished testing"
    Current.Close()

def TestSTAT():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSTAT.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].STAT:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "STAT:Create Record Test"
    newRecord = newMod.create_STAT()
    d(newRecord)

    print "STAT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "STATWarTest"

    print "modPath..."
    newRecord.modPath = r"STAT\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.16
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "STAT:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "STAT:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].STAT:
        record.CopyAsOverride(newMod)

    print "STAT:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].STAT:
        record.CopyAsNew(newMod)

    print "STAT:Save Test - TestSTAT.esp"
    newMod.save()
    print "STAT:Finished testing"
    Current.Close()

def TestGRAS():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestGRAS.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].GRAS:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "GRAS:Create Record Test"
    newRecord = newMod.create_GRAS()
    d(newRecord)

    print "GRAS:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "GRASWarTest"

    newRecord.modPath = r"GRAS\path\test.nif"
    newRecord.modb = 1.5
    newRecord.modt_p = [0xFF, 0x00, 0xFE]
    newRecord.density = 1
    newRecord.minSlope = 1
    newRecord.maxSlope = 255
    newRecord.unused1 = [1]
    newRecord.waterDistance = 300
    newRecord.unused2 = [0xFF, 0xFE]
    newRecord.waterOp = 5
    newRecord.posRange = 1.2
    newRecord.heightRange = 1.3
    newRecord.colorRange = 1.4
    newRecord.wavePeriod = 1.5
    newRecord.flags = 1
    newRecord.unused3 = [0xFF, 0x00, 0xFE]

    print "GRAS:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "density       :", newRecord.density
    print "minSlope      :", newRecord.minSlope
    print "maxSlope      :", newRecord.maxSlope
    print "unused1       :", newRecord.unused1
    print "waterDistance :", newRecord.waterDistance
    print "unused2       :", newRecord.unused2
    print "waterOp       :", newRecord.waterOp
    print "posRange      :", newRecord.posRange
    print "heightRange   :", newRecord.heightRange
    print "colorRange    :", newRecord.colorRange
    print "wavePeriod    :", newRecord.wavePeriod
    print "flags         :", newRecord.flags
    print "unused3       :", newRecord.unused3

    print "GRAS:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].GRAS:
        record.CopyAsOverride(newMod)

    print "GRAS:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].GRAS:
        record.CopyAsNew(newMod)

    print "GRAS:Save Test - TestGRAS.esp"
    newMod.save()
    print "GRAS:Finished testing"
    Current.Close()

def TestTREE():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestTREE.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].TREE:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "TREE:Create Record Test"
    newRecord = newMod.create_TREE()
    d(newRecord)

    print "TREE:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "TREEWarTest"

    newRecord.modPath = r"TREE\path\test.nif"
    newRecord.modb = 1.3
    newRecord.modt_p = [0xFF, 0x00, 0xFE]
    newRecord.iconPath = r"TREE\path\test.dds"
    newRecord.speedTree = [1, 12, 15, 20303]
    newRecord.curvature = 1.4
    newRecord.minAngle = 1.5
    newRecord.maxAngle = 1.6
    newRecord.branchDim = 1.7
    newRecord.leafDim = 1.8
    newRecord.shadowRadius = 12
    newRecord.rockSpeed = 1.9
    newRecord.rustleSpeed = 2.0
    newRecord.widthBill = 2.1
    newRecord.heightBill = 2.2

    print "TREE:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath      :", newRecord.modPath
    print "modb         :", newRecord.modb
    print "modt_p       :", newRecord.modt_p
    print "iconPath     :", newRecord.iconPath
    print "speedTree    :", newRecord.speedTree
    print "curvature    :", newRecord.curvature
    print "minAngle     :", newRecord.minAngle
    print "maxAngle     :", newRecord.maxAngle
    print "branchDim    :", newRecord.branchDim
    print "leafDim      :", newRecord.leafDim
    print "shadowRadius :", newRecord.shadowRadius
    print "rockSpeed    :", newRecord.rockSpeed
    print "rustleSpeed  :", newRecord.rustleSpeed
    print "widthBill    :", newRecord.widthBill
    print "heightBill   :", newRecord.heightBill

    print "TREE:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].TREE:
        record.CopyAsOverride(newMod)

    print "TREE:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].TREE:
        record.CopyAsNew(newMod)

    print "TREE:Save Test - TestTREE.esp"
    newMod.save()
    print "TREE:Finished testing"
    Current.Close()

def TestFLOR():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestFLOR.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].FLOR:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "FLOR:Create Record Test"
    newRecord = newMod.create_FLOR()
    d(newRecord)

    print "FLOR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "FLORWarTest"

    newRecord.full = "Fancy FLOR"
    newRecord.modPath = r"GRAS\path\test.nif"
    newRecord.modb = 1.5
    newRecord.modt_p = [0xFF, 0x00, 0xFE]
    newRecord.script = FormID(7)
    newRecord.ingredient = FormID(15)
    newRecord.spring = 25
    newRecord.summer = 35
    newRecord.fall = 45
    newRecord.winter = 55

    print "FLOR:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full       :", newRecord.full
    print "modPath    :", newRecord.modPath
    print "modb       :", newRecord.modb
    print "modt_p     :", newRecord.modt_p
    print "script     :", newRecord.script
    print "ingredient :", newRecord.ingredient
    print "spring     :", newRecord.spring
    print "summer     :", newRecord.summer
    print "fall       :", newRecord.fall
    print "winter     :", newRecord.winter
    print "FLOR:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].FLOR:
        record.CopyAsOverride(newMod)

    print "FLOR:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].FLOR:
        record.CopyAsNew(newMod)

    print "FLOR:Save Test - TestFLOR.esp"
    newMod.save()
    print "FLOR:Finished testing"
    Current.Close()

def TestFURN():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestFURN.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].FURN:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "FURN:Create Record Test"
    newRecord = newMod.create_FURN()
    d(newRecord)

    print "FURN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "FURNWarTest"
    print "full..."
    newRecord.full = "Fancy FURN"

    print "modPath..."
    newRecord.modPath = r"FURN\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.26
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.script = FormID(7)
    newRecord.flags = 1

    print "FURN:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "script  :", newRecord.script
    print "flags   :", newRecord.flags

    print "FURN:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].FURN:
        record.CopyAsOverride(newMod)

    print "FURN:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].FURN:
        record.CopyAsNew(newMod)

    print "FURN:Save Test - TestFURN.esp"
    newMod.save()
    print "FURN:Finished testing"
    Current.Close()

def TestWEAP():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWEAP.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].WEAP:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "WEAP:Create Record Test"
    newRecord = newMod.create_WEAP()
    d(newRecord)

    print "WEAP:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WEAPWarTest"

    newRecord.full = "Fancy WEAP"

    print "modPath..."
    newRecord.modPath = r"WEAP\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.46
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"WEAP\path\test.dds"
    newRecord.script = FormID(7)

    newRecord.enchantment = FormID(15)
    newRecord.enchantPoints = 255
    newRecord.weaponType = 1
    newRecord.speed = 1.2
    newRecord.reach = 1.3
    newRecord.flags = 1
    newRecord.value = 151
    newRecord.health = 362
    newRecord.weight = 32.5
    newRecord.damage = 15

    print "WEAP:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full          :", newRecord.full
    print "modPath       :", newRecord.modPath
    print "modb          :", newRecord.modb
    print "modt_p        :", newRecord.modt_p
    print "iconPath      :", newRecord.iconPath
    print "script        :", newRecord.script
    print "enchantment   :", newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "weaponType    :", newRecord.weaponType
    print "speed         :", newRecord.speed
    print "reach         :", newRecord.reach
    print "flags         :", newRecord.flags
    print "value         :", newRecord.value
    print "health        :", newRecord.health
    print "weight        :", newRecord.weight
    print "damage        :", newRecord.damage

    print "WEAP:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].WEAP:
        record.CopyAsOverride(newMod)

    print "WEAP:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].WEAP:
        record.CopyAsNew(newMod)

    print "WEAP:Save Test - TestWEAP.esp"
    newMod.save()
    print "WEAP:Finished testing"
    Current.Close()

def TestAMMO():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestAMMO.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].AMMO:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "AMMO:Create Record Test"
    newRecord = newMod.create_AMMO()
    d(newRecord)

    print "AMMO:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "AMMOWarTest"

    newRecord.full = "Fancy AMMO"

    print "modPath..."
    newRecord.modPath = r"AMMO\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.46
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"AMMO\path\test.dds"

    newRecord.enchantment = FormID(15)
    newRecord.enchantPoints = 255
    newRecord.speed = 1.2
    newRecord.flags = 1
    newRecord.unused1 = [0x08, 0x25, 0xFF]
    newRecord.value = 151
    newRecord.weight = 32.5
    newRecord.damage = 15

    print "AMMO:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full          :", newRecord.full
    print "modPath       :", newRecord.modPath
    print "modb          :", newRecord.modb
    print "modt_p        :", newRecord.modt_p
    print "iconPath      :", newRecord.iconPath
    print "enchantment   :", newRecord.enchantment
    print "enchantPoints :", newRecord.enchantPoints
    print "speed         :", newRecord.speed
    print "flags         :", newRecord.flags
    print "unused1       :", newRecord.unused1
    print "value         :", newRecord.value
    print "weight        :", newRecord.weight
    print "damage        :", newRecord.damage

    print "AMMO:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].AMMO:
        record.CopyAsOverride(newMod)

    print "AMMO:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].AMMO:
        record.CopyAsNew(newMod)

    print "AMMO:Save Test - TestAMMO.esp"
    newMod.save()
    print "AMMO:Finished testing"
    Current.Close()

def TestNPC_():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestNPC_.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].NPC_:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "NPC_:Create Record Test"
    newRecord = newMod.create_NPC_()
    d(newRecord)

    print "NPC_:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "NPC_WarTest"

    newRecord.full = "Fancy NPC_"

    print "modPath..."
    newRecord.modPath = r"NPC_\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.76
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.flags = 1
    newRecord.baseSpell = 10
    newRecord.fatigue = 20
    newRecord.barterGold = 30
    newRecord.level = 40
    newRecord.calcMin = 50
    newRecord.calcMax = 60

    print "factions..."
    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(1)
    newFaction.rank = 2
    newFaction.unused1 = [1,2,3]

    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(3)
    newFaction.rank = 4
    newFaction.unused1 = [4,5,6]

    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(5)
    newFaction.rank = 6
    newFaction.unused1 = [7,8,9]

    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(7)
    newFaction.rank = 8
    newFaction.unused1 = [10,11,12]
    newRecord.factions =[newRecord.factions[3], newRecord.factions[2], newRecord.factions[0]]

    newRecord.deathItem = FormID(14)
    newRecord.race = FormID(15)
    newRecord.spells = [FormID(0xFF000121), FormID(0xFE000222)]
    newRecord.script = FormID(7)

    item = newRecord.create_item()
    item.item = FormID(0x0100000A)
    item.count = 50
    item = newRecord.create_item()
    item.item = FormID(0x0000000B)
    item.count = 1
    item = newRecord.create_item()
    item.item = FormID(0x0000000C)
    item.count = 2
    item = newRecord.create_item()
    item.item = FormID(0x0000000D)
    item.count = 3
    newRecord.items = [newRecord.items[3], newRecord.items[2], newRecord.items[0]]

    newRecord.aggression = 1
    newRecord.confidence = 2
    newRecord.energyLevel = 3
    newRecord.responsibility = 4
    newRecord.services = 1
    newRecord.trainSkill = 5
    newRecord.trainLevel = 6
    newRecord.unused1 = [1,2]

    newRecord.aiPackages = [FormID(0xFF000223), FormID(0xFE000324)]

    newRecord.animations = [r"NPC_\hay2\anim1.nif", r"NPC_\hay2\anim2.nif", r"NPC_\hay2\anim3.nif", r"NPC_\hay2\anim4.nif"]

    newRecord.iclass = FormID(16)
    newRecord.armorer = 7
    newRecord.athletics = 8
    newRecord.blade = 9
    newRecord.block = 10
    newRecord.blunt = 11
    newRecord.h2h = 12
    newRecord.heavyArmor = 13
    newRecord.alchemy = 14
    newRecord.alteration = 15
    newRecord.conjuration = 16
    newRecord.destruction = 17
    newRecord.illusion = 18
    newRecord.mysticism = 19
    newRecord.restoration = 20
    newRecord.acrobatics = 21
    newRecord.lightArmor = 22
    newRecord.marksman = 23
    newRecord.mercantile = 24
    newRecord.security = 25
    newRecord.sneak = 26
    newRecord.speechcraft = 27
    newRecord.health = 28
    newRecord.unused2 = [3,4]
    newRecord.strength = 29
    newRecord.intelligence = 30
    newRecord.willpower = 31
    newRecord.agility = 32
    newRecord.speed = 33
    newRecord.endurance = 34
    newRecord.personality = 35
    newRecord.luck = 36
    newRecord.hair = FormID(9)
    newRecord.hairLength = 1.1
    newRecord.eye = FormID(10)
    newRecord.hairRed = 1
    newRecord.hairGreen = 2
    newRecord.hairBlue = 3
    newRecord.unused3 = [1]
    newRecord.combatStyle = FormID(11)
    newRecord.fggs_p = [4] * 200
    newRecord.fgga_p = [5] * 120
    newRecord.fgts_p = [6] * 200
    newRecord.fnam = 40

    print "NPC_:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full       :", newRecord.full
    print "modPath    :", newRecord.modPath
    print "modb       :", newRecord.modb
    print "modt_p     :", newRecord.modt_p
    print "flags      :", newRecord.flags
    print "baseSpell  :", newRecord.baseSpell
    print "fatigue    :", newRecord.fatigue
    print "barterGold :", newRecord.barterGold
    print "level      :", newRecord.level
    print "calcMin    :", newRecord.calcMin
    print "calcMax    :", newRecord.calcMax
    print "factions"
    for faction in newRecord.factions:
         print "  %i: Faction: %s, Rank: %i, Unused1:" % (faction._ListIndex, faction.faction, faction.rank), faction.unused1
    print "deathItem :", newRecord.deathItem
    print "race      :", newRecord.race

    print "spells    :"
    for spell in newRecord.spells:
        print "  ", spell

    print "script    :", newRecord.script
    print "items     :"
    for item in newRecord.items:
        print "  %i: item: %s, count: %i" % (item._ListIndex, item.item, item.count)
    print "aggression     :", newRecord.aggression
    print "confidence     :", newRecord.confidence
    print "energyLevel    :", newRecord.energyLevel
    print "responsibility :", newRecord.responsibility
    print "services       :", newRecord.services
    print "trainSkill     :", newRecord.trainSkill
    print "trainLevel     :", newRecord.trainLevel
    print "unused1        :", newRecord.unused1

    print "aiPackages     :"
    for package in newRecord.aiPackages:
        print "  ", package

    print "animations     :"
    for animation in newRecord.animations:
        print "  ", animation

    print "iclass         :", newRecord.iclass
    print "armorer      :", newRecord.armorer
    print "athletics    :", newRecord.athletics
    print "blade        :", newRecord.blade
    print "block        :", newRecord.block
    print "blunt        :", newRecord.blunt
    print "h2h          :", newRecord.h2h
    print "heavyArmor   :", newRecord.heavyArmor
    print "alchemy      :", newRecord.alchemy
    print "alteration   :", newRecord.alteration
    print "conjuration  :", newRecord.conjuration
    print "destruction  :", newRecord.destruction
    print "illusion     :", newRecord.illusion
    print "mysticism    :", newRecord.mysticism
    print "restoration  :", newRecord.restoration
    print "acrobatics   :", newRecord.acrobatics
    print "lightArmor   :", newRecord.lightArmor
    print "marksman     :", newRecord.marksman
    print "mercantile   :", newRecord.mercantile
    print "security     :", newRecord.security
    print "sneak        :", newRecord.sneak
    print "speechcraft  :", newRecord.speechcraft
    print "health       :", newRecord.health
    print "unused2      :", newRecord.unused2
    print "strength     :", newRecord.strength
    print "intelligence :", newRecord.intelligence
    print "willpower    :", newRecord.willpower
    print "agility      :", newRecord.agility
    print "speed        :", newRecord.speed
    print "endurance    :", newRecord.endurance
    print "personality  :", newRecord.personality
    print "luck         :", newRecord.luck
    print "hair        :", newRecord.hair
    print "hairLength  :", newRecord.hairLength
    print "eye         :", newRecord.eye
    print "hairRed     :", newRecord.hairRed
    print "hairGreen   :", newRecord.hairGreen
    print "hairBlue    :", newRecord.hairBlue
    print "unused3     :", newRecord.unused3
    print "combatStyle :", newRecord.combatStyle
    print "fggs_p :", newRecord.fggs_p
    print "fgga_p :", newRecord.fgga_p
    print "fgts_p :", newRecord.fgts_p
    print "fnam :", newRecord.fnam
    print "NPC_:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].NPC_:
        record.CopyAsOverride(newMod)

    print "NPC_:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].NPC_:
        record.CopyAsNew(newMod)

    print "NPC_:Save Test - TestNPC_.esp"
    newMod.save()
    print "NPC_:Finished testing"
    Current.Close()

def TestCREA():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCREA.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].CREA:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "CREA:Create Record Test"
    newRecord = newMod.create_CREA()
    d(newRecord)

    print "CREA:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CREAWarTest"

    newRecord.full = "Fancy CREA"

    print "modPath..."
    newRecord.modPath = r"CREA\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.76
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.spells = [FormID(0xFF000121), FormID(0xFE000222)]
    newRecord.bodyParts = [r"CREA\hay2\body1.nif", r"CREA\hay2\body2.nif", r"CREA\hay2\body3.nif", r"CREA\hay2\body4.nif"]

    newRecord.nift_p = [0x00, 0xFE, 0xFE]

    newRecord.flags = 1
    newRecord.baseSpell = 10
    newRecord.fatigue = 20
    newRecord.barterGold = 30
    newRecord.level = 40
    newRecord.calcMin = 50
    newRecord.calcMax = 60

    print "factions..."
    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(1)
    newFaction.rank = 2
    newFaction.unused1 = [1,2,3]

    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(3)
    newFaction.rank = 4
    newFaction.unused1 = [4,5,6]

    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(5)
    newFaction.rank = 6
    newFaction.unused1 = [7,8,9]

    newFaction = newRecord.create_faction()
    newFaction.faction = FormID(7)
    newFaction.rank = 8
    newFaction.unused1 = [10,11,12]
    newRecord.factions =[newRecord.factions[3], newRecord.factions[2], newRecord.factions[0]]

    newRecord.deathItem = FormID(14)
    newRecord.script = FormID(7)

    item = newRecord.create_item()
    item.item = FormID(0x0100000A)
    item.count = 50
    item = newRecord.create_item()
    item.item = FormID(0x0000000B)
    item.count = 1
    item = newRecord.create_item()
    item.item = FormID(0x0000000C)
    item.count = 2
    item = newRecord.create_item()
    item.item = FormID(0x0000000D)
    item.count = 3
    newRecord.items = [newRecord.items[3], newRecord.items[2], newRecord.items[0]]

    newRecord.aggression = 1
    newRecord.confidence = 2
    newRecord.energyLevel = 3
    newRecord.responsibility = 4
    newRecord.services = 1
    newRecord.trainSkill = 5
    newRecord.trainLevel = 6
    newRecord.unused1 = [1,2]

    newRecord.aiPackages = [FormID(0xFF000223), FormID(0xFE000324)]

    newRecord.animations = [r"CREA\hay2\anim1.nif", r"CREA\hay2\anim2.nif", r"CREA\hay2\anim3.nif", r"CREA\hay2\anim4.nif"]

    newRecord.creatureType = 1
    newRecord.combat = 7
    newRecord.magic = 8
    newRecord.stealth = 9
    newRecord.soulType = 1
    newRecord.unused2 = [3]
    newRecord.health = 27
    newRecord.unused3 = [4,5]
    newRecord.attackDamage = 28
    newRecord.strength = 29
    newRecord.intelligence = 30
    newRecord.willpower = 31
    newRecord.agility = 32
    newRecord.speed = 33
    newRecord.endurance = 34
    newRecord.personality = 35
    newRecord.luck = 36
    newRecord.attackReach = 10
    newRecord.combatStyle = FormID(11)
    newRecord.turningSpeed = 1.1
    newRecord.baseScale = 1.2
    newRecord.footWeight = 1.3
    newRecord.inheritsSoundsFrom = FormID(0x14)
    newRecord.bloodSprayPath = r"CREA\bloodSprayPath\anim1.dds"
    newRecord.bloodDecalPath = r"CREA\bloodDecalPath\anim1.dds"

    sound = newRecord.create_sound()
    sound.soundType = 0
    sound.sound = FormID(0x0100000A)
    sound.chance = 0
    sound = newRecord.create_sound()
    sound.soundType = 1
    sound.sound = FormID(0x0000000B)
    sound.chance = 1
    sound = newRecord.create_sound()
    sound.soundType = 2
    sound.sound = FormID(0x0000000C)
    sound.chance = 2
    sound = newRecord.create_sound()
    sound.soundType = 3
    sound.sound = FormID(0x0000000D)
    sound.chance = 3
    newRecord.sounds = [newRecord.sounds[3], newRecord.sounds[2], newRecord.sounds[0]]

    print "CREA:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full       :", newRecord.full
    print "modPath    :", newRecord.modPath
    print "modb       :", newRecord.modb
    print "modt_p     :", newRecord.modt_p

    print "spells"
    for spell in newRecord.spells:
        print "  ", spell

    print "bodyParts"
    for bodyPart in newRecord.bodyParts:
        print "  ", bodyPart

    print "nift_p     :", newRecord.nift_p

    print "flags      :", newRecord.flags
    print "baseSpell  :", newRecord.baseSpell
    print "fatigue    :", newRecord.fatigue
    print "barterGold :", newRecord.barterGold
    print "level      :", newRecord.level
    print "calcMin    :", newRecord.calcMin
    print "calcMax    :", newRecord.calcMax

    print "factions"
    for faction in newRecord.factions:
         print "  %i: Faction: %s, Rank: %i, Unused1:" % (faction._ListIndex, faction.faction, faction.rank), faction.unused1

    print "deathItem :", newRecord.deathItem
    print "script    :", newRecord.script

    print "items"
    for item in newRecord.items:
        print "  %i: item: %s, count: %i" % (item._ListIndex, item.item, item.count)

    print "aggression     :", newRecord.aggression
    print "confidence     :", newRecord.confidence
    print "energyLevel    :", newRecord.energyLevel
    print "responsibility :", newRecord.responsibility
    print "services       :", newRecord.services
    print "trainSkill     :", newRecord.trainSkill
    print "trainLevel     :", newRecord.trainLevel
    print "unused1        :", newRecord.unused1

    print "aiPackages     :"
    for package in newRecord.aiPackages:
        print "  ", package

    print "animations     :"
    for animation in newRecord.animations:
        print "  ", animation

    print "creatureType :", newRecord.creatureType
    print "combat       :", newRecord.combat
    print "magic        :", newRecord.magic
    print "stealth      :", newRecord.stealth
    print "soulType         :", newRecord.soulType
    print "unused2      :", newRecord.unused2
    print "health       :", newRecord.health
    print "unused3      :", newRecord.unused3
    print "attackDamage :", newRecord.attackDamage
    print "strength     :", newRecord.strength
    print "intelligence :", newRecord.intelligence
    print "willpower    :", newRecord.willpower
    print "agility      :", newRecord.agility
    print "speed        :", newRecord.speed
    print "endurance    :", newRecord.endurance
    print "personality  :", newRecord.personality
    print "luck         :", newRecord.luck

    print "attackReach  :", newRecord.attackReach
    print "combatStyle  :", newRecord.combatStyle
    print "turningSpeed :", newRecord.turningSpeed
    print "baseScale    :", newRecord.baseScale
    print "footWeight   :", newRecord.footWeight
    print "inheritsSoundsFrom  :", newRecord.inheritsSoundsFrom
    print "bloodSprayPath      :", newRecord.bloodSprayPath
    print "bloodDecalPath      :", newRecord.bloodDecalPath

    print "sounds"
    for sound in newRecord.sounds:
        print "  %i: type: %u, sound: %s, chance:%i" % (sound._ListIndex, sound.soundType, sound.sound, sound.chance)
    print "CREA:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].CREA:
        record.CopyAsOverride(newMod)

    print "CREA:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].CREA:
        record.CopyAsNew(newMod)

    print "CREA:Save Test - TestCREA.esp"
    newMod.save()
    print "CREA:Finished testing"
    Current.Close()

def TestLVLC():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLVLC.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].LVLC:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "LVLC:Create Record Test"
    newRecord = newMod.create_LVLC()
    d(newRecord)

    print "LVLC:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LVLCWarTest"

    newRecord.chanceNone = 20
    newRecord.flags = 1
    newRecord.script = FormID(7)
    newRecord.template = FormID(0x14)

    entry = newRecord.create_entry()
    entry.level = 1
    entry.unused1 = [0x14, 0xFF]
    entry.listId = FormID(0x0100000A)
    entry.count = 2
    entry.unused2 = [0x15, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 3
    entry.unused1 = [0x16, 0xFF]
    entry.listId = FormID(0x0000000B)
    entry.count = 4
    entry.unused2 = [0x17, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 5
    entry.unused1 = [0x18, 0xFF]
    entry.listId = FormID(0x0000000C)
    entry.count = 6
    entry.unused2 = [0x19, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 7
    entry.unused1 = [0x20, 0xFF]
    entry.listId = FormID(0x0000000D)
    entry.count = 8
    entry.unused2 = [0x21, 0xFF]
    newRecord.entries = [newRecord.entries[3], newRecord.entries[2], newRecord.entries[0]]


    print "LVLC:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "chanceNone :", newRecord.chanceNone
    print "flags      :", newRecord.flags
    print "script     :", newRecord.script
    print "template   :", newRecord.template
    print "entries"
    for entry in newRecord.entries:
        print
        print "  level   :", entry.level
        print "  unused1 :", entry.unused1
        print "  listId  :", entry.listId
        print "  count   :", entry.count
        print "  unused2 :", entry.unused2

    print "LVLC:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].LVLC:
        record.CopyAsOverride(newMod)

    print "LVLC:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].LVLC:
        record.CopyAsNew(newMod)

    print "LVLC:Save Test - TestLVLC.esp"
    newMod.save()
    print "LVLC:Finished testing"
    Current.Close()

def TestSLGM():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSLGM.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].SLGM:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "SLGM:Create Record Test"
    newRecord = newMod.create_SLGM()
    d(newRecord)

    print "SLGM:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SLGMWarTest"
    print "full..."
    newRecord.full = "Fancy SLGM"

    print "modPath..."
    newRecord.modPath = r"SLGM\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"SLGM\path\test.dds"
    newRecord.script = FormID(7)
    newRecord.value = 150
    newRecord.weight = 3.56

    newRecord.soulType = 1
    newRecord.capacityType = 50

    print "SLGM:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight

    print "soulType     :", newRecord.soulType
    print "capacityType :", newRecord.capacityType

    print "SLGM:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SLGM:
        record.CopyAsOverride(newMod)

    print "SLGM:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SLGM:
        record.CopyAsNew(newMod)

    print "SLGM:Save Test - TestSLGM.esp"
    newMod.save()
    print "SLGM:Finished testing"
    Current.Close()

def TestKEYM():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestKEYM.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].KEYM:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "KEYM:Create Record Test"
    newRecord = newMod.create_KEYM()
    d(newRecord)

    print "KEYM:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "KEYMWarTest"
    print "full..."
    newRecord.full = "Fancy KEYM"

    print "modPath..."
    newRecord.modPath = r"KEYM\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"KEYM\path\test.dds"
    newRecord.script = FormID(7)
    newRecord.value = 150
    newRecord.weight = 3.56

    print "KEYM:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p
    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight

    print "KEYM:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].KEYM:
        record.CopyAsOverride(newMod)

    print "KEYM:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].KEYM:
        record.CopyAsNew(newMod)

    print "KEYM:Save Test - TestKEYM.esp"
    newMod.save()
    print "KEYM:Finished testing"
    Current.Close()

def TestALCH():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestALCH.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].ALCH:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "ALCH:Create Record Test"
    newRecord = newMod.create_ALCH()
    d(newRecord)

    print "ALCH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ALCHWarTest"
    print "full..."
    newRecord.full = "Fancy ALCH"

    print "modPath..."
    newRecord.modPath = r"ALCH\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"ALCH\path\test.dds"
    newRecord.script = FormID(7)
    newRecord.weight = 3.56
    newRecord.value = 150

    newRecord.flags = 1

    newRecord.unused1 = [0x00, 0xFE, 0xFD]

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 3
    newEffect.rangeType = 4
    newEffect.actorValue = ActorValue(5)
    newEffect.script = FormID(0xFF000007)
    newEffect.schoolType = 324
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "ALCH?"

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 8
    newEffect.rangeType = 9
    newEffect.actorValue = ActorValue(10)
    newEffect.script = FormID(0xFF00000A)
    newEffect.schoolType = 11
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "ALCH??"

    print "ALCH:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script
    print "weight  :", newRecord.weight
    print "value   :", newRecord.value
    print "flags   :", newRecord.flags

    print "unused1 :", newRecord.unused1

    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  rangeType  :", effect.rangeType
        print "  actorValue :", effect.actorValue
        print "  script     :", effect.script
        print "  schoolType :", effect.schoolType
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print
    print "ALCH:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].ALCH:
        record.CopyAsOverride(newMod)

    print "ALCH:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].ALCH:
        record.CopyAsNew(newMod)

    print "ALCH:Save Test - TestALCH.esp"
    newMod.save()
    print "ALCH:Finished testing"
    Current.Close()

def TestSBSP():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSBSP.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].SBSP:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "SBSP:Create Record Test"
    newRecord = newMod.create_SBSP()
    d(newRecord)

    print "SBSP:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SBSPWarTest"

    newRecord.sizeX = 1.0
    newRecord.sizeY = 2.0
    newRecord.sizeZ = 3.0
    print "SBSP:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid
    print "sizeX  :", newRecord.sizeX
    print "sizeY  :", newRecord.sizeY
    print "sizeZ  :", newRecord.sizeZ


    print "SBSP:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SBSP:
        record.CopyAsOverride(newMod)

    print "SBSP:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SBSP:
        record.CopyAsNew(newMod)

    print "SBSP:Save Test - TestSBSP.esp"
    newMod.save()
    print "SBSP:Finished testing"
    Current.Close()

def TestSGST():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestSGST.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].SGST:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "SGST:Create Record Test"
    newRecord = newMod.create_SGST()
    d(newRecord)

    print "SGST:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "SGSTWarTest"
    print "full..."
    newRecord.full = "Fancy SGST"

    print "modPath..."
    newRecord.modPath = r"SGST\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    print "iconPath..."
    newRecord.iconPath = r"SGST\path\test.dds"
    newRecord.script = FormID(7)

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 1
    newEffect.area = 2
    newEffect.duration = 6
    newEffect.rangeType = 6
    newEffect.actorValue = ActorValue(5)
    newEffect.script = FormID(0x00000007)
    newEffect.schoolType = 324
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 16
    newEffect.unused1 = [3,4,5]
    newEffect.full = "SGST?"

    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 6
    newEffect.area = 7
    newEffect.duration = 7
    newEffect.rangeType = 9
    newEffect.actorValue = ActorValue(10)
    newEffect.script = FormID(0x0000000A)
    newEffect.schoolType = 11
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "SGST??"


    newEffect = newRecord.create_effect()
    newEffect.name0 = MGEFCode("SEFF")
    newEffect.name = MGEFCode("SEFF")
    newEffect.magnitude = 6
    newEffect.area = 8
    newEffect.duration = 8
    newEffect.rangeType = 9
    newEffect.actorValue = ActorValue(10)
    newEffect.script = FormID(0x0000000A)
    newEffect.schoolType = 11
    newEffect.visual = MGEFCode("SEFF")
    newEffect.flags = 13
    newEffect.unused1 = [6,7,8]
    newEffect.full = "SGST???"

    newRecord.effects = [newRecord.effects[0], newRecord.effects[2]]

    newRecord.uses = 16
    newRecord.value = 150
    newRecord.weight = 3.56

    print "SGST:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full    :", newRecord.full
    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "iconPath:", newRecord.iconPath
    print "script  :", newRecord.script

    print "effects :"
    for effect in newRecord.effects:
        print "  name0      :", effect.name0
        print "  name       :", effect.name
        print "  magnitude  :", effect.magnitude
        print "  area       :", effect.area
        print "  duration   :", effect.duration
        print "  rangeType  :", effect.rangeType
        print "  actorValue :", effect.actorValue
        print "  script     :", effect.script
        print "  schoolType :", effect.schoolType
        print "  visual     :", effect.visual
        print "  flags      :", effect.flags
        print "  unused1    :", effect.unused1
        print "  full       :", effect.full
        print

    print "uses   :", newRecord.uses
    print "value   :", newRecord.value
    print "weight  :", newRecord.weight

    print "SGST:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].SGST:
        record.CopyAsOverride(newMod)

    print "SGST:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].SGST:
        record.CopyAsNew(newMod)

    print "SGST:Save Test - TestSGST.esp"
    newMod.save()
    print "SGST:Finished testing"
    Current.Close()

def TestLVLI():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLVLI.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].LVLI:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "LVLI:Create Record Test"
    newRecord = newMod.create_LVLI()
    d(newRecord)

    print "LVLI:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LVLIWarTest"

    newRecord.chanceNone = 20
    newRecord.flags = 1

    entry = newRecord.create_entry()
    entry.level = 1
    entry.unused1 = [0x14, 0xFF]
    entry.listId = FormID(0x0100000A)
    entry.count = 2
    entry.unused2 = [0x15, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 3
    entry.unused1 = [0x16, 0xFF]
    entry.listId = FormID(0x0000000B)
    entry.count = 4
    entry.unused2 = [0x17, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 5
    entry.unused1 = [0x18, 0xFF]
    entry.listId = FormID(0x0000000C)
    entry.count = 6
    entry.unused2 = [0x19, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 7
    entry.unused1 = [0x20, 0xFF]
    entry.listId = FormID(0x0000000D)
    entry.count = 8
    entry.unused2 = [0x21, 0xFF]
    newRecord.entries = [newRecord.entries[3], newRecord.entries[2], newRecord.entries[0]]

    print "LVLI:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "chanceNone :", newRecord.chanceNone
    print "flags      :", newRecord.flags
    print "entries"
    for entry in newRecord.entries:
        print
        print "  level   :", entry.level
        print "  unused1 :", entry.unused1
        print "  listId  :", entry.listId
        print "  count   :", entry.count
        print "  unused2 :", entry.unused2
    print "LVLI:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].LVLI:
        record.CopyAsOverride(newMod)

    print "LVLI:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].LVLI:
        record.CopyAsNew(newMod)

    print "LVLI:Save Test - TestLVLI.esp"
    newMod.save()
    print "LVLI:Finished testing"
    Current.Close()

def TestWTHR():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWTHR.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].WTHR:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "WTHR:Create Record Test"
    newRecord = newMod.create_WTHR()
    d(newRecord)

    print "WTHR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WTHRWarTest"
    newRecord.lowerLayerPath = r"WTHR\Test1\e.dds"
    newRecord.upperLayerPath = r"WTHR\Test2\d.dds"
    print "modPath..."
    newRecord.modPath = r"WTHR\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.56
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    newRecord.upperSky.riseRed = 1
    newRecord.upperSky.riseGreen = 2
    newRecord.upperSky.riseBlue = 3
    newRecord.upperSky.unused1 = [1]
    newRecord.upperSky.dayRed = 4
    newRecord.upperSky.dayGreen = 5
    newRecord.upperSky.dayBlue = 6
    newRecord.upperSky.unused2 = [2]
    newRecord.upperSky.setRed = 7
    newRecord.upperSky.setGreen = 8
    newRecord.upperSky.setBlue = 9
    newRecord.upperSky.unused3 = [3]
    newRecord.upperSky.nightRed = 10
    newRecord.upperSky.nightGreen = 11
    newRecord.upperSky.nightBlue = 12
    newRecord.upperSky.unused4 = [4]
    newRecord.fog.riseRed = 13
    newRecord.fog.riseGreen = 14
    newRecord.fog.riseBlue = 15
    newRecord.fog.unused1 = [4]
    newRecord.fog.dayRed = 16
    newRecord.fog.dayGreen = 17
    newRecord.fog.dayBlue = 18
    newRecord.fog.unused2 = [4]
    newRecord.fog.setRed = 19
    newRecord.fog.setGreen = 20
    newRecord.fog.setBlue = 21
    newRecord.fog.unused3 = [4]
    newRecord.fog.nightRed = 22
    newRecord.fog.nightGreen = 23
    newRecord.fog.nightBlue = 24
    newRecord.fog.unused4 = [4]
    newRecord.lowerClouds.riseRed = 25
    newRecord.lowerClouds.riseGreen = 26
    newRecord.lowerClouds.riseBlue = 27
    newRecord.lowerClouds.unused1 = [4]
    newRecord.lowerClouds.dayRed = 28
    newRecord.lowerClouds.dayGreen = 29
    newRecord.lowerClouds.dayBlue = 30
    newRecord.lowerClouds.unused2 = [4]
    newRecord.lowerClouds.setRed = 31
    newRecord.lowerClouds.setGreen = 32
    newRecord.lowerClouds.setBlue = 33
    newRecord.lowerClouds.unused3 = [4]
    newRecord.lowerClouds.nightRed = 34
    newRecord.lowerClouds.nightGreen = 35
    newRecord.lowerClouds.nightBlue = 36
    newRecord.lowerClouds.unused4 = [4]
    newRecord.ambient.riseRed = 37
    newRecord.ambient.riseGreen = 38
    newRecord.ambient.riseBlue = 39
    newRecord.ambient.unused1 = [4]
    newRecord.ambient.dayRed = 40
    newRecord.ambient.dayGreen = 41
    newRecord.ambient.dayBlue = 42
    newRecord.ambient.unused2 = [4]
    newRecord.ambient.setRed = 43
    newRecord.ambient.setGreen = 44
    newRecord.ambient.setBlue = 45
    newRecord.ambient.unused3 = [4]
    newRecord.ambient.nightRed = 46
    newRecord.ambient.nightGreen = 47
    newRecord.ambient.nightBlue = 48
    newRecord.ambient.unused4 = [4]
    newRecord.sunlight.riseRed = 49
    newRecord.sunlight.riseGreen = 50
    newRecord.sunlight.riseBlue = 51
    newRecord.sunlight.unused1 = [4]
    newRecord.sunlight.dayRed = 52
    newRecord.sunlight.dayGreen = 53
    newRecord.sunlight.dayBlue = 54
    newRecord.sunlight.unused2 = [4]
    newRecord.sunlight.setRed = 55
    newRecord.sunlight.setGreen = 56
    newRecord.sunlight.setBlue = 57
    newRecord.sunlight.unused3 = [4]
    newRecord.sunlight.nightRed = 58
    newRecord.sunlight.nightGreen = 59
    newRecord.sunlight.nightBlue = 60
    newRecord.sunlight.unused4 = [4]
    newRecord.sun.riseRed = 61
    newRecord.sun.riseGreen = 62
    newRecord.sun.riseBlue = 63
    newRecord.sun.unused1 = [4]
    newRecord.sun.dayRed = 64
    newRecord.sun.dayGreen = 65
    newRecord.sun.dayBlue = 66
    newRecord.sun.unused2 = [4]
    newRecord.sun.setRed = 67
    newRecord.sun.setGreen = 68
    newRecord.sun.setBlue = 69
    newRecord.sun.unused3 = [4]
    newRecord.sun.nightRed = 70
    newRecord.sun.nightGreen = 71
    newRecord.sun.nightBlue = 72
    newRecord.sun.unused4 = [4]
    newRecord.stars.riseRed = 73
    newRecord.stars.riseGreen = 74
    newRecord.stars.riseBlue = 75
    newRecord.stars.unused1 = [4]
    newRecord.stars.dayRed = 76
    newRecord.stars.dayGreen = 77
    newRecord.stars.dayBlue = 78
    newRecord.stars.unused2 = [4]
    newRecord.stars.setRed = 79
    newRecord.stars.setGreen = 80
    newRecord.stars.setBlue = 81
    newRecord.stars.unused3 = [4]
    newRecord.stars.nightRed = 82
    newRecord.stars.nightGreen = 83
    newRecord.stars.nightBlue = 84
    newRecord.stars.unused4 = [4]
    newRecord.lowerSky.riseRed = 85
    newRecord.lowerSky.riseGreen = 86
    newRecord.lowerSky.riseBlue = 87
    newRecord.lowerSky.unused1 = [4]
    newRecord.lowerSky.dayRed = 88
    newRecord.lowerSky.dayGreen = 89
    newRecord.lowerSky.dayBlue = 90
    newRecord.lowerSky.unused2 = [4]
    newRecord.lowerSky.setRed = 91
    newRecord.lowerSky.setGreen = 92
    newRecord.lowerSky.setBlue = 93
    newRecord.lowerSky.unused3 = [4]
    newRecord.lowerSky.nightRed = 94
    newRecord.lowerSky.nightGreen = 95
    newRecord.lowerSky.nightBlue = 96
    newRecord.lowerSky.unused4 = [4]
    newRecord.horizon.riseRed = 97
    newRecord.horizon.riseGreen = 98
    newRecord.horizon.riseBlue = 99
    newRecord.horizon.unused1 = [4]
    newRecord.horizon.dayRed = 100
    newRecord.horizon.dayGreen = 101
    newRecord.horizon.dayBlue = 102
    newRecord.horizon.unused2 = [4]
    newRecord.horizon.setRed = 103
    newRecord.horizon.setGreen = 104
    newRecord.horizon.setBlue = 105
    newRecord.horizon.unused3 = [4]
    newRecord.horizon.nightRed = 106
    newRecord.horizon.nightGreen = 107
    newRecord.horizon.nightBlue = 108
    newRecord.horizon.unused4 = [4]
    newRecord.upperClouds.riseRed = 109
    newRecord.upperClouds.riseGreen = 110
    newRecord.upperClouds.riseBlue = 111
    newRecord.upperClouds.unused1 = [4]
    newRecord.upperClouds.dayRed = 112
    newRecord.upperClouds.dayGreen = 113
    newRecord.upperClouds.dayBlue = 114
    newRecord.upperClouds.unused2 = [4]
    newRecord.upperClouds.setRed = 115
    newRecord.upperClouds.setGreen = 116
    newRecord.upperClouds.setBlue = 117
    newRecord.upperClouds.unused3 = [4]
    newRecord.upperClouds.nightRed = 118
    newRecord.upperClouds.nightGreen = 119
    newRecord.upperClouds.nightBlue = 120
    newRecord.upperClouds.unused4 = [4]

    newRecord.fogDayNear = 1.1
    newRecord.fogDayFar = 1.2
    newRecord.fogNightNear = 1.3
    newRecord.fogNightFar = 1.4

    newRecord.eyeAdaptSpeed = 1.5
    newRecord.blurRadius = 1.6
    newRecord.blurPasses = 1.7
    newRecord.emissiveMult = 1.8
    newRecord.targetLum = 1.9
    newRecord.upperLumClamp = 2.0
    newRecord.brightScale = 2.1
    newRecord.brightClamp = 2.2
    newRecord.lumRampNoTex = 2.3
    newRecord.lumRampMin = 2.4
    newRecord.lumRampMax = 2.5
    newRecord.sunlightDimmer = 2.6
    newRecord.grassDimmer = 2.7
    newRecord.treeDimmer = 2.8

    newRecord.windSpeed = 1
    newRecord.lowerCloudSpeed = 2
    newRecord.upperCloudSpeed = 3
    newRecord.transDelta = 4
    newRecord.sunGlare = 5
    newRecord.sunDamage = 6
    newRecord.rainFadeIn = 7
    newRecord.rainFadeOut = 8
    newRecord.boltFadeIn = 9
    newRecord.boltFadeOut = 10
    newRecord.boltFrequency = 11
    newRecord.weatherType = 12
    newRecord.boltRed = 13
    newRecord.boltGreen = 14
    newRecord.boltBlue = 15

    newSound = newRecord.create_sound()
    newSound.sound = FormID(7)
    newSound.type = 0

    newSound = newRecord.create_sound()
    newSound.sound = FormID(8)
    newSound.type = 1

    newSound = newRecord.create_sound()
    newSound.sound = FormID(9)
    newSound.type = 2

    newSound = newRecord.create_sound()
    newSound.sound = FormID(10)
    newSound.type = 3

    newRecord.sounds = [newRecord.sounds[0], newRecord.sounds[3], newRecord.sounds[2]]

    print "WTHR:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "lowerLayerPath :", newRecord.lowerLayerPath
    print "upperLayerPath :", newRecord.upperLayerPath

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "upperSky.riseRed    :", newRecord.upperSky.riseRed
    print "upperSky.riseGreen  :", newRecord.upperSky.riseGreen
    print "upperSky.riseBlue   :", newRecord.upperSky.riseBlue
    print "upperSky.unused1    :", newRecord.upperSky.unused1
    print "upperSky.dayRed     :", newRecord.upperSky.dayRed
    print "upperSky.dayGreen   :", newRecord.upperSky.dayGreen
    print "upperSky.dayBlue    :", newRecord.upperSky.dayBlue
    print "upperSky.unused2    :", newRecord.upperSky.unused2
    print "upperSky.setRed     :", newRecord.upperSky.setRed
    print "upperSky.setGreen   :", newRecord.upperSky.setGreen
    print "upperSky.setBlue    :", newRecord.upperSky.setBlue
    print "upperSky.unused3    :", newRecord.upperSky.unused3
    print "upperSky.nightRed   :", newRecord.upperSky.nightRed
    print "upperSky.nightGreen :", newRecord.upperSky.nightGreen
    print "upperSky.nightBlue  :", newRecord.upperSky.nightBlue
    print "upperSky.unused4    :", newRecord.upperSky.unused4

    print "fog.riseRed    :", newRecord.fog.riseRed
    print "fog.riseGreen  :", newRecord.fog.riseGreen
    print "fog.riseBlue   :", newRecord.fog.riseBlue
    print "fog.unused1    :", newRecord.fog.unused1
    print "fog.dayRed     :", newRecord.fog.dayRed
    print "fog.dayGreen   :", newRecord.fog.dayGreen
    print "fog.dayBlue    :", newRecord.fog.dayBlue
    print "fog.unused2    :", newRecord.fog.unused2
    print "fog.setRed     :", newRecord.fog.setRed
    print "fog.setGreen   :", newRecord.fog.setGreen
    print "fog.setBlue    :", newRecord.fog.setBlue
    print "fog.unused3    :", newRecord.fog.unused3
    print "fog.nightRed   :", newRecord.fog.nightRed
    print "fog.nightGreen :", newRecord.fog.nightGreen
    print "fog.nightBlue  :", newRecord.fog.nightBlue
    print "fog.unused4    :", newRecord.fog.unused4

    print "lowerClouds.riseRed    :", newRecord.lowerClouds.riseRed
    print "lowerClouds.riseGreen  :", newRecord.lowerClouds.riseGreen
    print "lowerClouds.riseBlue   :", newRecord.lowerClouds.riseBlue
    print "lowerClouds.unused1    :", newRecord.lowerClouds.unused1
    print "lowerClouds.dayRed     :", newRecord.lowerClouds.dayRed
    print "lowerClouds.dayGreen   :", newRecord.lowerClouds.dayGreen
    print "lowerClouds.dayBlue    :", newRecord.lowerClouds.dayBlue
    print "lowerClouds.unused2    :", newRecord.lowerClouds.unused2
    print "lowerClouds.setRed     :", newRecord.lowerClouds.setRed
    print "lowerClouds.setGreen   :", newRecord.lowerClouds.setGreen
    print "lowerClouds.setBlue    :", newRecord.lowerClouds.setBlue
    print "lowerClouds.unused3    :", newRecord.lowerClouds.unused3
    print "lowerClouds.nightRed   :", newRecord.lowerClouds.nightRed
    print "lowerClouds.nightGreen :", newRecord.lowerClouds.nightGreen
    print "lowerClouds.nightBlue  :", newRecord.lowerClouds.nightBlue
    print "lowerClouds.unused4    :", newRecord.lowerClouds.unused4

    print "ambient.riseRed    :", newRecord.ambient.riseRed
    print "ambient.riseGreen  :", newRecord.ambient.riseGreen
    print "ambient.riseBlue   :", newRecord.ambient.riseBlue
    print "ambient.unused1    :", newRecord.ambient.unused1
    print "ambient.dayRed     :", newRecord.ambient.dayRed
    print "ambient.dayGreen   :", newRecord.ambient.dayGreen
    print "ambient.dayBlue    :", newRecord.ambient.dayBlue
    print "ambient.unused2    :", newRecord.ambient.unused2
    print "ambient.setRed     :", newRecord.ambient.setRed
    print "ambient.setGreen   :", newRecord.ambient.setGreen
    print "ambient.setBlue    :", newRecord.ambient.setBlue
    print "ambient.unused3    :", newRecord.ambient.unused3
    print "ambient.nightRed   :", newRecord.ambient.nightRed
    print "ambient.nightGreen :", newRecord.ambient.nightGreen
    print "ambient.nightBlue  :", newRecord.ambient.nightBlue
    print "ambient.unused4    :", newRecord.ambient.unused4

    print "sunlight.riseRed    :", newRecord.sunlight.riseRed
    print "sunlight.riseGreen  :", newRecord.sunlight.riseGreen
    print "sunlight.riseBlue   :", newRecord.sunlight.riseBlue
    print "sunlight.unused1    :", newRecord.sunlight.unused1
    print "sunlight.dayRed     :", newRecord.sunlight.dayRed
    print "sunlight.dayGreen   :", newRecord.sunlight.dayGreen
    print "sunlight.dayBlue    :", newRecord.sunlight.dayBlue
    print "sunlight.unused2    :", newRecord.sunlight.unused2
    print "sunlight.setRed     :", newRecord.sunlight.setRed
    print "sunlight.setGreen   :", newRecord.sunlight.setGreen
    print "sunlight.setBlue    :", newRecord.sunlight.setBlue
    print "sunlight.unused3    :", newRecord.sunlight.unused3
    print "sunlight.nightRed   :", newRecord.sunlight.nightRed
    print "sunlight.nightGreen :", newRecord.sunlight.nightGreen
    print "sunlight.nightBlue  :", newRecord.sunlight.nightBlue
    print "sunlight.unused4    :", newRecord.sunlight.unused4

    print "sun.riseRed    :", newRecord.sun.riseRed
    print "sun.riseGreen  :", newRecord.sun.riseGreen
    print "sun.riseBlue   :", newRecord.sun.riseBlue
    print "sun.unused1    :", newRecord.sun.unused1
    print "sun.dayRed     :", newRecord.sun.dayRed
    print "sun.dayGreen   :", newRecord.sun.dayGreen
    print "sun.dayBlue    :", newRecord.sun.dayBlue
    print "sun.unused2    :", newRecord.sun.unused2
    print "sun.setRed     :", newRecord.sun.setRed
    print "sun.setGreen   :", newRecord.sun.setGreen
    print "sun.setBlue    :", newRecord.sun.setBlue
    print "sun.unused3    :", newRecord.sun.unused3
    print "sun.nightRed   :", newRecord.sun.nightRed
    print "sun.nightGreen :", newRecord.sun.nightGreen
    print "sun.nightBlue  :", newRecord.sun.nightBlue
    print "sun.unused4    :", newRecord.sun.unused4

    print "stars.riseRed    :", newRecord.stars.riseRed
    print "stars.riseGreen  :", newRecord.stars.riseGreen
    print "stars.riseBlue   :", newRecord.stars.riseBlue
    print "stars.unused1    :", newRecord.stars.unused1
    print "stars.dayRed     :", newRecord.stars.dayRed
    print "stars.dayGreen   :", newRecord.stars.dayGreen
    print "stars.dayBlue    :", newRecord.stars.dayBlue
    print "stars.unused2    :", newRecord.stars.unused2
    print "stars.setRed     :", newRecord.stars.setRed
    print "stars.setGreen   :", newRecord.stars.setGreen
    print "stars.setBlue    :", newRecord.stars.setBlue
    print "stars.unused3    :", newRecord.stars.unused3
    print "stars.nightRed   :", newRecord.stars.nightRed
    print "stars.nightGreen :", newRecord.stars.nightGreen
    print "stars.nightBlue  :", newRecord.stars.nightBlue
    print "stars.unused4    :", newRecord.stars.unused4

    print "lowerSky.riseRed    :", newRecord.lowerSky.riseRed
    print "lowerSky.riseGreen  :", newRecord.lowerSky.riseGreen
    print "lowerSky.riseBlue   :", newRecord.lowerSky.riseBlue
    print "lowerSky.unused1    :", newRecord.lowerSky.unused1
    print "lowerSky.dayRed     :", newRecord.lowerSky.dayRed
    print "lowerSky.dayGreen   :", newRecord.lowerSky.dayGreen
    print "lowerSky.dayBlue    :", newRecord.lowerSky.dayBlue
    print "lowerSky.unused2    :", newRecord.lowerSky.unused2
    print "lowerSky.setRed     :", newRecord.lowerSky.setRed
    print "lowerSky.setGreen   :", newRecord.lowerSky.setGreen
    print "lowerSky.setBlue    :", newRecord.lowerSky.setBlue
    print "lowerSky.unused3    :", newRecord.lowerSky.unused3
    print "lowerSky.nightRed   :", newRecord.lowerSky.nightRed
    print "lowerSky.nightGreen :", newRecord.lowerSky.nightGreen
    print "lowerSky.nightBlue  :", newRecord.lowerSky.nightBlue
    print "lowerSky.unused4    :", newRecord.lowerSky.unused4

    print "horizon.riseRed    :", newRecord.horizon.riseRed
    print "horizon.riseGreen  :", newRecord.horizon.riseGreen
    print "horizon.riseBlue   :", newRecord.horizon.riseBlue
    print "horizon.unused1    :", newRecord.horizon.unused1
    print "horizon.dayRed     :", newRecord.horizon.dayRed
    print "horizon.dayGreen   :", newRecord.horizon.dayGreen
    print "horizon.dayBlue    :", newRecord.horizon.dayBlue
    print "horizon.unused2    :", newRecord.horizon.unused2
    print "horizon.setRed     :", newRecord.horizon.setRed
    print "horizon.setGreen   :", newRecord.horizon.setGreen
    print "horizon.setBlue    :", newRecord.horizon.setBlue
    print "horizon.unused3    :", newRecord.horizon.unused3
    print "horizon.nightRed   :", newRecord.horizon.nightRed
    print "horizon.nightGreen :", newRecord.horizon.nightGreen
    print "horizon.nightBlue  :", newRecord.horizon.nightBlue
    print "horizon.unused4    :", newRecord.horizon.unused4

    print "upperClouds.riseRed    :", newRecord.upperClouds.riseRed
    print "upperClouds.riseGreen  :", newRecord.upperClouds.riseGreen
    print "upperClouds.riseBlue   :", newRecord.upperClouds.riseBlue
    print "upperClouds.unused1    :", newRecord.upperClouds.unused1
    print "upperClouds.dayRed     :", newRecord.upperClouds.dayRed
    print "upperClouds.dayGreen   :", newRecord.upperClouds.dayGreen
    print "upperClouds.dayBlue    :", newRecord.upperClouds.dayBlue
    print "upperClouds.unused2    :", newRecord.upperClouds.unused2
    print "upperClouds.setRed     :", newRecord.upperClouds.setRed
    print "upperClouds.setGreen   :", newRecord.upperClouds.setGreen
    print "upperClouds.setBlue    :", newRecord.upperClouds.setBlue
    print "upperClouds.unused3    :", newRecord.upperClouds.unused3
    print "upperClouds.nightRed   :", newRecord.upperClouds.nightRed
    print "upperClouds.nightGreen :", newRecord.upperClouds.nightGreen
    print "upperClouds.nightBlue  :", newRecord.upperClouds.nightBlue
    print "upperClouds.unused4    :", newRecord.upperClouds.unused4

    print "fogDayNear   :", newRecord.fogDayNear
    print "fogDayFar    :", newRecord.fogDayFar
    print "fogNightNear :", newRecord.fogNightNear
    print "fogNightFar  :", newRecord.fogNightFar

    print "eyeAdaptSpeed  :", newRecord.eyeAdaptSpeed
    print "blurRadius     :", newRecord.blurRadius
    print "blurPasses     :", newRecord.blurPasses
    print "emissiveMult   :", newRecord.emissiveMult
    print "targetLum      :", newRecord.targetLum
    print "upperLumClamp  :", newRecord.upperLumClamp
    print "brightScale    :", newRecord.brightScale
    print "brightClamp    :", newRecord.brightClamp
    print "lumRampNoTex   :", newRecord.lumRampNoTex
    print "lumRampMin     :", newRecord.lumRampMin
    print "lumRampMax     :", newRecord.lumRampMax
    print "sunlightDimmer :", newRecord.sunlightDimmer
    print "grassDimmer    :", newRecord.grassDimmer
    print "treeDimmer     :", newRecord.treeDimmer

    print "windSpeed       :", newRecord.windSpeed
    print "lowerCloudSpeed :", newRecord.lowerCloudSpeed
    print "upperCloudSpeed :", newRecord.upperCloudSpeed
    print "transDelta      :", newRecord.transDelta
    print "sunGlare        :", newRecord.sunGlare
    print "sunDamage       :", newRecord.sunDamage
    print "rainFadeIn      :", newRecord.rainFadeIn
    print "rainFadeOut     :", newRecord.rainFadeOut
    print "boltFadeIn      :", newRecord.boltFadeIn
    print "boltFadeOut     :", newRecord.boltFadeOut
    print "boltFrequency   :", newRecord.boltFrequency
    print "weatherType     :", newRecord.weatherType
    print "boltRed         :", newRecord.boltRed
    print "boltGreen       :", newRecord.boltGreen
    print "boltBlue        :", newRecord.boltBlue
    print "sounds"
    for sound in newRecord.sounds:
        print "  sound: %s, type: %u" % (sound.sound, sound.type)

    print "WTHR:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].WTHR:
        record.CopyAsOverride(newMod)

    print "WTHR:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].WTHR:
        record.CopyAsNew(newMod)

    print "WTHR:Save Test - TestWTHR.esp"
    newMod.save()
    print "WTHR:Finished testing"
    Current.Close()

def TestCLMT():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCLMT.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].CLMT:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "CLMT:Create Record Test"
    newRecord = newMod.create_CLMT()
    d(newRecord)

    print "CLMT:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CLMTWarTest"

    newWeather = newRecord.create_weather()
    newWeather.weather = FormID(7)
    newWeather.chance = 31

    newWeather = newRecord.create_weather()
    newWeather.weather = FormID(8)
    newWeather.chance = 32

    newWeather = newRecord.create_weather()
    newWeather.weather = FormID(9)
    newWeather.chance = 33

    newWeather = newRecord.create_weather()
    newWeather.weather = FormID(10)
    newWeather.chance = 34

    newRecord.weathers = [newRecord.weathers[3], newRecord.weathers[2], newRecord.weathers[0]]
    newRecord.sunPath = r"CLMT\sunPath\1.nif"
    newRecord.glarePath = r"CLMT\glarePath\1.nif"
    print "modPath..."
    newRecord.modPath = r"CLMT\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.36
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]
    newRecord.riseBegin = 1
    newRecord.riseEnd = 2
    newRecord.setBegin = 3
    newRecord.setEnd = 4
    newRecord.volatility = 5
    newRecord.phaseLength = 6

    print "CLMT:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "weathers"
    for weather in newRecord.weathers:
        print "  weather: %s, chance: %u" % (weather.weather, weather.chance)
    print "sunPath     :", newRecord.sunPath
    print "glarePath   :", newRecord.glarePath
    print "modPath     :", newRecord.modPath
    print "modb        :", newRecord.modb
    print "modt_p      :", newRecord.modt_p
    print "riseBegin   :", newRecord.riseBegin
    print "riseEnd     :", newRecord.riseEnd
    print "setBegin    :", newRecord.setBegin
    print "setEnd      :", newRecord.setEnd
    print "volatility  :", newRecord.volatility
    print "phaseLength :", newRecord.phaseLength
    print "CLMT:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].CLMT:
        record.CopyAsOverride(newMod)

    print "CLMT:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].CLMT:
        record.CopyAsNew(newMod)

    print "CLMT:Save Test - TestCLMT.esp"
    newMod.save()
    print "CLMT:Finished testing"
    Current.Close()

def TestREGN():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestREGN.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].REGN:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "REGN:Create Record Test"
    newRecord = newMod.create_REGN()
    d(newRecord)

    print "REGN:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "REGNWarTest"

    print "iconPath..."
    newRecord.iconPath = r"REGN\path\test.dds"
    newRecord.mapRed = 1
    newRecord.mapGreen = 2
    newRecord.mapBlue = 3
    newRecord.unused1 = [4]
    newRecord.worldspace = FormID(7)

    newArea = newRecord.create_area()
    newArea.edgeFalloff = 1024
    newPoint = newArea.create_point()
    newPoint.posX = 1
    newPoint.posY = 2
    newPoint = newArea.create_point()
    newPoint.posX = 3.0
    newPoint.posY = 4.0
    newPoint = newArea.create_point()
    newPoint.posX = 5.0
    newPoint.posY = 6.0
    newPoint = newArea.create_point()
    newPoint.posX = 7.0
    newPoint.posY = 8.0
    newPoint = newArea.create_point()
    newPoint.posX = 9.0
    newPoint.posY = 10.0
    newPoint = newArea.create_point()
    newPoint.posX = 11.0
    newPoint.posY = 12.0
    newPoint = newArea.create_point()
    newPoint.posX = 13.0
    newPoint.posY = 14.0
    newPoint = newArea.create_point()
    newPoint.posX = 15.0
    newPoint.posY = 16.0
    newPoint = newArea.create_point()
    newPoint.posX = 17.0
    newPoint.posY = 18.0

    newArea.points = [newArea.points[0], newArea.points[2], newArea.points[4], newArea.points[6], newArea.points[8]]

    newArea = newRecord.create_area()
    newArea.edgeFalloff = 1025
    newPoint = newArea.create_point()
    newPoint.posX = 1.1
    newPoint.posY = 2.1
    newPoint = newArea.create_point()
    newPoint.posX = 3.1
    newPoint.posY = 4.1
    newPoint = newArea.create_point()
    newPoint.posX = 5.1
    newPoint.posY = 6.1
    newPoint = newArea.create_point()
    newPoint.posX = 7.1
    newPoint.posY = 8.1
    newPoint = newArea.create_point()
    newPoint.posX = 9.1
    newPoint.posY = 10.1
    newPoint = newArea.create_point()
    newPoint.posX = 11.1
    newPoint.posY = 12.1
    newPoint = newArea.create_point()
    newPoint.posX = 13.1
    newPoint.posY = 14.1
    newPoint = newArea.create_point()
    newPoint.posX = 15.1
    newPoint.posY = 16.1
    newPoint = newArea.create_point()
    newPoint.posX = 17.1
    newPoint.posY = 18.1

    newArea = newRecord.create_area()
    newArea.edgeFalloff = 1026
    newPoint = newArea.create_point()
    newPoint.posX = 1.2
    newPoint.posY = 2.2
    newPoint = newArea.create_point()
    newPoint.posX = 3.2
    newPoint.posY = 4.2
    newPoint = newArea.create_point()
    newPoint.posX = 5.2
    newPoint.posY = 6.2
    newPoint = newArea.create_point()
    newPoint.posX = 7.2
    newPoint.posY = 8.2
    newPoint = newArea.create_point()
    newPoint.posX = 9.2
    newPoint.posY = 10.2
    newPoint = newArea.create_point()
    newPoint.posX = 11.2
    newPoint.posY = 12.2
    newPoint = newArea.create_point()
    newPoint.posX = 13.2
    newPoint.posY = 14.2
    newPoint = newArea.create_point()
    newPoint.posX = 15.2
    newPoint.posY = 16.2
    newPoint = newArea.create_point()
    newPoint.posX = 17.2
    newPoint.posY = 18.2

    newRecord.areas = [newRecord.areas[2], newRecord.areas[0]]

    newEntry = newRecord.create_entry()
    newEntry.entryType = 2 ##Objects
##    newEntry.entryType = 3 ##Weathers
##    newEntry.entryType = 4 ##map
##    newEntry.entryType = 5 ##icon
##    newEntry.entryType = 6 ##Grasses
##    newEntry.entryType = 7 ##Sounds
    newEntry.flags = 2
    newEntry.priority = 3
    newEntry.unused1 = [1,2]

    newObject = newEntry.create_object()
    newObject.objectId = FormID(7)
    newObject.unused1 = [1,2]
    newObject.density = 1
    newObject.clustering = 2
    newObject.minSlope = 3
    newObject.maxSlope = 4
    newObject.flags = 5
    newObject.radiusWRTParent = 6
    newObject.radius = 7
    newObject.unk1 = [5,6,7,8]
    newObject.maxHeight = 8
    newObject.sink = 9
    newObject.sinkVar = 10
    newObject.angleVarX = 12
    newObject.angleVarY = 13
    newObject.angleVarZ = 14
    newObject.unused2 = [3,4]
    newObject.unk2 = [1,2,3,4]

    newObject = newEntry.create_object()
    newObject.objectId = FormID(8)
    newObject.unused1 = [1,2]
    newObject.density = 2
    newObject.clustering = 3
    newObject.minSlope = 4
    newObject.maxSlope = 5
    newObject.flags = 6
    newObject.radiusWRTParent = 7
    newObject.radius = 8
    newObject.unk1 = [5,6,7,8]
    newObject.maxHeight = 9
    newObject.sink = 10
    newObject.sinkVar = 11
    newObject.angleVarX = 13
    newObject.angleVarY = 14
    newObject.angleVarZ = 15
    newObject.unused2 = [3,4]
    newObject.unk2 = [1,2,3,4]

    newObject = newEntry.create_object()
    newObject.objectId = FormID(9)
    newObject.unused1 = [1,2]
    newObject.density = 3
    newObject.clustering = 4
    newObject.minSlope = 5
    newObject.maxSlope = 6
    newObject.flags = 7
    newObject.radiusWRTParent = 8
    newObject.radius = 9
    newObject.unk1 = [5,6,7,8]
    newObject.maxHeight = 10
    newObject.sink = 11
    newObject.sinkVar = 12
    newObject.angleVarX = 14
    newObject.angleVarY = 15
    newObject.angleVarZ = 16
    newObject.unused2 = [3,4]
    newObject.unk2 = [1,2,3,4]

    newEntry.objects = [newEntry.objects[2], newEntry.objects[0]]

##    newWeather = newEntry.create_weather()
##    newWeather.weather = 7
##    newWeather.chance = 10
##    newWeather = newEntry.create_weather()
##    newWeather.weather = 8
##    newWeather.chance = 11
##    newWeather = newEntry.create_weather()
##    newWeather.weather = 9
##    newWeather.chance = 12
##    newWeather = newEntry.create_weather()
##    newWeather.weather = 10
##    newWeather.chance = 13
##    newWeather = newEntry.create_weather()
##    newWeather.weather = 11
##    newWeather.chance = 14
##    newEntry.weathers = [newEntry.weathers[3], newEntry.weathers[0], newEntry.weathers[4]]

##    newEntry.mapName = r"Durgh"
##    newEntry.iconPath = r"OBSOLETE\Test\ICON.dds"

##    newGrass = newEntry.create_grass()
##    newGrass.grass = 7
##    newGrass.unk1 = [1,2,3,4]
##    newGrass = newEntry.create_grass()
##    newGrass.grass = 8
##    newGrass.unk1 = [2,2,3,4]
##    newGrass = newEntry.create_grass()
##    newGrass.grass = 9
##    newGrass.unk1 = [3,2,3,4]
##    newGrass = newEntry.create_grass()
##    newGrass.grass = 10
##    newGrass.unk1 = [4,2,3,4]
##    newEntry.grasses = [newEntry.grasses[2], newEntry.grasses[0]]

##    newSound = newEntry.create_sound()
##    newSound.sound = 7
##    newSound.flags = 1
##    newSound.chance = 10
##    newSound = newEntry.create_sound()
##    newSound.sound = 8
##    newSound.flags = 2
##    newSound.chance = 11
##    newSound = newEntry.create_sound()
##    newSound.sound = 9
##    newSound.flags = 3
##    newSound.chance = 12
##    newSound = newEntry.create_sound()
##    newSound.sound = 10
##    newSound.flags = 4
##    newSound.chance = 13
##    newEntry.sounds = [newEntry.sounds[2], newEntry.sounds[0]]

    print "REGN:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "iconPath   :", newRecord.iconPath
    print "mapRed     :", newRecord.mapRed
    print "mapGreen   :", newRecord.mapGreen
    print "mapBlue    :", newRecord.mapBlue
    print "unused1    :", newRecord.unused1
    print "worldspace :", newRecord.worldspace
    print "areas"
    for area in newRecord.areas:
        print "  edgeFalloff :", area.edgeFalloff
        print "  points"
        for point in area.points:
            print "    posX:%.6f, posY:%.6f" % (point.posX, point.posY)
        print
    print "entries"
    for entry in newRecord.entries:
        print "  entryType :", entry.entryType
        print "  flags     :", entry.flags
        print "  priority  :", entry.priority
        print "  unused1   :", entry.unused1
        print "  objects"
        for recObject in entry.objects:
            print "    objectId        :", recObject.objectId
            print "    parentIndex     :", recObject.parentIndex
            print "    unused1         :", recObject.unused1
            print "    density         :", recObject.density
            print "    clustering      :", recObject.clustering
            print "    minSlope        :", recObject.minSlope
            print "    maxSlope        :", recObject.maxSlope
            print "    flags           :", recObject.flags
            print "    radiusWRTParent :", recObject.radiusWRTParent
            print "    radius          :", recObject.radius
            print "    unk1            :", recObject.unk1
            print "    maxHeight       :", recObject.maxHeight
            print "    sink            :", recObject.sink
            print "    sinkVar         :", recObject.sinkVar
            print "    angleVarX       :", recObject.angleVarX
            print "    angleVarY       :", recObject.angleVarY
            print "    angleVarZ       :", recObject.angleVarZ
            print "    unused2         :", recObject.unused2
            print "    unk2            :", recObject.unk2
            print
        print "  mapName   :", entry.mapName
        print "  iconPath  :", entry.iconPath
        print "  grasses"
        for grass in entry.grasses:
            print "    grass :", grass.grass,
            print ", unk1 :", grass.unk1
        print "  musicType :", entry.musicType
        print "  sounds"
        for sound in entry.sounds:
            print "    sound  :", sound.sound
            print "    flags  :", sound.flags
            print "    chance :", sound.chance
        print "  weathers"
        for weather in entry.weathers:
            print "    weather :", weather.weather
            print "    chance  :", weather.chance
        print
    print "REGN:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].REGN:
        record.CopyAsOverride(newMod)

    print "REGN:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].REGN:
        record.CopyAsNew(newMod)

    print "REGN:Save Test - TestREGN.esp"
    newMod.save()
    print "REGN:Finished testing"
    Current.Close()

def TestCELL():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCELL.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].CELL:
        print "fid     :", record.fid
        printRecord(record)

        print "Placed NPCs"
        for achr in record.ACHR:
            print
            print "fid     :", achr.fid
            printRecord(achr)
            break

        print "Placed Creatures"
        for acre in record.ACRE:
            print
            print "fid     :", acre.fid
            printRecord(acre)
            break

        print "Placed Objects"
        for refr in record.REFR:
            print
            print "fid     :", refr.fid
            printRecord(refr)
            break

        print "Pathgrid"
        pgrd = record.PGRD
        if(pgrd != None):
            print
            print "fid     :", pgrd.fid
            printRecord(pgrd)
            break
        break

    print "CELL:Create Record Test"
    newRecord = newMod.create_CELL()
    d(newRecord)

    print "CELL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CELLWarTest"

    newRecord.full = "WarTestCELL"
    newRecord.flags = 1
    newRecord.ambientRed = 2
    newRecord.ambientGreen = 3
    newRecord.ambientBlue = 4
    newRecord.unused1 = [1]
    newRecord.directionalRed = 5
    newRecord.directionalGreen = 6
    newRecord.directionalBlue = 7
    newRecord.unused2 = [2]
    newRecord.fogRed = 8
    newRecord.fogGreen = 9
    newRecord.fogBlue = 10
    newRecord.unused3 = [3]
    newRecord.fogNear = 11
    newRecord.fogFar = 12
    newRecord.directionalXY = 13
    newRecord.directionalZ = 14
    newRecord.directionalFade = 15
    newRecord.fogClip = 16
    newRecord.musicType = 1
    newRecord.owner = FormID(7)
    newRecord.rank = 1
    newRecord.globalVariable = FormID(17)
    newRecord.climate = FormID(18)
    newRecord.waterHeight = 19
    newRecord.regions = [FormID(7),FormID(8),FormID(9)]
    newRecord.posX = 20
    newRecord.posY = 21
    newRecord.water = FormID(22)

    newNPCRef = newRecord.create_ACHR()

    newNPCRef.eid = "WarACHRTest"
    newNPCRef.base = FormID(7)
    newNPCRef.unknownXPCIFormID = FormID(14)
    newNPCRef.unknownXPCIString = "Hrm?"
    newNPCRef.lod1 = 10.1
    newNPCRef.lod2 = 11.2
    newNPCRef.lod3 = 12.3
    newNPCRef.parent = FormID(7)
    newNPCRef.parentFlags = 1
    newNPCRef.unused1 = [1,2,3]
    newNPCRef.merchantContainer = FormID(18)
    newNPCRef.horse = FormID(19)
    newNPCRef.xrgd_p = []
    newNPCRef.scale = 1.8
    newNPCRef.posX = 100
    newNPCRef.posY = 200
    newNPCRef.posZ = 300
    newNPCRef.rotX = 1
    newNPCRef.rotY = 2
    newNPCRef.rotZ = 3

    newCreaRef = newRecord.create_ACRE()

    newCreaRef.eid = "WarACRETest"
    newCreaRef.base = FormID(7)
    newCreaRef.owner = FormID(8)
    newCreaRef.rank = 1
    newCreaRef.globalVariable = FormID(2)
    newCreaRef.parent = FormID(14)
    newCreaRef.parentFlags = 1
    newCreaRef.unused1 = [1,2,3]
    newCreaRef.xrgd_p = [0x23,0xff, 0x25]
    newCreaRef.scale = 1.2
    newCreaRef.posX = 1
    newCreaRef.posY = 2
    newCreaRef.posZ = 3
    newCreaRef.rotX = 4
    newCreaRef.rotY = 5
    newCreaRef.rotZ = 6

    newObjRef = newRecord.create_REFR()

    newObjRef.eid = "WarREFRTest"
    newObjRef.base = FormID(7)
    newObjRef.destination = FormID(8)
    newObjRef.destinationPosX = 1
    newObjRef.destinationPosY = 2
    newObjRef.destinationPosZ = 3
    newObjRef.destinationRotX = 4
    newObjRef.destinationRotY = 5
    newObjRef.destinationRotZ = 6
    newObjRef.lockLevel = 5
    newObjRef.unused1 = [1,2,3]
    newObjRef.lockKey = FormID(14)
    newObjRef.unused2 = [1,2,3,4]
    newObjRef.lockFlags = 1
    newObjRef.unused3 = [1,2,3]
    newObjRef.owner = FormID(15)
    newObjRef.rank = 1
    newObjRef.globalVariable = FormID(2)
    newObjRef.parent = FormID(16)
    newObjRef.parentFlags = 1
    newObjRef.unused4 = [1, 2, 3]
    newObjRef.target = FormID(17)
    newObjRef.seed = 1234
    newObjRef.lod1 = 1
    newObjRef.lod2 = 2
    newObjRef.lod3 = 3
    newObjRef.charge = 4
    newObjRef.health = 5
    newObjRef.unknownXPCIFormID = FormID(6)
    newObjRef.unknownXPCIString = "blah?"
    newObjRef.levelMod = 7
    newObjRef.unknownXRTMFormID = FormID(8)
    newObjRef.actionFlags = 1
    newObjRef.count = 10
    newObjRef.markerFlags = 1
    newObjRef.markerName = "Marker!"
    newObjRef.markerType = 1
    newObjRef.markerUnused = [1]
    newObjRef.scale = 1.2
    newObjRef.soulType = 6
    newObjRef.posX = 5
    newObjRef.posY = 4
    newObjRef.posZ = 3
    newObjRef.rotX = 2
    newObjRef.rotY = 1
    newObjRef.rotZ = 11.2

    print "pathgrid..."
    newPgrd = newRecord.create_PGRD()
    newPgrd.count = 5
    newPgrp1 = newPgrd.create_pgrp()
    newPgrp1.x = 1
    newPgrp1.y = 2
    newPgrp1.z = 3
    newPgrp1.connections = 4
    newPgrp2 = newPgrd.create_pgrp()
    newPgrp2.x = 2
    newPgrp2.y = 3
    newPgrp2.z = 4
    newPgrp2.connections = 4
    newPgrp3 = newPgrd.create_pgrp()
    newPgrp3.x = 3
    newPgrp3.y = 4
    newPgrp3.z = 5
    newPgrp3.connections = 4
    newPgrp4 = newPgrd.create_pgrp()
    newPgrp4.x = 4
    newPgrp4.y = 5
    newPgrp4.z = 6
    newPgrp4.connections = 4
    newPgrp5 = newPgrd.create_pgrp()
    newPgrp5.x = 5
    newPgrp5.y = 6
    newPgrp5.z = 7
    newPgrp5.connections = 4
    newPgrp6 = newPgrd.create_pgrp()
    newPgrp6.x = 6
    newPgrp6.y = 7
    newPgrp6.z = 8
    newPgrp6.connections = 4
    newPgrd.pgrp = [newPgrp6, newPgrp1, newPgrp2, newPgrp3, newPgrp4]
##
####    newPgrd.PGAG = [0x22, 0x23, 0x01]
####
####    newPgrd.PGRR = [0x00, 0xFF, 0x00]
##
    newPgri1 = newPgrd.create_pgri()
    newPgri1.point = 1
    newPgri1.unused1 = [1,2]
    newPgri1.x = 2
    newPgri1.y = 3
    newPgri1.z = 4
    newPgri2 = newPgrd.create_pgri()
    newPgri2.point = 2
    newPgri2.unused1 = [1,2]
    newPgri2.x = 2
    newPgri2.y = 3
    newPgri2.z = 4
    newPgri3 = newPgrd.create_pgri()
    newPgri3.point = 3
    newPgri3.unused1 = [1,2]
    newPgri3.x = 2
    newPgri3.y = 3
    newPgri3.z = 4
    newPgri4 = newPgrd.create_pgri()
    newPgri4.point = 4
    newPgri4.unused1 = [1,2]
    newPgri4.x = 2
    newPgri4.y = 3
    newPgri4.z = 4
    newPgri5 = newPgrd.create_pgri()
    newPgri5.point = 5
    newPgri5.unused1 = [1,2]
    newPgri5.x = 2
    newPgri5.y = 3
    newPgri5.z = 4
    newPgri6 = newPgrd.create_pgri()
    newPgri6.point = 6
    newPgri6.unused1 = [1,2]
    newPgri6.x = 2
    newPgri6.y = 3
    newPgri6.z = 4
    newPgrd.pgri = [newPgri6, newPgri1, newPgri2, newPgri3, newPgri4]

    print 111
    newPgrl1 = newPgrd.create_pgrl()
    print 112
    newPgrl1.reference = FormID(7)
    print 11
    newPgrl1.points = [1,2,3]
    newPgrl2 = newPgrd.create_pgrl()
    print 12
    newPgrl2.reference = FormID(8)
    newPgrl2.points = [1]
    newPgrl3 = newPgrd.create_pgrl()
    print 13
    newPgrl3.reference = FormID(9)
    newPgrl3.points = [1,2]
    newPgrl4 = newPgrd.create_pgrl()
    print 14
    newPgrl4.reference = FormID(10)
    newPgrl4.points = [1,2,3,4]
    newPgrl5 = newPgrd.create_pgrl()
    print 15
    newPgrl5.reference = FormID(11)
    newPgrl5.points = [1,2,3]
    newPgrl6 = newPgrd.create_pgrl()
    print 16
    newPgrl6.reference = FormID(14)
    newPgrl6.points = [1, 2, 3, 4, 5, 6]
    print 1
    newPgrd.pgrl = [newPgrl6, newPgrl1, newPgrl2, newPgrl3, newPgrl4]
    print 1

    print "CELL:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full             :", newRecord.full
    print "flags            :", newRecord.flags
    print "ambientRed       :", newRecord.ambientRed
    print "ambientGreen     :", newRecord.ambientGreen
    print "ambientBlue      :", newRecord.ambientBlue
    print "unused1          :", newRecord.unused1
    print "directionalRed   :", newRecord.directionalRed
    print "directionalGreen :", newRecord.directionalGreen
    print "directionalBlue  :", newRecord.directionalBlue
    print "unused2          :", newRecord.unused2
    print "fogRed           :", newRecord.fogRed
    print "fogGreen         :", newRecord.fogGreen
    print "fogBlue          :", newRecord.fogBlue
    print "unused3          :", newRecord.unused3
    print "fogNear          :", newRecord.fogNear
    print "fogFar           :", newRecord.fogFar
    print "directionalXY    :", newRecord.directionalXY
    print "directionalZ     :", newRecord.directionalZ
    print "directionalFade  :", newRecord.directionalFade
    print "fogClip          :", newRecord.fogClip
    print "musicType        :", newRecord.musicType
    print "owner            :", newRecord.owner
    print "rank             :", newRecord.rank
    print "globalVariable   :", newRecord.globalVariable
    print "climate          :", newRecord.climate
    print "waterHeight      :", newRecord.waterHeight
    print "regions          :", newRecord.regions
    print "posX             :", newRecord.posX
    print "posY             :", newRecord.posY
    print "water            :", newRecord.water

    print "Placed NPCs"
    for achr in newRecord.ACHR:
        print
        print "  fid    :", achr.fid
        print "  flags1 :", achr.flags1
        print "  flags2 :", achr.flags2
        print "  eid    :", achr.eid

        print "  base              :", achr.base
        print "  unknownXPCIFormID :", achr.unknownXPCIFormID
        print "  unknownXPCIString :", achr.unknownXPCIString
        print "  lod1              :", achr.lod1
        print "  lod2              :", achr.lod2
        print "  lod3              :", achr.lod3
        print "  parent            :", achr.parent
        print "  parentFlags       :", achr.parentFlags
        print "  unused1           :", achr.unused1
        print "  merchantContainer :", achr.merchantContainer
        print "  horse             :", achr.horse
        print "  xrgd_p            :", achr.xrgd_p
        print "  scale             :", achr.scale
        print "  posX              :", achr.posX
        print "  posY              :", achr.posY
        print "  posZ              :", achr.posZ
        print "  rotX              :", achr.rotX
        print "  rotY              :", achr.rotY
        print "  rotZ              :", achr.rotZ

    print "Placed Creatures"
    for acre in newRecord.ACRE:
        print
        print "  fid    :", acre.fid
        print "  flags1 :", acre.flags1
        print "  flags2 :", acre.flags2
        print "  eid    :", acre.eid

        print "  base           :", acre.base
        print "  owner          :", acre.owner

        print "  rank           :", acre.rank
        print "  globalVariable :", acre.globalVariable
        print "  parent         :", acre.parent
        print "  parentFlags    :", acre.parentFlags
        print "  unused1        :", acre.unused1
        print "  xrgd_p         :", acre.xrgd_p
        print "  scale          :", acre.scale
        print "  posX           :", acre.posX
        print "  posY           :", acre.posY
        print "  posZ           :", acre.posZ
        print "  rotX           :", acre.rotX
        print "  rotY           :", acre.rotY
        print "  rotZ           :", acre.rotZ

    print "Placed Objects"
    for refr in newRecord.REFR:
        print
        print "  fid    :", refr.fid
        print "  flags1 :", refr.flags1
        print "  flags2 :", refr.flags2
        print "  eid    :", refr.eid
        print "  base              :", refr.base
        print "  destination :", refr.destination

        print "  destinationPosX   :", refr.destinationPosX
        print "  destinationPosY   :", refr.destinationPosY
        print "  destinationPosZ   :", refr.destinationPosZ
        print "  destinationRotX   :", refr.destinationRotX
        print "  destinationRotY   :", refr.destinationRotY
        print "  destinationRotZ   :", refr.destinationRotZ
        print "  lockLevel         :", refr.lockLevel
        print "  unused1           :", refr.unused1

        print "  lockKey           :", refr.lockKey

        print "  unused2           :", refr.unused2
        print "  lockFlags         :", refr.lockFlags
        print "  unused3           :", refr.unused3
        print "  owner             :", refr.owner

        print "  rank              :", refr.rank
        print "  globalVariable    :", refr.globalVariable
        print "  parent            :", refr.parent
        print "  parentFlags       :", refr.parentFlags
        print "  unused4           :", refr.unused4
        print "  target      :", refr.target
        print "  seed              :", refr.seed
        print "  seed_as_offset        :", refr.seed_as_offset
        print "  lod1              :", refr.lod1
        print "  lod2              :", refr.lod2
        print "  lod3              :", refr.lod3
        print "  charge            :", refr.charge
        print "  health            :", refr.health
        print "  unknownXPCIFormID :", refr.unknownXPCIFormID
        print "  unknownXPCIString :", refr.unknownXPCIString
        print "  levelMod          :", refr.levelMod
        print "  unknownXRTMFormID :", refr.unknownXRTMFormID
        print "  actionFlags       :", refr.actionFlags
        print "  count             :", refr.count
        print "  markerFlags       :", refr.markerFlags
        print "  markerName        :", refr.markerName
        print "  markerType        :", refr.markerType
        print "  markerUnused      :", refr.markerUnused
        print "  scale             :", refr.scale
        print "  soulType              :", refr.soulType
        print "  posX              :", refr.posX
        print "  posY              :", refr.posY
        print "  posZ              :", refr.posZ
        print "  rotX              :", refr.rotX
        print "  rotY              :", refr.rotY
        print "  rotZ              :", refr.rotZ

    print "Pathgrid"
    pgrd = newRecord.PGRD
    if(pgrd != None):
        print
        print "  fid    :", pgrd.fid
        print "  flags1 :", pgrd.flags1
        print "  flags2 :", pgrd.flags2

        print "  count :", pgrd.count
        print "  pgrp"
        for pgrp in pgrd.pgrp:
            print "    x           :", pgrp.x
            print "    y           :", pgrp.y
            print "    z           :", pgrp.z
            print "    connections :", pgrp.connections
            print "    unused1     :", pgrp.unused1
            break

        print "  PGAG_p :", pgrd.pgag_p
        print "  PGRR_p :", pgrd.pgrr_p
        print "  PGRI"
        for pgri in pgrd.pgri:
            print "    point   :", pgri.point
            print "    unused1 :", pgri.unused1
            print "    x       :", pgri.x
            print "    y       :", pgri.y
            print "    z       :", pgri.z
            break
        print "  PGRL"
        for pgrl in pgrd.pgrl:
            print "    reference :", pgrl.reference
            print "    points"
            for point in pgrl.points:
                print "      ", point
            break
    print "CELL:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].CELL:
        trgCell = record.CopyAsOverride(newMod)
        for npcRef in record.ACHR:
            npcRef.CopyAsOverride(trgCell)
        for creaRef in record.ACRE:
            creaRef.CopyAsOverride(trgCell)
        for objRef in record.REFR:
            objRef.CopyAsOverride(trgCell)
        Pgrd = record.PGRD
        if(Pgrd): Pgrd.CopyAsOverride(trgCell)

    print "CELL:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].CELL:
        trgCell = record.CopyAsNew(newMod)
        for npcRef in record.ACHR:
            npcRef.CopyAsNew(trgCell)
        for creaRef in record.ACRE:
            creaRef.CopyAsNew(trgCell)
        for objRef in record.REFR:
            objRef.CopyAsNew(trgCell)
        Pgrd = record.PGRD
        if(Pgrd): Pgrd.CopyAsNew(trgCell)

    print "CELL:Save Test - TestCELL.esp"
    newMod.save()
    print "CELL:Finished testing"
    Current.Close()

def TestWRLD():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWRLD.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].WRLD:
        print
        print "fid     :", record.fid
        printRecord(record)
        print "World CELL"
        wrldCell = record.WorldCELL
        if(wrldCell != None):
            print
            print "fid     :", wrldCell.fid
            printRecord(wrldCell)
            print "Placed NPCs"
            for achr in wrldCell.ACHR:
                print
                print "fid     :", achr.fid
                printRecord(achr)
                break

            print "Placed Creatures"
            for acre in wrldCell.ACRE:
                print
                print "fid     :", acre.fid
                printRecord(acre)
                break

            print "Placed Objects"
            for refr in wrldCell.REFR:
                print
                print "fid     :", refr.fid
                printRecord(refr)
                break

            pgrd = wrldCell.PGRD
            if(pgrd != None):
                print
                print "fid     :", pgrd.fid
                printRecord(pgrd)
                break
            cLand = wrldCell.LAND
            if(cLand != None):
                print
                print "fid     :", cLand.fid
                printRecord(cLand)
                break
##                print
##                print "  LAND"
##                print "  fid    :", cLand.fid
##                print "  flags1 :", cLand.flags1
##                print "  flags2 :", cLand.flags2
##
##
##                print "  data         :", cLand.data
##                print "  normals"
##                for cRow in cLand.normals:
##                    for cColumn in cRow:
##                        print "    Co-ords : ", cColumn._ListIndex, ",", cColumn._listX2Index
##                        print "        x   :", cColumn.x
##                        print "        y   :", cColumn.y
##                        print "        z   :", cColumn.z
##                        print
##                print "  heightOffset :", cLand.heightOffset
##                print "  heights"
##                for cRow in cLand.heights:
##                    for cColumn in cRow:
##                        print "    Co-ords    : ", cColumn._ListIndex, ",", cColumn._listX2Index
##                        print "        height :", cColumn.height
##                        print
##                print "  unused1      :", cLand.unused1
##                print "  colors"
##                for cRow in cLand.colors:
##                    for cColumn in cRow:
##                        print "    Co-ords   : ", cColumn._ListIndex, ",", cColumn._listX2Index
##                        print "        red   :", cColumn.red
##                        print "        green :", cColumn.green
##                        print "        blue  :", cColumn.blue
##                        print
##                print "  baseTextures"
##                for baseTexture in cLand.baseTextures:
##                    print "    texture  :", baseTexture.texture
##                    print "    quadrant :", baseTexture.quadrant
##                    print "    unused1  :", baseTexture.unused1
##                    print "    layer    :", baseTexture.layer
##                    print
##                print "  alphaLayers"
##                for alphaLayer in cLand.alphaLayers:
##                    print "    texture  :", alphaLayer.texture
##                    print "    quadrant :", alphaLayer.quadrant
##                    print "    unused1  :", alphaLayer.unused1
##                    print "    layer    :", alphaLayer.layer
##                    print "    opacities"
##                    for cOpacity in alphaLayer.opacities:
##                        print "      position :", cOpacity.position
##                        print "      unused1  :", cOpacity.unused1
##                        print "      opacity  :", cOpacity.opacity
##                        print
##                    print
##                print "  vertexTextures"
##                for vertexTexture in cLand.vertexTextures:
##                    print "    texture  :", vertexTexture.texture
##                    print
##
##                print "  Position"
##                for cRow in cLand.Position:
##                    for cColumn in cRow:
##                        print "    Co-ords row:", cColumn._ListIndex, ", col:", cColumn._listX2Index
##                        print "        height        :", cColumn.height
##                        print "        normalX       :", cColumn.normalX
##                        print "        normalY       :", cColumn.normalY
##                        print "        normalZ       :", cColumn.normalZ
##                        print "        red           :", cColumn.red
##                        print "        green         :", cColumn.green
##                        print "        blue          :", cColumn.blue
##                        print "        baseTexture   :", cColumn.baseTexture
##
##                        print "        layer1Texture :", cColumn.layer1Texture
##                        print "        layer1Opacity :", cColumn.layer1Opacity
##
##                        print "        layer2Texture :", cColumn.layer2Texture
##                        print "        layer2Opacity :", cColumn.layer2Opacity
##
##                        print "        layer3Texture :", cColumn.layer3Texture
##                        print "        layer3Opacity :", cColumn.layer3Opacity
##
##                        print "        layer4Texture :", cColumn.layer4Texture
##                        print "        layer4Opacity :", cColumn.layer4Opacity
##
##                        print "        layer5Texture :", cColumn.layer5Texture
##                        print "        layer5Opacity :", cColumn.layer5Opacity
##
##                        print "        layer6Texture :", cColumn.layer6Texture
##                        print "        layer6Opacity :", cColumn.layer6Opacity
##
##                        print "        layer7Texture :", cColumn.layer7Texture
##                        print "        layer7Opacity :", cColumn.layer7Opacity
##
##                        print "        layer8Texture :", cColumn.layer8Texture
##                        print "        layer8Opacity :", cColumn.layer8Opacity
##                        print


        for wrldCell in record.CELLS:
            print
            print "fid     :", wrldCell.fid
            printRecord(wrldCell)
            print "Placed NPCs"
            for achr in wrldCell.ACHR:
                print
                print "fid     :", achr.fid
                printRecord(achr)
                break

            print "Placed Creatures"
            for acre in wrldCell.ACRE:
                print
                print "fid     :", acre.fid
                printRecord(acre)
                break

            print "Placed Objects"
            for refr in wrldCell.REFR:
                print
                print "fid     :", refr.fid
                printRecord(refr)
                break

            pgrd = wrldCell.PGRD
            if(pgrd != None):
                print
                print "fid     :", pgrd.fid
                printRecord(pgrd)
                break
            cLand = wrldCell.LAND
            if(cLand != None):
                print
                print "fid     :", cLand.fid
                printRecord(cLand)
                break
##                print
##                print "  LAND"
##                print "  fid    :", cLand.fid
##                print "  flags1 :", cLand.flags1
##                print "  flags2 :", cLand.flags2
##
##
##                print "  data         :", cLand.data
##                print "  normals"
##                for cRow in cLand.normals:
##                    for cColumn in cRow:
##                        print "    Co-ords : ", cColumn._ListIndex, ",", cColumn._listX2Index
##                        print "        x   :", cColumn.x
##                        print "        y   :", cColumn.y
##                        print "        z   :", cColumn.z
##                        print
##                        break
##                    break
##                print "  heightOffset :", cLand.heightOffset
##                print "  heights"
##                for cRow in cLand.heights:
##                    for cColumn in cRow:
##                        print "    Co-ords    : ", cColumn._ListIndex, ",", cColumn._listX2Index
##                        print "        height :", cColumn.height
##                        print
##                        break
##                    break
##                print "  unused1      :", cLand.unused1
##                print "  colors"
##                for cRow in cLand.colors:
##                    for cColumn in cRow:
##                        print "    Co-ords   : ", cColumn._ListIndex, ",", cColumn._listX2Index
##                        print "        red   :", cColumn.red
##                        print "        green :", cColumn.green
##                        print "        blue  :", cColumn.blue
##                        print
##                        break
##                    break
##                print "  baseTextures"
##                for baseTexture in cLand.baseTextures:
##                    print "    texture  :", baseTexture.texture
##                    print "    quadrant :", baseTexture.quadrant
##                    print "    unused1  :", baseTexture.unused1
##                    print "    layer    :", baseTexture.layer
##                    print
##                    break
##                print "  alphaLayers"
##                for alphaLayer in cLand.alphaLayers:
##                    print "    texture  :", alphaLayer.texture
##                    print "    quadrant :", alphaLayer.quadrant
##                    print "    unused1  :", alphaLayer.unused1
##                    print "    layer    :", alphaLayer.layer
##                    print "    opacities"
##                    for cOpacity in alphaLayer.opacities:
##                        print "      position :", cOpacity.position
##                        print "      unused1  :", cOpacity.unused1
##                        print "      opacity  :", cOpacity.opacity
##                        print
##                        break
##                    print
##                    break
##                print "  vertexTextures"
##                for vertexTexture in cLand.vertexTextures:
##                    print "    texture  :", vertexTexture.texture
##                    print
##                    break
##
##                print "  Position"
##                for cRow in cLand.Position:
##                    for cColumn in cRow:
##                        print "    Co-ords row:", cColumn._ListIndex, ", col:", cColumn._listX2Index
##                        print "        height        :", cColumn.height
##                        print "        normalX       :", cColumn.normalX
##                        print "        normalY       :", cColumn.normalY
##                        print "        normalZ       :", cColumn.normalZ
##                        print "        red           :", cColumn.red
##                        print "        green         :", cColumn.green
##                        print "        blue          :", cColumn.blue
##                        print "        baseTexture   :", cColumn.baseTexture
##
##                        print "        layer1Texture :", cColumn.layer1Texture
##                        print "        layer1Opacity :", cColumn.layer1Opacity
##
##                        print "        layer2Texture :", cColumn.layer2Texture
##                        print "        layer2Opacity :", cColumn.layer2Opacity
##
##                        print "        layer3Texture :", cColumn.layer3Texture
##                        print "        layer3Opacity :", cColumn.layer3Opacity
##
##                        print "        layer4Texture :", cColumn.layer4Texture
##                        print "        layer4Opacity :", cColumn.layer4Opacity
##
##                        print "        layer5Texture :", cColumn.layer5Texture
##                        print "        layer5Opacity :", cColumn.layer5Opacity
##
##                        print "        layer6Texture :", cColumn.layer6Texture
##                        print "        layer6Opacity :", cColumn.layer6Opacity
##
##                        print "        layer7Texture :", cColumn.layer7Texture
##                        print "        layer7Opacity :", cColumn.layer7Opacity
##
##                        print "        layer8Texture :", cColumn.layer8Texture
##                        print "        layer8Opacity :", cColumn.layer8Opacity
##                        print
##                        break
##                    break
            break
        break

    print "WRLD:Create Record Test"
    newRecord = newMod.create_WRLD()
    d(newRecord)

    print "WRLD:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WRLDWarTest"

    newRecord.full =  "TestWarWorld"
    newRecord.parent = FormID(7)
    newRecord.climate = FormID(8)
    newRecord.water = FormID(9)
    newRecord.mapPath = r"MapTest\Path\Destination\test.dds"
    newRecord.dimX = 10
    newRecord.dimY = 11
    newRecord.NWCellX = 12
    newRecord.NWCellY = 13
    newRecord.SECellX = 14
    newRecord.SECellY = 15
    newRecord.flags = 1
    newRecord.xMinObjBounds = 16.0
    newRecord.yMinObjBounds = 17.0
    newRecord.xMaxObjBounds = 18.0
    newRecord.yMaxObjBounds = 19.0
    newRecord.musicType = 20
    newRecord.ofst_p = [1,2,3,4,5,6,7,8,9,10]

    print "WRLD:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "full      :", newRecord.full
    print "parent    :", newRecord.parent
    print "climate   :", newRecord.climate
    print "water     :", newRecord.water
    print "mapPath   :", newRecord.mapPath
    print "dimX      :", newRecord.dimX
    print "dimY      :", newRecord.dimY
    print "NWCellX   :", newRecord.NWCellX
    print "NWCellY   :", newRecord.NWCellY
    print "SECellX   :", newRecord.SECellX
    print "SECellY   :", newRecord.SECellY
    print "flags     :", newRecord.flags
    print "xMinObjBounds :", newRecord.xMinObjBounds
    print "yMinObjBounds :", newRecord.yMinObjBounds
    print "xMaxObjBounds :", newRecord.xMaxObjBounds
    print "yMaxObjBounds :", newRecord.yMaxObjBounds
    print "musicType     :", newRecord.musicType
    print "ofst_p    :", newRecord.ofst_p

    print "WRLD:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].WRLD:
        trgWrld = record.CopyAsOverride(newMod)
        road = record.ROAD
        if(road != None):
            road.CopyAsOverride(trgWrld)
            road.UnloadRecord()
        cell = record.WorldCELL
        if(cell != None):
            trgCell = cell.CopyAsOverride(trgWrld)
            cLand = cell.LAND
            if(cLand != None):
                cLand.CopyAsOverride(trgCell)
                cLand.UnloadRecord()
            for npcRef in cell.ACHR:
                npcRef.CopyAsOverride(trgCell)
                npcRef.UnloadRecord()
            for creaRef in cell.ACRE:
                creaRef.CopyAsOverride(trgCell)
                creaRef.UnloadRecord()
            for objRef in cell.REFR:
                objRef.CopyAsOverride(trgCell)
                objRef.UnloadRecord()
            Pgrd = cell.PGRD
            if(Pgrd != None):
                Pgrd.CopyAsOverride(trgCell)
                Pgrd.UnloadRecord()
            cell.UnloadRecord()
        for wrldCell in record.CELLS:
            trgCell = wrldCell.CopyAsOverride(trgWrld)
            cLand = wrldCell.LAND
            if(cLand != None):
                cLand.CopyAsOverride(trgCell)
                cLand.UnloadRecord()
            for npcRef in wrldCell.ACHR:
                npcRef.CopyAsOverride(trgCell)
                npcRef.UnloadRecord()
            for creaRef in wrldCell.ACRE:
                creaRef.CopyAsOverride(trgCell)
                creaRef.UnloadRecord()
            for objRef in wrldCell.REFR:
                objRef.CopyAsOverride(trgCell)
                objRef.UnloadRecord()
            Pgrd = wrldCell.PGRD
            if(Pgrd != None):
                Pgrd.CopyAsOverride(trgCell)
                Pgrd.UnloadRecord()
            wrldCell.UnloadRecord()
        record.UnloadRecord()

##    print "WRLD:CopyAsNew Test"
##    for record in Current.LoadOrderMods[0].WRLD:
##        trgWrld = record.CopyAsNew(newMod)
##        road = record.ROAD
##        if(road != None):
##            road.CopyAsNew(trgWrld)
##            road.UnloadRecord()
##        cell = record.WorldCELL
##        if(cell != None):
##            trgCell = cell.CopyAsNew(trgWrld)
##            cLand = cell.LAND
##            if(cLand != None):
##                cLand.CopyAsNew(trgCell)
##                cLand.UnloadRecord()
##            for npcRef in cell.ACHR:
##                npcRef.CopyAsNew(trgCell)
##                npcRef.UnloadRecord()
##            for creaRef in cell.ACRE:
##                creaRef.CopyAsNew(trgCell)
##                creaRef.UnloadRecord()
##            for objRef in cell.REFR:
##                objRef.CopyAsNew(trgCell)
##                objRef.UnloadRecord()
##            Pgrd = cell.PGRD
##            if(Pgrd != None):
##                Pgrd.CopyAsNew(trgCell)
##                Pgrd.UnloadRecord()
##            cell.UnloadRecord()
##        for wrldCell in record.CELLS:
##            trgCell = wrldCell.CopyAsNew(trgWrld)
##            cLand = wrldCell.LAND
##            if(cLand != None):
##                cLand.CopyAsNew(trgCell)
##                cLand.UnloadRecord()
##            for npcRef in wrldCell.ACHR:
##                npcRef.CopyAsNew(trgCell)
##                npcRef.UnloadRecord()
##            for creaRef in wrldCell.ACRE:
##                creaRef.CopyAsNew(trgCell)
##                creaRef.UnloadRecord()
##            for objRef in wrldCell.REFR:
##                objRef.CopyAsNew(trgCell)
##                objRef.UnloadRecord()
##            Pgrd = wrldCell.PGRD
##            if(Pgrd != None):
##                Pgrd.CopyAsNew(trgCell)
##                Pgrd.UnloadRecord()
##            wrldCell.UnloadRecord()
##        record.UnloadRecord()

    print "WRLD:Save Test - TestWRLD.esp"
    newMod.save()
    print "WRLD:Finished testing"
    Current.Close()

def TestDIAL():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestDIAL.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].DIAL:
        print
        print "fid     :", record.fid
        printRecord(record)

        print "infos"
        for info in record.INFO:
            print
            print "fid     :", info.fid
            printRecord(info)
            break
        break

    print "DIAL:Create Record Test"
    newRecord = newMod.create_DIAL()
    d(newRecord)

    print "DIAL:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "DIALWarTest"

    newRecord.quests = [FormID(0xFF000121), FormID(0xFE000222)]
    print "full..."
    newRecord.full = "Fancy DIAL"
    newRecord.dialType = 1

    print "INFO:Set Test"
    newInfo = newRecord.create_INFO()
    newInfo.flags1 = 0x0102
    newInfo.flags2 = 0x0201

    newInfo.dialType = 1
    newInfo.flags = 2
    newInfo.quest = FormID(7)
    newInfo.topic = FormID(10)
    newInfo.prevInfo = FormID(15)
    newInfo.addTopics = [FormID(7),FormID(15),FormID(22)]

    newResponse = newInfo.create_response()
    newResponse.emotionType = 1
    newResponse.emotionValue = 2
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 3
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "RARGH!...1..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newResponse = newInfo.create_response()
    newResponse.emotionType = 4
    newResponse.emotionValue = 5
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 6
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "RARGH!...2..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newResponse = newInfo.create_response()
    newResponse.emotionType = 7
    newResponse.emotionValue = 8
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 9
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "RARGH!...3..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newInfo.responses = [newInfo.responses[2], newInfo.responses[0], newInfo.responses[0], newInfo.responses[2]]

    newCondition = newInfo.create_condition()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(4)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(5)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(6)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newInfo.conditions = [newInfo.conditions[3], newInfo.conditions[1], newInfo.conditions[0]]

    newInfo.choices = [FormID(0x0A), FormID(0x0B), FormID(0x0C)]

    newInfo.linksFrom = [FormID(0x0D), FormID(0x0E), FormID(0x0F)]


    newInfo.unused1 = [2,3,4,5]
    newInfo.numRefs = 15
    newInfo.compiledSize = 3
    newInfo.lastIndex = 4
    newInfo.scriptType = 1
    newInfo.compiled_p = [1,67,255]
    newInfo.scriptText = "scn DummyScript\nThis won't compile"

    newInfo.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newInfo.references = [newInfo.references[3], newInfo.references[1], newInfo.references[0]]

    print "INFO:Set Test"
    newInfo = newRecord.create_INFO()
    newInfo.flags1 = 0x0102
    newInfo.flags2 = 0x0201

    newInfo.dialType = 1
    newInfo.flags = 2
    newInfo.quest = FormID(7)
    newInfo.topic = FormID(10)
    newInfo.prevInfo = FormID(15)
    newInfo.addTopics = [FormID(7),FormID(15),FormID(22)]

    newResponse = newInfo.create_response()
    newResponse.emotionType = 1
    newResponse.emotionValue = 2
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 3
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "1RARGH!...1..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newResponse = newInfo.create_response()
    newResponse.emotionType = 4
    newResponse.emotionValue = 5
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 6
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "1RARGH!...2..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newResponse = newInfo.create_response()
    newResponse.emotionType = 7
    newResponse.emotionValue = 8
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 9
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "1RARGH!...3..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newInfo.responses = [newInfo.responses[2], newInfo.responses[0], newInfo.responses[0], newInfo.responses[2]]

    newCondition = newInfo.create_condition()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(4)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(5)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(6)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newInfo.conditions = [newInfo.conditions[3], newInfo.conditions[1], newInfo.conditions[0]]

    newInfo.choices = [FormID(0x0A), FormID(0x0B), FormID(0x0C)]

    newInfo.linksFrom = [FormID(0x0D), FormID(0x0E), FormID(0x0F)]

    print "INFO:Set Test"
    newInfo = newRecord.create_INFO()
    newInfo.flags1 = 0x0102
    newInfo.flags2 = 0x0201

    newInfo.dialType = 1
    newInfo.flags = 2
    newInfo.quest = FormID(7)
    newInfo.topic = FormID(10)
    newInfo.prevInfo = FormID(15)
    newInfo.addTopics = [FormID(7),FormID(15),FormID(22)]

    newResponse = newInfo.create_response()
    newResponse.emotionType = 1
    newResponse.emotionValue = 2
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 3
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "2RARGH!...1..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newResponse = newInfo.create_response()
    newResponse.emotionType = 4
    newResponse.emotionValue = 5
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 6
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "2RARGH!...2..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newResponse = newInfo.create_response()
    newResponse.emotionType = 7
    newResponse.emotionValue = 8
    newResponse.unused1 = [1,2,3,4]
    newResponse.responseNum = 9
    newResponse.unused2 = [5,6,7]
    newResponse.responseText = "2RARGH!...3..oops"
    newResponse.actorNotes = "Say it with all your might!"

    newInfo.responses = [newInfo.responses[2], newInfo.responses[0], newInfo.responses[0], newInfo.responses[2]]

    newCondition = newInfo.create_condition()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(4)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(5)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(6)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newInfo.create_condition()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newInfo.conditions = [newInfo.conditions[3], newInfo.conditions[1], newInfo.conditions[0]]

    newInfo.choices = [FormID(0x0A), FormID(0x0B), FormID(0x0C)]

    newInfo.linksFrom = [FormID(0x0D), FormID(0x0E), FormID(0x0F)]


    newInfo.unused1 = [2,3,4,5]
    newInfo.numRefs = 15
    newInfo.compiledSize = 3
    newInfo.lastIndex = 4
    newInfo.scriptType = 1
    newInfo.compiled_p = [1,67,255]
    newInfo.scriptText = "scn DummyScript\nThis won't compile"

    newInfo.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newInfo.references = [newInfo.references[3], newInfo.references[1], newInfo.references[0]]

    print "DIAL:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "quests"
    for quest in newRecord.quests:
        print "  ", quest
    print "full     :", newRecord.full
    print "dialType :", newRecord.dialType

    print "infos"
    for info in newRecord.INFO:
        print
        print "  fid    :", info.fid
        print "  flags1 :", info.flags1
        print "  flags2 :", info.flags2

        print "  dialType     :", info.dialType
        print "  flags        :", info.flags
        print "  quest        :", info.quest
        print "  topic        :", info.topic
        print "  prevInfo     :", info.prevInfo
        print "  addTopics"
        for topic in info.addTopics:
            print "    ", topic

        print "  responses"
        for response in info.responses:
            print "    emotionType  :", response.emotionType
            print "    emotionValue :", response.emotionValue
            print "    unused1      :", response.unused1
            print "    responseNum  :", response.responseNum
            print "    unused2      :", response.unused2
            print "    responseText :", response.responseText
            print "    actorNotes   :", response.actorNotes
            print

        print "  conditions"
        for condition in info.conditions:
            print "    operType  :", condition.operType
            print "    unused1   :", condition.unused1
            print "    compValue :", condition.compValue
            print "    ifunc     :", condition.ifunc
            print "    param1    :", condition.param1
            print "    param2    :", condition.param2
            print "    unused2   :", condition.unused2
            print

        print "  choices"
        for choice in info.choices:
            print "    ", choice

        print "  linksFrom"
        for linksFrom in info.linksFrom:
            print "    ", linksFrom

        print "  unused1      :", info.unused1
        print "  numRefs      :", info.numRefs
        print "  compiledSize :", info.compiledSize
        print "  lastIndex    :", info.lastIndex
        print "  scriptType   :", info.scriptType
        print "  compiled_p   :", info.compiled_p
        print "  scriptText   :", info.scriptText

        print "  references"
        for reference in info.references:
            if isinstance(reference, tuple):
                print "    SCRO:", reference
            else:
                print "    SCRV:", reference

    print "DIAL:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].DIAL:
        newRecord = record.CopyAsOverride(newMod)
        for info in record.INFO:
            info.CopyAsOverride(newRecord)


    print "DIAL:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].DIAL:
        newRecord = record.CopyAsNew(newMod)
        for info in record.INFO:
            info.CopyAsNew(newRecord)

    print "DIAL:Save Test - TestDIAL.esp"
    newMod.save()
    print "DIAL:Finished testing"
    Current.Close()

def TestQUST():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestQUST.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].QUST:
        print
        print "fid     :", record.fid
        printRecord(record)
        break


    print "QUST:Create Record Test"
    newRecord = newMod.create_QUST()
    d(newRecord)

    print "QUST:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "QUSTWarTest"

    newRecord.script = FormID(7)
    newRecord.full = "Waruddar's Quest Test"
    newRecord.iconPath = r"QUST\Icon\Path\Test.dds"
    newRecord.flags = 1
    newRecord.priority = 2

    newCondition = newRecord.create_condition()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(4)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(5)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(6)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newRecord.conditions = [newRecord.conditions[3], newRecord.conditions[1], newRecord.conditions[0]]

    newStage = newRecord.create_stage()
    newStage.stage = 10
    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(8)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(9)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "10How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "10Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "20How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "20Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "30How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "30Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newStage.entries = [newStage.entries[2], newStage.entries[0]]

    newStage = newRecord.create_stage()
    newStage.stage = 20
    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "11How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "11Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "21How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "21Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "31How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "31Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newStage.entries = [newStage.entries[2], newStage.entries[0]]

    newStage = newRecord.create_stage()
    newStage.stage = 30
    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "12How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "12Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "22How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "22Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newEntry = newStage.create_entry()
    newEntry.flags = 1

    newCondition = newEntry.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newEntry.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newEntry.conditions = [newEntry.conditions[3], newEntry.conditions[1], newEntry.conditions[0]]

    newEntry.text = "32How does this thing expect to work? It doesn't?!"
    newEntry.unused1 = [5,6,7,8]
    newEntry.numRefs = 15
    newEntry.compiledSize = 0
    newEntry.lastIndex = 16
    newEntry.scriptType = 1
    newEntry.compiled_p = []
    newEntry.scriptText = "32Another futile attempt at making this thing work"

    newEntry.references = [FormID('Oblivion.esm',0x000007), 8, FormID('Oblivion.esm',0x000009), 10]
    newEntry.references = [newEntry.references[0], newEntry.references[2], newEntry.references[3], newEntry.references[0], newEntry.references[1]]

    newStage.entries = [newStage.entries[2], newStage.entries[0]]

    newRecord.stages = [newRecord.stages[2], newRecord.stages[0]]

    newTarget = newRecord.create_target()
    newTarget.targetId = FormID(7)
    newTarget.flags = 1
    newTarget.unused1 = [1,2,3]

    newCondition = newTarget.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newTarget.conditions = [newTarget.conditions[3], newTarget.conditions[1], newTarget.conditions[0]]

    newTarget = newRecord.create_target()
    newTarget.targetId = FormID(8)
    newTarget.flags = 2
    newTarget.unused1 = [1,2,3]

    newCondition = newTarget.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newTarget.conditions = [newTarget.conditions[3], newTarget.conditions[1], newTarget.conditions[0]]

    newTarget = newRecord.create_target()
    newTarget.targetId = FormID(9)
    newTarget.flags = 3
    newTarget.unused1 = [1,2,3]

    newCondition = newTarget.create_condition()
    newCondition.operType = 5
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 6
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(7)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 7
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(7)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newTarget.create_condition()
    newCondition.operType = 8
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newTarget.conditions = [newTarget.conditions[3], newTarget.conditions[1], newTarget.conditions[0]]

    newRecord.targets = [newRecord.targets[2], newRecord.targets[0]]

    print "QUST:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "script     :", newRecord.script
    print "full       :", newRecord.full
    print "iconPath   :", newRecord.iconPath
    print "flags      :", newRecord.flags
    print "priority   :", newRecord.priority

    print "conditions"
    for condition in newRecord.conditions:
        print "  operType  :", condition.operType
        print "  unused1   :", condition.unused1
        print "  compValue :", condition.compValue
        print "  ifunc     :", condition.ifunc
        print "  param1    :", condition.param1
        print "  param2    :", condition.param2
        print "  unused2   :", condition.unused2
        print
    print "stages"
    for stage in newRecord.stages:
        print "  stage :", stage.stage
        print "  entries"
        for entry in stage.entries:
            print "    flags        :", entry.flags
            print "    conditions"
            for condition in entry.conditions:
                print "      operType  :", condition.operType
                print "      unused1   :", condition.unused1
                print "      compValue :", condition.compValue
                print "      ifunc     :", condition.ifunc
                print "      param1    :", condition.param1
                print "      param2    :", condition.param2
                print "      unused2   :", condition.unused2
                print
            print "    text         :", entry.text
            print "    unused1      :", entry.unused1
            print "    numRefs      :", entry.numRefs
            print "    compiledSize :", entry.compiledSize
            print "    lastIndex    :", entry.lastIndex
            print "    scriptType   :", entry.scriptType
            print "    compiled_p   :", entry.compiled_p
            print "    scriptText   :", entry.scriptText
            print "    references"
            for reference in entry.references:
                if isinstance(reference, tuple):
                    print "      SCRO:", reference
                else:
                    print "      SCRV:", reference
            print
        print
    print "targets"
    for target in newRecord.targets:
        print "  targetId :", target.targetId
        print "  flags    :", target.flags
        print "  unused1  :", target.unused1
        print "  conditions"
        for condition in target.conditions:
            print "    operType  :", condition.operType
            print "    unused1   :", condition.unused1
            print "    compValue :", condition.compValue
            print "    ifunc     :", condition.ifunc
            print "    param1    :", condition.param1
            print "    param2    :", condition.param2
            print "    unused2   :", condition.unused2
            print

    print "QUST:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].QUST:
        record.CopyAsOverride(newMod)

    print "QUST:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].QUST:
        record.CopyAsNew(newMod)

    print "QUST:Save Test - TestQUST.esp"
    newMod.save()
    print "QUST:Finished testing"
    Current.Close()

def TestIDLE():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestIDLE.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].IDLE:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "IDLE:Create Record Test"
    newRecord = newMod.create_IDLE()
    d(newRecord)

    print "IDLE:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "IDLEWarTest"

    print "modPath..."
    newRecord.modPath = r"IDLE\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.06
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newCondition = newRecord.create_condition()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(4)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(5)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(6)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newRecord.conditions = [newRecord.conditions[3], newRecord.conditions[1], newRecord.conditions[0]]

    newRecord.group = 1
    newRecord.parent = FormID(7)
    newRecord.prevId = FormID(15)

    print "IDLE:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "conditions"
    for condition in newRecord.conditions:
        print "  operType  :", condition.operType
        print "  unused1   :", condition.unused1
        print "  compValue :", condition.compValue
        print "  ifunc     :", condition.ifunc
        print "  param1    :", condition.param1
        print "  param2    :", condition.param2
        print "  unused2   :", condition.unused2
        print

    print "group  :", newRecord.group
    print "parent :", newRecord.parent
    print "prevId :", newRecord.prevId

    print "IDLE:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].IDLE:
        record.CopyAsOverride(newMod)

    print "IDLE:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].IDLE:
        record.CopyAsNew(newMod)

    print "IDLE:Save Test - TestIDLE.esp"
    newMod.save()
    print "IDLE:Finished testing"
    Current.Close()

def TestPACK():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestPACK.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].PACK:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "PACK:Create Record Test"
    newRecord = newMod.create_PACK()
    d(newRecord)

    print "PACK:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "PACKWarTest"

    newRecord.flags = 1
    newRecord.aiType = 2
    newRecord.unused1 = [1,2,3]
    newRecord.locType = 5
    newRecord.locId = 4
    newRecord.locRadius = 5
    newRecord.month = 6
    newRecord.day = 7
    newRecord.date = 8
    newRecord.time = 9
    newRecord.duration = 10
    newRecord.targetType = 1
    newRecord.targetId = 12
    newRecord.targetCount = 13

    newCondition = newRecord.create_condition()
    newCondition.operType = 1
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 2
    newCondition.ifunc = 280
    newCondition.param1 = FormID(4)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 2
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 3
    newCondition.ifunc = 214
    newCondition.param1 = FormID(5)
    newCondition.param2 = 365
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 3
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 4
    newCondition.ifunc = 280
    newCondition.param1 = FormID(6)
    newCondition.param2 = FormID(10)
    newCondition.unused2 = [1,2,3,4]

    newCondition = newRecord.create_condition()
    newCondition.operType = 4
    newCondition.unused1 = [1,2,3]
    newCondition.compValue = 5
    newCondition.ifunc = 147
    newCondition.param1 = 251
    newCondition.param2 = 168
    newCondition.unused2 = [1,2,3,4]

    newRecord.conditions = [newRecord.conditions[3], newRecord.conditions[1], newRecord.conditions[0]]

    print "PACK:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "flags   :", newRecord.flags
    print "aiType  :", newRecord.aiType
    print "unused1 :", newRecord.unused1

    print "locType   :", newRecord.locType
    if(newRecord.locType != 5):
        print "locId     :", newRecord.locId
    else:
        print "locId     :", newRecord.locId
    print "locRadius :", newRecord.locRadius

    print "month    :", newRecord.month
    print "day      :", newRecord.day
    print "date     :", newRecord.date
    print "time     :", newRecord.time
    print "duration :", newRecord.duration

    print "targetType  :", newRecord.targetType
    if(newRecord.targetType != 2):
        print "targetId    :", newRecord.targetId
    else:
        print "targetId    :", newRecord.targetId
    print "targetCount :", newRecord.targetCount

    print "conditions"
    for condition in newRecord.conditions:
        print "  operType  :", condition.operType
        print "  unused1   :", condition.unused1
        print "  compValue :", condition.compValue
        print "  ifunc     :", condition.ifunc
        print "  param1    :", condition.param1
        print "  param2    :", condition.param2
        print "  unused2   :", condition.unused2
        print

    print "PACK:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].PACK:
        record.CopyAsOverride(newMod)

    print "PACK:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].PACK:
        record.CopyAsNew(newMod)

    print "PACK:Save Test - TestPACK.esp"
    newMod.save()
    print "PACK:Finished testing"
    Current.Close()

def TestCSTY():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestCSTY.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].CSTY:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "CSTY:Create Record Test"
    newRecord = newMod.create_CSTY()
    d(newRecord)

    print "CSTY:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "CSTYWarTest"

    newRecord.dodgeChance = 1
    newRecord.lrChance = 2
    newRecord.unused1 = [1,2]
    newRecord.lrTimerMin = 3
    newRecord.lrTimerMax = 4
    newRecord.forTimerMin = 5
    newRecord.forTimerMax = 6
    newRecord.backTimerMin = 7
    newRecord.backTimerMax = 8
    newRecord.idleTimerMin = 9
    newRecord.idleTimerMax = 10
    newRecord.blkChance = 11
    newRecord.atkChance = 12
    newRecord.unused2 = [3,4]
    newRecord.atkBRecoil = 13
    newRecord.atkBUnc = 14
    newRecord.atkBh2h = 15
    newRecord.pAtkChance = 16
    newRecord.unused3 = [5,6,7]
    newRecord.pAtkBRecoil = 17
    newRecord.pAtkBUnc = 18
    newRecord.pAtkNormal = 19
    newRecord.pAtkFor = 20
    newRecord.pAtkBack = 21
    newRecord.pAtkL = 22
    newRecord.pAtkR = 23
    newRecord.unused4 = [8,9,10]
    newRecord.holdTimerMin = 24
    newRecord.holdTimerMax = 25
    newRecord.flagsA = 1
    newRecord.acroDodge = 26
    newRecord.unused5 = [11,12]
    newRecord.rMultOpt = 27
    newRecord.rMultMax = 28
    newRecord.mDistance = 29
    newRecord.rDistance = 30
    newRecord.buffStand = 31
    newRecord.rStand = 32
    newRecord.groupStand = 33
    newRecord.rushChance = 34
    newRecord.unused6 = [13,14,15]
    newRecord.rushMult = 35
    newRecord.flagsB = 2
    newRecord.dodgeFMult = 36
    newRecord.dodgeFBase = 37
    newRecord.encSBase = 38
    newRecord.encSMult = 39
    newRecord.dodgeAtkMult = 40
    newRecord.dodgeNAtkMult = 41
    newRecord.dodgeBAtkMult = 42
    newRecord.dodgeBNAtkMult = 43
    newRecord.dodgeFAtkMult = 44
    newRecord.dodgeFNAtkMult = 45
    newRecord.blockMult = 46
    newRecord.blockBase = 47
    newRecord.blockAtkMult = 48
    newRecord.blockNAtkMult = 49
    newRecord.atkMult = 50
    newRecord.atkBase = 51
    newRecord.atkAtkMult = 52
    newRecord.atkNAtkMult = 53
    newRecord.atkBlockMult = 54
    newRecord.pAtkFBase = 55
    newRecord.pAtkFMult = 56

    print "CSTY:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "dodgeChance  :", newRecord.dodgeChance
    print "lrChance     :", newRecord.lrChance
    print "unused1      :", newRecord.unused1
    print "lrTimerMin   :", newRecord.lrTimerMin
    print "lrTimerMax   :", newRecord.lrTimerMax
    print "forTimerMin  :", newRecord.forTimerMin
    print "forTimerMax  :", newRecord.forTimerMax
    print "backTimerMin :", newRecord.backTimerMin
    print "backTimerMax :", newRecord.backTimerMax
    print "idleTimerMin :", newRecord.idleTimerMin
    print "idleTimerMax :", newRecord.idleTimerMax
    print "blkChance    :", newRecord.blkChance
    print "atkChance    :", newRecord.atkChance
    print "unused2      :", newRecord.unused2
    print "atkBRecoil   :", newRecord.atkBRecoil
    print "atkBUnc      :", newRecord.atkBUnc
    print "atkBh2h      :", newRecord.atkBh2h
    print "pAtkChance   :", newRecord.pAtkChance
    print "unused3      :", newRecord.unused3
    print "pAtkBRecoil  :", newRecord.pAtkBRecoil
    print "pAtkBUnc     :", newRecord.pAtkBUnc
    print "pAtkNormal   :", newRecord.pAtkNormal
    print "pAtkFor      :", newRecord.pAtkFor
    print "pAtkBack     :", newRecord.pAtkBack
    print "pAtkL        :", newRecord.pAtkL
    print "pAtkR        :", newRecord.pAtkR
    print "unused4      :", newRecord.unused4
    print "holdTimerMin :", newRecord.holdTimerMin
    print "holdTimerMax :", newRecord.holdTimerMax
    print "flagsA       :", newRecord.flagsA
    print "acroDodge    :", newRecord.acroDodge
    print "unused5      :", newRecord.unused5
    print "rMultOpt     :", newRecord.rMultOpt
    print "rMultMax     :", newRecord.rMultMax
    print "mDistance    :", newRecord.mDistance
    print "rDistance    :", newRecord.rDistance
    print "buffStand    :", newRecord.buffStand
    print "rStand       :", newRecord.rStand
    print "groupStand   :", newRecord.groupStand
    print "rushChance   :", newRecord.rushChance
    print "unused6      :", newRecord.unused6
    print "rushMult     :", newRecord.rushMult
    print "flagsB       :", newRecord.flagsB
    print "dodgeFMult     :", newRecord.dodgeFMult
    print "dodgeFBase     :", newRecord.dodgeFBase
    print "encSBase       :", newRecord.encSBase
    print "encSMult       :", newRecord.encSMult
    print "dodgeAtkMult   :", newRecord.dodgeAtkMult
    print "dodgeNAtkMult  :", newRecord.dodgeNAtkMult
    print "dodgeBAtkMult  :", newRecord.dodgeBAtkMult
    print "dodgeBNAtkMult :", newRecord.dodgeBNAtkMult
    print "dodgeFAtkMult  :", newRecord.dodgeFAtkMult
    print "dodgeFNAtkMult :", newRecord.dodgeFNAtkMult
    print "blockMult      :", newRecord.blockMult
    print "blockBase      :", newRecord.blockBase
    print "blockAtkMult   :", newRecord.blockAtkMult
    print "blockNAtkMult  :", newRecord.blockNAtkMult
    print "atkMult        :", newRecord.atkMult
    print "atkBase        :", newRecord.atkBase
    print "atkAtkMult     :", newRecord.atkAtkMult
    print "atkNAtkMult    :", newRecord.atkNAtkMult
    print "atkBlockMult   :", newRecord.atkBlockMult
    print "pAtkFBase      :", newRecord.pAtkFBase
    print "pAtkFMult      :", newRecord.pAtkFMult

    print "CSTY:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].CSTY:
        record.CopyAsOverride(newMod)

    print "CSTY:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].CSTY:
        record.CopyAsNew(newMod)

    print "CSTY:Save Test - TestCSTY.esp"
    newMod.save()
    print "CSTY:Finished testing"
    Current.Close()

def TestLSCR():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLSCR.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].LSCR:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "LSCR:Create Record Test"
    newRecord = newMod.create_LSCR()
    d(newRecord)

    print "LSCR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LSCRWarTest"

    newRecord.iconPath = r"LSCR\War\Test\Longer\Than\Usual\Just\Because\Test.dds"
    newRecord.text = "Hrm, what on earth could be going on?\n I don't know what this is all about, but I'm sure it'll be fine"

    newLocation = newRecord.create_location()
    newLocation.direct = FormID(7)
    newLocation.indirect = FormID(10)
    newLocation.gridY = 0
    newLocation.gridX = 1

    newLocation = newRecord.create_location()
    newLocation.direct = FormID(8)
    newLocation.indirect = FormID(11)
    newLocation.gridY = 2
    newLocation.gridX = 3

    newLocation = newRecord.create_location()
    newLocation.direct = FormID(9)
    newLocation.indirect = FormID(12)
    newLocation.gridY = 4
    newLocation.gridX = 5

    newLocation = newRecord.create_location()
    newLocation.direct = FormID(10)
    newLocation.indirect = FormID(13)
    newLocation.gridY = 6
    newLocation.gridX = 7

    newRecord.locations = [newRecord.locations[3], newRecord.locations[0], newRecord.locations[2]]

    print "LSCR:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "iconPath :", newRecord.iconPath
    print "text     :", newRecord.text
    print "locations"
    for location in newRecord.locations:
        print "  direct   :", location.direct
        print "  indirect :", location.indirect
        print "  gridY    :", location.gridY
        print "  gridX    :", location.gridX

    print "LSCR:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].LSCR:
        record.CopyAsOverride(newMod)

    print "LSCR:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].LSCR:
        record.CopyAsNew(newMod)

    print "LSCR:Save Test - TestLSCR.esp"
    newMod.save()
    print "LSCR:Finished testing"
    Current.Close()

def TestLVSP():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestLVSP.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].LVSP:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "LVSP:Create Record Test"
    newRecord = newMod.create_LVSP()
    d(newRecord)

    print "LVSP:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "LVSPWarTest"

    newRecord.chanceNone = 20
    newRecord.flags = 1

    entry = newRecord.create_entry()
    entry.level = 1
    entry.unused1 = [0x14, 0xFF]
    entry.listId = FormID(0x0100000A)
    entry.count = 2
    entry.unused2 = [0x15, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 3
    entry.unused1 = [0x16, 0xFF]
    entry.listId = FormID(0x0000000B)
    entry.count = 4
    entry.unused2 = [0x17, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 5
    entry.unused1 = [0x18, 0xFF]
    entry.listId = FormID(0x0000000C)
    entry.count = 6
    entry.unused2 = [0x19, 0xFF]
    entry = newRecord.create_entry()
    entry.level = 7
    entry.unused1 = [0x20, 0xFF]
    entry.listId = FormID(0x0000000D)
    entry.count = 8
    entry.unused2 = [0x21, 0xFF]
    newRecord.entries = [newRecord.entries[3], newRecord.entries[2], newRecord.entries[0]]

    print "LVSP:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "chanceNone :", newRecord.chanceNone
    print "flags      :", newRecord.flags
    print "entries"
    for entry in newRecord.entries:
        print
        print "  level   :", entry.level
        print "  unused1 :", entry.unused1
        print "  listId  :", entry.listId
        print "  count   :", entry.count
        print "  unused2 :", entry.unused2

    print "LVSP:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].LVSP:
        record.CopyAsOverride(newMod)

    print "LVSP:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].LVSP:
        record.CopyAsNew(newMod)

    print "LVSP:Save Test - TestLVSP.esp"
    newMod.save()
    print "LVSP:Finished testing"
    Current.Close()

def TestANIO():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestANIO.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].ANIO:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "ANIO:Create Record Test"
    newRecord = newMod.create_ANIO()
    d(newRecord)

    print "ANIO:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "ANIOWarTest"

    print "modPath..."
    newRecord.modPath = r"ANIO\hay2\1.nif"
    print "modb..."
    newRecord.modb = 2.76
    print "modt_p..."
    newRecord.modt_p = [0x00, 0xFF, 0xFF]

    newRecord.animationId = FormID(7)
    print "ANIO:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "modPath :", newRecord.modPath
    print "modb    :", newRecord.modb
    print "modt_p  :", newRecord.modt_p

    print "animationId :", newRecord.animationId

    print "ANIO:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].ANIO:
        record.CopyAsOverride(newMod)

    print "ANIO:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].ANIO:
        record.CopyAsNew(newMod)

    print "ANIO:Save Test - TestANIO.esp"
    newMod.save()
    print "ANIO:Finished testing"
    Current.Close()

def TestWATR():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestWATR.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].WATR:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "WATR:Create Record Test"
    newRecord = newMod.create_WATR()
    d(newRecord)

    print "WATR:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "WATRWarTest"

    newRecord.texturePath = r"WATR\Texture\Path\Test\1.dds"
    newRecord.opacity = 1
    newRecord.flags = 2
    newRecord.materialPath = r"WATR\Material\Path\Test\2.dds"
    newRecord.sound = FormID(7)
    newRecord.windVelocity = 3
    newRecord.windDirection = 4
    newRecord.waveAmp = 5
    newRecord.waveFreq = 6
    newRecord.sunPower = 7
    newRecord.reflectAmt = 8
    newRecord.fresnelAmt = 9
    newRecord.xSpeed = 10
    newRecord.ySpeed = 11
    newRecord.fogNear = 12
    newRecord.fogFar = 13
    newRecord.shallowRed = 14
    newRecord.shallowGreen = 15
    newRecord.shallowBlue = 16
    newRecord.unused1 = [1]
    newRecord.deepRed = 17
    newRecord.deepGreen = 18
    newRecord.deepBlue = 19
    newRecord.unused2 = [2]
    newRecord.reflRed = 20
    newRecord.reflGreen = 21
    newRecord.reflBlue = 22
    newRecord.unused3 = [3]
    newRecord.blend = 23
    newRecord.unused4 = [4,5,6]
    newRecord.rainForce = 24
    newRecord.rainVelocity = 25
    newRecord.rainFalloff = 26
    newRecord.rainDampner = 27
    newRecord.rainSize = 28
    newRecord.dispForce = 29
    newRecord.dispVelocity = 30
    newRecord.dispFalloff = 31
    newRecord.dispDampner = 32
    newRecord.dispSize = 33
    newRecord.damage = 34
    newRecord.dayWater = FormID(10)
    newRecord.nightWater = FormID(14)
    newRecord.underWater = FormID(35)

    print "WATR:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "texturePath   :", newRecord.texturePath
    print "opacity       :", newRecord.opacity
    print "flags         :", newRecord.flags
    print "materialPath  :", newRecord.materialPath
    print "sound         :", newRecord.sound
    print "windVelocity  :", newRecord.windVelocity
    print "windDirection :", newRecord.windDirection
    print "waveAmp       :", newRecord.waveAmp
    print "waveFreq      :", newRecord.waveFreq
    print "sunPower      :", newRecord.sunPower
    print "reflectAmt    :", newRecord.reflectAmt
    print "fresnelAmt    :", newRecord.fresnelAmt
    print "xSpeed        :", newRecord.xSpeed
    print "ySpeed        :", newRecord.ySpeed
    print "fogNear       :", newRecord.fogNear
    print "fogFar        :", newRecord.fogFar
    print "shallowRed    :", newRecord.shallowRed
    print "shallowGreen  :", newRecord.shallowGreen
    print "shallowBlue   :", newRecord.shallowBlue
    print "unused1       :", newRecord.unused1
    print "deepRed       :", newRecord.deepRed
    print "deepGreen     :", newRecord.deepGreen
    print "deepBlue      :", newRecord.deepBlue
    print "unused2       :", newRecord.unused2
    print "reflRed       :", newRecord.reflRed
    print "reflGreen     :", newRecord.reflGreen
    print "reflBlue      :", newRecord.reflBlue
    print "unused3       :", newRecord.unused3
    print "blend         :", newRecord.blend
    print "unused4       :", newRecord.unused4
    print "rainForce     :", newRecord.rainForce
    print "rainVelocity  :", newRecord.rainVelocity
    print "rainFalloff   :", newRecord.rainFalloff
    print "rainDampner   :", newRecord.rainDampner
    print "rainSize      :", newRecord.rainSize
    print "dispForce     :", newRecord.dispForce
    print "dispVelocity  :", newRecord.dispVelocity
    print "dispFalloff   :", newRecord.dispFalloff
    print "dispDampner   :", newRecord.dispDampner
    print "dispSize      :", newRecord.dispSize
    print "damage        :", newRecord.damage
    print "dayWater      :", newRecord.dayWater
    print "nightWater    :", newRecord.nightWater
    print "underWater    :", newRecord.underWater

    print "WATR:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].WATR:
        record.CopyAsOverride(newMod)

    print "WATR:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].WATR:
        record.CopyAsNew(newMod)

    print "WATR:Save Test - TestWATR.esp"
    newMod.save()
    print "WATR:Finished testing"
    Current.Close()

def TestEFSH():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestEFSH.esp")
    Current.load()

    for record in Current.LoadOrderMods[0].EFSH:
        print
        print "fid     :", record.fid
        printRecord(record)
        break

    print "EFSH:Create Record Test"
    newRecord = newMod.create_EFSH()
    d(newRecord)

    print "EFSH:Set Test"
    print "flags1..."
    newRecord.flags1 = 0x0102
    print "flags2..."
    newRecord.flags2 = 0x0201
    print "eid..."
    newRecord.eid = "EFSHWarTest"

    newRecord.fillTexturePath = r"EFSH\fillTexture\Path\Test\1.dds"
    newRecord.particleTexturePath = r"EFSH\particleTexture\Path\Test\2.dds"
    newRecord.flags = 1
    newRecord.unused1 = [1,2,3]
    newRecord.memSBlend = 2
    newRecord.memBlendOp = 3
    newRecord.memZFunc = 4
    newRecord.fillRed = 5
    newRecord.fillGreen = 6
    newRecord.fillBlue = 7
    newRecord.unused2 = [4]
    newRecord.fillAIn = 8
    newRecord.fillAFull = 9
    newRecord.fillAOut = 10
    newRecord.fillAPRatio = 11
    newRecord.fillAAmp = 12
    newRecord.fillAFreq = 13
    newRecord.fillAnimSpdU = 14
    newRecord.fillAnimSpdV = 15
    newRecord.edgeOff = 16
    newRecord.edgeRed = 17
    newRecord.edgeGreen = 18
    newRecord.edgeBlue = 19
    newRecord.unused3 = [5]
    newRecord.edgeAIn = 20
    newRecord.edgeAFull = 21
    newRecord.edgeAOut = 22
    newRecord.edgeAPRatio = 23
    newRecord.edgeAAmp = 24
    newRecord.edgeAFreq = 25
    newRecord.fillAFRatio = 26
    newRecord.edgeAFRatio = 27
    newRecord.memDBlend = 28
    newRecord.partSBlend = 29
    newRecord.partBlendOp = 30
    newRecord.partZFunc = 31
    newRecord.partDBlend = 32
    newRecord.partBUp = 33
    newRecord.partBFull = 34
    newRecord.partBDown = 35
    newRecord.partBFRatio = 36
    newRecord.partBPRatio = 37
    newRecord.partLTime = 38
    newRecord.partLDelta = 39
    newRecord.partNSpd = 40
    newRecord.partNAcc = 41
    newRecord.partVel1 = 42
    newRecord.partVel2 = 43
    newRecord.partVel3 = 44
    newRecord.partAcc1 = 45
    newRecord.partAcc2 = 46
    newRecord.partAcc3 = 47
    newRecord.partKey1 = 48
    newRecord.partKey2 = 49
    newRecord.partKey1Time = 50
    newRecord.partKey2Time = 51
    newRecord.key1Red = 52
    newRecord.key1Green = 53
    newRecord.key1Blue = 54
    newRecord.unused4 = [6]
    newRecord.key2Red = 55
    newRecord.key2Green = 56
    newRecord.key2Blue = 57
    newRecord.unused5 = [7]
    newRecord.key3Red = 58
    newRecord.key3Green = 59
    newRecord.key3Blue = 60
    newRecord.unused6 = [8]
    newRecord.key1A = 61
    newRecord.key2A = 62
    newRecord.key3A = 63
    newRecord.key1Time = 64
    newRecord.key2Time = 65
    newRecord.key3Time = 66

    print "EFSH:Set Test Results"
    print
    print "fid    :", newRecord.fid
    print "flags1 :", newRecord.flags1
    print "flags2 :", newRecord.flags2
    print "eid    :", newRecord.eid

    print "fillTexturePath     :", newRecord.fillTexturePath
    print "particleTexturePath :", newRecord.particleTexturePath
    print "flags               :", newRecord.flags
    print "unused1             :", newRecord.unused1
    print "memSBlend           :", newRecord.memSBlend
    print "memBlendOp          :", newRecord.memBlendOp
    print "memZFunc            :", newRecord.memZFunc
    print "fillRed             :", newRecord.fillRed
    print "fillGreen           :", newRecord.fillGreen
    print "fillBlue            :", newRecord.fillBlue
    print "unused2             :", newRecord.unused2
    print "fillAIn             :", newRecord.fillAIn
    print "fillAFull           :", newRecord.fillAFull
    print "fillAOut            :", newRecord.fillAOut
    print "fillAPRatio         :", newRecord.fillAPRatio
    print "fillAAmp            :", newRecord.fillAAmp
    print "fillAFreq           :", newRecord.fillAFreq
    print "fillAnimSpdU        :", newRecord.fillAnimSpdU
    print "fillAnimSpdV        :", newRecord.fillAnimSpdV
    print "edgeOff             :", newRecord.edgeOff
    print "edgeRed             :", newRecord.edgeRed
    print "edgeGreen           :", newRecord.edgeGreen
    print "edgeBlue            :", newRecord.edgeBlue
    print "unused3             :", newRecord.unused3
    print "edgeAIn             :", newRecord.edgeAIn
    print "edgeAFull           :", newRecord.edgeAFull
    print "edgeAOut            :", newRecord.edgeAOut
    print "edgeAPRatio         :", newRecord.edgeAPRatio
    print "edgeAAmp            :", newRecord.edgeAAmp
    print "edgeAFreq           :", newRecord.edgeAFreq
    print "fillAFRatio         :", newRecord.fillAFRatio
    print "edgeAFRatio         :", newRecord.edgeAFRatio
    print "memDBlend           :", newRecord.memDBlend
    print "partSBlend          :", newRecord.partSBlend
    print "partBlendOp         :", newRecord.partBlendOp
    print "partZFunc           :", newRecord.partZFunc
    print "partDBlend          :", newRecord.partDBlend
    print "partBUp             :", newRecord.partBUp
    print "partBFull           :", newRecord.partBFull
    print "partBDown           :", newRecord.partBDown
    print "partBFRatio         :", newRecord.partBFRatio
    print "partBPRatio         :", newRecord.partBPRatio
    print "partLTime           :", newRecord.partLTime
    print "partLDelta          :", newRecord.partLDelta
    print "partNSpd            :", newRecord.partNSpd
    print "partNAcc            :", newRecord.partNAcc
    print "partVel1            :", newRecord.partVel1
    print "partVel2            :", newRecord.partVel2
    print "partVel3            :", newRecord.partVel3
    print "partAcc1            :", newRecord.partAcc1
    print "partAcc2            :", newRecord.partAcc2
    print "partAcc3            :", newRecord.partAcc3
    print "partKey1            :", newRecord.partKey1
    print "partKey2            :", newRecord.partKey2
    print "partKey1Time        :", newRecord.partKey1Time
    print "partKey2Time        :", newRecord.partKey2Time
    print "key1Red             :", newRecord.key1Red
    print "key1Green           :", newRecord.key1Green
    print "key1Blue            :", newRecord.key1Blue
    print "unused4             :", newRecord.unused4
    print "key2Red             :", newRecord.key2Red
    print "key2Green           :", newRecord.key2Green
    print "key2Blue            :", newRecord.key2Blue
    print "unused5             :", newRecord.unused5
    print "key3Red             :", newRecord.key3Red
    print "key3Green           :", newRecord.key3Green
    print "key3Blue            :", newRecord.key3Blue
    print "unused6             :", newRecord.unused6
    print "key1A               :", newRecord.key1A
    print "key2A               :", newRecord.key2A
    print "key3A               :", newRecord.key3A
    print "key1Time            :", newRecord.key1Time
    print "key2Time            :", newRecord.key2Time
    print "key3Time            :", newRecord.key3Time

    print "EFSH:CopyAsOverride Test"
    for record in Current.LoadOrderMods[0].EFSH:
        record.CopyAsOverride(newMod)

    print "EFSH:CopyAsNew Test"
    for record in Current.LoadOrderMods[0].EFSH:
        record.CopyAsNew(newMod)

    print "EFSH:Save Test - TestEFSH.esp"
    newMod.save()
    print "EFSH:Finished testing"
    Current.Close()

def TestIdenticalToMaster():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    newMod = Current.addMod("TestIdentical.esp")
    Current.load()
    for block, records in Current.LoadOrderMods[0].aggregates.items():
        for record in records:
            over = record.CopyAsOverride(newMod)
            if over.fid[1] % 10 == 0:
                try:
                    over.eid += 'Testt'
                except:
                    try:
                        over.eid = 'Testt'
                    except:
                        continue
            over.UnloadRecord()
            record.CopyAsNew(newMod).UnloadRecord()
            record.UnloadRecord()

    ident = newMod.GetRecordsIdenticalToMaster()

    for record in ident:
        print record.fid
        record.DeleteRecord()
    newMod.CleanMasters()
    newMod.save()
    Current.Close()

def TestUndelete():
    Current = ObCollection()
    Current.addMod("Oblivion.esm")
    oldMod = Current.addMod("undelete.esp")
    newMod = Current.addMod("TestUndelete.esp")
    delMod = Current.addMod("TestDelete.esp")
    Current.load()
    for records in oldMod.aggregates.values():
        for record in records:
            if record.IsDeleted:
                rec = record.CopyAsOverride(newMod)
                rec.IsDeleted = False
            rec = record.CopyAsOverride(delMod)
            rec.IsDeleted = True
    newMod.save(False)
    delMod.save()
    Current.Close()

def TestFilter():
    with ObCollection() as Current:
        modFile = Current.addMergeMod("FilterTest.esp")
        Current.addMod("Oblivion.esm")
##        Current.addMod("Oblivifall Master File.esm")
        Current.load()
        for group, records in modFile.aggregates.iteritems():
            for record in records:
                print
                print 'HasInvalidFormIDs = ', record.HasInvalidFormIDs()
                d(record)

from timeit import Timer

##print "1TestMinimalLoad"
##test = [Timer('TestMinimalLoad()', 'from __main__ import TestMinimalLoad').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "10TestMinimalLoad"
##test = [Timer('TestMinimalLoad()', 'from __main__ import TestMinimalLoad').timeit(1) for x in range(0, 10)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "1TestFullLoad"
##test = [Timer('TestFullLoad()', 'from __main__ import TestFullLoad').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##print "10TestFullLoad"
##test = [Timer('TestFullLoad()', 'from __main__ import TestFullLoad').timeit(1) for x in range(0, 10)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

##phonenumber = raw_input(">")

##print "1TestReadWriteAll"
##test = [Timer('TestReadWriteAll()', 'from __main__ import TestReadWriteAll').timeit(1) for x in range(0, 1)]
##mini = min(test)
##avgi = sum(test) / len(test)
##maxi = max(test)
##print "Min:%.15f, Avg:%.15f, Max:%.15f" % (mini, avgi, maxi)

phonenumber = raw_input(">")
Current = ObCollection()
Current.addMod("Oblivion.esm")
print "MinLoad"
##Current.addMod("Oblivion.esm", MinLoad=False)
##print "FullLoad"
Current.load()
phonenumber = raw_input(">")
Current.Close()
del Current
phonenumber = raw_input("!")

##regressionTests()

##TestIdenticalToMaster()
##TestUndelete()
##TestAttrReport()
##TestCopyAttrs()
##TestCleanMasters()
##TestFullLoad()
##TestMinimalLoad()
##TestLoadMasters()
##TestDeleteRecord()
##TestReadWriteAll()
##TestTES4()
##TestGMST()
##TestGLOB()
##TestCLAS()
##TestFACT()
##TestHAIR()
##TestEYES()
##TestRACE()
##TestSOUN()
##TestSKIL()
##TestMGEF()
##TestSCPT()
##TestLTEX()
##TestENCH()
##TestSPEL()
##TestBSGN()
##TestACTI()
##TestAPPA()
##TestARMO()
##TestBOOK()
##TestCLOT()
##TestCONT()
##TestDOOR()
##TestINGR()
##TestLIGH()
##TestMISC()
##TestSTAT()
##TestGRAS()
##TestTREE()
##TestFLOR()
##TestFURN()
##TestWEAP()
##TestAMMO()
##TestNPC_()
##TestCREA()
##TestLVLC()
##TestSLGM()
##TestKEYM()
##TestALCH()
##TestSBSP()
##TestSGST()
##TestLVLI()
##TestWTHR()
##TestCLMT()
##TestREGN()
##TestCELL()
##TestWRLD()
##TestDIAL()
##TestQUST()
##TestIDLE()
##TestPACK()
##TestCSTY()
##TestLSCR()
##TestLVSP()
##TestANIO()
##TestWATR()
##TestEFSH()
##TestFilter()
####Current.debug(6, True)
##print "Entirely Finished\n"

##del Current