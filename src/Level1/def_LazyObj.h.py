# -*- coding: utf-8 -*-
from MethodHelper import *

for m in methods:
    if m[ 0 ] == 'O':
        print 'struct LazyObjectOperationData_' + m + ' {'
        c = 0
        for l in m[ 1: ]:
            if l != 'o' and l != 'O':
                print '    ' + cor( l ) + ' ' + letters[ c ] + ';'
            c += 1
        print '};'

def p_m( pref, obj ):
    print '#define MET_' + pref + m + '( N ) \\'
    print '    ' + cor( m[ 0 ] ) + ' metil_def_##N##__when__' + obj + '__isa__LazyObject__pert__10( ' + args( m ) + ' ) { \\'
    print '        Type *type = &metil_type_bas_LazyOperation_##N; \\'
    print '        typedef Owcp<' + str( nb_MO_args( m ) ) + ',LazyObjectOperationData_' + m + '> TR; \\'
    print '        TR *data = NEW( TR, type, ' + MO_arg_names( m ) + ' ); \\'
    c = 0
    for l in m[ 1: ]:
        if l != 'o' and l != 'O':
            print '        data->data.' + letters[ c ] + ' = ' + letters[ c ] + '; \\'
        c += 1
    print '        return MO( data, type ); \\'
    print '    }'

for m in methods:
    if m[ 0 ] == 'O':
        p_m( "", "a" )
        if nb_MO_args( m ) >= 2:
            p_m( "1_", "b" )
    else:
        print '#define MET_' + m + '( N )'
        if nb_MO_args( m ) >= 2:
            print '#define MET_1_' + m + '( N )'
