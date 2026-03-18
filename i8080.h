// Intel 8080 (KR580VM80A) microprocessor core model
//
// Copyright (C) 2012 Alexander Demin <alexander@demin.ws>
//
// Credits
//
// Viacheslav Slavinsky, Vector-06C FPGA Replica
// http://code.google.com/p/vector06cc/
//
// Dmitry Tselikov, Bashrikia-2M and Radio-86RK on Altera DE1
// http://bashkiria-2m.narod.ru/fpga.html
//
// Ian Bartholomew, 8080/8085 CPU Exerciser
// http://www.idb.me.uk/sunhillow/8080.html
//
// Frank Cringle, The original exerciser for the Z80.
//
// Thanks to zx.pk.ru and nedopc.org/forum communities.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#ifndef I8080_H
#define I8080_H

typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct {
    u8 carry_flag;
    u8 unused1;
    u8 parity_flag;
    u8 unused3;
    u8 half_carry_flag;
    u8 unused5;
    u8 zero_flag;
    u8 sign_flag;
} i8080_flags;

typedef struct {
    i8080_flags f;
    u8 a, flags;
    u8 b, c;
    u8 d, e;
    u8 h, l;
    u16 sp, pc;
    u16 iff;
} i8080_state;

extern void i8080_init(i8080_state *cpu);
extern int i8080_instruction(i8080_state *cpu);

extern void i8080_jump(i8080_state *cpu, int addr);
extern int i8080_pc(i8080_state *cpu);

extern int i8080_regs_bc(i8080_state *cpu);
extern int i8080_regs_de(i8080_state *cpu);
extern int i8080_regs_hl(i8080_state *cpu);
extern int i8080_regs_sp(i8080_state *cpu);

extern int i8080_regs_a(i8080_state *cpu);
extern int i8080_regs_b(i8080_state *cpu);
extern int i8080_regs_c(i8080_state *cpu);
extern int i8080_regs_d(i8080_state *cpu);
extern int i8080_regs_e(i8080_state *cpu);
extern int i8080_regs_h(i8080_state *cpu);
extern int i8080_regs_l(i8080_state *cpu);

#endif
