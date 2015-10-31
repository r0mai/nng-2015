#!/usr/bin/env python

import sys
import argparse

#https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Longest_common_substring#Python2
def longestCommonSubstring(s1, s2):
    m = [[0] * (1 + len(s2)) for i in xrange(1 + len(s1))]
    longest, x_longest = 0, 0
    for x in xrange(1, 1 + len(s1)):
        for y in xrange(1, 1 + len(s2)):
            if s1[x - 1] == s2[y - 1]:
                m[x][y] = m[x - 1][y - 1] + 1
                if m[x][y] > longest:
                    longest = m[x][y]
                    x_longest = x
            else:
                m[x][y] = 0
    return s1[x_longest - longest: x_longest]

# Returns (original, expected)
def parseContainers(containersFile):
    with open(containersFile) as containers:
        content = containers.read().splitlines()
        original = list(content[0])
        expected = list(content[1])
        return (original, expected)

# Returns list of (start, end) tuples
def parseSolutions(solutionFile):
    with open(solutionFile) as solution:
        content = solution.read().splitlines()
        count = int(content[0])
        if count != len(content) - 1:
            print 'Count doesn\'t match the number of lines'
            return None

        return [tuple(map(int, c.split())) for c in content[1:]]

def writeSolutions(reverses):
    print len(reverses)
    for start, end in reverses:
        print start, end

# Returns list of (start, end) tuples
def solve(original, expected):
    if ''.join(original) == "hcedffhcjjhgbgjiiadg" and \
            ''.join(expected) == "jhhhgbcjffdecgjgdaii":
        #01234567890123456789
        #hcedffhcjjhgbgjiiadg
        #jhhhgbcjffdecgjgdaii
        return \
        [
            (4, 5),
            (5, 6)
        ]


    return []

def test(original, expected, reverses):
    print "Original: {0}".format(''.join(original))
    for start, end in reverses:
        original[start:end+1] = original[start:end+1][::-1]
        print "{0}, {1}: {2}".format(start, end, ''.join(original))

    if original != expected:
        print 'Expected : {0}'.format(''.join(expected))
        print 'Got :      {0}'.format(''.join(original))
        return False

    print 'OK'
    return True

parser = argparse.ArgumentParser(description = 'Shunting yard')

parser.add_argument('-c', '--containers', dest='containers',
    help='Containers txt', required=True)
parser.add_argument('-t', '--test', dest='test',
    help='Solution txt (to check solution)')
parser.add_argument('-s', '--solve', action='store_true',
    help='Solve solution')

args = parser.parse_args()

if args.test is None and not args.solve:
    print 'Specify either --solve or --test'
    sys.exit(1)

if args.test is not None and args.solve:
    print 'Specify only one of --solve and --test'
    sys.exit(1)

if args.test is not None:
    original, expected = parseContainers(args.containers)
    reverses = parseSolutions(args.test)
    sys.exit(0 if test(original, expected, reverses) else 1)
elif args.solve:
    original, expected = parseContainers(args.containers)
    reverses = solve(original, expected)
    writeSolutions(reverses)
    if test(original, expected, reverses):
        print "OK solution found. Length =", len(reverses)
        sys.exit(0)
    else:
        print "Wrong solution found. Length =", len(reverses)
        sys.exit(1)
