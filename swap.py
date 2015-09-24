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

args=sys.argv
if len(sys.argv) == 1:
	print "Usage: python signsmu.py <smu firmware>"
	sys.exit()

def reverse(strs):
    return ''.join([strs[i] for i in xrange(len(strs)-1, -1, -1)])

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

sys.stdout.write(firmware)
