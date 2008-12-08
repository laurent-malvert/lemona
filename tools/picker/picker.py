#!/usr/bin/env python
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


from __future__ import with_statement
from datetime   import timedelta
from cStringIO  import StringIO
from optparse   import OptionParser
from Zest       import *

import re, os, sys

BACKENDS        = []
BACKENDS_DIR    = "blades"
DEFAULT_BACKEND = "console"
KERNEL_VERSION  = "2.6.26.3"
PICKER_VERSION  = "0.1"

#
def BackendsGet(dir):
    global DEFAULT_BACKEND

    if os.path.isdir(dir) == False:
        return
    if os.path.exists(dir + "/__init__.py") == False:
        return

    entries     = os.listdir(dir)
    for e in entries:
        path = dir + "/" + e;
        if os.path.isdir(path) and os.path.exists(path + "/__init__.py"):
            #print "importing", path.replace("/", ".")
            mod         = __import__(path.replace("/", "."), fromlist=["*"])
            mod.kernel  = KERNEL_VERSION
            BACKENDS.append(mod)
            if e == DEFAULT_BACKEND:
                DEFAULT_BACKEND = mod

#
def ParseOptionListBackends(option, opt, value, parser):
    if len(BACKENDS) == 0:
        print "There is no available backends"
    else:
        print "The following backend(s) are available:"
        for b in BACKENDS:
            print "\t", b.__name__.split(".")[1]
    exit(0)

#
def ParseOptionOnly(option, opt, value, parser):
    syscalls    = set(value.lower().split(","))
    if len(syscalls) > 0:
        entries = []
        for e in syscalls:
            entries.append(e)
        setattr(parser.values, option.dest, entries)

#
def ParseOptionExclude(option, opt, value, parser):
    ParseOptionOnly(option, opt, value, parser)

#
def ParseOptionBackends(option, opt, value, parser):
    backends    = set(value.lower().split(",")) #no duplicates please
    if len(backends) > 0:
        vals    = []
        for b in BACKENDS:
            if b.__name__.split(".")[-1] in backends:
                vals.append(b)
        setattr(parser.values, option.dest, vals)
    else:
        setattr(parser.values, option.dest, [ DEFAULT_BACKEND ])

#
def main():
    #get available backends
    BackendsGet(BACKENDS_DIR)

    #parsing options
    usage               = "usage: %prog [options] <directories|files>"
    parser              = OptionParser(usage=usage,
                                       version="%prog " + PICKER_VERSION)
    parser.add_option("-b", "--backends", dest="backends",
                      help="backends to be called separated by commas",
                      action="callback", type="string",
                      callback=ParseOptionBackends,
                      default=[ DEFAULT_BACKEND ])
    parser.add_option("-l", "--list-backends",
                      help="Print a list of available backends",
                      action="callback",
                      callback=ParseOptionListBackends)
    parser.add_option("-o", "--only", dest="only",
                      help="Parse only entry type matching the ones given",
                      action="callback", type="string",
                      callback=ParseOptionOnly)
    parser.add_option("-e", "--exclude", dest="exclude",
                      help="Parse every entry except the ones given",
                      action="callback", type="string",
                      callback=ParseOptionExclude)
    (opts, args)        = parser.parse_args()

    #do we have our working directory/file? If not use the current directory
    if len(args) == 0:
        args.append(".")

    #list of files to work on
    files       = []

    #if it's a directory list it contents to find on what to work on
    for path in args:
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
                        #pass the zest to the requested backend(s)
                        #(e.g. console, database)
                        for b in opts.backends:
                            b.Process(opts, z)
                    except ZestTruncatedFile, e:
                        missing = e.missing
                        f.seek(pos, os.SEEK_SET)
                        left.write(f.read())
                        print "\t\t>Truncated Zest, Read: %d Missing: %d"\
                            % (left.tell(), missing)
                        break
                    except ZestNullSizeError:
                        print "\t\t Seems like there is no more entries"
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

