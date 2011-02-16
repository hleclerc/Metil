    if ( c[ 1 ] == 'm' and c[ 2 ] == 'e' and c[ 3 ] == 't' and c[ 4 ] == 'i' and c[ 5 ] == 'l' and c[ 6 ] == '_' ) {
        if ( c[ 7 ] == 't' and c[ 8 ] == 'y' and c[ 9 ] == 'p' and c[ 10 ] == 'e' and c[ 11 ] == '_' ) {
            if ( c[ 12 ] == 'r' and c[ 13 ] == 'e' and c[ 14 ] == 'f' and c[ 15 ] == '_' ) {
                metil_type_ref_( c += 1 );
                continue;
            }
            if ( c[ 12 ] == 'b' and c[ 13 ] == 'a' and c[ 14 ] == 's' and c[ 15 ] == '_' ) {
                metil_type_bas_( c += 1 );
                continue;
            }
            if ( c[ 12 ] == 'c' and c[ 13 ] == 's' and c[ 14 ] == 't' and c[ 15 ] == '_' ) {
                metil_type_cst_( c += 1 );
                continue;
            }
        }
        if ( c[ 7 ] == 'g' and c[ 8 ] == 'e' and c[ 9 ] == 'n' and c[ 10 ] == '_' ) {
            metil_gen_( c += 1 );
            continue;
        }
        if ( c[ 7 ] == 'd' and c[ 8 ] == 'e' and c[ 9 ] == 'f' and c[ 10 ] == '_' ) {
            metil_def_( c += 1 );
            continue;
        }
    }
