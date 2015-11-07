#!/usr/bin/env bash

tmpFile="/tmp/punchcard_sorting_output.txt"

if [ -e $tmpFile ]; then
  echo "You already have a $tmpFile. Remove it before running" >&2
  exit 1
fi

time build/punchcard_sorting < punchcard_sorting/sample.txt > $tmpFile

diff $tmpFile <(tail -n+2 punchcard_sorting/sample.txt | sort)

rm $tmpFile
