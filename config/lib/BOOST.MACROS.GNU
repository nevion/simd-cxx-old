#-*-Makefile-*-

# These library setting will work fine with BOOST 1.40. If you are
# using an older version of boost it is likely that you need to change
# the library names below.


SIMD_LD_LIBS+=-lboost_signals
SIMD_LD_LIBS+=-lboost_program_options
SIMD_LD_LIBS+=-lboost_thread
