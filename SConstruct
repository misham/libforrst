import commands

TOP = '.'

DEBUG = '-g -DDEBUG '

CURL_LIBS = commands.getoutput( 'curl-config --libs' )
CURL_CFLAGS = commands.getoutput( 'curl-config --cflags' )

TEST_LDFLAGS = '-lcunit '

INCLUDES = '-I ' + TOP + '/includes '
LDFLAGS = '-ljson ' + CURL_LIBS
WARNINGS = '-Wall -Wextra '

CC = 'gcc'
CCFLAGS = '-std=c99 ' + WARNINGS  + DEBUG + INCLUDES + CURL_CFLAGS

env = Environment()
my_flags = env.ParseFlags( CCFLAGS + LDFLAGS )
env.MergeFlags( my_flags )
env.VariantDir( 'build', 'src', 0 )

test_exec = 'test_forrst'

lib_name = 'libforrs'

src = Split("""
            build/common.c
						build/info.c
						build/post.c
						build/forrst_list.c
						build/user.c
            build/connection.c
						""")

test_src = Split("""
								 tests/test_forrst.c
                 """)

#env.Program( target = test_exec,
#						 source = test_src + src )

# StaticLibrary( target = lib_name, source = src )
# SharedLibrary( target = lib_name, source = src )

env.Program( target = 'bin/stats', source = src + ['examples/stats.c'] )
env.Program( target = 'bin/user', source = src + ['examples/user.c'] )

