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

__all__ = []

kernel  = None
syshand = {}
sysnohd = []

def PrintZest(mod, z):
    print "-" * 80
    #Header: syscall name
    print ("(" + str(z.sysnr) + ") " + mod.sysname).center(80)
    print "-" * 80
    #date
    inout       = "entry"
    if z.inout == 0:
        inout   = "exit"
    print ("Syscall _%s_ ON %s:%s UTC" % (inout,
                                      z.date.strftime("%A %d %B %G %T"),
                                      z.date.microsecond)).center(80)
    print "-" * 80
    #pid, tgid, uid, gid
    print " %s | %s | %s | %s " % ("PID".center(17), "TGID".center(17),
                                   "UID".center(17), "GID".center(17))
    print "-" * 80
    print " %s | %s | %s | %s " % (str(z.pid).center(17),
                                   str(z.tgid).center(17),
                                   str(z.uid).center(17),
                                   str(z.gid).center(17))
    print "-" * 80
    #euid, fsuid, egid, fsgid
    print " %s | %s | %s | %s " % ("EUID".center(17), "FSUID".center(17),
                                   "EGID".center(17), "FSGID".center(17))
    print "-" * 80
    print " %s | %s | %s | %s " % (str(z.euid).center(17),
                                   str(z.fsuid).center(17),
                                   str(z.egid).center(17),
                                   str(z.fsgid).center(17))
    print "-" * 80
    mod.Process(z)


def PrintString(header, str, strlen):
    off         = 0
    hdrpos      = strlen / 58
    hdrpos      = hdrpos / 2
    if strlen % 2:
        hdrpos  += 1
        hdrpos  = hdrpos * 58
    while off < strlen:
        if off + 58 == hdrpos:
            print " %s | %s " % (header.center(17), str[:58])
        else:
            print " %s | %s " % (" " * 17, str[off:off+58])
        off     += 58
    print "-" * 80

def PrintBuffer(header, buf, buflen):
    print "%s" % header.center(80)
    print "-" * 80
    offTot      = 0
    bufs        = buf.replace("\t", "    ").split("\n")
    for b in bufs:
        off     = 0
        blen    = len(b)
        while off < blen:
            print " %017x | %s " % (offTot + off, b[off:off+58])
            off     += 58
        offTot  += blen
    print "-" * 80

def Process(opts, zest):
    if kernel == None:
        raise NameError("No Kernel Version Provided!")

    dict        = globals() #get this module __dict__
    mod         = None

    if zest.sysnr in syshand:
        mod     = syshand[zest.sysnr]
    elif zest.sysnr not in sysnohd:
        for m in __all__:
            if m in dict and kernel in dict[m].sysnr:
                if zest.sysnr == dict[m].sysnr[kernel]:
                    mod = dict[m]

    if mod != None:
        name = mod.__name__.rsplit(".", 1)[1]
        if opts.only == None or name in opts.only:
            if opts.exclude == None or name not in opts.exclude:
                syshand[zest.sysnr]     = mod
                PrintZest(mod, zest)
    else:
        print "Warning: No handler for %s in backend %s" % (zest.sysnr,
                                                            __name__)
        if zest.sysnr not in sysnohd:
            sysnohd.append(zest.sysnr)
        print zest

def Fill__all__():
    global __all__

    os          = __import__("os")
    re          = __import__("re")

    entries     = os.listdir(__path__[0])
    res         = None
    for e in entries:
        if e == "__init__.py":
            continue
        res = re.match("^(.*)\.py$", e)
        if os.path.isfile(__path__[0] + "/" + e) and res != None:
            __all__.append(res.group(1))

Fill__all__()
del Fill__all__
