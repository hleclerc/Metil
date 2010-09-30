/*
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License version 2 as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESST FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#ifndef METIL_TENSOR_ORDER_H
#define METIL_TENSOR_ORDER_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE

/**
  @brief To get the static dimensionnality of objects

  Meaning of \c res
   - 0 -> scalar
   - 1 -> vector
   - 2 -> matrix
   - ...
   - -1 -> dynamic tensor order (not fixed during the compilation)
*/
template<class T> struct TensorOrder { static const int res = 0; };

END_METIL_NAMESPACE

#endif // METIL_TENSOR_ORDER_H
