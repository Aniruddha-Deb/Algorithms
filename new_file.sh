#!/bin/bash

NAME="$1"

if [[ $NAME == *.cpp ]]; then cp src/template.cpp src/$NAME; \
elif [[ $NAME == *.py ]]; then cp src/template.py src/$NAME; \
else touch src/$NAME; \
fi

vim src/$NAME
