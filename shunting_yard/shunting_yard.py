#!/usr/bin/env python

import sys
import copy
import argparse

#Based on https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Longest_common_substring#Python2
# Returns (s1_startindex, s2_startindex, length)
def longestCommonSubstring(s1, s2):
    m = [[0] * (1 + len(s2)) for i in xrange(1 + len(s1))]
    longest, x_longest, y_longest = 0, 0, 0
    for x in xrange(1, 1 + len(s1)):
        for y in xrange(1, 1 + len(s2)):
            if s1[x - 1] == s2[y - 1]:
                m[x][y] = m[x - 1][y - 1] + 1
                if m[x][y] > longest:
                    longest = m[x][y]
                    x_longest = x
                    y_longest = y
            else:
                m[x][y] = 0

    return (x_longest - longest, y_longest - longest, longest)
    #return s1[x_longest - longest: x_longest]

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

def writeSolutions(solutionFile, reverses):
    with open(solutionFile, 'w') as solution:
        print >> solution, len(reverses)
        for start, end in reverses:
            print >> solution, start, end

def getDiffCount(original, expected):
    i = 0
    c = 0
    while i < len(original):
        if original[i] != expected[i]:
            c += 1
        i += 1
    return c

def getLCSSCandidate(original, expected):
    if original == expected:
        return None

    # original_start, expected_start, length
    os, es, l = longestCommonSubstring(original, expected)
    ros, res, rl = longestCommonSubstring(original, expected[::-1])

    # Adjust, because the string was reversed
    res = len(expected) - res - rl

    # forward case
    if l > 1 and l > rl and os != es:
        step1 = (min(os, es), max(os + l, es + l) - 1)
        step2 = (es, es + l - 1)
        return [step1, step2]
    # backward case
    elif rl > 1:
        step = (min(ros, res), max(ros + rl, res + rl) - 1)
        return [step]

    return None

def swapSteps(i, j):
    if i == j:
        print "Warning swap with itself"
        return []

    low = min(i, j)
    high = max(i, j)

    if low + 1 == high or low + 2 == high:
        return [(i, j)]

    return [
        (low, high),
        (low + 1, high - 1)
    ]

def getSwapCandidate(original, expected):
    if original == expected:
        return None

    # Search for 2 way swaps
    i = 0
    while i < len(original):
        if original[i] != expected[i]:
            j = i + 1
            while j < len(original):
                if original[j] == expected[i] and original[i] == expected[j]:
                    return swapSteps(i, j)
                j += 1
        i += 1

    # Search for N way swaps
    i = 0
    while i < len(original):
        if original[i] != expected[i]:
            j = i+1
            while j < len(original):
                if original[j] != expected[j] and original[i] == expected[j]:
                    return swapSteps(i, j)
                j += 1
        i += 1

    return None

def getGreedyCandidate(originalCopy, expected):
    original = copy.copy(originalCopy)
    if original == expected:
        return None

    bestDiff = 0
    best = None
    i = 0
    while i < len(original):
        j = i + 1
        while j < len(original):
            beforeDiff = getDiffCount(original, expected)
            originalTmp = applySteps(original, [(i, j)])
            afterDiff = getDiffCount(originalTmp, expected)
            if beforeDiff - afterDiff > bestDiff:
                bestDiff = beforeDiff - afterDiff
                best = [(i, j)]
            j += 1
        i += 1

    if bestDiff > 1:
        return best

    return None

def applySteps(originalCopy, steps):
    original = copy.copy(originalCopy)
    for start, end in steps:
        original[start:end+1] = original[start:end+1][::-1]

    return original


# Returns list of (start, end) tuples
def solve(original, expected):
    result = []
    while True:
        steps = getLCSSCandidate(original, expected)
        if steps is None:
            break
        beforeDiff = getDiffCount(original, expected)
        originalTmp = applySteps(original, steps)
        afterDiff = getDiffCount(originalTmp, expected)
        if beforeDiff <= afterDiff:
            break
        result += steps
        original = copy.copy(originalTmp)

    print "Diff after longest substring matching: ", getDiffCount(original, expected)

    while True:
        steps = getGreedyCandidate(original, expected)
        if steps is None:
            break

        original = applySteps(original, steps)
        result += steps

    print "Diff after greedy algo: ", getDiffCount(original, expected)

    while True:
        steps = getSwapCandidate(original, expected)
        if steps is None:
            break

        original = applySteps(original, steps)
        result += steps

    print "Diff after swapping: ", getDiffCount(original, expected)

    return result

def test(original, expected, reverses):
    print "Expected:\t{0}".format(''.join(expected))
    print "Original:\t{0}".format(''.join(original))
    for start, end in reverses:
        if start >= end:
            print "Error: start = {0} > end = {1}".format(start, end)
            return False
        original[start:end+1] = original[start:end+1][::-1]
        # print "{0}, {1}:\t\t{2}".format(start, end, ''.join(original))

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
parser.add_argument('-s', '--solve', dest='solve',
    help='Solve solution to file')

args = parser.parse_args()

if args.test is None and args.solve is None:
    print 'Specify either --solve or --test'
    sys.exit(1)

if args.test is not None and args.solve is not None:
    print 'Specify only one of --solve and --test'
    sys.exit(1)

if args.test is not None:
    original, expected = parseContainers(args.containers)
    reverses = parseSolutions(args.test)
    sys.exit(0 if test(original, expected, reverses) else 1)
elif args.solve is not None:
    original, expected = parseContainers(args.containers)
    reverses = solve(original, expected)
    writeSolutions(args.solve, reverses)
    if test(original, expected, reverses):
        print "OK solution found. Length =", len(reverses)
        sys.exit(0)
    else:
        print "Wrong solution found. Length =", len(reverses)
        sys.exit(1)
