/****************************************************************************
** Parser - class
**
**   Created : Tue Jun 15 12:09:08 2014
**        by : Varol Okan using LightTable
** Copyright : (c) Varol Okan
**   License : GPL v 2.0
**
** This class will parse the command line options and execute the propper
** actions.
**
****************************************************************************/
#ifndef _PARSER_H_
#define _PARSER_H_

#define UTIL_VERSION "0.1"

#include <vector>

class Parser
{
public:
           Parser ( );
  virtual ~Parser ( );

  bool parseCommandLine ( int, char ** );
  std::vector<std::string> &input    ( );
  std::string &output   ( );
  std::string &toType   ( );
  std::string &fromType ( );

protected:
  void printHelp   ( );
  bool getFileList ( std::string & );
  std::string getPathName ( std::string & );

private:
  std::vector<std::string> m_listInputFiles;
  std::string m_strOutputName;
  std::string m_strToType;
  std::string m_strFromType;
  int m_iLogLevel;
};

#endif
