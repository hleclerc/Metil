#ifndef TYPEINFORMATION_H
#define TYPEINFORMATION_H

template<class T>
struct TypeInformation {
};

#define DECL_TYPEINFORMATION( T ) template<> struct TypeInformation<T> { static const char *type() { return #T; } }

DECL_TYPEINFORMATION( double );
DECL_TYPEINFORMATION( float );
DECL_TYPEINFORMATION( int );

#endif // TYPEINFORMATION_H
