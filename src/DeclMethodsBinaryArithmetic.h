DECL_MET( OCC       , add                     ); // +
DECL_MET( OCC       , sub                     ); // -
DECL_MET( OCC       , mul                     ); // *
DECL_MET( OCC       , div                     ); // /
DECL_MET( OCC       , quo                     ); // // ( quotient )
DECL_MET( OCC       , mod                     ); // % ( remainder )
DECL_MET( OCC       , pow                     ); // ^
DECL_MET( OCC       , atan2                   ); //

DECL_MET( OCC       , inf                     ); // <
DECL_MET( OCC       , infeq                   ); // <=
DECL_MET( OCC       , sup                     ); // >
DECL_MET( OCC       , supeq                   ); // >=
DECL_MET( OCC       , equal                   ); // ==
DECL_MET( OCC       , noteq                   ); // !=

#ifndef AVOID_BITWISE
DECL_MET( OCC       , bitwise_and             ); // &
DECL_MET( OCC       , bitwise_or              ); // |
DECL_MET( OCC       , bitwise_xor             ); // ^
#endif // AVOID_BITWISE

DECL_MET( OCC       , boolean_and             ); // &&
DECL_MET( OCC       , boolean_or              ); // ||
DECL_MET( OCC       , boolean_xor             ); // ^^
