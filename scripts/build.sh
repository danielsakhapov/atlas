#!/bin/bash
if [ ${PWD##*/} == "scripts" ]
then
	cd ..
	./scripts/clean.sh
else
	./scripts/clean.sh
fi

mkdir build
cd build
cmake ..
make -j 10
cd ..
rm -rf build

