# smutool  Tool for SMU
# Copyright (C) 2015  Damien Zammit <damien@zamaudio.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# See <http://www.gnu.org/licenses/>. 
#

import sys
import struct, hashlib, hmac

args=sys.argv
if len(sys.argv) == 1:
	print "Usage: python signsmu.py <smu firmware>"
	sys.exit()

def reverse(strs):
    return ''.join([strs[i] for i in xrange(len(strs)-1, -1, -1)])

key1 = "\x77\x33\xbf\x25\x5c\x07\x03\x78\x1f\xb7\xc1\x3b\x7f\x4b\x92\xaf"

f = open(args[1], "rb")
firmware = bytearray()
try:
	firmware = bytearray(f.read())
finally:
	f.close()

for wcnt in range(0,len(firmware)/4):
	tmp = firmware[wcnt*4]
	firmware[wcnt*4] = firmware[wcnt*4+3]
	firmware[wcnt*4+3] = tmp
	tmp = firmware[wcnt*4+1]
	firmware[wcnt*4+1] = firmware[wcnt*4+2]
	firmware[wcnt*4+2] = tmp

h = hmac.new(key1, firmware, hashlib.sha1)
mhash = h.digest()
print hex(struct.unpack(">5I", mhash)[0])
print hex(struct.unpack(">5I", mhash)[1])
print hex(struct.unpack(">5I", mhash)[2])
print hex(struct.unpack(">5I", mhash)[3])
print hex(struct.unpack(">5I", mhash)[4])

