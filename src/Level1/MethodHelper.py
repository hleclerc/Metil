# -*- coding: utf-8 -*-
import string

methods = [
    "Vo",
    "OO",
    "BO",
    "IO",
    "LO",
    "SO",
    "FO",
    "DO",
    "EO",
    "VOt",
    "pO",
    "Vot",
    "po",
    "VoPS",
    "VOpS",
    "OOO",
    "BOO",
    "VoO",
    "OoO",
    "OOS",
    "VoY",
    "YO",
]

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

def args( m ):
    l = "abcdefgh"
    return string.join( [ cor( c ) + l[ n ] for c, n in zip( m[1:], range( 100 ) ) ], ", " )

def arg_names( m ):
    l = "abcdefgh"
    return string.join( [ l[ n ] for n in range( len( m[1:] ) ) ], ", " )



