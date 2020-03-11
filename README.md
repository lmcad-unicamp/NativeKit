[![GNU LGPL v3.0](http://www.gnu.org/graphics/lgplv3-88x31.png)](http://www.gnu.org/licenses/lgpl.html)

### About
<p style="text-indent: 2em;" align="justify">
A virtual machine is a computer program that emulates an interface to another application. This technology is present in many computer systems and has been used from the support of high-level programming languages, such as the Java virtual machine, to the implementation of processor with integrated hardware and software design, such as the Transmeta's Efficeon processor.
</p>

<p style="text-indent: 2em;" align="justify">
In an attempt to improve the overall performance, some specific types of virtual machines may need privileged access to resources managed by the operating system. Consequently, because of this need for greater privileged access, some virtual machines rely on a native design, running directly on the hardware. This approach, despite the complexity, enables a reduction of the software stack, present between the virtual machine and the hardware. Moreover, this solution eliminates the restrictions on the device access and the competition for resource utilization.
</p>

<p style="text-indent: 2em;" align="justify">
Despite the flexibility afforded by a native architecture, there is a price to pay when we choose this kind of solution. Implementing an application without the abstraction provided by an operating system is a complex task, susceptible to errors and can seriously impair portability. Therefore, we believe that a minimum infrastructure, capable of abstracting the essential hardware and providing a POSIX interface, could simplify the design of new native virtual machines.
</p>

<p style="text-indent: 2em;" align="justify">
In this work we present the Native Kit, a modular infrastructure, compatible with the POSIX standard and built to support the implementation and execution of native virtual machines. All modules were designed to avoid dependencies, making this infrastructure simple, flexible and able to adapt to different design requirements of native virtual machines. In addition, to confirm and to show how our infrastructure works in practice, we present two test applications that can run directly on bare-metal, without an operating system. These applications can be used as a starting point to build new native virtual machines,  contributing to develop of several related research.
</p>

### Installation
Before you start, make sure you have the follow packages installed:

1. gcc
2. g++
3. nasm
4. cmake
5. grub
6. GNU GMP
7. GNU MPFR
8. ISL
9. ClooG
10. GNU MPC
11. GNU Texinfo
12. qemu
13. genisoimage
14. build-essential

then, type:

```sh
. ./config.sh
make
make test
```

For better compatibility I recommend a debian-based-i386 distro: Debian, Ubuntu, Lubuntu, Xubuntu or Kubuntu.

### Utilization
1. To check the instalation, type:
```sh
make
make test
```

2. To compile and execute the default kernel (/src/kernel.cpp), type:
```sh
make
make run
```
### Demo
Turning an x86 computer into a Nintendo 8-bits.

[![](https://i.ytimg.com/vi/jj--cF3suvU/3.jpg?time=1441224313074)](https://www.youtube.com/embed/jj--cF3suvU)
