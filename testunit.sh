#!/bin/bash

./compile.sh
chmod ugo+rwx build/run_test.sh
./build/run_test.sh