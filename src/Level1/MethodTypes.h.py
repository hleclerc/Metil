from MethodHelper import *

for m in methods:
    if m[1:].count( "O" ) + m[1:].count( "o" ) == 2:
        print 'typedef ' + cor( m[ 0 ] ) + '(* Method_' + m + ')( ' + args( m ) + ' );'
    else:
        print 'typedef ' + cor( m[ 0 ] ) + 'Method_' + m + '( ' + args( m ) + ' );'
