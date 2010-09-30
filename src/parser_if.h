    if ( c[ 0 ] == 'm' and c[ 1 ] == 'e' and c[ 2 ] == 't' and c[ 3 ] == 'i' and c[ 4 ] == 'l' and c[ 5 ] == '_' ) {
        if ( c[ 6 ] == 't' and c[ 7 ] == 'y' and c[ 8 ] == 'p' and c[ 9 ] == 'e' and c[ 10 ] == '_' ) {
            if ( c[ 11 ] == 'r' and c[ 12 ] == 'e' and c[ 13 ] == 'f' and c[ 14 ] == '_' ) {
                metil_type_ref_( c );
                c += 14;
                continue;
            }
            if ( c[ 11 ] == 'b' and c[ 12 ] == 'a' and c[ 13 ] == 's' and c[ 14 ] == '_' ) {
                metil_type_bas_( c );
                c += 14;
                continue;
            }
            if ( c[ 11 ] == 'c' and c[ 12 ] == 's' and c[ 13 ] == 't' and c[ 14 ] == '_' ) {
                metil_type_cst_( c );
                c += 14;
                continue;
            }
        }
        if ( c[ 6 ] == 'g' and c[ 7 ] == 'e' and c[ 8 ] == 'n' and c[ 9 ] == '_' ) {
            metil_gen_( c );
            c += 9;
            continue;
        }
        if ( c[ 6 ] == 'd' and c[ 7 ] == 'e' and c[ 8 ] == 'f' and c[ 9 ] == '_' ) {
            metil_def_( c );
            c += 9;
            continue;
        }
    }
