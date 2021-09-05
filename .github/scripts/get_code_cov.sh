#!/bin/bash

for filename in `find ./src | egrep '\.c'`; 
do 
  f=${filename#./src/}
  gcov ./build/objs/$f; 
  #gcov ./build/objs/$f && mv *.gcov ./build/results/
done

