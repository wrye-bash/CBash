import os, glob

for top, dirs, files in os.walk('./'):
    for file in files:
        if file.endswith('.h') or file.endswith('.cpp'):
            infile = os.path.join(top, file)
            f = open(infile)
            contents = f.readlines()
            f.close()
            if 'BEGIN LICENSE BLOCK' not in contents[0]:
                print infile
