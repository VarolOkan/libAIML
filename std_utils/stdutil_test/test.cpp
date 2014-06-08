/***************************************************************************
 *   This file is part of "std_utils" library.                             *
 *   Copyright (C) 2005 by V01D                                            *
 *                                                                         *
 *   "std_utils" is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   "std_utils" is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include "std_util.h"
#include "cconfig.h"
using namespace std_util;
using namespace std;

int main(void) {
  cout << "strip() test" << endl;
  string test_str = "   , . !  . bleh . ! .";
  string test_str2 = "bleh . ! .";
  string test_str3 = " . ! bleh";
  string test_str4 = " bleh";
  string test_str5 = "bleh";
  cout << "Test1: [" << strip(test_str, " ,.!") << "] should be [bleh]" << endl;
  cout << "Test2: [" << strip(test_str2, " ,.!") << "] should be [bleh]" << endl;
  cout << "Test3: [" << strip(test_str3, " ,.!") << "] should be [bleh]" << endl;
  cout << "Test4: [" << strip(test_str4, " ,.!") << "] should be [bleh]" << endl;
  cout << "Test5: [" << strip(test_str5, " ,.!") << "] should be [bleh]" << endl;
  cout << "Test6: [" << strip(string(), " ,.!") << "] should be []" << endl;
  cout << "Test7: [" << strip(string(), string()) << "] should be []" << endl;
  cout << "Test8: [" << strip(string("   ")) << "] should be []" << endl;
  cout << endl;

  cout << "gettok() test" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 1) << "] should be [bla]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 2) << "] should be [ble]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 3) << "] should be [bli]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 4) << "] should be [as]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 5) << "] should be [b]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 6) << "] should be [a]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 7) << "] should be [s]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 8) << "] should be []" << endl;
  cout << "[" << gettok(" ", 1) << "] should be []" << endl;
  cout << "[" << gettok(" ", 2) << "] should be []" << endl;
  cout << "[" << gettok("a", 1) << "] should be [a]" << endl;
  cout << "[" << gettok("a", 2) << "] should be []" << endl;
  cout << "[" << gettok("a  ", 1) << "] should be [a]" << endl;
  cout << "[" << gettok("a  ", 2) << "] should be []" << endl;
  cout << "[" << gettok("a  b", 1) << "] should be [a]" << endl;
  cout << "[" << gettok("a  b", 2) << "] should be [b]" << endl;
  cout << "[" << gettok("a  b", 3) << "] should be []" << endl;
  cout << "[" << gettok("  ", 1) << "] should be []" << endl;
  cout << "[" << gettok("  ", 2) << "] should be []" << endl;
  cout << "[" << gettok(string(), 8) << "] should be []" << endl;
  
  cout << "[" << gettok("    bla ble   bli as b a s   ", 1, true) << "]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 2, true) << "]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 3, true) << "]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 4, true) << "]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 5, true) << "]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 6, true) << "]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 7, true) << "]" << endl;
  cout << "[" << gettok("    bla ble   bli as b a s   ", 8, true) << "]" << endl;

  cout << "[" << gettok("test1 a v a", 2, true) << "]" << endl;
  cout << "[" << gettok("logger/logger.so chanbot/chanbot.so aiml/impaiml.so nickserv/nickserv.so lrms/lrms.so", 1) << "]" << endl;
  cout << "[" << gettok("logger/logger.so chanbot/chanbot.so aiml/impaiml.so nickserv/nickserv.so lrms/lrms.so", 2) << "]" << endl;
  cout << "[" << gettok("logger/logger.so chanbot/chanbot.so aiml/impaiml.so nickserv/nickserv.so lrms/lrms.so", 3) << "]" << endl;
  cout << "[" << gettok("logger/logger.so chanbot/chanbot.so aiml/impaiml.so nickserv/nickserv.so lrms/lrms.so", 4) << "]" << endl;
  cout << "[" << gettok("logger/logger.so chanbot/chanbot.so aiml/impaiml.so nickserv/nickserv.so lrms/lrms.so", 5) << "]" << endl;
  cout << "[" << gettok("logger/logger.so chanbot/chanbot.so aiml/impaiml.so nickserv/nickserv.so lrms/lrms.so", 6) << "]" << endl;
  return 0;
}
