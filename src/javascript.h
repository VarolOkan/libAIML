/***************************************************************************
 *   This file is part of "libaiml"                                        *
 *   Copyright (C) 2014 by Varol Okan                                      *
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

#ifndef __LIBAIML_SUBENGINE_JAVASCRIPT_H__
#define __LIBAIML_SUBENGINE_JAVASCRIPT_H__

#include <string>
#include <config.h>

#ifdef ENABLE_JAVASCRIPT
#define XP_UNIX
#include <v8.h>
#undef XP_UNIX
#endif

namespace aiml
{
  class StarsHolder;
  class cUser;

  class cJavaScript
  {
    public:
       cJavaScript ( );
      ~cJavaScript ( );

    bool  init ( );
    bool  eval ( const std::string &, std::string & );
    void  set_variables ( const StarsHolder &, cUser & );
    const std::string& getRuntimeError ( );

    private:
      #ifdef ENABLE_JAVASCRIPT
      v8::Isolate *isolate;
      v8::Handle<v8::ObjectTemplate> global;
      v8::Handle<v8::Context> context;
      #endif

      std::string m_strError;
      std::string m_strEval;
      std::string m_strAiml; // AIML vars in JS
  };

}

#endif // __LIBAIML_SUBENGINE_JAVASCRIPT_H__
