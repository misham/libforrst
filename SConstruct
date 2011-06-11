
TOP = '.'

DEBUG = '-g -DDEBUG '

INCLUDES = '-I ' + TOP + '/includes '
LDFLAGS = '-lcurl -Wl,-Bsymbolic-functions -lcunit '
WARNINGS = '-Wall -Wextra '

CC = 'gcc'
CCFLAGS = '-std=c99 ' + WARNINGS  + DEBUG + INCLUDES

env = Environment()
my_flags = env.ParseFlags( CCFLAGS + LDFLAGS )
env.MergeFlags( my_flags )

test_exec = 'test_forrst'

lib_name = 'libforrs'

src = Split("""
						src/info.c \
						src/post.c \
						src/forrst_list.c \
						src/user.c
						""")

test_src = Split("""
								 tests/test_forrst.c
                 """)

env.Program( target = test_exec,
						 source = test_src + src )

# StaticLibrary( target = lib_name, source = src )
# SharedLibrary( target = lib_name, source = src )

