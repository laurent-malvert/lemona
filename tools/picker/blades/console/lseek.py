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

sysnr   = { "2.6.26.3" : 19 }

sysname = "__NR_lseek"

def ProcessIn(z):
    # some sanity check
    if z.argnr != 3 or z.extnr != 0:
        raise NameError("Invalid '%s' Zest (In)" % sysname, z)
    #fd, offset & whence
    print " %s | %s | %s " % ("FD".center(24), "OFFSET".center(24),
                              "WHENCE".center(24))
    print "-" * 80
    fd  = unpack_from("i", z.args[0])[0]
    off = unpack_from("i", z.args[1])[0]
    wh  = unpack_from("i", z.args[2])[0]
    if wh == 0:
        wh      = "SEEK_SET"
    elif wh == 1:
        wh      = "SEEK_CUR"
    else:
        wh      = "SEEK_END"
    print " %s | %s | %s " % (str(fd).center(24), str(off).center(24),
                              wh.center(24))
    print "-" * 80

def ProcessOut(z):
    # some sanity check
    if z.argnr != 1 or z.extnr != 0:
        print z
        raise NameError("Invalid '%s' Zest (Out)" % sysname, z)
    ret = unpack_from("i", z.args[0])[0]
    print " %s | %s " % ("RETURNED".center(17), str(ret).center(58))
    print "-" * 80

def Process(zest):
    if zest.inout == True:
        ProcessIn(zest)
    else:
        ProcessOut(zest)
