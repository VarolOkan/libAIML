bAIML
=======

Derived off of :: libaiml :: by V01D
====================================

This repository continues the work of the C++ AIML parser from V01D.<br>
It is based off of version 0.6 of libaiml.<br>
I also include the source of std_std_utils-0.7.5 in here to make it easier to compile the code<p>

BUILD:
======

./rebuild.sh

This script will do the following<br>
  cd std_utils<br>
  ./configure <br>
  cd ..<br>
<br>
  autoreconf -i<br>
  ./configure --enable-caiml --enable-pcrecpp<br>
  make<br>


Note: --enable-javascript: JavaScript integration is broken at this moment but I intend to replace the previous integration of SpiderMonkey with googles v8 engine.<br>
This should not only make the system faster but bring it also to the same level as NodeJS.

RUN:
====

This should build std_util, libaiml, and the test_app.<p>

cd test_app<br>
cp libaiml.xml.dist libaiml.xml
./test_app


