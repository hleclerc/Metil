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

#ifndef METILMUTEX_H
#define METILMUTEX_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Mutex.cpp
#endif

#include <pthread.h>

namespace Metil {

/**
    @author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>
*/
class Mutex {
public:
    Mutex();
    ~Mutex();
    
    void acquire();
    void release();
private:
    pthread_mutex_t id;
};

}

#endif
