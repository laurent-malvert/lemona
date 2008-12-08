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

sysnr   = { "2.6.26.3" : 4 }

sysname = "__NR_write"

def ProcessIn(z):
    # some sanity check
    if z.argnr != 3 or z.extnr != 0:
        raise NameError("Invalid '%s' Zest (In)" % sysname, z)
    #fd & count (i.e. buffer size)
    print " %s | %s " % ("FD".center(37), "BUFFER SIZE".center(37))
    print "-" * 80
    fd          = unpack_from("i", z.args[0])[0]
    count       = unpack_from("i", z.args[1])[0]
    print " %s | %s " % (str(fd).center(37), str(count).center(37))
    print "-" * 80
    if count > 0:
        console.PrintBuffer("BUFFER", z.args[2], z.argsz[2])

def ProcessOut(z):
    # some sanity check
    if z.argnr != 1 or z.extnr != 0:
        raise NameError("Invalid '%s' Zest (Out)" % sysname, zest)
    ret = unpack_from("i", z.args[0])[0]
    print " %s | %s " % ("RETURNED".center(17), str(ret).center(58))
    print "-" * 80

def Process(zest):
    if zest.inout == True:
        ProcessIn(zest)
    else:
        ProcessOut(zest)
