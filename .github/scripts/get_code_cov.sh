#!/bin/bash

for filename in `find ./src | egrep '\.c'`; 
do 
  f=${filename#./src/}
  gcov ./build/objs/$f; 
done

