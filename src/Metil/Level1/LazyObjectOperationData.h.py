# -*- coding: utf-8 -*-
from MethodHelper import *

print "// generated file"
print "#ifndef LAZYOBJECTOPERATIONDATA_H"
print "#define LAZYOBJECTOPERATIONDATA_H"
print ''
print '#include <Config.h>'
print ''
print 'BEG_METIL_LEVEL1_NAMESPACE;'
print ''

for m in methods:
    if m[ 0 ] == 'O':
        print 'struct LazyObjectOperationData_' + m + ' {'
        c = 0
        for l in m[ 1: ]:
            if l != 'o' and l != 'O':
                print '    ' + cor( l ) + letters[ c ] + ';'
            c += 1
        print '};'

print ''
print 'END_METIL_LEVEL1_NAMESPACE;'
print ''
print "#endif // LAZYOBJECTOPERATIONDATA_H"
