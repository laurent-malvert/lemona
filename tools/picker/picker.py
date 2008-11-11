#!/usr/bin/env python

from __future__ import with_statement
from datetime   import timedelta
from Zest       import *
from cStringIO  import StringIO

import re, os, sys


def usage():
    print >> sys.stderr, "usage: picker <directories|files>"
    exit(2)

def main():
    #do we have our working directory/file?
    if len(sys.argv) == 1:
        usage()

    #list of files to work on
    files       = []

    #if it's a directory list it contents to find on what to work on
    for path in sys.argv[1:]:
        if os.path.isdir(path):
            dir             = path
            dirFiles        = sorted(os.listdir(dir))
            for f in dirFiles:
                if re.match("^\d+$", f) != None:
                    if dir[len(dir) - 1] == "/":
                        files.append(dir + f)
                    else:
                        files.append(dir + "/" + f)
        else:
            files.append(path)

    #do we find something to work on?
    if len(files) == 0:
        print >> sys.stderr, "Sorry, I didn't find anything relevant to me!"
        exit(3)

    #following vars help us keeping track of truncated zest
    missing     = 0
    left        = StringIO()

    #Yes? Good, go on
    for file in files:
        try:
            fileSize    = os.path.getsize(file)
            print ">>>Examining File", file
            with open(file, "rb") as f:
                pos     = 0;
                while pos != fileSize:
                    print "\t>>Parsing new entry at %s:%d" % (file, pos)
                    try:
                        if missing != 0:
                            print "\t\t>Concatening with previous half", missing
                            left.write(f.read(missing))
                            left.seek(0, os.SEEK_SET)
                            z           = Zest(left)
                            missing     = 0;
                            left.truncate(0);
                        else:
                            z   = Zest(f)
                        pos = f.tell()
                        #TODO, pass the zest to a backend
                        #(e.g. console, database)
                        print z
                    except ZestTruncatedFile, e:
                        missing = e.missing
                        f.seek(pos, os.SEEK_SET)
                        left.write(f.read())
                        print "\t\t>Truncated Zest, Read: %d Missing: %d"\
                            % (left.tell(), missing)
                        break
                    except ZestNullSizeError:
                        break   # No more entry in this file
                    except ZestInvalidFormat:
                        print >> sys.stdout, "Invalid file format!"
                        break
                    finally:
                        print "\t<<Done"
            print "<<<Done", file
        except (IOError, OSError), inst:
            print >> sys.stderr, "Error:", inst
        except Exception, inst:
            print >> sys.stderr, "Error:", inst

#scripting
if __name__ == "__main__":
    main()
    exit(0)

