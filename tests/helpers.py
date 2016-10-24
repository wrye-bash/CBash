from cintold import FormID

RecIndent = 2
LastIndent = RecIndent
expandLists = True


def d(record, expand=False):
    global expandLists
    expandLists = expand
    try:
        msize = max([len(attr) for attr in record.copyattrs])
        print "  fid" + " " * (msize - len("fid")), ":", record.fid
    except AttributeError:
        pass
    printRecord(record)


def fflags(y):
    for x in range(32):
        z = 1 << x
        if y & z == z:
            print hex(z)


def printRecord(record):
    global RecIndent
    global LastIndent
    if hasattr(record, 'copyattrs'):
        if expandLists == True:
            msize = max([len(attr) for attr in record.copyattrs if not attr.endswith('_list')])
        else:
            msize = max([len(attr) for attr in record.copyattrs])
        for attr in record.copyattrs:
            wasList = False
            if expandLists == True:
                if attr.endswith('_list'):
                    attr = attr[:-5]
                    wasList = True
            rec = getattr(record, attr)
            if RecIndent: print " " * (RecIndent - 1),
            if wasList:
                print attr
            else:
                print attr + " " * (msize - len(attr)), ":",
            if rec is None:
                print rec
            elif 'flag' in attr.lower() or 'service' in attr.lower():
                print hex(rec)
                if expandLists == True:
                    for x in range(32):
                        z = pow(2, x)
                        if rec & z == z:
                            print " " * RecIndent, " Active" + " " * (msize - len("  Active")), "  :", hex(z)

            elif isinstance(rec, list):
                if len(rec) > 0:
                    IsFidList = True
                    for obj in rec:
                        if not isinstance(obj, FormID):
                            IsFidList = False
                            break
                    if IsFidList:
                        print rec
                    elif not wasList:
                        print rec
                elif not wasList:
                    print rec
            elif isinstance(rec, basestring):
                print `rec`
            elif not wasList:
                print rec
            RecIndent += 2
            printRecord(rec)
            RecIndent -= 2
    elif isinstance(record, list):
        if len(record) > 0:
            if hasattr(record[0], 'copyattrs'):
                LastIndent = RecIndent
                for rec in record:
                    printRecord(rec)
                    if LastIndent == RecIndent:
                        print

