import os, glob
lineCount = 0
for infile in glob.glob('*.cpp'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    lineCount += len(contents)
##    o = open(infile,'w')
##    [o.write(l.rstrip() + '\n') for l in contents]
##    o.close()

for infile in glob.glob('*.h'):
    f = open(infile)
    contents = f.readlines()
    f.close()
    lineCount += len(contents)

print lineCount    