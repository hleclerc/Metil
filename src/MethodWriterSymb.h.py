# -*- coding: utf-8 -*-
from MethodHelper import *

def cor_cxx( c, s ):
    if c == "O":
        l = s.find( "O" )
        if l >= 0:
            return "ES" + str( l + 1 ) + "_"
        s += c
        return "ENS0_2MOE"
    if c == "o":
        s += c
        return "ERNS0_2MOE"
    if c == "V": return "v"
    if c == "B": return "b"
    if c == "I": return "i"
    if c == "L": return "x"
    if c == "S": return "x"
    if c == "F": return "f"
    if c == "D": return "d"
    if c == "E": return "e"
    if c == "p": return "Pv"
    if c == "P": return "PKv"
    if c == "t":
        s += c
        return "ERNS_6StringE"
    if c == "Y":
        s += c
        return "EPNS0_9OwcpChildE"

def arg_cxx( m ):
    r = ""
    s = ""
    for c in m[ 1: ]:
        r += cor_cxx( c, s )
    return r

for m in methods:
    print '    if ( type == "' + m + '" ) { args = "' + arg_cxx( m ) + '"; }'
