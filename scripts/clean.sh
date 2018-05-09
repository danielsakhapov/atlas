#!/bin/bash
if [ ${PWD##*/} == "scripts" ]
then
	cd ..

fi

rm -rf bin build lib

