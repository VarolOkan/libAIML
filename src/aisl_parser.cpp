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

#include <iostream>
#include "core.h"

#include "aisl_parser.h"

using namespace std;
using namespace aiml;

AISLparser::AISLparser ( cGraphMaster &_graphmaster, AIMLError &_errnum )
  : graphmaster ( _graphmaster ), errnum ( _errnum )
{
}

void AISLparser::set_error(AIMLError _errnum )
{
  errnum = _errnum;
}

/**
 * Loading
 */ 
bool AISLparser::load ( const std::string &filename )
{
  ifstream file  ( filename.c_str ( ) );
  if ( ! file )  {
    set_error ( AIMLERR_CAIML_NOOPEN_READ );
    return false;
  }
/*
  // header
  char magic[6];
  if (!file.read(magic, 5)) { set_error(AIMLERR_CAIML_NOMAGIC); return false; }
  magic[5] = '\0';
  if (string("CAIML") != magic) { set_error(AIMLERR_CAIML_NOTCAIML); return false; }
  size_t version;
  if (!readNumber(file, version)) { set_error(AIMLERR_CAIML_NOVERSION); return false; }

  if (version != CAIML_VERSION_NUMBER) { set_error(AIMLERR_CAIML_WRONGVERSION); return false; }

  // data
  size_t gmsize;
  if (!readNumber(file, gmsize)) { set_error(AIMLERR_CAIML_NOSIZE); return false; }
  graphmaster.getSize() = gmsize;
  
  if (!readChilds(file, graphmaster.getRoot(), graphmaster.getRoot(), NODE_PATT)) { return false; }
*/
  return true;
}

bool AISLparser::readChilds(ifstream& file, NodeVec& same_childs, NodeVec& diff_childs, NodeType type) {
  size_t same_size, diff_size;
  if (!readNumber(file, same_size) || !readNumber(file, diff_size)) { set_error(AIMLERR_CAIML_NOCHILDSNUM); return false; }

  Node n;
  n.type = type;

  if (same_size != 0) {
    same_childs.resize(same_size, n); 
    
    for (NodeVec::iterator it = same_childs.begin(); it != same_childs.end(); ++it) {
      if (!readString(file, it->key)) { set_error(AIMLERR_CAIML_NOKEY); return false; }
      
      bool is_leaf;
      if (!checkForLeaf(file, is_leaf)) { set_error(AIMLERR_CAIML_NOCHILDSNUM); return false; }

      if (is_leaf) { if (!it->templ.readFromFile(file)) { set_error(AIMLERR_CAIML_NOTEMPLATE); return false; } }
      else { if (!readChilds(file, it->same_childs, it->diff_childs, type)) { return false; } }
    }
  }

  if (diff_size != 0) {
    diff_childs.resize(diff_size, n);
  
    for (NodeVec::iterator it = diff_childs.begin(); it != diff_childs.end(); ++it) {
      if (!readString(file, it->key)) { set_error(AIMLERR_CAIML_NOKEY); return false; }

      bool is_leaf;
      if (!checkForLeaf(file, is_leaf)) { set_error(AIMLERR_CAIML_NOCHILDSNUM); return false; }

      if (is_leaf) { if (!it->templ.readFromFile(file)) { set_error(AIMLERR_CAIML_NOTEMPLATE); return false; } }
      else {
        if (type == NODE_TOPIC) { set_error(AIMLERR_CAIML_INCORRECTSTRUCT); return false; }
        if (!readChilds(file, it->same_childs, it->diff_childs, nextNodeType(type))) { return false; }
      }
    }
  }
  return true;
}

bool AISLparser::checkForLeaf(ifstream& file, bool& is_leaf) {
  size_t same_size, diff_size;
  streampos pos = file.tellg();
  if (!readNumber(file, same_size) || !readNumber(file, diff_size)) { return false; }

  // say if it is a leaf and only reset the position if it isn't
  is_leaf = ((same_size == 0) && (diff_size == 0));
  if (!is_leaf) { file.seekg(pos); }
  return true;
}

/**
 * Saving
 */
bool AISLparser::save ( const std::string &filename )
{
  if ( graphmaster.getRoot ( ).empty ( ) )  {
    set_error ( AIMLERR_CAIML_EMPTYGM );
    return false;
  }

  // set error now just in case, unset it if no error found
  set_error ( AIMLERR_CAIML_NOOPEN_WRITE );
  
  ofstream file ( filename.c_str ( ), ios_base::binary );
  if ( ! file )
    return false;

  // header
  if ( ! ( file << ".aisl." << AISL_VERSION_NUMBER << endl << endl ) )
    return false;

//  size_t version = AISL_VERSION_NUMBER;
//  if (!writeNumber(file, version) || !writeNumber(file, graphmaster.getSize())) { return false; }

  // data
  if ( ! writeChilds ( file, graphmaster.getRoot ( ), NodeVec ( ) ) )
    return false;

  file << endl << endl;

  set_error ( AIMLERR_NO_ERR );
  return true;
}

bool AISLparser::writeChilds ( ofstream &file, const NodeVec &same_childs, const NodeVec &diff_childs )
{
//  if ( ! writeNumber ( file, same_childs.size ( ) ) || ! writeNumber ( file, diff_childs.size ( ) ) )
//    return false; 

  NodeVec children = same_childs;
  NodeVec::const_iterator it = children.begin ( );

// < const aiml::Node*, std::vector<aiml::Node> >
/*class Node;
  typedef std::vector<Node> NodeVec;
  typedef std::list<AIMLentry> EntryList;

  class Node {
    public:
      std::string key;
      cWriteBuffer templ;
      NodeVec same_childs, diff_childs;
      NodeType type;

      bool operator< (const Node& other) const;
  }; */


  for ( int t=0; t<2; t++ )  {
    while ( it != children.end ( ) )  {
      const Node *pVec = &(*it++);
      if ( ! writeString ( file, pVec->key ) )
        return false;
      file << "  ";

      if ( ! it->templ.empty ( ) ) {
        if ( ! it->templ.writeToFile ( file ) )
          return false; 
      }
      file << endl;
    }
    children = diff_childs;
    it = children.begin ( );
  }
  return true;
}

/*
bool AISLparser::writeChilds ( ofstream &file, const NodeVec &same_childs, const NodeVec &diff_childs )
{
  if ( ! writeNumber ( file, same_childs.size ( ) ) || ! writeNumber ( file, diff_childs.size ( ) ) )
    return false;
      
  for ( NodeVec::const_iterator it = same_childs.begin ( ); it != same_childs.end ( ); ++it )  {
    if ( ! writeString ( file, it->key ) )
      return false;
    
    if ( ! it->templ.empty ( ) ) {
      if ( ! writeNumber ( file, 0 ) || ! writeNumber ( file, 0 ) || ! it->templ.writeToFile ( file ) )
        return false;
    }
    else { 
      if ( ! writeChilds ( file, it->same_childs, it->diff_childs ) )
        return false;
    }
  }
  
  for ( NodeVec::const_iterator it = diff_childs.begin ( ); it != diff_childs.end ( ); ++it )  {
    if ( ! writeString ( file, it->key ) )
      return false;
    
    if ( ! it->templ.empty ( ) ) {
      if ( ! writeNumber ( file, 0 ) || ! writeNumber ( file, 0 ) || ! it->templ.writeToFile ( file ) )
        return false;
    }
    else {
      if ( ! writeChilds ( file, it->same_childs, it->diff_childs ) )
        return false;
    }
  }
  return true;
}
*/
