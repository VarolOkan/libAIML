AIML
=======

libaiml by Varol Okan:
=======================

This repository continues the work of the C++ AIML parser from V01D.<br>
It is based off of version 0.6.1 of libaiml.<br>
I also include the source of std_utils-0.7.5 in here to make it easier to compile the code<p>

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

Note: --enable-javascript: Youneed to make sure that the library files are either in the search path ( I.e. ise LDFLAGS, and LIBS ) or you can specify the path to v8's top source directory with --with-v8-path=/path/to/v8/
Please let me know if you run into issues with the libs. You can modify configure.in and run autoconf afterwards and try again ./configure ...


RUN:
====

This should build std_util, libaiml, and the test_app.<p>

cd test_app<br>
cp libaiml.xml.dist libaiml.xml<br>
./test_app<p>

Once you have grown tired of chatting you can simply type

quit

