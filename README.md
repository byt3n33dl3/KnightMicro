# Friendly like a Pony

```shell
Knight Cavalry      /
               ,.. /
             ,'   ';
  ,,.__    _,' /';  .
 :','  ~~~~    '. '~
:' (   )         )::,
'. '. .=----=..-~  .;'
 '  ;'  ::   ':.  '"
   (:   ':    ;)
    \\   '"  ./
     '"      '"
--------------------
```

**KnightMicro** is an implementation of an advanced payload written in pure C and designed for portability and extensibility.

This repository contains KnightMicro, which is supposed to work on *MacOS*, *Linux*, *Windows* and *iOS*, but can be ported to almost every POSIX system. KnightMicro is optimized to work with or without [HatSploit](https://github.com/EntySec/HatSploit) Framework.

## Features

* Portable C code that can be compiled for a big range of targets.
* Support for *MacOS*, *Linux*, *Windows* and *iOS* targets.
* Small executable with low resource utilization optimized for embedded systems.
* Dynamically Extendable, supports loading plugins (TABs) which extend its functionality.
* Evasion techniques such as process migration and in-memory loading.

## Installing

To install KnightMicro you simply need to install [HatSploit](https://github.com/EntySec/HatSploit) Framework and this will make KnightMicro available automatically.

```python
pip3 install git+https://github.com/EntySec/HatSploit
```

## Building

**Building dependencies:**

```shell
make TARGET=<target>
```

**NOTE:** For *MacOS / iOS* targets you are required to set `SDK` to the desired SDK path before running `make`. For example:

```shell
make TARGET=<target> SDK=<path>
```

You can find list of supported `TARGET` values for different platforms.

<details>
    <summary>Linux</summary><br>
    <code>aarch64-linux-musl</code><br>
    <code>armv5l-linux-musleabi</code><br>
    <code>armv5b-linux-musleabi</code><br>
    <code>i486-linux-musl</code><br>
    <code>x86_64-linux-musl</code><br>
    <code>powerpc-linux-muslsf</code><br>
    <code>powerpc64le-linux-musl</code><br>
    <code>mips-linux-muslsf</code><br>
    <code>mipsel-linux-muslsf</code><br>
    <code>mips64-linux-musl</code><br>
    <code>s390x-linux-musl</code><br>
    <br>
</details>

<details>
    <summary>Windows</summary><br>
    <code>x86_64-w64-mingw32</code><br>
    <code>x86_64-w64-mingw32</code><br>
    <br>
</details>

<details>
    <summary>MacOS / iOS</summary><br>
    <code>arm-iphone-darwin</code><br>
    <code>aarch64-iphone-darwin</code><br>
    <code>i386-apple-darwin</code><br>
    <code>x86_64-apple-darwin</code><br>
    <code>aarch64-apple-darwin</code><br>
    <br>
</details>

**Building sources:**

```shell
cmake -DCMAKE_TOOLCHAIN_FILE=<toolchain> -B build
cmake --build build
```

**NOTE:** For *MacOS / iOS* targets you are required to set `CMAKE_OSX_SYSROOT` to the desired SDK path with `-D`. For example:

```shell
cmake -DCMAKE_TOOLCHAIN_FILE=<toolchain> -DCMAKE_OSX_SYSROOT=<path> -B build
```

**NOTE:** Toolchains are located at `toolchain/cmake/`.

These are other `cmake` build options:

* `MAIN` - Should be `ON` if you want to build a source file to executable.
* `SOURCE` - Custom executable source file (default are in `src/main/`).
* `DEBUG` - Should be `ON` if you want to build KnightMicro in debug mode.
* `BUNDLE` - Build as bundle (macOS specific flag, adds `-bundle`)

## Basic usage

To use KnightMicro and build payloads you should import it to your source.

```python3
from KnightMicro import KnightMicro
from KnightMicro.session import KnightMicroSession
```

* `KnightMicro` - KnightMicro object that is used to generate payload implant.

```python3
KnightMicro = KnightMicro(
    target='aarch64-apple-darwin',
    options={
        'uri': 'tcp://127.0.0.1:8888'
    }
)

with open('payload.exe', 'wb') as f:
    f.write(KnightMicro.to_binary())
```

* `KnightMicroSession` - Wrapper for `HatSploitSession` for KnightMicro, HatSploit should use it with KnightMicro payload. It might also be used without HatSploit as demonstrated in `examples/listener.py`.

## Projects

* [SeaShell](https://github.com/EntySec/SeaShell) Framework - iOS post-exploitation framework that enables you to access the device remotely, control it and extract sensitive information. SeaShell actively uses KnightMicro implant to communicate with iOS.

## Caveats

The code provided in this repository has not yet been prepared for use in a production environment. It can be improved, so any contribution is welcome. You can even experience memory leaks, so we'll be glad to accept every single PR which is fixing a potential issue.

# Thanks To
>- EntySec
