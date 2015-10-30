#!/usr/bin/env python

import sys

if len(sys.argv) != 3:
    print "Usage: " + sys.argv[0] + " jailX.txt solutionX.txt"
    sys.exit(1)

with open(sys.argv[1]) as jail:
    content = map(int, jail.read().splitlines())
    prisoners = content[1:]

with open(sys.argv[2]) as solution:
    content = solution.read().splitlines()
    count = int(content[0])
    if count != len(content) - 1:
        print "Count doesn't match the number of lines"
        sys.exit(1)

    del content[0]
    shifts = [[int(y) for y in x.split()] for x in content]

map(lambda x: x.sort(), shifts)

if sorted([item for sublist in shifts for item in sublist]) != sorted(prisoners):
    print "Prisoners in solution file don't match the jail file"
    sys.exit(1)

for shift in shifts:
    l = len(shift)
    c = 2
    while c < l:
        b = 1
        while b < c:
            a = 0
            while a < b:
                if shift[a] + shift[b] == shift[c]:
                    print "(a = " + str(shift[a]) + \
                        ") + (b = " + str(shift[b]) + \
                        ") == (c = " + str(shift[c]) + ")"
                    sys.exit(1)
                a += 1
            b += 1
        c += 1
print "OK"
