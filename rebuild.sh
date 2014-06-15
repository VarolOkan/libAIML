#!/bin/bash

cd std_utils/
./configure 
cd ..

autoreconf -i
#./configure --enable-caiml --enable-pcrecpp
./configure --enable-caiml --enable-pcrecpp --enable-javascript --with-v8-path=/home/varol/projects/AstraNOS/tech/AI/libAIML/JavaScript/v8
make

