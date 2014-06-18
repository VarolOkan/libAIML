/*****************************************************************************
 ** Class Parser
 **
 **
 **   Created : Tue Jun 15 12:09:08 2014
 **        by : Varol Okan using LightTabe
 ** Copyright : (c) Varol Okan
 ** License   : GPL v 2.0
 **
 **
 *****************************************************************************/

#include <iostream>
#include <string>

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "parser.h"

extern char *optarg;
extern int optind, opterr, optopt;

using namespace std;

Parser::Parser ( )
{
  m_iLogLevel = 3;
  m_strToType = string ( "caiml" );
}

Parser::~Parser ( )
{
}

bool Parser::parseCommandLine ( int iArgs, char *pArguments[] )
{
  int iChar = 0;

  static struct  option longOpts[] =  {
    { "verbose", no_argument,       0, 'v' },
    { "help",    no_argument,       0, 'h' },
    { "in",      required_argument, 0, 'i' },
    { "type",    required_argument, 0, 't' },
    { "out",     required_argument, 0, 'o' },
    { 0, 0, 0, 0 } };

  while ( true ) {
    iChar = getopt_long_only ( iArgs, pArguments, "vhi:o:", longOpts, NULL );
    if ( iChar == -1 )
      break;

    switch ( iChar ) {
      case 'i':
        m_strInputName = string ( optarg );
      break;
      case 't':
        m_strToType = string ( optarg );
      break;
      case 'o':
        m_strOutputName = string ( optarg );
      break;
      case 'v':
        m_iLogLevel = atoi ( optarg );
      break;
      case 'h':
      default:
        printHelp ( );
        return true;
      break;
    }
  }

  if ( m_strInputName.empty ( ) || m_strOutputName.empty ( ) )  {
    cout << "Missing input or output file." << endl << endl;
    printHelp ( );
  }
  else if ( ( m_strToType != "aiml" ) && ( m_strToType != "caiml" ) && ( m_strToType != "aisl" ) )  {
    cout << "Wrong output type defined " << m_strToType << endl << endl;
    printHelp ( );
  }

  return true;
}


void Parser::printHelp ( )
{
  cout << "aiml_util version " << UTIL_VERSION << ", built date " << __DATE__ << endl;
  cout << "Part of libAIML: https://github.com/VarolOkan/libAIML" << endl << endl;

  cout << "aiml_util [-hv] -i FILE -t TYPE -o FILE" << endl;
  cout << " -h  --help        print this help and exit." << endl;
  cout << " -v  --verbose lvl logging level [0..5] where 0=no output." << endl << endl;

  cout << " -i  --in   FILE set log file name." << endl;
  cout << " -t  --type TYPE, where type can be aiml, caiml, or aisl" << endl;
  cout << " -o  --out  FILE set output file." << endl << endl;
}

std::string &Parser::input  ( )
{
  return m_strInputName;
}

std::string &Parser::output ( )
{
  return m_strOutputName;
}

std::string &Parser::type   ( )
{
  return m_strToType;
}
