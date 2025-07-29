import sys
import os
import os.path
import subprocess

t = sys.argv[1]
className = t
n = len( t )
define=t.upper() + '_HPP'

hFileName =  className+'.hpp'
cppFileName = className+'.cpp' 
gtestFileName = 'tests/test_'+className+'.cpp'
cMakeListsFileName = '../CMakeLists.txt'

if os.path.isfile( hFileName ):
    print( 'file ' + hFileName + ' exist'  )
    exit( 1 )

if os.path.isfile( cppFileName ):
    print( 'file ' + cppFileName + ' exist'  )
    exit( 1 )

with open(hFileName, 'w') as header:
    print( '///************************* OUTS HOMEWORK ****************************************', file = header )
    print( '#ifndef ' + define, file = header )
    print( '#define ' + define, file = header )
    print( '', file = header )

    msg=(
    f'class {className}\n'
    f'{{\n'
    f'public:\n'
    f'}};\n')

    print( msg, file = header )
    print( '#endif //#ifndef ' + define, file = header )

with open(cppFileName, 'w') as source:
    print( '///************************* OUTS HOMEWORK ****************************************', file = source )
    print( '', file = source )
    print( '#include "' + className + '.hpp"', file = source )
    print( '', file = source )

with open(gtestFileName, 'w') as source:

    msg=(
    f'///************************* OUTS HOMEWORK ****************************************\n'
    f'\n'
    f'#include <gtest/gtest.h>\n'
    f'\n'
    f'#include "{className}.hpp"\n'
    f'\n'
    f'// gTest grouping class\n'
    f'class test_{className} : public ::testing::Test\n'
    f'{{\n'
    f'public:\n'
    f'  // additional class to access to member of tested class\n'
    f'  class Test_{className} : public {className}\n'
    f'  {{\n'
    f'  public:\n'
    f'    // add here members for free access.\n'
    f'    using {className}::{className}; // delegate constructors\n'
    f'  }};\n'
    f'\n'
    f'}};\n'
    f' \n'
    f'TEST_F(test_{className}, test_ctor )\n'
    f'{{\n'
    f'  Test_{className} t;\n'
    f'}}\n')
    print( msg, file = source )


cMakeListsFileLines = []
with open(cMakeListsFileName, 'r') as cMakeListsFile:
    for line in cMakeListsFile:
        if line.startswith( '#add source file here' ):
            cMakeListsFileLines.append( '  source/' +  hFileName + '\n')
            cMakeListsFileLines.append( '  source/' +  cppFileName + '\n' )
        if line.startswith( '#add test file here' ):
            cMakeListsFileLines.append( '  source/' +  gtestFileName + '\n' )
        cMakeListsFileLines.append(line)

print( ''.join(cMakeListsFileLines) )

with open(cMakeListsFileName, 'w') as cMakeListsFile:
    print( ''.join(cMakeListsFileLines), file = cMakeListsFile, end = '' )

print( ' '.join(["git add", hFileName, cppFileName, gtestFileName ]) )
result = subprocess.run(' '.join(["git add", hFileName, cppFileName, gtestFileName ]), shell=True )
print(f"Files added to git with status: {result.returncode}")