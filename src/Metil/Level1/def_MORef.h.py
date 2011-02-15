# -*- coding: utf-8 -*-
from MethodHelper import *

for m in methods:
    if nb_MO_args( m ) >= 1:
        if arg_const( m[ 1 ] ):
            print '#define MET_' + m + '( N ) ' + cor( m[ 0 ] ) + ' metil_def_##N##__when__a__isa__MORef__pert__10( ' + args( m ) + ' ) { Ad v = CM_1( copy, a ); return CM_' + str( nb_MO_args( m ) ) + '( N, v.o' + ', b' * ( nb_args( m ) >= 2 ) + ', c' * ( nb_args( m ) >= 3 ) + ' ); }'
        else:
            print '#define MET_' + m + '( N )'
    if nb_MO_args( m ) >= 2:
        if arg_const( m[ 2 ] ):
            print '#define MET_1_' + m + '( N ) ' + cor( m[ 0 ] ) + ' metil_def_##N##__when__b__isa__MORef__pert__11( ' + args( m ) + ' ) { Ad v = CM_1( copy, b ); return CM_' + str( nb_MO_args( m ) ) + '( N, a, v.o' + remaining_args( m, 2 ) + ' ); }'
        else:
            print '#define MET_1_' + m + '( N )'
