set(LIBRARY tsf)
project(${LIBRARY})

add_library(${LIBRARY} STATIC
    chorus.c
    dspfunc.c
    minisdl_audio.c
    reverb.c
)