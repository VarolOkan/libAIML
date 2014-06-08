libAIML
=======

Derived off of :: libaiml :: by V01D
====================================

This repository continues the work of the C++ AIML parser from V01D.
It is based off of version 0.6 of libaiml.
I also include the source of std_std_utils-0.7.5 in here to make it easier to compile the code

BUILD:
======

./rebuild.sh

This script will do the following 
  cd st_dutils/
  ./configure 
  cd ..

  autoreconf -i
  ./configure --enable-caiml --enable-pcrecpp
  make


Note: --enable-javascript: JavaScript integration is broken at this moment but I intend to replace the previous integration of SpiderMonkey with googles v8 engine.
This should not only make the system faster but bring it also to the same level as NodeJS.


