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

#include "Stream.h"
#include "String.h"
#include "Number.h"
#include "TypeConfig.h"
#include "BasicVec.h"

namespace Metil {
    
Stream::Stream() {
    nb_digits = 5;
}

Stream::~Stream() {
}

Stream::Endl Stream::endl;
Stream::Flsh Stream::flsh;

char   Stream::get_char() { char   res; get_char( res ); return res; }
String Stream::get_word() { String res; get_word( res ); return res; }
String Stream::get_line() { String res; get_line( res ); return res; }
String Stream::get_left() { String res; get_left( res ); return res; }

bool Stream::get_word( String &word ) {
    if ( eof() ) {
        word.resize( 0 );
        return false;
    }
    // skip_spaces
    char c = get_char();
    while ( c == ' ' or c == '\n' or c == '\t' or c == '\r' ) {
        c = get_char();
        if ( eof() )
            return false;
    }
    //
    word = c;
    do {
        char c = get_char();
        if ( c == ' ' or c == '\n' or c == '\t' or c == '\r' )
            return true;
        word += c;
    } while ( *this );
    return true;
}

bool Stream::get_line( String &line ) {
    line.resize( 0 );
    if ( eof() )
        return false;
    char c;
    do {
        c = get_char();
        line += c;
    } while ( c != '\n' and c != '\r' and not eof() );
    return true;
}

bool Stream::get_left( String &left ) {
    left.resize( 0 );
    if ( eof() )
        return false;
    do {
        left += get_char();
    } while ( not eof() );
    return true;
}


Stream &operator<<( Stream &os, bool          val ) { if ( val ) os.write( "true", 4 ); else os.write( "false", 5 ); return os; }
Stream &operator<<( Stream &os, const char   *val ) { os.write( val, String::strlen( val ) ); return os; }
Stream &operator<<( Stream &os, char         *val ) { os.write( val, String::strlen( val ) ); return os; }
Stream &operator<<( Stream &os, char          val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Int8          val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Int16         val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Int32         val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Int64         val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Unsigned8     val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Unsigned16    val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Unsigned32    val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Unsigned64    val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Float32       val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Float64       val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, Float96       val ) { os.write( val ); return os; }
Stream &operator<<( Stream &os, void         *val ) { os.write( val ); return os; }

Stream &operator>>( Stream &os, bool         &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, char         &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Int8         &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Int16        &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Int32        &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Int64        &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Unsigned8    &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Unsigned16   &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Unsigned32   &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Unsigned64   &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Float32      &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Float64      &val ) { os.read( val ); return os; }
Stream &operator>>( Stream &os, Float96      &val ) { os.read( val ); return os; }


void Stream::Endl::write_to_stream( Stream &os ) const {
    os << "\n";
    os.flush();
}

void Stream::Flsh::write_to_stream( Stream &os ) const {
    os.flush();
}

void Stream::Spaces::write_to_stream( Stream &os ) const {
    const char *toto = "                ";
    int r = n;
    while ( r ) {
        int m = min( 16, r );
        os.write( toto, m );
        r -= m;
    }
}

template<class T,int base>
struct MaxNbCharIn {};

template<> struct MaxNbCharIn<Int8      ,10> { static const int res =  3; };
template<> struct MaxNbCharIn<Int16     ,10> { static const int res =  5; };
template<> struct MaxNbCharIn<Int32     ,10> { static const int res = 11; };
template<> struct MaxNbCharIn<Int64     ,10> { static const int res = 20; };

template<> struct MaxNbCharIn<Unsigned8 ,10> { static const int res =  3; };
template<> struct MaxNbCharIn<Unsigned16,10> { static const int res =  5; };
template<> struct MaxNbCharIn<Unsigned32,10> { static const int res = 10; };
template<> struct MaxNbCharIn<Unsigned64,10> { static const int res = 20; };

template<> struct MaxNbCharIn<Unsigned32,16> { static const int res =  8; };
template<> struct MaxNbCharIn<Unsigned64,16> { static const int res = 16; };

template<int base,class T>
int write_int_number_rec( Number<base> n, char *tmp, T data, int size = 0 ) {
    const char t[] = "0123456789ABCDEF";
    if ( not data )
        return size;
    int res = write_int_number_rec( n, tmp, data / base, size + 1 );
    tmp[ res - size - 1 ] = t[ data % base ];
    return res;
}

template<int base,class T>
inline void write_int_number( Number<base> n, Stream &os, T data ) {
    if ( data < 0 ) {
        os << '-';
        write_int_number( n, os, -data );
    } else if ( data == 0 ) {
        if ( base == 16 )
            os.write( "0x0", 3 );
        else
            os.write( '0' );
    } else {
        const int pre = 2 * ( base == 16 );
        char tmp[ pre + MaxNbCharIn<T,base>::res ];
        if ( base == 16 ) {
            tmp[ 0 ] = '0';
            tmp[ 1 ] = 'x';
        }
        int size = write_int_number_rec( n, tmp + pre, data );
        os.write( tmp, size + pre );
    }
}

template<class T> struct NbDigitsFor;
template<> struct NbDigitsFor<Float32> { static const unsigned res =  7; };
template<> struct NbDigitsFor<Float64> { static const unsigned res = 16; };
template<> struct NbDigitsFor<Float96> { static const unsigned res = 19; };

template<class T>
T pow_int( T val, int e ) {
    if ( e < 0 )
        return pow_int( 1.0 / val, -e );
    if ( e == 0 )
        return 1;
    if ( e == 1 )
        return val;
    if ( e % 2 )
        return val * pow_int( val, e - 1 );
    T tmp = pow_int( val, e / 2 );
    return tmp * tmp;
}

template<int base,class T>
void write_flt_number( Number<base> n, Stream &os, const T &data ) {
    int nb_digits = os.nb_digits ? os.nb_digits : NbDigitsFor<T>::res;
    if ( data < 0 ) {
        os << '-';
        write_flt_number( n, os, -data );
    } else if ( data == 0 ) {
        os.write( "0.", 2 );
        for( int i=1; i<nb_digits; ++i )
            os.write( '0' );
        os.write( "e0", 2 );
    } else {

        //
        BasicVec<int,-1,50> res( SetSize(), nb_digits + 1 );
        int e_d = int( log( data ) / log( 10.0 ) );
        e_d -= e_d < 0;
        T b_d = pow_int( 10.0, - e_d );
        for( int i=0; i<=nb_digits; ++i ) {
            res[ i ] = int( data * b_d ) % base;
            b_d *= base;
        }

        // round
        if ( res[ nb_digits ] > 5 ) {
            for( int i=nb_digits-1; i>=0; --i ) {
                if ( ++res[ i ] < 10 )
                    break;
                else
                    res[ i ] = 0;
            }
        }

        // display
        os.write( char( '0' + res[ 0 ] ) );
        os.write( '.' );
        for( int i=1; i<nb_digits; ++i )
            os.write( char( '0' + res[ i ] ) );
        os.write( 'e' );
        os.write( e_d );
    }

}

template<class T> struct IsSigned {};
template<> struct IsSigned<Int8 > { static const bool res = true; };
template<> struct IsSigned<Int16> { static const bool res = true; };
template<> struct IsSigned<Int32> { static const bool res = true; };
template<> struct IsSigned<Int64> { static const bool res = true; };
template<> struct IsSigned<Unsigned8 > { static const bool res = false; };
template<> struct IsSigned<Unsigned16> { static const bool res = false; };
template<> struct IsSigned<Unsigned32> { static const bool res = false; };
template<> struct IsSigned<Unsigned64> { static const bool res = false; };
template<> struct IsSigned<Float32   > { static const bool res = true; };
template<> struct IsSigned<Float64   > { static const bool res = true; };
template<> struct IsSigned<Float96   > { static const bool res = true; };

template<class T>
bool read_int_number( Stream &is, T &data, Int64 old_pos ) {
    // skip_spaces
    char c = is.get_char();
    while ( c == ' ' or c == '\n' or c == '\t' ) {
        c = is.get_char();
        if ( is.eof() ) {
            is.seek( old_pos );
            return false;
        }
    }
    // go
    bool neg = false;
    if ( IsSigned<T>::res and c == '-' ) {
        if ( is.eof() ) { // - is not enough to form a number
            is.seek( old_pos );
            return false;
        }
        neg = true;
        c = is.get_char();
    }
    //
    if ( c < '0' or c > '9' ) {
        is.seek( old_pos );
        return false;
    }
    data = neg ? '0' - c : c - '0';
    while ( not is.eof() ) {
        c = is.get_char();
        if ( c < '0' or c > '9' ) {
            is.seek( is.tell() - 1 );
            return true;
        }
        data *= 10;
        data += neg ? '0' - c : c - '0';
    }
    return true;
}

template<class T>
bool read_int_number( Stream &is, T &data ) {
    if ( not is )
        return false;
    return read_int_number( is, data, is.tell() );
}

template<class T>
bool read_flt_number( Stream &is, T &data ) {
    if ( not is )
        return false;
    Int64 old_pos = is.tell();
    if ( not read_int_number( is, data, old_pos ) )
        return false;

}

void Stream::write( Int8          data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Int16         data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Int32         data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Int64         data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Unsigned8     data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Unsigned16    data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Unsigned32    data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Unsigned64    data ) { write_int_number( Number<10>(), *this, data ); }
void Stream::write( Float32       data ) { write_flt_number( Number<10>(), *this, data ); }
void Stream::write( Float64       data ) { write_flt_number( Number<10>(), *this, data ); }
void Stream::write( Float96       data ) { write_flt_number( Number<10>(), *this, data ); }
void Stream::write( const void   *data ) { write_int_number( Number<16>(), *this, UnsignedSizeType(data) ); }

bool Stream::read( char          &data ) { bool res = not eof(); data = get_char(); return res; }
bool Stream::read( bool          &data ) {
    if ( eof() )
        return false;
    Int64 old_pos = tell();
    // skip_spaces
    char c = get_char();
    while ( c == ' ' or c == '\n' or c == '\t' ) {
        c = get_char();
        if ( eof() ) {
            seek( old_pos );
            return false;
        }
    }
    //
    if ( c == 't' ) {
        if ( get_char() == 'r' and get_char() == 'u' and get_char() == 'e' ) {
            data = true;
            return true;
        }
        seek( old_pos );
        return false;
    }
    if ( c == 'f' ) {
        if ( get_char() == 'a' and get_char() == 'l' and get_char() == 's' and get_char() == 'e' ) {
            data = false;
            return true;
        }
        seek( old_pos );
        return false;
    }
    return false;
}
bool Stream::read( Int8          &data ) { return read_int_number( *this, data ); }
bool Stream::read( Int16         &data ) { return read_int_number( *this, data ); }
bool Stream::read( Int32         &data ) { return read_int_number( *this, data ); }
bool Stream::read( Int64         &data ) { return read_int_number( *this, data ); }
bool Stream::read( Unsigned8     &data ) { return read_int_number( *this, data ); }
bool Stream::read( Unsigned16    &data ) { return read_int_number( *this, data ); }
bool Stream::read( Unsigned32    &data ) { return read_int_number( *this, data ); }
bool Stream::read( Unsigned64    &data ) { return read_int_number( *this, data ); }
bool Stream::read( Float32       &data ) { return false; }
bool Stream::read( Float64       &data ) { return false; }
bool Stream::read( Float96       &data ) { return false; }

}

