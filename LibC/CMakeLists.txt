add_library(c

    ../AK/StringImpl.o
    ../AK/String.o
    ../AK/StringView.o
    ../AK/StringBuilder.o
    ../AK/FileSystemPath.o
    ../AK/StdLibExtras.o
    ../AK/MappedFile.o

    SharedBuffer.cpp
    stdio.cpp
    unistd.cpp
    string.cpp
    strings.cpp
    mman.cpp
    dirent.cpp
    malloc.cpp
    stdlib.cpp
    time.cpp
    utsname.cpp
    assert.cpp
    signal.cpp
    getopt.cpp
    scanf.cpp
    pwd.cpp
    grp.cpp
    times.cpp
    termcap.cpp
    stat.cpp
    mntent.cpp
    ctype.cpp
    fcntl.cpp
    termios.cpp
    ulimit.cpp
    qsort.cpp
    ioctl.cpp
    utime.cpp
    sys/select.cpp
    sys/socket.cpp
    sys/wait.cpp
    sys/uio.cpp
    poll.cpp
    locale.cpp
    arpa/inet.cpp
    netdb.cpp
    sched.cpp

    setjmp.S
    crti.S
    crtn.S
)
serenity_flags(c)
target_include_directories(c PUBLIC .. .)
target_compile_options(c PUBLIC -DUSERLAND)

file(GLOB_RECURSE libc_headers ./*.h)
set_target_properties(c PROPERTIES PUBLIC_HEADER "${libc_headers}")
set_target_properties(c PROPERTIES START_OBJS crti.o crtn.o crt0.o)

install(TARGETS c
    LIBRARY DESTINATION ./usr/lib
    PUBLIC_HEADER DESTINATION ./usr/include
    START_OBJS DESTINATION ./usr/lib
)




#-       cp crt0.o ../Root/usr/lib/
#-       cp crti.ao ../Root/usr/lib/crti.o
#-       cp crtn.ao ../Root/usr/lib/crtn.o
#
