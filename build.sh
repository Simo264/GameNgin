#! /bin/bash
cmake -S . -B build/ -D BUILD_SHARED_LIBS=ON && make -C build/