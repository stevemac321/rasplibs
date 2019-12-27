#!/bin/bash

mv $1 $1.tmp
clang-format $1.tmp > $1
rm $1.tmp
