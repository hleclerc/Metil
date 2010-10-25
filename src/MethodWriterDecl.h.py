# -*- coding: utf-8 -*-
from MethodHelper import *

for m in methods:
    print '    if ( type == "' + m + '" ) return "' + cor( m[ 0 ] ) + 'metil_def_" + def_name + "( ' + args( m ) + ' )";'
