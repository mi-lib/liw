LIW - Linux Wizard to assist system dependent operations on Linux
Copyright (C) 2000 Tomomichi Sugihara (Zhidao)

-----------------------------------------------------------------
[What is this?]

LIW is a library to assist your system-dependent programming
including:

 - kernel module operation
 - time management (measurement, periodic action, rtc handling)
 - process locking operation
 - coprocess operation
 - FIFO communication
 - socket communication
 - System V IPC (semaphore, shared memory, message queue)
 - dynamic link architecture

ZEDA is required.

-----------------------------------------------------------------
[Installation / Uninstallation]

<install>
0. Install ZEDA in advance.

1. Unpack the distributed archive where you want.

% zcat liw-X.Y.Z.tgz | tar xvf
or, if you use GNU tar,
% tar xzvf liw-X.Y.Z.tgz

X.Y.Z is for the revision.

2. Enter the directory.

% cd liw-X.Y.Z

3. Edit config file if necessary.
  PREFIX          directory where the library is installed.
                  ~/usr as a default. In this case, header files
                  and library are installed under ~/usr/include
                  and ~/usr/lib, respectively.

  CONFIG_USE_LIBDL to use dynamic link library. libdl is required.

  CONFIG_USE_PTHREAD to enable POSIX thread programming. libpthread is required.

  CONFIG_USE_RT  to use realtime extension. librt is required.

  COFIG_USE_RTC  to use enhanced realtime controller (RTC).
                 Check if /dev/rtc is available.

  Initially, the whole options are validated.

4. Make it.

% make

5. Install it.

% make install

Or,

% cp -a lib/libliw.so $PREFIX/lib/
% cp -a include/liw $PREFIX/include/
% cp -a bin/* $PREFIX/bin/

<uninstall>
Delete $PREFIX/lib/libliw.so and $PREFIX/include/liw.

-----------------------------------------------------------------
[How to use]

You may need to set your PATH and LD_LIBRARY_PATH environment
variables. This is done by:
 export PATH=$PATH:$PREFIX/bin
 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PREFIX/lib
if your working shell is Bourne shell (bash, zsh, etc.), or by:
 set path = ( $path $PREFIX/bin )
 setenv LD_LIBRARY_PATH $LD_LIBRARY_PATH:$PREFIX/lib
if your working shell is C shell (csh, tcsh, etc.).

When you want to compile your code test.c, for example, the following
line will work.

% gcc `liw-config -L` `liw-config -I` test.c `liw-config -l`

-----------------------------------------------------------------
[Contact]

zhidao@ieee.org
