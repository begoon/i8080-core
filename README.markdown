Intel 8080 (KR580VM80A) microprocessor core model
=================================================

[![GitHub Action](https://github.com/begoon/i8080-core/actions/workflows/build.yml/badge.svg)](https://github.com/begoon/i8080-core)

This project is an abstract logic model of the Intel 8080 microprocessor
written in C. To be more precise, this model replicates a clone of the original
Intel 8080 called KR580VM80A manufactured in Russia.

According to tests, this models works exactly the same way as the real
KR580VM80A including vaguely documented or even undocumented features.
The extensive "8080/8085 CPU Exerciser" test by Ian Bartholomew provides
strong guarantees of the match.

Build
-----

Use any standard C compiler, for example, GNU C, Visual Studio or TCC. But
the Makefile requires GNU Make.

Type `make`, and it should build and run the test suite. It must print out
the following:

    *********************************
    File "CPUTEST.COM" loaded, size 19200

    DIAGNOSTICS II V1.2 - CPU TEST
    COPYRIGHT (C) 1981 - SUPERSOFT ASSOCIATES

    ABCDEFGHIJKLMNOPQRSTUVWXYZ
    CPU IS 8080/8085
    BEGIN TIMING TEST
    END TIMING TEST
    CPU TESTS OK

    Jump to 0000 from 3B25

    *********************************
    File "TEST.COM" loaded, size 1793
    MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC VERSION 1.0  (C) 1980

    CPU IS OPERATIONAL
    Jump to 0000 from 014F

    *********************************
    File "8080PRE.COM" loaded, size 1024
    8080 Preliminary tests complete
    Jump to 0000 from 032F

    *********************************
    File "8080EX1.COM" loaded, size 4608
    8080 instruction exerciser (KR580VM80A CPU)
    dad <b,d,h,sp>................  OK
    aluop nn......................  OK
    aluop <b,c,d,e,h,l,m,a>.......  OK
    <daa,cma,stc,cmc>.............  OK
    <inr,dcr> a...................  OK
    <inr,dcr> b...................  OK
    <inx,dcx> b...................  OK
    <inr,dcr> c...................  OK
    <inr,dcr> d...................  OK
    <inx,dcx> d...................  OK
    <inr,dcr> e...................  OK
    <inr,dcr> h...................  OK
    <inx,dcx> h...................  OK
    <inr,dcr> l...................  OK
    <inr,dcr> m...................  OK
    <inx,dcx> sp..................  OK
    lhld nnnn.....................  OK
    shld nnnn.....................  OK
    lxi <b,d,h,sp>,nnnn...........  OK
    ldax <b,d>....................  OK
    mvi <b,c,d,e,h,l,m,a>,nn......  OK
    mov <bcdehla>,<bcdehla>.......  OK
    sta nnnn / lda nnnn...........  OK
    <rlc,rrc,ral,rar>.............  OK
    stax <b,d>....................  OK
    Tests complete
    Jump to 0000 from 0137

Tests
-----

The test suite includes four tests at the moment:

* 8080/8085 CPU Diagnostic, version 1.0, by Microcosm Associates (file 
  `TEST.COM`)

* Diagnostics II, version 1.2, CPU test by Supersoft Associates (file 
  `CPUTEST.COM`)

* [8080/8085 CPU Exerciser][] by Ian Bartholomew and Frank Cringles

  * The preliminary test (file `8080PRE.COM`).
  * The basic excerciser (file `8080EX1.COM`). This file is a copy of the
    vanilla `8080EXER.COM` file having CRCs from the real KR580VM80A
    contributed by Alexander Timoshenko and Viacheslav Slavinsky.

[8080/8085 CPU Exerciser]: http://www.idb.me.uk/sunhillow/8080.html

All tests pass.

Note
----

Unfortunately, the current implementation needs the little-endian system
to run properly. It uses unions to mix different data types, and such
technique is not portable across little- and big-endian systems. Fortunately,
most of popular desktop systems running Windows and OSX are based on Intel
x86/64 which is little endian. Also, this emulator was tested on the PIC32
platform (little endian as well).

Usage
-----

The implemention of the Intel 8080 model is self-contained and independent.
It only requires the `i8080_hal.h` header providing the hardware abstraction
layer.

The example of use is the test suite (`i8080_test.c` and `i8080_hal.c`).
It creates bare miminum hardware plumbing to run tests.

WASM
----

The code can be also built on the WebAssembly platform using [emscripten][]:

    make build-wasm

Run WebAssembly test suite in the command line (`node` executable is required):

    make run-node

To run the test suite in the browser, start the local web server:

    make web-browser

In the browser, open the URL [http://localhost:8000/i8080_test.html](http://localhost:8000/i8080_test.html) or in another terminal run:

    make run-web

Credits
-------

* Viacheslav Slavinsky, [Vector-06C FPGA Replica][]
* Dmitry Tselikov, [Bashrikia-2M and Radio-86RK on Altera DE1][]
* Ian Bartholomew, [8080/8085 CPU Exerciser][]
* Frank Cringle, The original exerciser for the Z80
* [zx.pk.ru][] and [nedopc.org/forum][] communities

[Vector-06C FPGA Replica]: http://code.google.com/p/vector06cc/
[Bashrikia-2M and Radio-86RK on Altera DE1]: http://bashkiria-2m.narod.ru/fpga.html
[8080/8085 CPU Exerciser]: http://www.idb.me.uk/sunhillow/8080.html
[zx.pk.ru]: http://zx.pk.ru
[nedopc.org/forum]: http://nedopc.org/forum
[emscripten]: https://emscripten.org/

Links
-----

* [Серия микросхем КР580][]

[Серия микросхем КР580]: http://demin.ws/projects/radio86/info/kr580/
