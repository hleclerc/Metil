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

#ifndef IMGITEMGRID_H
#define IMGITEMGRID_H

#include "ImgItem.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file ImgItemGrid.cpp
#endif

namespace Metil {
    
/**
  stored in a contiguous vector (aligned in memory, using a memalign and a internal_width() which can be > size(0))
  */
class ImgItemGrid : public ImgItem {
public:
    ImgItemGrid( const Type *type );
    virtual ~ImgItemGrid();

    // LazyObject
    virtual bool done() const;

    // ImgItem
    virtual const Type *type() const;
    virtual void write_in_grid( const ImgItemGrid *grid ) const;

    virtual int internal_width() const;

    // ImgItemGrid
    void allocate() const; // size must be updated before
    void *data() const;

    template<class T>
    void write_line( void *&data, const T *line ) const { // allocate must be done before
        type()->write( data, line, _line_size );
        data = reinterpret_cast<char *>( data ) + _line_size_in_bytes;
    }

    void write_line( void *&data, const Type *line_type, const void *line ) const;

protected:
    const Type *_type;
    mutable void *_data;
    mutable int _line_size, _internal_line_size, _line_size_in_bytes;
};

} //  namespace Metil

#endif // IMGITEMGRID_H
