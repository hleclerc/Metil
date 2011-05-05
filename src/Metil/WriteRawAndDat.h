#ifndef WRITERAWANDDAT_H
#define WRITERAWANDDAT_H

#include "MathBasicVec.h"
#include "String.h"

BEG_METIL_NAMESPACE;

namespace Level1 {
    template<class T>
    struct RawAndDatFormat;

    template<> struct RawAndDatFormat<unsigned  char> { static String res() { return "UCHAR" ; } };
    template<> struct RawAndDatFormat<  signed  char> { static String res() { return "CHAR"  ; } };
    template<> struct RawAndDatFormat<unsigned short> { static String res() { return "USHORT"; } };
    template<> struct RawAndDatFormat<  signed short> { static String res() { return "SHORT" ; } };
    template<> struct RawAndDatFormat<unsigned   int> { static String res() { return "UINT"  ; } };
    template<> struct RawAndDatFormat<  signed   int> { static String res() { return "INT"   ; } };
    template<> struct RawAndDatFormat<         float> { static String res() { return "FLOAT" ; } };
}

template<class T,class V>
void write_raw_and_dat( const String &filename, const T *cpu, const V &size ) {
    // raw
    File raw( filename + ".raw", "w" );
    raw.write( cpu, product( size ) * sizeof( T ) );
    // dat
    File dat( filename + ".dat", "w" );
    dat << "ObjectFileName: " << filename << ".raw\n";
    dat << "TaggedFileName: ---\n";
    dat << "Resolution:     " << size << "\n";
    dat << "SliceThickness: 1.0 1.0 1.0\n";
    dat << "Format:         " << Level1::RawAndDatFormat<T>::res() << "\n";
    dat << "NbrTags:        0\n";
    dat << "ObjectType:     TEXTURE_VOLUME_OBJECT\n";
    dat << "ObjectModel:    I\n";
    dat << "GridType:       EQUIDISTANT\n";
    dat << "Modality:       unknown\n";
    dat << "TimeStep:       0\n";
    dat << "Unit:           mm\n";


}

END_METIL_NAMESPACE;

#endif // WRITERAWANDDAT_H
