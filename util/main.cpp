/***************************************************************************
 *   This file is part of "libAIML"                                        *
 *   Copyright (C) 2014 by Varol Okan                                      *
 *                                                                         *
 *   "libAIML" is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   "libAIML" is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with "libAIML"; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <fstream>
#include <iostream>

#include "std_util.h"
#include "../src/aiml.h"

#include "parser.h"

using namespace std;
using std_util::strip;
using namespace aiml;

class cTestAppCallbacks : public cInterpreterCallbacks
{
  public:
    void onLoad ( const std::string &filename )
    {
      cout << "Loaded " << filename << endl;
    }
};

int main ( int argc, char* argv[] )
{

  Parser parser;
  if ( ! parser.parseCommandLine ( argc, argv ) )
    return 0;

  cInterpreter *pInterpreter = cInterpreter::newInterpreter ( );
  int ret = 0;

  // exceptions are used because returning in the middle of the program wouldn't let 'interpreter' be freed
  try {
    cTestAppCallbacks cb;
    pInterpreter->registerCallbacks ( &cb );

    cCoreOptions options;
    options.allow_system     = true;
    options.allow_javascript = true;
    options.file_patterns    = parser.input ( );

    cout << "Initializing interpreter..." << endl;
    if ( ! pInterpreter->initialize ( options ) )
      throw 1;

    if ( ! pInterpreter->saveGraphmaster ( parser.output ( ) ) )
      throw 1;

  }
  catch ( int _ret )  {
    cout << "ERROR: " << pInterpreter->getErrorStr ( pInterpreter->getError ( ) ) << " (" << pInterpreter->getError ( ) << ")" << endl;
    if ( ! pInterpreter->getRuntimeErrorStr ( ).empty ( ) )
      cout << "Runtime Error: " << pInterpreter->getRuntimeErrorStr ( ) << endl;
    ret = _ret;
  }

  delete pInterpreter;
  // the above is equivalent to cInterpreter::freeInterpreter(interpreter);
  return ret;
}
