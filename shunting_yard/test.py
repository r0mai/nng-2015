#!/usr/bin/env python

import sys

if len(sys.argv) != 3:
    print "Usage: " + sys.argv[0] + " containersX.txt solutionX.txt"
    sys.exit(1)

with open(sys.argv[1]) as containers:
    content = containers.read().splitlines()
    original = list(content[0])
    expected = list(content[1])

with open(sys.argv[2]) as solution:
    content = solution.read().splitlines()
    count = int(content[0])
    if count != len(content) - 1:
        print "Count doesn't match the number of lines"
        sys.exit(1)

    reverses = content
    del reverses[0]

for reverse in reverses:
    start, end = tuple(map(int, reverse.split()))
    original[start:end+1] = original[start:end+1][::-1]

if original != expected:
    print "Expected : ", expected
    print "Got :      ", original
    sys.exit(1)

print "OK"
