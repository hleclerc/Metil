import string

def ap( m, c, w ):
    if c in m:
        m[ c ].append( w )
    else:
        m[ c ] = [ w ]

def gen( words, beg ):
    if beg in words:
        return []
    m = {}
    for w in words:
        if len( beg ) < len( w ):
            ap( m, w[ len( beg ) ], w )
    res = []
    for c, new_words in m.items():
        res.append( ( c, gen( new_words, beg + c ) ) )
    return res

def simplify( split, p = "" ):
    res = []
    for k, v in split:
        w = k
        while len( v ) == 1:
            w += v[ 0 ][ 0 ]
            v = v[ 0 ][ 1 ]
        res.append( ( w, simplify( v ) ) )
    return res

def display( split, sp, cpt = 0, acc = "" ):
    if len( split ) == 0:
        print sp + acc + "( c );"
        print sp + "c += " + str( len( acc ) - 1 ) + ";"
        print sp + "continue;"
    else:
        for c, f in split:
            s = string.join( [ "c[ " + str( n ) +" ] == '" + v + "'" for n, v in zip( range( cpt, cpt + len( c ) ), c ) ], " and " )
            print sp + "if ( " + s + " ) {"
            display( f, sp + "    ", cpt + len( c ), acc + c )
            print sp + "}"

words = ["metil_type_bas_","metil_type_ref_","metil_type_cst_","metil_def_","metil_gen_"]
split = simplify( gen( words, "" ) )
display( split, "    " )
