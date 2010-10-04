/**
*/
#include "Dout.h"
#include "Math.h"
#include "BasicVec.h"
#include "CudaMetil.h"
#include "TypeInformation.h"

#include <fstream>

BEG_METIL_NAMESPACE;

#define APPLY_BS( res, n ) res.apply( #n, n )

template<class TS>
struct CompactStructAppl {
    template<class T>
    void apply( const char *name, const T & ) {
        *os << "        APPLY_BS( res, " << name << " );\n";
    }
    TS *os;
};

template<class TS>
struct CompactStructDecl {
    template<class T>
    void apply( const char *name, const BasicVec<T> & ) {
        *os << "    Vec<" << TypeInformation<T>::type() << "> " << name << ";\n";
    }
    template<class T>
    void apply( const char *name, const BasicVec<BasicVec<T> > & ) {
        *os << "    Vec<Vec<" << TypeInformation<T>::type() << "> > " << name << ";\n";
    }
    TS *os;
};

template<class TS>
struct CompactStructUpda {
    template<class T>
    void apply( const char *name, const BasicVec<T> & ) {
        *os << "    reinterpret_cast<Metil::ST &>( res->" << name << ".data_ ) += off;\n";
    }
    template<class T>
    void apply( const char *name, const BasicVec<BasicVec<T> > & ) {
        *os << "    reinterpret_cast<Metil::ST &>( res->" << name << ".data_ ) += off;\n";
        *os << "    for( int i = 0; i < res->" << name << ".size(); ++i )\n";
        *os << "        reinterpret_cast<Metil::ST &>( res->" << name << "[ i ].data_ ) += off;\n";
    }
    TS *os;
};

template<class T>
void compact_struct_decl( const T &str, std::string name, std::string dir = "." ) {
    std::ofstream fh( ( dir + '/' + name + ".h"  ).c_str() );
    std::ofstream fc( ( dir + '/' + name + ".cu" ).c_str() );

    // header file
    fh << "#ifndef " << name << "_H\n";
    fh << "#define " << name << "_H\n";
    fh << "\n";
    fh << "#include <TypeConfig.h>\n";
    fh << "#include <CudaMetil.h>\n";
    fh << "\n";
    fh << "struct " << name << " {\n";
    fh << "    template<class T> struct Vec {\n";
    fh << "        __inline__ T &operator[]( int index ) { return data_[ index ]; }\n";
    fh << "        __inline__ const T &operator[]( int index ) const { return data_[ index ]; }\n";
    fh << "        __inline__ int size() const { return size_; }\n";
    fh << "        __inline__ int rese() const { return rese_; }\n";
    fh << "        int size_;\n";
    fh << "        int rese_;\n";
    fh << "        T  *data_;\n";
    fh << "    };\n";
    fh << "    \n";

    // apply_bs
    fh << "    template<class TB>\n";
    fh << "    void apply_bs( TB &res ) const {\n";
    CompactStructAppl<std::ostream> ma; ma.os = &fh;
    str.apply_bs( ma );
    fh << "    }\n";
    fh << "    \n";

    // decl of copy, update_pointers
    fh << "    " << name << " *copy( cudaMemcpyKind memcpy_kind ) const;\n";
    fh << "    static void update_pointers( " << name << " *res, Metil::ST off, bool targets_gpu );\n";
    fh << "    \n";

    // attributes
    fh << "    Metil::ST size; ///< size in memory\n";
    CompactStructDecl<std::ostream> mc; mc.os = &fh;
    str.apply_bs( mc );
    fh << "};\n";
    fh << "\n";
    fh << "#endif // " << name << "_H\n";

    // src file
    fc << "#include \"" << name << ".h\"\n";
    fc << "\n";
    fc << name << " *" << name << "::copy( cudaMemcpyKind memcpy_kind ) const {\n";
    fc << "    // get size\n";
    fc << "    Metil::ST room;\n";
    fc << "    if ( memcpy_kind == cudaMemcpyHostToDevice or memcpy_kind == cudaMemcpyHostToHost ) // src is in the CPU memory\n";
    fc << "        room = size;\n";
    fc << "    else // src is in the GPU memory\n";
    fc << "        cudaMemcpy( &room, this, sizeof( Metil::ST ), cudaMemcpyDeviceToHost );\n";
    fc << "    \n";
    fc << "    // copy all the data\n";
    fc << "    " << name << " *res;\n";
    fc << "    bool targets_gpu = memcpy_kind == cudaMemcpyHostToDevice or memcpy_kind == cudaMemcpyDeviceToDevice;\n";
    fc << "    if ( targets_gpu )\n";
    fc << "        cudaMalloc( &res, room );\n";
    fc << "    else\n";
    fc << "        res = reinterpret_cast<" << name << " *>( malloc( room ) );\n";
    fc << "    cudaMemcpy( res, this, room, memcpy_kind );\n";
    fc << "    \n";
    fc << "    // update the pointers\n";
    fc << "    Metil::ST off = (const char *)res - (const char *)this;\n";
    fc << "    update_pointers( res, off, targets_gpu );\n";
    fc << "    \n";
    fc << "    return res;\n";
    fc << "}\n";
    fc << "\n";
    fc << "__global__\n";
    fc << "void update_gpu_ptr_kernel( " << name << " *res, Metil::ST off ) {\n";
    CompactStructUpda<std::ostream> mu; mu.os = &fc;
    str.apply_bs( mu );
    fc << "}\n";
    fc << "\n";
    fc << "void update_cpu_ptr_kernel( " << name << " *res, Metil::ST off ) {\n";
    str.apply_bs( mu );
    fc << "}\n";
    fc << "\n";
    fc << "void " << name << "::update_pointers( " << name << " *res, Metil::ST off, bool targets_gpu ) {\n";
    fc << "    if ( targets_gpu ) // dst in GPU\n";
    fc << "        update_gpu_ptr_kernel<<<1,1>>>( res, off );\n";
    fc << "    else // dst in CPU\n";
    fc << "        update_cpu_ptr_kernel( res, off );\n";
    fc << "}\n";
}




struct CompactStructGetRoomOrCopyData {
    typedef ST I;
    typedef ST P;

    struct TV {
        TV() {}
        TV( I len, P ptr ) : len( len ), ptr( ptr ) {}

        I len;
        P ptr;
    };

    CompactStructGetRoomOrCopyData() {
        copy_data = false;

        alig = 16 * 4;
        head = sizeof( I ); // size (first attribute)
        data = 0;
    }

    /// Beware: needs a first pass ( apply(...) )
    ST needed_room() const { return ceil( head, alig ) + data; }

    /// true if beg_copy_phase says that the target is a gpu
    bool gpu_target() const { return memcpy_kind == cudaMemcpyDeviceToDevice or memcpy_kind == cudaMemcpyDeviceToHost; }

    /// Beware: needs a first pass ( apply(...) )
    void beg_copy_phase( cudaMemcpyKind memcpy_kind_ ) {
        memcpy_kind = memcpy_kind_;
        copy_data = true;

        ST room = needed_room();
        if ( gpu_target() )
            cudaMalloc( &pt, room );
        else
            pt = reinterpret_cast<char *>( malloc( room ) );
        tm = (char *)malloc( head ); // local

        data = ceil( head, alig );
        head = 0;
        append_head( room );
    }

    void end_copy_phase() {
        cudaMemcpy( pt, tm, head, memcpy_kind );
    }

    template<class T>
    P append_head( const T &val ) {
        if ( copy_data )
            *reinterpret_cast<T *>( tm + head ) = val;
        P res = P( pt + head );
        head += sizeof( T ); // len
        return res;
    }

    template<class T>
    P append_data( const T &val ) {
        if ( copy_data )
            cudaMemcpy( pt + data, &val, sizeof( T ), memcpy_kind );
        P res = P( pt + data );
        data += sizeof( T ); // len
        return res;
    }

    template<class T,class S>
    P append_data( const T *val, S size ) { /// returns ptr
        data = ceil( data, alig );
        P res = P( pt + data );
        if ( copy_data )
            cudaMemcpy( pt + data, val, sizeof( T ) * size, memcpy_kind );
        data += sizeof( T ) * size;
        return res;
    }


    template<class T>
    void apply( const char *, const BasicVec<T> &val ) {
        // data
        P data_ptr = append_data( val.ptr(), val.size() );
        // len_v, ptr_v
        append_head( TV( val.size(), data_ptr ) );
    }

    template<class T>
    void apply( const char *, const BasicVec<BasicVec<T> > &val ) {
        // tmp vec with len_0 ptr_0 len_1 ptr_1 ...
        BasicVec<TV> tmp; tmp.resize( val.size() );
        for( unsigned i = 0; i < val.size(); ++i )
            tmp[ i ] = TV( val[ i ].size(), append_data( val[ i ].ptr(), val[ i ].size() ) );

        // copy tmp vec in data
        append_head( TV( tmp.size(), append_data( tmp.ptr(), tmp.size() ) ) );
    }

    // input
    ST   alig;
    bool copy_data;

    // output
    ST    head; /// offset in header
    ST    data; /// offset in data
    char *pt; ///< target data. Used if copy_data == 1
    char *tm; ///< tmp local data for header. Used if copy_data == 1
    cudaMemcpyKind memcpy_kind;
};



/// get size of the compact struct generated from str
template<class T>
ST compact_struct_size( const T &str ) {
    CompactStructGetRoomOrCopyData cs;
    str.apply_bs( cs );
    return cs.needed_room();
}


/// make a new compact structure from a non compact struct
template<class T>
void *compact_struct_make( const T &str, cudaMemcpyKind memcpy_kind ) {
    // first pass to get sizes
    CompactStructGetRoomOrCopyData cs;
    str.apply_bs( cs );

    // second pass: copy data
    cs.beg_copy_phase( memcpy_kind );
    str.apply_bs( cs );
    cs.end_copy_phase();

    return cs.pt;
}


END_METIL_NAMESPACE;
