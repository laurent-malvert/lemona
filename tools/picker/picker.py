#!/usr/bin/env python

import re, os, sys

from datetime   import timedelta
from struct     import unpack, calcsize

class Zest:
    "A Simple Zest of Lemon(a)"
    Zest_Properties = (
        [ "magic"       , "4s"  , calcsize("4s") ],
        [ "size"        , "i"   , calcsize("i")  ],
        [ "inout"  	, "i"	, calcsize("i")  ],
        [ "sec"    	, "l"	, calcsize("l")  ],
        [ "usec"   	, "l"	, calcsize("l")  ],
        [ "pid"    	, "i"	, calcsize("i")  ],
        [ "tgid"   	, "i"	, calcsize("i")  ],
        [ "uid"    	, "i"	, calcsize("i")  ], #unsigned short
        [ "euid"   	, "i"	, calcsize("i")  ],
        [ "fsuid"  	, "i"	, calcsize("i")  ],
        [ "gid"    	, "i"	, calcsize("i")  ],
        [ "egid"   	, "i"  	, calcsize("i")  ],
        [ "fsgid"  	, "i"  	, calcsize("i")  ],
        [ "sysnr"  	, "i"  	, calcsize("i")  ],
        [ "argnr"  	, "i"  	, calcsize("i")  ],
        [ "pad"    	, "2P" 	, calcsize("2P") ], #void * / argsz, args
        [ "extnr"  	, "i"  	, calcsize("i")  ],
        [ "pad"    	, "2P"  , calcsize("2P") ], #void * / extsz, exts
        )
    Zest_Properties_Size = calcsize("4s 2i 2l 2i 6i 2i 2P i 2P");

    def __init__(self, f):
        parsed_sz = 0
        #get C struct values
        for arg, fmt, sz in self.Zest_Properties:
            buf = f.read(sz)
            if len(buf) != sz:
                print "Invalid File!!! %d <=> %d (%d)" % (len(buf),
                                                          sz, f.tell())
                return None
            if arg != "pad":
                val = unpack(fmt, buf)[0]
                self.setattr(arg, val)

        #get args size
        self.setattr("argsz", [])
        for i in range(self.argnr):
            parsed_sz += calcsize("i");
            val = unpack("i", f.read(calcsize("i")))[0]
            self.argsz.append(val)

        #get args
        self.setattr("args", [])
        for sz in self.argsz:
            parsed_sz += calcsize(str(sz) + "s");
            val = unpack(str(sz) + "s", f.read(sz))[0]
            self.args.append(val)

        #get exts size
        self.setattr("extsz", [])
        for i in range(self.extnr):
            parsed_sz += calcsize("i");
            val = unpack("i", f.read(calcsize("i")))[0]
            self.extsz.append(val)

        #get exts
        self.setattr("exts", [])
        for sz in self.extsz:
            parsed_sz += calcsize(str(sz) + "s");
            val = unpack(str(sz) + "s", f.read(sz))[0]
            self.exts.append(val)

        if self.size - parsed_sz != self.Zest_Properties_Size:
            print self
            raise NameError("Corrupted file!")

    def __str__(self):
        return str(self.__dict__)

    def setattr(self, key, val):
        self.__dict__[key] = val

# scripting

PATH = "../basket/"

files   = []
dirlist = sorted(os.listdir(PATH))

for f in dirlist:
    if re.match("^\d+$", f) != None:
        files.append(f)

print "Preparing to examin files", files

zests = []

#for filename in files:
filename = files[0]
path        = PATH + filename
sz          = os.path.getsize(path)
pos         = 0
f           = open(path, "rb")
while pos < sz:
    print "====PARSING NEW ZEST (Off: %d)====" % pos
    z       = Zest(f)
    pos     = pos + z.size
    print z
f.close()
