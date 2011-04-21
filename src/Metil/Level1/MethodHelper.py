# -*- coding: utf-8 -*-
import string, os, re

methods = {}
for h in os.listdir( "src/Metil/Level1/" ):
    if "DeclMethods" in h:
        for l in file( "src/Metil/Level1/" + h ).readlines():
            res = re.findall( '^DECL_MET\( ([^ ,]*)', l )
            if len( res ):
                methods[ res[ 0 ] ] = 0

methods = methods.keys()

letters = "abcdefgh"

def cor( c ):
    if c == "O": return "MO "
    if c == "o": return "MO &"
    if c == "V": return "void "
    if c == "B": return "bool "
    if c == "I": return "SI32 "
    if c == "L": return "SI64 "
    if c == "S": return "ST "
    if c == "F": return "FP32 "
    if c == "D": return "FP64 "
    if c == "E": return "FP80 "
    if c == "p": return "void *"
    if c == "P": return "const void *"
    if c == "t": return "String &"
    if c == "Y": return "struct OwcpChild *"
    if c == "M": return "const MachineId *"
    if c == "X": return "struct MetilException *"
    print "unknown char " + c
    return "Bing"

def arg_const( c ):
    return c.isupper()

def nb_args( c ):
    return len( c ) - 1

def nb_MO_args( m ):
    res = 0
    for c in m[ 1: ]:
        res += c == 'o'
        res += c == 'O'
    return res

def remaining_args( m, beg ):
    res = ""
    l = "abcdefgh"
    n = beg
    for c in m[ beg + 1: ]:
        res += ', '
        res += l[ n ]
        n += 1
    return res

def args( m ):
    return string.join( [ cor( c ) + letters[ n ] for c, n in zip( m[1:], range( 100 ) ) ], ", " )

def arg_names( m ):
    return string.join( [ letters[ n ] for n in range( len( m[1:] ) ) ], ", " )

def MO_arg_names( m ):
    return string.join( [ letters[ n ] for n in range( nb_MO_args( m ) ) ], ", " )


