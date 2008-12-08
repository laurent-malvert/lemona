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

from struct     import unpack_from
from blades     import console

sysnr   = { "2.6.26.3" : 5 }

sysname = "__NR_open"

def ProcessIn(z):
    # some sanity check
    if z.argnr != 2 or z.extnr != 0:
        raise NameError("Invalid '%s' Zest (In)" % sysname, zest)
    #Filename as passed by user
    console.PrintString("FILENAME", z.args[0], z.argsz[0])
    #Flags & mode
    print " %s | %s " % ("FLAGS".center(37), "MODE".center(37))
    print "-" * 80
    flags       = unpack_from("i", z.args[1])[0]
    mode        = unpack_from("i", z.args[2])[0]
    print " %s | %s " % (str(flags).center(37), str(mode).center(37))
    print "-" * 80

def ProcessOut(z):
    # some sanity check
    if z.argnr != 2 or z.extnr != 0:
        print z
        raise NameError("Invalid '%s' Zest (Out)" % sysname, zest)
    ret = unpack_from("i", z.args[0])[0]
    print " %s | %s " % ("RETURNED".center(17), str(ret).center(58))
    print "-" * 80
    #Path as resolved by kernel
    if ret >= 0:
        str     = z.args[1].split("/")
        str.reverse()
        str     = "/".join(str)
        console.PrintString("RESOLVED PATH", str, z.argsz[1])

def Process(zest):
    if zest.inout == True:
        ProcessIn(zest)
    else:
        ProcessOut(zest)
