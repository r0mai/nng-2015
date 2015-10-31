#!/usr/bin/env python

import sys
import argparse

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

def test(original, expected, reverses):
    for start, end in reverses:
        original[start:end+1] = original[start:end+1][::-1]

    if original != expected:
        print 'Expected : ', expected
        print 'Got :      ', original
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
