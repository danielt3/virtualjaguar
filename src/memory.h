//
// MEMORY.H: Header file
//
// All Jaguar related memory and I/O locations are contained in this file
//

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "types.h"

extern uint8 jagMemSpace[];

extern uint8 * jaguarMainRAM;
extern uint8 * jaguarMainROM;
extern uint8 jaguarBootROM[];
extern uint8 jaguarCDBootROM[];
extern uint8 * gpuRAM;
extern uint8 * dspRAM;

extern uint16 & memcon1, & memcon2, & hc, & vc, & lph, & lpv;

#if 1
extern uint32 & butch, & dscntrl;
extern uint16 & ds_data;
extern uint32 & i2cntrl, & sbcntrl, & subdata, & subdatb, & sb_time, & fifo_data, & i2sdat2, & unknown;
#else
extern uint32 butch, dscntrl, ds_data, i2cntrl, sbcntrl, subdata, subdatb, sb_time, fifo_data, i2sdat2, unknown;
#endif

extern uint32 obData, olp, obf, vmode, bord1, bord2, hp, hbb, hbe, hs, hvs,
	hdb1, hdb2, hde, vp, vbb, vbe, vs, vdb, vde, veb, vee, vi, pit0, pit1, heq, bg, int1, int2, clut, lbuf,
	g_flags, g_mtxc, g_mtxa, g_end, g_pc, g_ctrl, g_hidata, g_remain, g_divctrl,
	a1_base, a1_pixel, a1_flags, a1_clip, a1_step, a1_fstep, a1_fpixel, a1_inc, a1_finc,
	a2_base, a2_flags, a2_pixel, a2_mask, a2_step, b_cmd, b_count, b_srcd, b_dstd, b_dstz, b_srcz1, b_srcz2,
	b_patd, b_iinc, b_zinc, b_stop, b_i3, b_i2, b_i1, b_i0, b_z3, b_z2, b_z1, b_z0,
	jpit1, jpit2, jpit3, jpit4, clk1, clk2, clk3, j_int, asidata, asistat, asictrl, asiclk, joystick,
	joybuts, d_flags, d_mtxc, d_mtxa, d_end, d_pc, d_ctrl, d_mod, d_remain, d_divctrl, d_machi,
	ltxd, rtxd, sstat, sclk, smode;

// Read/write tracing enumeration

enum { UNKNOWN, JAGUAR, DSP, GPU, TOM, JERRY, M68K, BLITTER, OP };
extern const char * whoName[9];

// Some handy macros to help converting native endian to big endian (jaguar native)
// & vice versa

#define SET64(r, a, v) 	r[(a)] = ((v) & 0xFF00000000000000) >> 56, r[(a)+1] = ((v) & 0x00FF000000000000) >> 48, \
						r[(a)+2] = ((v) & 0x0000FF0000000000) >> 40, r[(a)+3] = ((v) & 0x000000FF00000000) >> 32, \
						r[(a)+4] = ((v) & 0xFF000000) >> 24, r[(a)+5] = ((v) & 0x00FF0000) >> 16, \
						r[(a)+6] = ((v) & 0x0000FF00) >> 8, r[(a)+7] = (v) & 0x000000FF
#define GET64(r, a)		(((uint64)r[(a)] << 56) | ((uint64)r[(a)+1] << 48) | \
						((uint64)r[(a)+2] << 40) | ((uint64)r[(a)+3] << 32) | \
						((uint64)r[(a)+4] << 24) | ((uint64)r[(a)+5] << 16) | \
						((uint64)r[(a)+6] << 8) | (uint64)r[(a)+7])
#define SET32(r, a, v)	r[(a)] = ((v) & 0xFF000000) >> 24, r[(a)+1] = ((v) & 0x00FF0000) >> 16, \
						r[(a)+2] = ((v) & 0x0000FF00) >> 8, r[(a)+3] = (v) & 0x000000FF
#define GET32(r, a)		((r[(a)] << 24) | (r[(a)+1] << 16) | (r[(a)+2] << 8) | r[(a)+3])
#define SET16(r, a, v)	r[(a)] = ((v) & 0xFF00) >> 8, r[(a)+1] = (v) & 0xFF
#define GET16(r, a)		((r[(a)] << 8) | r[(a)+1])

// This is GCC specific, but we can fix that if we need to...
// Big plus of this approach is that these compile down to single instructions on little
// endian machines while one big endian machines we don't have any overhead. :-)

#include <byteswap.h>
#include <endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
	#define ESAFE16(x)	bswap_16(x)
	#define ESAFE32(x)	bswap_32(x)
	#define ESAFE64(x)	bswap_64(x)
#else
	#define ESAFE16(x)	(x)
	#define ESAFE32(x)	(x)
	#define ESAFE64(x)	(x)
#endif

#endif	// __MEMORY_H__
