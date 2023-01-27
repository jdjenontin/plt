#!/bin/bash
chmod ugo+rwx build/run_test.sh
./build/run_test.sh

# Generation du coverage 
make -C build code-coverage

# Ouvrir la page de Coverage dans le navigateur

xdg-open build/code-coverage/index.html