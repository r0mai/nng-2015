#!/usr/bin/env python

import sys

if len(sys.argv) != 3:
    print "Usage: " + sys.argv[0] + " <(./message) dns.txt"
    sys.exit(1)

with open(sys.argv[1]) as output:
    with open(sys.argv[2]) as reference:
        index = 0
        while True:
            co = output.read(1)
            cr = reference.read(1)
            if not co and not cr:
                print "Files are identical"
                sys.exit(0)
            if not co:
                print "More chars in reference"
                sys.exit(1)
            if not cr:
                print "More chars in output"
                sys.exit(1)
            if co != cr:
                print "Diff found at", index
                sys.exit(1)
            index += 1

