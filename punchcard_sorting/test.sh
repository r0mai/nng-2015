#!/usr/bin/env bash

diff <(build/punchcard_sorting < punchcard_sorting/sample.txt) <(tail -n+2 punchcard_sorting/sample.txt | sort)
