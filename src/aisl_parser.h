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
 *   along with "libAISL"; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __LIBAISL_PARSER_H__
#define __LIBAISL_PARSER_H__

#define AISL_VERSION_NUMBER  "1.0.0"

#include <string>
//#include <fstream>

namespace aiml {

class AISLparser {
  public:
    AISLparser ( cGraphMaster &, aiml::AIMLError & );

    bool load ( const std::string & );
    bool save ( const std::string & );

  private:
    cGraphMaster    &graphmaster;
    aiml::AIMLError &errnum;

    bool readChilds   ( std::ifstream &file, NodeVec &sameChilds, NodeVec &diffChilds, NodeType type );
    bool checkForLeaf ( std::ifstream &file, bool &isLeaf );
    bool writeChilds  ( std::ofstream &file, const NodeVec &same_childs, const NodeVec &diff_childs );
    void set_error    ( aiml::AIMLError );
};

}

#endif
