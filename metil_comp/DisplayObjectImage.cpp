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

#include "DisplayObjectImage.h"

namespace Metil {

DisplayObjectImage::DisplayObjectImage( const DisplayableObject *dob, DisplayScene *dsc, BasicVec<int> size, const void *data, const Type *type ) : DisplayObject( dob, dsc ), _size( size ), _data( data ), _type( type ) {
}


DisplayObjectImage::~DisplayObjectImage() {
}

void DisplayObjectImage::update_borders( const BasicVec<Vec<double,3> > &axes, BasicVec<double> &mi, BasicVec<double> &ma ) {
    for(int i=0;i<axes.size();++i) {
        // -> dot( _size, axes[ i ] )
        double m = 0; for(int j=0;j<min(3,_size.size());++j) m += axes[ i ][ j ] * _size[ j ];
        mi[ i ] = min( mi[ i ], min( 0.0, m ) );
        ma[ i ] = max( ma[ i ], max( 0.0, m ) );
    }
}

}

