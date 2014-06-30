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
//#include <vector>

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
//#include <glob.h>

#include "parser.h"

extern char *optarg;
extern int optind, opterr, optopt;

using namespace std;

static string getExtension ( string &str )  {
  string::size_type idx = str.rfind( '.' );
  if ( idx != std::string::npos )  {
    std::string extension = str.substr ( idx + 1 );
    return extension;
  }
  return string ( "aiml" );
}

Parser::Parser ( )
{
  m_iLogLevel   = 3;
  m_strToType   = string ( "caiml" );
  m_strFromType = string ( "aiml" );
}

Parser::~Parser ( )
{
}

bool Parser::parseCommandLine ( int iArgs, char *pArguments[] )
{
  int iChar = 0;
  // Note UNIX file clobering ( I.e. a*.aiml ) is done prioer to entering main

  static struct  option longOpts[] =  {
    { "verbose", no_argument,       0, 'v' },
    { "help",    no_argument,       0, 'h' },
    { "in",      required_argument, 0, 'i' },
    { "type",    required_argument, 0, 't' },
    { "out",     required_argument, 0, 'o' },
    { 0, 0, 0, 0 } };

  bool bSpecType = false;
  int index = 0;
  std::string strInput;
  while ( true )  {
    iChar = getopt_long ( iArgs, pArguments, "vhi:o:", longOpts, &index );
    if ( iChar == -1 )
      break;

    switch ( iChar ) {
      case 'i':
        strInput = string ( optarg );
      break;
      case 't':
        bSpecType = true;
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

  m_listInputFiles.push_back ( strInput );
  while ( optind < iArgs && *pArguments[optind] != '-' )  {
    m_listInputFiles.push_back ( pArguments[optind] );
    ++optind;
  }

  if ( strInput.empty ( ) || m_strOutputName.empty ( ) )  {
    cout << "Missing input or output file." << endl << endl;
    printHelp ( );
  }
  else {
    m_strFromType = getExtension ( strInput ); 
    if ( ! bSpecType )  {
      // The user did not specify the output type, so we should deduct this from teh file extension
      m_strToType = getExtension ( m_strOutputName );
    }
    if ( ( m_strToType != "aiml" ) && ( m_strToType != "caiml" ) && ( m_strToType != "aisl" ) )  {
      cout << "Wrong output type defined " << m_strToType << endl << endl;
      printHelp ( );
    }
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

std::vector<std::string> &Parser::input  ( )
{
  return m_listInputFiles;
}

std::string &Parser::output ( )
{
  return m_strOutputName;
}

std::string &Parser::toType   ( )
{
  return m_strToType;
}

std::string &Parser::fromType ( )
{
  return m_strFromType;
}
