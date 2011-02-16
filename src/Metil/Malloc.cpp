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

#include "Malloc.h"
#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/mman.h>
    #include <pthread.h>
#endif

#ifdef __DEBUG_ALLOC__
    #include <cstdlib> // atexit
    #include <cstdio>
#endif
#ifdef DEBUG_ALLOC_LEVEL_1
    #include <map>
#endif

BEG_METIL_LEVEL1_NAMESPACE

void *_malloc( ST &size ) {
    if ( size <= 8192 ) {
        if ( size <= 96 ) {
            if ( size <= 24 ) {
                if ( size <= 8 ) {
                    if ( size <= 4 ) {
                        return SmallSizeAllocator<4>::malloc( size );
                    } else {
                        return SmallSizeAllocator<8>::malloc( size );
                    }
                } else {
                    if ( size <= 16 ) {
                        return SmallSizeAllocator<16>::malloc( size );
                    } else {
                        if ( size <= 20 ) {
                            return SmallSizeAllocator<20>::malloc( size );
                        } else {
                            return SmallSizeAllocator<24>::malloc( size );
                        }
                    }
                }
            } else {
                if ( size <= 48 ) {
                    if ( size <= 28 ) {
                        return SmallSizeAllocator<28>::malloc( size );
                    } else {
                        if ( size <= 32 ) {
                            return SmallSizeAllocator<32>::malloc( size );
                        } else {
                            return SmallSizeAllocator<48>::malloc( size );
                        }
                    }
                } else {
                    if ( size <= 64 ) {
                        return SmallSizeAllocator<64>::malloc( size );
                    } else {
                        if ( size <= 80 ) {
                            return SmallSizeAllocator<80>::malloc( size );
                        } else {
                            return SmallSizeAllocator<96>::malloc( size );
                        }
                    }
                }
            }
        } else {
            if ( size <= 256 ) {
                if ( size <= 160 ) {
                    if ( size <= 112 ) {
                        return SmallSizeAllocator<112>::malloc( size );
                    } else {
                        if ( size <= 128 ) {
                            return SmallSizeAllocator<128>::malloc( size );
                        } else {
                            return SmallSizeAllocator<160>::malloc( size );
                        }
                    }
                } else {
                    if ( size <= 192 ) {
                        return SmallSizeAllocator<192>::malloc( size );
                    } else {
                        if ( size <= 224 ) {
                            return SmallSizeAllocator<224>::malloc( size );
                        } else {
                            return SmallSizeAllocator<256>::malloc( size );
                        }
                    }
                }
            } else {
                if ( size <= 2048 ) {
                    if ( size <= 512 ) {
                        return SmallSizeAllocator<512>::malloc( size );
                    } else {
                        if ( size <= 1024 ) {
                            return SmallSizeAllocator<1024>::malloc( size );
                        } else {
                            return SmallSizeAllocator<2048>::malloc( size );
                        }
                    }
                } else {
                    if ( size <= 4096 ) {
                        return SmallSizeAllocator<4096>::malloc( size );
                    } else {
                        if ( size <= 6144 ) {
                            return SmallSizeAllocator<6144>::malloc( size );
                        } else {
                            return SmallSizeAllocator<8192>::malloc( size );
                        }
                    }
                }
            }
        }
    }
    return new_room_large_size( size );
}
void _free( const void *address, ST size ) {
    if ( size <= 8192 ) {
        if ( size <= 96 ) {
            if ( size <= 24 ) {
                if ( size <= 8 ) {
                    if ( size <= 4 ) {
                        SmallSizeAllocator<4>::free( address );
                    } else {
                        SmallSizeAllocator<8>::free( address );
                    }
                } else {
                    if ( size <= 16 ) {
                        SmallSizeAllocator<16>::free( address );
                    } else {
                        if ( size <= 20 ) {
                            SmallSizeAllocator<20>::free( address );
                        } else {
                            SmallSizeAllocator<24>::free( address );
                        }
                    }
                }
            } else {
                if ( size <= 48 ) {
                    if ( size <= 28 ) {
                        SmallSizeAllocator<28>::free( address );
                    } else {
                        if ( size <= 32 ) {
                            SmallSizeAllocator<32>::free( address );
                        } else {
                            SmallSizeAllocator<48>::free( address );
                        }
                    }
                } else {
                    if ( size <= 64 ) {
                        SmallSizeAllocator<64>::free( address );
                    } else {
                        if ( size <= 80 ) {
                            SmallSizeAllocator<80>::free( address );
                        } else {
                            SmallSizeAllocator<96>::free( address );
                        }
                    }
                }
            }
        } else {
            if ( size <= 256 ) {
                if ( size <= 160 ) {
                    if ( size <= 112 ) {
                        SmallSizeAllocator<112>::free( address );
                    } else {
                        if ( size <= 128 ) {
                            SmallSizeAllocator<128>::free( address );
                        } else {
                            SmallSizeAllocator<160>::free( address );
                        }
                    }
                } else {
                    if ( size <= 192 ) {
                        SmallSizeAllocator<192>::free( address );
                    } else {
                        if ( size <= 224 ) {
                            SmallSizeAllocator<224>::free( address );
                        } else {
                            SmallSizeAllocator<256>::free( address );
                        }
                    }
                }
            } else {
                if ( size <= 2048 ) {
                    if ( size <= 512 ) {
                        SmallSizeAllocator<512>::free( address );
                    } else {
                        if ( size <= 1024 ) {
                            SmallSizeAllocator<1024>::free( address );
                        } else {
                            SmallSizeAllocator<2048>::free( address );
                        }
                    }
                } else {
                    if ( size <= 4096 ) {
                        SmallSizeAllocator<4096>::free( address );
                    } else {
                        if ( size <= 6144 ) {
                            SmallSizeAllocator<6144>::free( address );
                        } else {
                            SmallSizeAllocator<8192>::free( address );
                        }
                    }
                }
            }
        }
    } else
        del_room_large_size( address, size );
}




// multi thread
void *_malloc_mt( ST &size ) {
    if ( size <= 8192 ) {
        if ( size <= 96 ) {
            if ( size <= 24 ) {
                if ( size <= 8 ) {
                    if ( size <= 4 ) {
                        return SmallSizeAllocator<4>::malloc_mt( size );
                    } else {
                        return SmallSizeAllocator<8>::malloc_mt( size );
                    }
                } else {
                    if ( size <= 16 ) {
                        return SmallSizeAllocator<16>::malloc_mt( size );
                    } else {
                        if ( size <= 20 ) {
                            return SmallSizeAllocator<20>::malloc_mt( size );
                        } else {
                            return SmallSizeAllocator<24>::malloc_mt( size );
                        }
                    }
                }
            } else {
                if ( size <= 48 ) {
                    if ( size <= 28 ) {
                        return SmallSizeAllocator<28>::malloc_mt( size );
                    } else {
                        if ( size <= 32 ) {
                            return SmallSizeAllocator<32>::malloc_mt( size );
                        } else {
                            return SmallSizeAllocator<48>::malloc_mt( size );
                        }
                    }
                } else {
                    if ( size <= 64 ) {
                        return SmallSizeAllocator<64>::malloc_mt( size );
                    } else {
                        if ( size <= 80 ) {
                            return SmallSizeAllocator<80>::malloc_mt( size );
                        } else {
                            return SmallSizeAllocator<96>::malloc_mt( size );
                        }
                    }
                }
            }
        } else {
            if ( size <= 256 ) {
                if ( size <= 160 ) {
                    if ( size <= 112 ) {
                        return SmallSizeAllocator<112>::malloc_mt( size );
                    } else {
                        if ( size <= 128 ) {
                            return SmallSizeAllocator<128>::malloc_mt( size );
                        } else {
                            return SmallSizeAllocator<160>::malloc_mt( size );
                        }
                    }
                } else {
                    if ( size <= 192 ) {
                        return SmallSizeAllocator<192>::malloc_mt( size );
                    } else {
                        if ( size <= 224 ) {
                            return SmallSizeAllocator<224>::malloc_mt( size );
                        } else {
                            return SmallSizeAllocator<256>::malloc_mt( size );
                        }
                    }
                }
            } else {
                if ( size <= 2048 ) {
                    if ( size <= 512 ) {
                        return SmallSizeAllocator<512>::malloc_mt( size );
                    } else {
                        if ( size <= 1024 ) {
                            return SmallSizeAllocator<1024>::malloc_mt( size );
                        } else {
                            return SmallSizeAllocator<2048>::malloc_mt( size );
                        }
                    }
                } else {
                    if ( size <= 4096 ) {
                        return SmallSizeAllocator<4096>::malloc_mt( size );
                    } else {
                        if ( size <= 6144 ) {
                            return SmallSizeAllocator<6144>::malloc_mt( size );
                        } else {
                            return SmallSizeAllocator<8192>::malloc_mt( size );
                        }
                    }
                }
            }
        }
    }
    return new_room_large_size( size );
}
void _free_mt( const void *address, ST size ) {
    if ( size <= 8192 ) {
        if ( size <= 96 ) {
            if ( size <= 24 ) {
                if ( size <= 8 ) {
                    if ( size <= 4 ) {
                        SmallSizeAllocator<4>::free_mt( address );
                    } else {
                        SmallSizeAllocator<8>::free_mt( address );
                    }
                } else {
                    if ( size <= 16 ) {
                        SmallSizeAllocator<16>::free_mt( address );
                    } else {
                        if ( size <= 20 ) {
                            SmallSizeAllocator<20>::free_mt( address );
                        } else {
                            SmallSizeAllocator<24>::free_mt( address );
                        }
                    }
                }
            } else {
                if ( size <= 48 ) {
                    if ( size <= 28 ) {
                        SmallSizeAllocator<28>::free_mt( address );
                    } else {
                        if ( size <= 32 ) {
                            SmallSizeAllocator<32>::free_mt( address );
                        } else {
                            SmallSizeAllocator<48>::free_mt( address );
                        }
                    }
                } else {
                    if ( size <= 64 ) {
                        SmallSizeAllocator<64>::free_mt( address );
                    } else {
                        if ( size <= 80 ) {
                            SmallSizeAllocator<80>::free_mt( address );
                        } else {
                            SmallSizeAllocator<96>::free_mt( address );
                        }
                    }
                }
            }
        } else {
            if ( size <= 256 ) {
                if ( size <= 160 ) {
                    if ( size <= 112 ) {
                        SmallSizeAllocator<112>::free_mt( address );
                    } else {
                        if ( size <= 128 ) {
                            SmallSizeAllocator<128>::free_mt( address );
                        } else {
                            SmallSizeAllocator<160>::free_mt( address );
                        }
                    }
                } else {
                    if ( size <= 192 ) {
                        SmallSizeAllocator<192>::free_mt( address );
                    } else {
                        if ( size <= 224 ) {
                            SmallSizeAllocator<224>::free_mt( address );
                        } else {
                            SmallSizeAllocator<256>::free_mt( address );
                        }
                    }
                }
            } else {
                if ( size <= 2048 ) {
                    if ( size <= 512 ) {
                        SmallSizeAllocator<512>::free_mt( address );
                    } else {
                        if ( size <= 1024 ) {
                            SmallSizeAllocator<1024>::free_mt( address );
                        } else {
                            SmallSizeAllocator<2048>::free_mt( address );
                        }
                    }
                } else {
                    if ( size <= 4096 ) {
                        SmallSizeAllocator<4096>::free_mt( address );
                    } else {
                        if ( size <= 6144 ) {
                            SmallSizeAllocator<6144>::free_mt( address );
                        } else {
                            SmallSizeAllocator<8192>::free_mt( address );
                        }
                    }
                }
            }
        }
    } else
        del_room_large_size( address, size );
}



void update_size_in_mem_large_size( ST &size_in_mem ) {
    size_in_mem = ( size_in_mem + MaxSmallAllocatorSize - 1 ) & ~( MaxSmallAllocatorSize - 1 );
}

void *new_room_large_size( ST &size_in_mem ) {
    update_size_in_mem_large_size( size_in_mem );
    #ifdef WIN32
    return std::malloc( size_in_mem );
    #else
    return mmap( 0, size_in_mem, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0 ); ///< MAP_ANONYMOUS |
    #endif
}

void del_room_large_size( const void *data, ST size_in_mem ) {
    #ifdef WIN32
    std::free( const_cast<void *>( data ) );
    #else
    munmap( const_cast<void *>( data ), size_in_mem );
    #endif
}

void del_room_large_size_with_probably_wrong_reservation_size( const void *data, ST size_in_mem ) {
    update_size_in_mem_large_size( size_in_mem );
    del_room_large_size( data, size_in_mem );
}



#ifdef DEBUG_ALLOC_LEVEL_0
    void _check_total_allocated_memory() {
        if ( total_allocated_memory() )
            fprintf( stderr, "WARNING: MEMORY LEAK OF SIZE %li (to get more details, use -DDEBUG_ALLOC_LEVEL_1)\n", total_allocated_memory() );
    }

    struct TotalAllocatedMemory {
        TotalAllocatedMemory() : n( 0 ) {
            atexit( _check_total_allocated_memory );
        }
        ST n;
    };

    ST &total_allocated_memory() {
        static TotalAllocatedMemory res;
        return res.n;
    }
#endif // DEBUG_ALLOC_LEVEL_0

#ifdef DEBUG_ALLOC_LEVEL_1
    void _check_allocated_objects();

    struct AllocObjInfo {
        ST nb_objects;
        const char *name;
        int line;
        const char *file;
    };

    std::map<const void *,AllocObjInfo> &get_alloc_obj_info() {
        static std::map<const void *,AllocObjInfo> *res = 0;
        if ( not res ) {
            res = new std::map<const void *,AllocObjInfo>;
            atexit( _check_allocated_objects );
        }
        return *res;
    }
    pthread_mutex_t mutex_DEBUG_ALLOC_LEVEL_1 = PTHREAD_MUTEX_INITIALIZER;

    void *_add_alloc_obj_ref( ST nb_objects, void *obj, const char *name, int line, const char *file ) {
        AllocObjInfo &res = get_alloc_obj_info()[ obj ];
        res.nb_objects = nb_objects;
        res.name = name;
        res.line = line;
        res.file = file;
        return obj;
    }

    bool _rem_alloc_obj_ref( ST nb_objects, const void *obj, const char *name, int line, const char *file ) {
        if ( not obj )
            return false;
        std::map<const void *,AllocObjInfo>::iterator res = get_alloc_obj_info().find( obj );
        if ( res == get_alloc_obj_info().end() ) {
            fprintf( stderr, "%s:%i: ALLOCATION PROBLEM: freeing a non existing object (of type %s, address %p)\n", file, line, name, obj );
            return false;
        }
        if ( res->second.nb_objects != nb_objects )
            fprintf( stderr, "%s:%i: ALLOCATION PROBLEM: freeing the wrong number of objects (of type %s) (%zi -> %zi)\n", file, line, name, res->second.nb_objects, nb_objects );
        get_alloc_obj_info().erase( res );
        return true;
    }

    void *_add_alloc_obj_ref_mt( ST nb_objects, void *obj, const char *name, int line, const char *file ) {
        pthread_mutex_lock( &mutex_DEBUG_ALLOC_LEVEL_1 );
        AllocObjInfo &res = get_alloc_obj_info()[ obj ];
        res.nb_objects = nb_objects;
        res.name = name;
        res.line = line;
        res.file = file;
        pthread_mutex_unlock( &mutex_DEBUG_ALLOC_LEVEL_1 );
        return obj;
    }

    bool _rem_alloc_obj_ref_mt( ST nb_objects, const void *obj, const char *name, int line, const char *file ) {
        if ( not obj )
            return false;
        pthread_mutex_lock( &mutex_DEBUG_ALLOC_LEVEL_1 );
        std::map<const void *,AllocObjInfo>::iterator res = get_alloc_obj_info().find( obj );
        pthread_mutex_unlock( &mutex_DEBUG_ALLOC_LEVEL_1 );
        if ( res == get_alloc_obj_info().end() ) {
            fprintf( stderr, "%s:%i: ALLOCATION PROBLEM: freeing a non existing object (of type %s, address %p)\n", file, line, name, obj );
            return false;
        }
        if ( res->second.nb_objects != nb_objects )
            fprintf( stderr, "%s:%i: ALLOCATION PROBLEM: freeing the wrong number of objects (of type %s) (%zi -> %zi)\n", file, line, name, res->second.nb_objects, nb_objects );
        pthread_mutex_lock( &mutex_DEBUG_ALLOC_LEVEL_1 );
        get_alloc_obj_info().erase( res );
        pthread_mutex_unlock( &mutex_DEBUG_ALLOC_LEVEL_1 );
        return true;
    }

    void _check_allocated_objects() {
        std::map<const void *,AllocObjInfo> &res = get_alloc_obj_info();
        for(std::map<const void *,AllocObjInfo>::const_iterator iter=res.begin(); iter != res.end(); ++iter )
            if ( iter->second.nb_objects > 1 )
                fprintf( stderr, "%s:%i: MEMORY LEAK: %zi objects (of type %s) created here are not freed\n", iter->second.file, iter->second.line, iter->second.nb_objects, iter->second.name );
            else
                fprintf( stderr, "%s:%i: MEMORY LEAK: 1 object (of type %s) created here is not freed\n", iter->second.file, iter->second.line, iter->second.name );
        delete &get_alloc_obj_info();
    }
#endif // DEBUG_ALLOC_LEVEL_1

//static ObjectDeleter *last_obj_to_be_deleted_at_the_end = 0;
//
//ObjectDeleter::~ObjectDeleter() {
//}
//
//void _del_obj_to_be_deleted_at_the_end() {
//    for( const ObjectDeleter *obj = last_obj_to_be_deleted_at_the_end; obj; ) {
//        const ObjectDeleter *prev = obj->prev;
//        DEL( obj );
//        obj = prev;
//    }
//}
//
//void _reg_obj_to_be_deleted_at_the_end( ObjectDeleter *obj ) {
//    if ( not obj )
//        return;
//    if ( not last_obj_to_be_deleted_at_the_end )
//        atexit( _del_obj_to_be_deleted_at_the_end );
//    obj->prev = last_obj_to_be_deleted_at_the_end;
//    last_obj_to_be_deleted_at_the_end = obj;
//}

END_METIL_LEVEL1_NAMESPACE
