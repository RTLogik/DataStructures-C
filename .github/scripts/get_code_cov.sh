#!/bin/bash

cd ../..

for filename in `find ./src | egrep '\.c'`; 
do 
  gcov ./build/objs/$filename > /dev/null; 
  # gcov ./build/objs/$filename && mv *.gcov ./build/results/
done

