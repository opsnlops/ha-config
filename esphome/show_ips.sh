#!/bin/bash

grep 'ip:' *.yaml | cut -d . -f 5 | sort -n

