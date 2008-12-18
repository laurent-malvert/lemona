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

sysnr   = { "2.6.26.3" : 6 }

sysname = "__NR_close"

def ProcessDo(z, hdr):
    # some sanity check
    if z.argnr != 1 or z.extnr != 0:
        raise NameError("Invalid '%s' Zest (In)" % sysname, z)
    val       = unpack_from("i", z.args[0])[0]
    print " %s | %s " % (hdr.center(17), str(val).center(38))
    print "-" * 80

def Process(zest):
    if zest.inout == True:
        ProcessDo(zest, "FD")
    else:
        ProcessDo(zest, "RETURNED")
