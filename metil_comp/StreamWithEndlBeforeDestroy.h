/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef METIL_StreamWithEndlBeforeDestroy_H
#define METIL_StreamWithEndlBeforeDestroy_H

#include "Stream.h"

namespace Metil {

/**

*/
class StreamWithEndlBeforeDestroy {
public:
    StreamWithEndlBeforeDestroy( Stream &stream ) : stream( stream ), put_endl( true ) {}
    
    StreamWithEndlBeforeDestroy( const StreamWithEndlBeforeDestroy &swe ) : stream( swe.stream ), put_endl( true ) {
        swe.put_endl = false;
    }

    ~StreamWithEndlBeforeDestroy() { if ( put_endl ) stream << Stream::endl; }
    
    Stream &stream;
    mutable bool put_endl;
};

///
template<class T>
StreamWithEndlBeforeDestroy operator<<( StreamWithEndlBeforeDestroy os, const T &val ) {
    os.stream << val;
    return os;
}

/**

*/
class StreamWithEndlBeforeDestroyMaker {
public:
    StreamWithEndlBeforeDestroyMaker( Stream &stream ) : stream( stream ) {}
    
    Stream &stream;
};

///
template<class T>
StreamWithEndlBeforeDestroy operator<<( StreamWithEndlBeforeDestroyMaker os, const T &val ) {
    os.stream << val;
    return os.stream;
}

}


#endif // METIL_StreamWithEndlBeforeDestroy_H
