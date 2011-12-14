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