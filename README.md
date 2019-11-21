LIW - Linux Wizard to assist system dependent operations on Linux
=================================================================
Copyright (C) Tomomichi Sugihara (Zhidao) since 2000

-----------------------------------------------------------------
## [What is this?]

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

ZEDA is required to be installed.

-----------------------------------------------------------------
## [Installation / Uninstallation]

### install

Install ZEDA in advance.

Move to a directly under which you want to install LIW, and run:

   ```
   % git clone https://github.com/zhidao/liw.git
   % cd liw
   ```

Edit *config* file if necessary.

   **PREFIX** : specify a directory where the header files, the
   library and some utilities are installed. (default: ~/usr)
   - header files: $PREFIX/include/liw
   - library file: $PREFIX/lib
   - utilities: $PREFIX/bin

   **CONFIG\_USE\_LIBDL** : to use dynamic link library.
   libdl is required. (default: y)

   **CONFIG\_USE\_PTHREAD** : to enable POSIX thread programming.
   libpthread is required. (default: y)

   **CONFIG\_USE\_RT** : to use realtime extension.
   librt is required. (default: y)

   **COFIG\_USE\_RTC** : to use enhanced realtime controller (RTC).
   Check if /dev/rtc is available. (default: y)

Then, make and install.

   ```
   % make && make install
   ```

## uninstall

Do:

   ```
   % make uninstall
   ```

which removes $PREFIX/lib/libliw.so and $PREFIX/include/liw.

-----------------------------------------------------------------
## [How to use]

When you want to compile your code *test.c*, for example, the following
line will work.

   ```
   % gcc `liw-config -L` `liw-config -I` test.c `liw-config -l`
   ```

-----------------------------------------------------------------
## [Contact]

zhidao@ieee.org
