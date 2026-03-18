Intel 8080 (KR580VM80A) microprocessor core model
=================================================

[![build](https://github.com/begoon/i8080-core/actions/workflows/build.yml/badge.svg)](https://github.com/begoon/i8080-core/actions/workflows/build.yml)

An abstract logic model of the Intel 8080 microprocessor written in C.
More precisely, this model replicates a clone of the original Intel 8080
called KR580VM80A, manufactured in Russia.

According to tests, this model behaves exactly like the real KR580VM80A,
including vaguely documented and even undocumented features. The extensive
"8080/8085 CPU Exerciser" test by Ian Bartholomew provides strong
guarantees of correctness.

Design
------

The emulator separates CPU state from the execution logic. The CPU state
is represented by the `i8080_state` struct, which the caller allocates and
passes to all emulator functions. The executor itself is stateless -- it
reads and modifies only the state provided to it. This makes it possible to
run multiple independent CPU instances simultaneously, serialize and restore
state, and simplifies testing.

The register representation is endian-independent. Register pairs are
composed and decomposed using explicit bit shifts and masks rather than
unions, so the emulator runs correctly on both little-endian and big-endian
architectures.

Memory and I/O access is abstracted through a hardware abstraction layer
(`i8080_hal.h`). The emulator core has no dependencies beyond this HAL,
making it straightforward to embed into different environments.

Build
-----

Use any standard C compiler, for example, GCC, Clang, or MSVC. The
Makefile requires GNU Make.

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

The test suite includes four tests:

* 8080/8085 CPU Diagnostic, version 1.0, by Microcosm Associates (file
  `TEST.COM`)

* Diagnostics II, version 1.2, CPU test by Supersoft Associates (file
  `CPUTEST.COM`)

* [8080/8085 CPU Exerciser][] by Ian Bartholomew and Frank Cringle

  * The preliminary test (file `8080PRE.COM`).
  * The full exerciser (file `8080EX1.COM`). This file is a copy of the
    vanilla `8080EXER.COM` with CRCs from the real KR580VM80A, contributed
    by Alexander Timoshenko and Viacheslav Slavinsky.

All tests pass.

Usage
-----

The implementation of the Intel 8080 model is self-contained and
independent. It only requires the `i8080_hal.h` header providing the
hardware abstraction layer.

The test suite (`i8080_test.c` and `i8080_hal.c`) serves as a usage
example. It creates the bare minimum hardware plumbing to run tests.

WASM
----

The code can also be built for WebAssembly using [emscripten][]:

    make build-wasm

Run the WebAssembly test suite from the command line (`bun` is required):

    make run-wasm

To run the test suite in a browser, start a local web server:

    make web-server

Then open [http://localhost:8000/i8080_test.html](http://localhost:8000/i8080_test.html), or in another terminal run:

    make run-web

Benchmark
---------

Full test suite run time (all four tests) on Apple M1, 16 GB RAM:

| Build                          | Compiler / Runtime                | Time   |
|--------------------------------|-----------------------------------|--------|
| Native (`-O3`)                 | Apple Clang 17.0.0               | ~16s   |
| Native (`-O3 -flto`)           | Apple Clang 17.0.0               | ~10s   |
| WASM (`-O3`)                   | Emscripten + Bun 1.3.10          | ~10s   |

The native build without LTO is significantly slower because the HAL
functions (`i8080_hal_memory_read_byte`, etc.) are in a separate
translation unit and cannot be inlined. With `-flto`, the linker inlines
them across files, closing the gap with WASM where Emscripten enables LTO
by default.

Credits
-------

* Viacheslav Slavinsky, [Vector-06C FPGA Replica][]
* Dmitry Tselikov, [Bashrikia-2M and Radio-86RK on Altera DE1][]
* Ian Bartholomew, [8080/8085 CPU Exerciser][]
* Frank Cringle, the original exerciser for the Z80
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

License
-------

GNU General Public License v2.0 or later. See [LICENSE](LICENSE) for details.
