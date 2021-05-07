#!/bin/bash

NAME="$1"

if [[ $NAME == *.cpp ]]; then cp src/template.cpp $NAME; \
elif [[ $NAME == *.py ]]; then cp src/template.py $NAME; \
else touch $NAME; \
fi

vim $NAME
