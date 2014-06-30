#!/bin/bash

cd std_utils/
./configure 
cd ..

autoreconf -i
#./configure --enable-caiml --enable-pcrecpp
./configure --enable-caiml --enable-aisl --enable-pcrecpp --enable-javascript --with-v8-path=/home/varol/projects/v8
make

