# -*- coding: utf-8 -*-
##
## This file is part of Lemona.
## Copyright (C) 2008 Kenfe-Mickaël Laventure
##
## The contents of this file are subject to the terms of either the
## GNU General Public License Version 2 ("GPL") or the MIT License
## (collectively, the "License"). You may not use this file except in
## compliance with the License. You can obtain a copy of the License
## at http://www.opensource.org/licenses/gpl-2.0.php and
## http://www.opensource.org/licenses/mit-license.php or GPL.LICENSE
## and MIT.LICENSE. See the License for the specific language
## governing permissions and limitations under the License.
##

from struct     import unpack, calcsize
from datetime   import datetime

import sys, traceback

class ZestInvalidFormat(Exception):
    pass

class ZestNullSizeError(Exception):
    pass

class ZestTruncatedFile(Exception):
    def __init__(self, zest):
        self.unparsed   = zest.parsed
        self.missing    = zest.size - zest.parsed + (zest.size % zest.Alignment)

class Zest:
    "A Simple Zest of Lemon(a)"
    Properties = (
        [ "size"        , "i"   , calcsize("i")  ],
        [ "magic"       , "4s"  , calcsize("4s") ],
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
    Properties_Size     = calcsize("4s 2i 2l 2i 6i 2i 2P i 2P")
    Alignment           = calcsize("i")

    def __init__(self, f):
        #Keep track of how many bytes we read so far
        self.parsed     = 0

        #get C struct values
        for arg, fmt, sz in self.Properties:
            buf         = f.read(sz)
            self.parsed = self.parsed + len(buf)

            if len(buf) != sz:
                if self.size == 0:
                    raise ZestNullSizeError
                else:
                    raise ZestTruncatedFile(self)

            if arg != "pad":
                val     = unpack(fmt, buf)[0]
                self.setattr(arg, val)

        if self.size == 0:
            raise ZestNullSizeError()

        if self.magic != 'ZeSt':
            print self
            raise ZestInvalidFormat()

        #get args size
        self.setattr("argsz", [])
        for i in range(self.argnr):
            toRead      = calcsize("i")
            buf         = f.read(toRead)
            bsz         = len(buf)
            self.parsed = self.parsed + bsz
            if bsz != toRead:
                raise ZestTruncatedFile(self)
            val         = unpack("i",  buf)[0]
            self.argsz.append(val)

        #get args
        self.setattr("args", [])
        for sz in self.argsz:
            toRead      = calcsize(str(sz) + "s");
            buf         = f.read(sz)
            bsz         = len(buf)
            self.parsed = self.parsed + bsz
            if bsz != toRead:
                raise ZestTruncatedFile(self)
            val         = unpack(str(sz) + "s", buf)[0]
            self.args.append(val)

        #get exts size
        self.setattr("extsz", [])
        for i in range(self.extnr):
            toRead      = calcsize("i")
            buf         = f.read(toRead)
            bsz         = len(buf)
            self.parsed = self.parsed + bsz
            if bsz != toRead:
                raise ZestTruncatedFile(self)
            val         = unpack("i",  buf)[0]
            self.extsz.append(val)

        #get exts
        self.setattr("exts", [])
        for sz in self.extsz:
            toRead      =  calcsize(str(sz) + "s");
            buf         = f.read(sz)
            bsz         = len(buf)
            self.parsed = self.parsed + bsz
            if bsz != toRead:
                raise ZestTruncatedFile(self)
            val         = unpack(str(sz) + "s", buf)[0]
            self.exts.append(val)


        #sanity check
        if self.size != self.parsed:
            raise NameError("Corrupted file!", self)

        #set date
        sec     = self.sec + self.usec / 1000000
        usec    = self.usec % 1000000
        self.date = datetime.utcfromtimestamp(sec).replace(microsecond=usec)

        #skip alignment
        align   = self.Alignment
        align   = (self.size / align + self.size % align) * align;
        f.read(align - self.size)

    def __str__(self):
        return str(self.__dict__)

    def setattr(self, key, val):
        self.__dict__[key] = val
