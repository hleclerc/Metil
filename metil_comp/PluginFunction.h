#ifndef PLUGINFUNCTION_H
#define PLUGINFUNCTION_H

#include "CString.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file PluginFunction.cpp
#endif


namespace Metil {

///
void *make_function( const String &cpp_filename, const String &cpp_function );

///
class PluginFunctionAncestor {
public:
    typedef void V();

    PluginFunctionAncestor( const String &cpp_filename, const String &cpp_function ) : cpp_filename( cpp_filename ), cpp_function( cpp_function ) {}
protected:
    String cpp_filename;
    String cpp_function;
};

///
template<class Output,class I0=void,class I1=void,class I2=void,class I3=void>
class PluginFunction;

/// 2 arguments
template<class Output,class I0,class I1>
class PluginFunction<Output,I0,I1,void,void> : public PluginFunctionAncestor {
public:
    typedef Output F( I0, I1 );

    PluginFunction( const String &cpp_filename, const String &cpp_function ) : PluginFunctionAncestor( cpp_filename, cpp_function ), function( 0 ) {}

    Output operator()( I0 i0, I1 i1 ) {
        if ( not function )
            function = reinterpret_cast<F *>( make_function( cpp_filename, cpp_function ) );
        return function( i0, i1 );
    }
protected:
    F *function;
};

/// 1 argument
template<class Output,class I0>
class PluginFunction<Output,I0,void,void,void> : public PluginFunctionAncestor {
public:
    typedef Output F( I0 );

    PluginFunction( const String &cpp_filename, const String &cpp_function ) : PluginFunctionAncestor( cpp_filename, cpp_function ), function( 0 ) {}

    Output operator()( I0 i0 ) {
        if ( not function )
            function = reinterpret_cast<F *>( make_function( cpp_filename, cpp_function ) );
        return function( i0 );
    }
private:
    F *function;
};


} // namespace Metil


#endif // PLUGINFUNCTION_H
