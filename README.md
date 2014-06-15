AIML
=======

libAIML by Varol Okan:
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
  ./configure --enable-caiml --enable-pcrecpp --enable-javascript --with-v8-path=/path/to/v8 <br>
  make<br>


Note: --enable-javascript: You need to make sure that the library files are either in the search path ( I.e. ise LDFLAGS, and LIBS ) or you can specify the path to v8's top source directory with --with-v8-path=/path/to/v8/
Please let me know if you run into issues with the libs. You can modify configure.in and run autoconf afterwards and try again ./configure ...


RUN:
====

This should build std_util, libaiml, and the test_app.<p>

cd test_app<br>
cp libaiml.xml.dist libaiml.xml<br>
./test_app<p>

Once you have grown tired of chatting you can simply type

quit


JAVASCRIPT
==========

JavaScript is handled natively through v8. <br>
Please follow the instructions on https://developers.google.com/v8/build to build the libraries.<p>

Since JS is not well specified in the AIML spec, I added test_app/aiml/TestJavaScript file to deonstrate how to use it with libAIML.<br>
Note that the CDATA construct is required for libxml2 to properly read in the JS code.<p>

Also please note that you will have access to the aiml - object in JavaScript. 
```JAVASCRIPT
  var aiml = { 
    user : "name",
    star : "star",
    that : "that",
    topic: "topic",
    bot  : {
      someBotVars ...
    }
  }
```

to test the JS categories you can enter <br>
You: test something<br>
or<br>
You: test aiml<p>

```xml
<category>
  <pattern>TEST *</pattern>
  <template>
    This is cool <star/>.
    <javascript><![CDATA[
      print ( "   Testing JavaScript integration. Working !!! " + JSON.stringify ( aiml ) );
      var t;
      for ( var t=0; t<10; t++ )  {
        print ( "t=" + t );
      }
    ]]></javascript>
  </template>
</category>

<category>
  <pattern>TEST AIML</pattern>
  <template>
    <javascript><![CDATA[
      function objFields ( obj )  {
        for ( var key in obj )  {
         var val = obj[key];
         print ( "  Key[" +key+ "] = " + val );
        }
      }
      print ( "------------------ aiml - object ------------------" );
      objFields ( aiml );
      print ( "------------------ aiml.bot ------------------" );
      objFields ( aiml.bot );
    ]]></javascript>
  </template>
</category>
```

