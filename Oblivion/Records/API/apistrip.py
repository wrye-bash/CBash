import os, glob

def maxer(lines):
    nums = [-1]
    for line in lines:
##        if line.lstrip()[:2] == '//':
##            continue
        pos = line.find('=')
        if pos != -1:
            i = 1
            while line[pos-i] == ' ':
                i += 1
            nums.append(pos-i+2)
    return max(nums)

def spacer(line, maxsize):
    pos = line.find('=')
    if pos != -1:
        i = 1
        while line[pos-i] == ' ':
            i += 1
        g = 1
        while line[pos+g] == ' ':
            g += 1
        line = line[:pos-i+1] + ' = ' + line[pos+g:]
        pos = line.find('=')
        return line[:pos] + ' ' * (maxsize - pos) + line[pos:]
    return line
for infile in glob.glob('*.cpp~'):
    os.remove(infile)
for infile in glob.glob('*.h~'):
    os.remove(infile)
for infile in glob.glob('*.bak'):
    os.remove(infile)
for infile in glob.glob('*.cpp'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    o = open(infile,'w')
    inEnum = False
    inTest = False
    inSet = False
    inDel = False
    inGet = False
    inAttr = False
    enumLines = []
    testLines = []
    num = 0
    for l in contents[:-1]:
        num += 1
        l = l.rstrip() + '\n'
        if inEnum:
            enumLines += [l]
            if '}' in l:
                maxsize = maxer(enumLines)
                for line in enumLines:
                    pos = line.find('=')
                    if pos != -1:
                        line = spacer(line, maxsize)
                    o.write(line)
                inEnum = False
                enumLines = []
        elif inSet or inDel or inGet or inAttr:
            testLines += [l]
            if inDel:
                if 'break' in l:
                    print 'Break found in ', infile, 'DeleteField'
                    print '\t', testLines[-3],
                    print '\t', testLines[-2],
                    print '\t', l
            if inGet:
                if 'UNKNOWN_FIELD' in l:
                    print 'UNKNOWN_FIELD found in ', infile, 'GetField'
                    print '\t', testLines[-3],
                    print '\t', testLines[-2],
                    print '\t', l
            if inAttr:
                pass
            if inDel or inSet or inGet:
                if 'default:' in l:
                    if 'break' not in testLines[-2] and 'return' not in testLines[-2]:
                        if '}' in testLines[-2] or 'break' not in testLines[-3] and 'return' not in testLines[-3]:
                            print 'Missing break found in ', infile, 'line', num
                            print '\t', testLines[-3],
                            print '\t', testLines[-2],
                            print '\t', l
                if ' case ' in l and 'switch' not in testLines[-3]:
                    if 'break' not in testLines[-2] and 'return' not in testLines[-2]:
                        if '}' in testLines[-2] or 'break' not in testLines[-3] and 'return' not in testLines[-3]:
                            print 'Missing break or return found in ', infile, 'line', num
                            print '\t', testLines[-3],
                            print '\t', testLines[-2],
                            print '\t', l
            if l.startswith('    }'):
                inSet = False
                inDel = False
                inGet = False
                inAttr = False
                testLines = []
            o.write(l)
        else:
            o.write(l)
        if ' enum ' in l:
            inEnum = True
        if 'SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)' in l:
            inSet = True
        if 'DeleteField(FIELD_IDENTIFIERS)' in l:
            inDel = True
        if 'GetField(FIELD_IDENTIFIERS, void **FieldValues)' in l:
            inGet = True
        if 'GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)' in l:
            inAttr = True
            
    l = contents[-1].rstrip()
    if inEnum:
        enumLines += [l]
        if '}' in l:
            maxsize = maxer(enumLines)
            for line in enumLines:
                pos = line.find('=')
                if pos != -1:
                    line = spacer(line, maxsize)
                o.write(line)
            inEnum = False
            enumLines = []
    else:
        o.write(l) 
    o.close()

for infile in glob.glob('*.h'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    o = open(infile,'w')
    inEnum = False
    enumLines = []
    for l in contents[:-1]:
        l = l.rstrip() + '\n'
        if inEnum:
            enumLines += [l]
            if '}' in l:
                maxsize = maxer(enumLines)
                for line in enumLines:
                    pos = line.find('=')
                    if pos != -1:
                        line = spacer(line, maxsize)
                    o.write(line)
                inEnum = False
                enumLines = []
        else:
            o.write(l)
        if ' enum ' in l:
            inEnum = True
    l = contents[-1].rstrip()
    if inEnum:
        enumLines += [l]
        if '}' in l:
            maxsize = maxer(enumLines)
            for line in enumLines:
                pos = line.find('=')
                if pos != -1:
                    line = spacer(line, maxsize)
                o.write(line)
            inEnum = False
            enumLines = []
    else:
        o.write(l) 
    o.close()