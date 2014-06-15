/***************************************************************************
 *   This file is part of "libaiml"                                        *
 *   Copyright (C) 2005 by V01D                                            *
 *                                                                         *
 *   "libaiml" is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   "libaiml" is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with "libaiml"; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <sstream>
#include "javascript.h"
#include "config.h"
#include "global.h"

#ifdef ENABLE_JAVASCRIPT
#include <v8.h>
using namespace v8;
#endif

#include "aiml.h"
#include "user.h"
#include "serializer.h"
#include "graphmaster.h"

using namespace std;
using namespace aiml;

/** Initialization / Destruction **/
cJavaScript::cJavaScript(void) {
#ifdef ENABLE_JAVASCRIPT
//  interpreter = NULL;
#endif
}

cJavaScript::~cJavaScript(void) {
#ifdef ENABLE_JAVASCRIPT
//  v8::V8::Dispose ( );
#endif
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
#ifdef ENABLE_JAVASCRIPT
void Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
  bool first = true;
  for (int i = 0; i < args.Length(); i++) {
    v8::HandleScope handle_scope(args.GetIsolate());
    if (first) {
      first = false;
    } else {
      printf(" ");
    }
    v8::String::Utf8Value str(args[i]);
    printf("%s", *str);
  }
  printf("\n");
  fflush(stdout);
}
#endif

bool cJavaScript::init(void) {
#ifdef ENABLE_JAVASCRIPT

  V8::InitializeICU ( );
  isolate = Isolate::New ( );

#endif
  return true;
}


/** Evaluation **/
bool cJavaScript::eval ( const std::string &in, std::string &out )  {
#ifdef ENABLE_JAVASCRIPT
  bool success = true;
  m_strError = "";

  Isolate::Scope isolate_scope ( isolate );

  // Create a stack-allocated handle scope.
  HandleScope handle_scope ( isolate );

  // Create a template for the global object.
  v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
  // Bind the global 'print' function to the C++ Print callback.
  global->Set(v8::String::NewFromUtf8(isolate, "print"),
              v8::FunctionTemplate::New(isolate, Print));

  // Create a new context.
  context = Context::New ( isolate, NULL, global );

  // Enter the context for compiling and running the hello world script.
  Context::Scope context_scope ( context );

  std::string str = m_strAiml + in;
  try {
    Handle<String> source = String::NewFromUtf8 ( isolate, str.c_str ( ) );
    // Compile the source code.
    Handle<Script> script = Script::Compile ( source );
    if ( script.IsEmpty ( ) )  {
      m_strError = "JavaScript Compilation error.";
    }
    else  {
      // Run the script to get the result.
      Handle<Value> result = script->Run ( );

      // Convert the result to an UTF8 string and print it.
      String::Utf8Value utf8 ( result );
      m_strEval = *utf8;
      success = true;
//    printf ( "result of %s =  %s\n", in.c_str ( ), str.c_str ( ) );
    }
  }
  catch (...)  {
    m_strError = "Failed to compile";
  }

  return success;
#else
  m_strError = "no JavaScript support";
  return false;
#endif
}

void cJavaScript::set_variables ( const aiml::StarsHolder &sh, aiml::cUser &user )
{
  // Adding AIML objects to the JS interpreter environment
  //
  std::string name  = user.name;
  std::string star  = ( sh.patt.size  ( ) > 0 ) ? *sh.patt.begin  ( ) : "";
  std::string that  = ( sh.that.size  ( ) > 0 ) ? *sh.that.begin  ( ) : "";
  std::string topic = ( sh.topic.size ( ) > 0 ) ? *sh.topic.begin ( ) : "";
  const StringMAP map = user.getAllBotVars ( );

  m_strAiml  = "aiml = { ";
  m_strAiml += "  user : \"" + name  + "\", \n";
  m_strAiml += "  star : \"" + star  + "\", \n";
  m_strAiml += "  that : \"" + that  + "\", \n";
  m_strAiml += "  topic: \"" + topic + "\", \n";
  m_strAiml += "  bot  : { \n";
  StringMAP::const_iterator it = map.begin ( );
  while ( it != map.end ( ) )  {
    m_strAiml += "    " + (*it).first + " : \"" + (*it).second + "\", ";
    ++it;
  }
  m_strAiml += "  }\n";
  m_strAiml += "};";

/*
p user
$17 = (aiml::cUser &) @0xb05198: {
  that_array = {std::vector of length 0, capacity 0, std::vector of length 0, capacity 0, std::vector of length 0, capacity 0, std::vector of length 0, capacity 0,
    std::vector of length 0, capacity 0, std::vector of length 0, capacity 0, std::vector of length 0, capacity 0, std::vector of length 0, capacity 0},
  input_array = {std::vector of length 1, capacity 1 = {"test ddddddddd"}, std::vector of length 0, capacity 0 <repeats 15 times>},
  vars_map = std::map with 0 elements,
  name = "localhost",
  botvars_map = 0xa14a08,
  graphmaster = 0xa14a38,
  last_error = 0xa149d8
}
*/
}


const string& cJavaScript::getRuntimeError(void) {
  return m_strError;
}

