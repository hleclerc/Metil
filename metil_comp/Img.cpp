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

#include "Img.h"
#include "File.h"
#include "ImgItemFunction.h"
// #include "ImgItemTif.h"

namespace Metil {

Img::Img() : _data( 0 ) {
}

//Img::Img( const CString &filename ) {
//    if ( filename.ends_with( ".tif" ) or filename.ends_with( ".tiff" ) or filename.ends_with( ".TIF" ) or filename.ends_with( ".TIFF" ) ) {
//        _data = new ImgItemTif( filename );
//    } else
//        ASSERT( 0, "unknown extension of " + filename );
//}

Img::Img( Float64Function *f, int w, int h ) { _data = new ImgItemFunction<Float64   ,2>( f, BasicVec<int,2>( w, h ) ); }

Img::~Img() {
    if ( _data )
        dec_ref( _data );
}

Val nb_dim() const {
    return _data->nb_dim();
}


//void Img::save( const CString &filename ) const {
//    if ( _data )
//        LazyObject::add_todo( _data->save( filename ) );
//}

}

