DECL_MET( OOO       , add                     ); // +
DECL_MET( OOO       , sub                     ); // -
DECL_MET( OOO       , mul                     ); // *
DECL_MET( OOO       , div                     ); // /
DECL_MET( OOO       , quo                     ); // // ( quotient )
DECL_MET( OOO       , mod                     ); // % ( remainder )
DECL_MET( OOO       , pow                     ); // ^
DECL_MET( OOO       , atan2                   ); //

DECL_MET( OOO       , inf                     ); // <
DECL_MET( OOO       , infeq                   ); // <=
DECL_MET( OOO       , sup                     ); // >
DECL_MET( OOO       , supeq                   ); // >=
DECL_MET( OOO       , equal                   ); // ==
DECL_MET( OOO       , noteq                   ); // !=

#ifndef AVOID_BITWISE
DECL_MET( OOO       , bitwise_and             ); // &
DECL_MET( OOO       , bitwise_or              ); // |
DECL_MET( OOO       , bitwise_xor             ); // ^
#endif // AVOID_BITWISE

DECL_MET( OOO       , boolean_and             ); // &&
DECL_MET( OOO       , boolean_or              ); // ||
DECL_MET( OOO       , boolean_xor             ); // ^^
