function(serenity_kernel_flags target)
    serenity_flags("${target}")
    target_include_directories("${target}" PUBLIC .. .)
    target_compile_options("${target}" PUBLIC -ffreestanding -mregparm=3 -mno-80387 -mno-mmx -mno-sse -mno-sse2 -nostdinc++ -nostdlib -nostdinc -DKERNEL)
    target_link_options("${target}" PUBLIC -nostdlib)
endfunction()

add_library(
    KernelCore

    init.cpp
    kmalloc.cpp
    StdLib.cpp
    i386.cpp
    Process.cpp
    Thread.cpp
    i8253.cpp
    Devices/KeyboardDevice.cpp
    CMOS.cpp
    PIC.cpp
    Syscall.cpp
    Devices/IDEDiskDevice.cpp
    VM/MemoryManager.cpp
    VM/Region.cpp
    VM/VMObject.cpp
    VM/PageDirectory.cpp
    VM/PhysicalPage.cpp
    VM/RangeAllocator.cpp
    Console.cpp
    IRQHandler.cpp
    kprintf.cpp
    RTC.cpp
    TTY/TTY.cpp
    TTY/PTYMultiplexer.cpp
    TTY/MasterPTY.cpp
    TTY/SlavePTY.cpp
    TTY/VirtualConsole.cpp
    FileSystem/FIFO.cpp
    Scheduler.cpp
    DoubleBuffer.cpp
    ELF/ELFImage.cpp
    ELF/ELFLoader.cpp
    KSyms.cpp
    SharedMemory.cpp
    FileSystem/DevPtsFS.cpp
    Devices/BXVGADevice.cpp
    PCI.cpp
    Devices/PS2MouseDevice.cpp
    Net/Socket.cpp
    Net/LocalSocket.cpp
    Net/IPv4Socket.cpp
    Net/TCPSocket.cpp
    Net/UDPSocket.cpp
    Net/NetworkAdapter.cpp
    Net/E1000NetworkAdapter.cpp
    Net/LoopbackAdapter.cpp
    Net/Routing.cpp
    Net/NetworkTask.cpp
    ProcessTracer.cpp
    Devices/PCSpeaker.cpp
    File.o
)
serenity_kernel_flags(KernelCore)

add_library(
    KernelVFS

    FileSystem/ProcFS.cpp
    FileSystem/Inode.cpp
    Devices/DiskDevice.cpp
    Devices/Device.cpp
    Devices/CharacterDevice.cpp
    Devices/BlockDevice.cpp
    Devices/NullDevice.cpp
    Devices/FullDevice.cpp
    Devices/ZeroDevice.cpp
    Devices/RandomDevice.cpp
    Devices/DebugLogDevice.cpp
    FileSystem/FileSystem.cpp
    FileSystem/DiskBackedFileSystem.cpp
    FileSystem/Ext2FileSystem.cpp
    FileSystem/VirtualFileSystem.cpp
    FileSystem/FileDescriptor.cpp
    FileSystem/SyntheticFileSystem.o
)
serenity_kernel_flags(KernelVFS)

add_library(
    KernelAK

    ../AK/String.cpp
    ../AK/StringImpl.cpp
    ../AK/StringBuilder.cpp
    ../AK/StringView.cpp
    ../AK/FileSystemPath.cpp
    ../AK/StdLibExtras.cpp
)
serenity_kernel_flags(KernelAK)

add_executable(
    kernel
    null.cpp
)
add_custom_command(TARGET kernel PRE_LINK COMMAND i686-pc-serenity-as -o Boot/boot.ao Boot/boot.S)
add_custom_command(TARGET kernel POST_BUILD COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/mkmap.sh" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
serenity_kernel_flags(kernel)
target_link_libraries(kernel PUBLIC KernelCore KernelVFS KernelAK)
target_link_options(kernel PUBLIC -Ttext 0x10000 -Wl,-T linker.ld -nostdlib)

add_custom_target(run
    COMMAND sudo "${CMAKE_CURRENT_SOURCE_DIR}/sync.sh"
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/run"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
