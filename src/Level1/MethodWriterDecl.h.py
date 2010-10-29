# -*- coding: utf-8 -*-
from MethodHelper import *

for m in methods:
    print '    if ( type == "' + m + '" ) return "' + cor( m[ 0 ] ) + '" + def_name + "( ' + args( m ) + ' )";'
