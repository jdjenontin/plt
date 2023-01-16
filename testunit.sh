#!/bin/bash

make -C build all 
#./compile.sh
chmod ugo+rwx build/run_test.sh
./build/run_test.sh


# Generation du coverage 
make -C build code-coverage