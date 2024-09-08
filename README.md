# MiniFB

A condensed fork of the [original minifb](https://github.com/emoon/minifb) used as the native library part of the actual [managed MiniFB library](https://github.com/fruediger/MiniFB).

## Build

Atm. OS-specific builds are done from those operating system itself. While cross-OS builds might be possible, they are currently not recommended.

### Shared requirements

- CMake (at least 3.7, I believe)

### On Windows/for Windows

#### Requirements

- MS Visual Studio, but at least MSVC
- Windows SDK
- Visual C++ Redistributable (2015+)

#### Setup

> tested on:
>
> - Windows 11 x64
> - Visual Studio 17.10.6
> - MSVC 19.40
> - Windows SDK 10.0.22621.0

While other compiler toolchains might work, it's recommended to use MSVC instead of, e.g. a MinGW GCC toolchain. MSVC makes cross-architecture building way easier while also often producing better assemblies (at least on Windows).

For `x64` from `x64` run from a commandline:

```console
$ cmake -G "Visual Studio 17 2022" -A x64 -B build/x64
```

<details>
<summary>x86</summary>

For `x86` from `x64` run from a commandline:

```console
$ cmake -G "Visual Studio 17 2022" -A Win32 -B build/Win32
```

</details>

<details>
<summary>arm64</summary>

For `arm64` from `x64` run from a commandline:

```console
$ cmake -G "Visual Studio 17 2022" -A arm64 -B build/arm64
```

</details>

<details>
<summary>arm</summary>

For `arm` from `x64` run from a commandline:

```console
$ cmake -G "Visual Studio 17 2022" -A arm -B build/arm
```

</details>

#### Building

For `x64` from `x64` run from a commandline:

```console
$ cmake --build build/x64 --config Release
```

<details>
<summary>x86</summary>

For `x86` from `x64` run from a commandline:

```console
$ cmake --build build/Win32 --config Release
```

</details>

<details>
<summary>arm64</summary>

For `arm64` from `x64` run from a commandline:

```console
$ cmake --build build/arm64 --config Release
```

</details>

<details>
<summary>arm</summary>

For `arm` from `x64` run from a commandline:

```console
$ cmake --build build/arm --config Release
```

</details>

### On Linux/for Linux

#### Requirements

- A GCC toolchain
  - plus GCC toolchain for your target architecture, if you want to cross compile
- Development versions of the library dependencies
  - for the X11 variant this should only really be libX11 and libGL
  - plus those development libraries for your target architecture, if you want to cross compile

#### Setup

> tested on:
>
> - Ubuntu 24.04 x64
> - GCC 14.0.1 (same version for all architectures)

For `amd64` from `x64` run from a commandline:

```console
$ cmake -B build/amd64 -DCMAKE_BUILD_TYPE=Release
```

> [!NOTE]
> Since this not a cross-compiling (`amd64` from `x64`), nothing special is required to setup the build.

<details>
<summary>x86 (i686)</summary>

For `i686` from `x64` run from a commandline

```console
$ cmake -DCMAKE_TOOLCHAIN_FILE=generic-cross-gcc-toolchain.cmake -DCROSS_SYSTEM_PROCESSOR=i686 -DCROSS_TOOLCHAIN_PREFIX=i686-linux-gnu -B build/i686 -DCMAKE_BUILD_TYPE=Release
```

</details>

<details>
<summary>arm64 (aarch64)</summary>

For `aarch64` from `x64` run from a commandline

```console
$ cmake -DCMAKE_TOOLCHAIN_FILE=generic-cross-gcc-toolchain.cmake -DCROSS_SYSTEM_PROCESSOR=aarch64 -DCROSS_TOOLCHAIN_PREFIX=aarch64-linux-gnu -B build/aarch64 -DCMAKE_BUILD_TYPE=Release
```

</details>

<details>
<summary>arm (armhf)</summary>

For `armhf` from `x64` run from a commandline

```console
$ cmake -DCMAKE_TOOLCHAIN_FILE=generic-cross-gcc-toolchain.cmake -DCROSS_SYSTEM_PROCESSOR=armhf -DCROSS_TOOLCHAIN_PREFIX=arm-linux-gnueabihf -B build/armhf -DCMAKE_BUILD_TYPE=Release
```

</details>

#### Building

For `amd64` from `x64` run from a commandline:

```console
$ cmake --build build/amd64 --config Release
```

<details>
<summary>x86 (i686)</summary>

For `i686` from `x64` run from a commandline

```console
$ cmake --build build/i686 --config Release
```

</details>

<details>
<summary>arm64 (aarch64)</summary>

For `aarch64` from `x64` run from a commandline

```console
$ cmake --build build/aarch64 --config Release
```

</details>

<details>
<summary>arm (armhf)</summary>

For `armhf` from `x64` run from a commandline

```console
$ cmake --build build/armhf --config Release
```

</details>

### Other operating systems

While other configurations and other operating systems are technically supported, they're not tested yet and also the [managed MiniFB library](https://github.com/fruediger/MiniFB) does not yet make use of them.

There are also configuration where it is known that those require some fixing (like Linux Wayland for example).

Therefore no instructions on how to compile for those platforms are given.

This might change in the future, but until then it's simply not recommended to blindly issue such builds. You are on your own with that.
