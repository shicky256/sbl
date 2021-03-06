/*	Copyright(c) 1994 SEGA			*/
/*
 *
 * なんでもありの関数群
 *
 */


#include "smp_bios.h"


/*
 *  PutHexNum32関数用１６進->アスキーキャラクタテーブル
 */
const Sint16 SMMI_hexchr_tbl[] = {
    ('0' - ' '), ('1' - ' '), ('2' - ' '), ('3' - ' '),
    ('4' - ' '), ('5' - ' '), ('6' - ' '), ('7' - ' '),
    ('8' - ' '), ('9' - ' '), ('A' - ' '), ('B' - ' '),
    ('C' - ' '), ('D' - ' '), ('E' - ' '), ('F' - ' '),
    };


/*
 *   sin table ($FF00...$0100)
 */
const Sint16 SMMI_sintbl8[] = {
	0x0000,0x0006,0x000C,0x0012,0x0019,0x001F,0x0025,0x002B,
	0x0031,0x0038,0x003E,0x0044,0x004A,0x0050,0x0056,0x005C,
	0x0061,0x0067,0x006D,0x0073,0x0078,0x007E,0x0083,0x0088,
	0x008E,0x0093,0x0098,0x009D,0x00A2,0x00A7,0x00AB,0x00B0,
	0x00B5,0x00B9,0x00BD,0x00C1,0x00C5,0x00C9,0x00CD,0x00D1,
	0x00D4,0x00D8,0x00DB,0x00DE,0x00E1,0x00E4,0x00E7,0x00EA,
	0x00EC,0x00EE,0x00F1,0x00F3,0x00F4,0x00F6,0x00F8,0x00F9,
	0x00FB,0x00FC,0x00FD,0x00FE,0x00FE,0x00FF,0x00FF,0x00FF,
	
	0x0100,0x00FF,0x00FF,0x00FF,0x00FE,0x00FE,0x00FD,0x00FC,
	0x00FB,0x00F9,0x00F8,0x00F6,0x00F4,0x00F3,0x00F1,0x00EE,
	0x00EC,0x00EA,0x00E7,0x00E4,0x00E1,0x00DE,0x00DB,0x00D8,
	0x00D4,0x00D1,0x00CD,0x00C9,0x00C5,0x00C1,0x00BD,0x00B9,
	0x00B5,0x00B0,0x00AB,0x00A7,0x00A2,0x009D,0x0098,0x0093,
	0x008E,0x0088,0x0083,0x007E,0x0078,0x0073,0x006D,0x0067,
	0x0061,0x005C,0x0056,0x0050,0x004A,0x0044,0x003E,0x0038,
	0x0031,0x002B,0x0025,0x001F,0x0019,0x0012,0x000C,0x0006,
	
	0x0000,0xFFFA,0xFFF4,0xFFEE,0xFFE7,0xFFE1,0xFFDB,0xFFD5,
	0xFFCF,0xFFC8,0xFFC2,0xFFBC,0xFFB6,0xFFB0,0xFFAA,0xFFA4,
	0xFF9F,0xFF99,0xFF93,0xFF8B,0xFF88,0xFF82,0xFF7D,0xFF78,
	0xFF72,0xFF6D,0xFF68,0xFF63,0xFF5E,0xFF59,0xFF55,0xFF50,
	0xFF4B,0xFF47,0xFF43,0xFF3F,0xFF3B,0xFF37,0xFF33,0xFF2F,
	0xFF2C,0xFF28,0xFF25,0xFF22,0xFF1F,0xFF1C,0xFF19,0xFF16,
	0xFF14,0xFF12,0xFF0F,0xFF0D,0xFF0C,0xFF0A,0xFF08,0xFF07,
	0xFF05,0xFF04,0xFF03,0xFF02,0xFF02,0xFF01,0xFF01,0xFF01,
	
	0xFF00,0xFF01,0xFF01,0xFF01,0xFF02,0xFF02,0xFF03,0xFF04,
	0xFF05,0xFF07,0xFF08,0xFF0A,0xFF0C,0xFF0D,0xFF0F,0xFF12,
	0xFF14,0xFF16,0xFF19,0xFF1C,0xFF1F,0xFF22,0xFF25,0xFF28,
	0xFF2C,0xFF2F,0xFF33,0xFF37,0xFF3B,0xFF3F,0xFF43,0xFF47,
	0xFF4B,0xFF50,0xFF55,0xFF59,0xFF5E,0xFF63,0xFF68,0xFF6D,
	0xFF72,0xFF78,0xFF7D,0xFF82,0xFF88,0xFF8B,0xFF93,0xFF99,
	0xFF9F,0xFFA4,0xFFAA,0xFFB0,0xFFB6,0xFFBC,0xFFC2,0xFFC8,
	0xFFCF,0xFFD5,0xFFDB,0xFFE1,0xFFE7,0xFFEE,0xFFF4,0xFFFA,
	
	0x0000,0x0006,0x000C,0x0012,0x0019,0x001F,0x0025,0x002B,
	0x0031,0x0038,0x003E,0x0044,0x004A,0x0050,0x0056,0x005C,
	0x0061,0x0067,0x006D,0x0073,0x0078,0x007E,0x0083,0x0088,
	0x008E,0x0093,0x0098,0x009D,0x00A2,0x00A7,0x00AB,0x00B0,
	0x00B5,0x00B9,0x00BD,0x00C1,0x00C5,0x00C9,0x00CD,0x00D1,
	0x00D4,0x00D8,0x00DB,0x00DE,0x00E1,0x00E4,0x00E7,0x00EA,
	0x00EC,0x00EE,0x00F1,0x00F3,0x00F4,0x00F6,0x00F8,0x00F9,
	0x00FB,0x00FC,0x00FD,0x00FE,0x00FE,0x00FF,0x00FF,0x00FF,
	};
	
/*
 *	sin table 0000...4096
 */
const Sint16 SMMI_sintbl3[] = {
	0x0000,0x0065,0x00C9,0x012E,0x0192,0x01F7,0x025B,0x02C0,
	0x0324,0x0388,0x03ED,0x0451,0x04B5,0x051A,0x057E,0x05E2,
	0x0646,0x06AA,0x070E,0x0772,0x07D6,0x0839,0x089D,0x0901,
	0x0964,0x09C7,0x0A2B,0x0A8E,0x0AF1,0x0B54,0x0BB7,0x0C1A,
	0x0C7C,0x0CDF,0x0D41,0x0DA4,0x0E06,0x0E68,0x0ECA,0x0F2B,
	0x0F8D,0x0FEE,0x1050,0x10B1,0x1112,0x1173,0x11D3,0x1234,
	0x1294,0x12F4,0x1354,0x13B4,0x1413,0x1473,0x14D2,0x1531,
	0x1590,0x15EE,0x164C,0x16AB,0x1709,0x1766,0x17C4,0x1821,
	0x187E,0x18DB,0x1937,0x1993,0x19EF,0x1A4B,0x1AA7,0x1B02,
	0x1B5D,0x1BB8,0x1C12,0x1C6C,0x1CC6,0x1D20,0x1D79,0x1DD3,
	0x1E2B,0x1E84,0x1EDC,0x1F34,0x1F8C,0x1FE3,0x203A,0x2091,
	0x20E7,0x213D,0x2193,0x21E8,0x223D,0x2292,0x22E7,0x233B,
	0x238E,0x23E2,0x2435,0x2488,0x24DA,0x252C,0x257E,0x25CF,
	0x2620,0x2671,0x26C1,0x2711,0x2760,0x27AF,0x27FE,0x284C,
	0x289A,0x28E7,0x2935,0x2981,0x29CE,0x2A1A,0x2A65,0x2AB0,
	0x2AFB,0x2B45,0x2B8F,0x2BD8,0x2C21,0x2C6A,0x2CB2,0x2CFA,
	0x2D41,0x2D88,0x2DCF,0x2E15,0x2E5A,0x2E9F,0x2EE4,0x2F28,
	0x2F6C,0x2FAF,0x2FF2,0x3034,0x3076,0x30B8,0x30F9,0x3139,
	0x3179,0x31B9,0x31F8,0x3236,0x3274,0x32B2,0x32EF,0x332C,
	0x3368,0x33A3,0x33DF,0x3419,0x3453,0x348D,0x34C6,0x34FF,
	0x3537,0x356E,0x35A5,0x35DC,0x3612,0x3648,0x367D,0x36B1,
	0x36E5,0x3718,0x374B,0x377E,0x37B0,0x37E1,0x3812,0x3842,
	0x3871,0x38A1,0x38CF,0x38FD,0x392B,0x3958,0x3984,0x39B0,
	0x39DB,0x3A06,0x3A30,0x3A59,0x3A82,0x3AAB,0x3AD3,0x3AFA,
	0x3B21,0x3B47,0x3B6D,0x3B92,0x3BB6,0x3BDA,0x3BFD,0x3C20,
	0x3C42,0x3C64,0x3C85,0x3CA5,0x3CC5,0x3CE4,0x3D03,0x3D21,
	0x3D3F,0x3D5B,0x3D78,0x3D93,0x3DAF,0x3DC9,0x3DE3,0x3DFC,
	0x3E15,0x3E2D,0x3E45,0x3E5C,0x3E72,0x3E88,0x3E9D,0x3EB1,
	0x3EC5,0x3ED8,0x3EEB,0x3EFD,0x3F0F,0x3F20,0x3F30,0x3F40,
	0x3F4F,0x3F5D,0x3F6B,0x3F78,0x3F85,0x3F91,0x3F9C,0x3FA7,
	0x3FB1,0x3FBB,0x3FC4,0x3FCC,0x3FD4,0x3FDB,0x3FE1,0x3FE7,
	0x3FEC,0x3FF1,0x3FF5,0x3FF8,0x3FFB,0x3FFD,0x3FFF,0x4000,
	0x4000,0x4000,0x3FFF,0x3FFD,0x3FFB,0x3FF8,0x3FF5,0x3FF1,
	0x3FEC,0x3FE7,0x3FE1,0x3FDB,0x3FD4,0x3FCC,0x3FC4,0x3FBB,
	0x3FB1,0x3FA7,0x3F9C,0x3F91,0x3F85,0x3F78,0x3F6B,0x3F5D,
	0x3F4F,0x3F40,0x3F30,0x3F20,0x3F0F,0x3EFD,0x3EEB,0x3ED8,
	0x3EC5,0x3EB1,0x3E9D,0x3E88,0x3E72,0x3E5C,0x3E45,0x3E2D,
	0x3E15,0x3DFC,0x3DE3,0x3DC9,0x3DAF,0x3D93,0x3D78,0x3D5B,
	0x3D3F,0x3D21,0x3D03,0x3CE4,0x3CC5,0x3CA5,0x3C85,0x3C64,
	0x3C42,0x3C20,0x3BFD,0x3BDA,0x3BB6,0x3B92,0x3B6D,0x3B47,
	0x3B21,0x3AFA,0x3AD3,0x3AAB,0x3A82,0x3A59,0x3A30,0x3A06,
	0x39DB,0x39B0,0x3984,0x3958,0x392B,0x38FD,0x38CF,0x38A1,
	0x3871,0x3842,0x3812,0x37E1,0x37B0,0x377E,0x374B,0x3718,
	0x36E5,0x36B1,0x367D,0x3648,0x3612,0x35DC,0x35A5,0x356E,
	0x3537,0x34FF,0x34C6,0x348D,0x3453,0x3419,0x33DF,0x33A3,
	0x3368,0x332C,0x32EF,0x32B2,0x3274,0x3236,0x31F8,0x31B9,
	0x3179,0x3139,0x30F9,0x30B8,0x3076,0x3034,0x2FF2,0x2FAF,
	0x2F6C,0x2F28,0x2EE4,0x2E9F,0x2E5A,0x2E15,0x2DCF,0x2D88,
	0x2D41,0x2CFA,0x2CB2,0x2C6A,0x2C21,0x2BD8,0x2B8F,0x2B45,
	0x2AFB,0x2AB0,0x2A65,0x2A1A,0x29CE,0x2981,0x2935,0x28E7,
	0x289A,0x284C,0x27FE,0x27AF,0x2760,0x2711,0x26C1,0x2670,
	0x2620,0x25CF,0x257E,0x252C,0x24DA,0x2488,0x2435,0x23E2,
	0x238E,0x233B,0x22E7,0x2292,0x223D,0x21E8,0x2193,0x213D,
	0x20E7,0x2091,0x203A,0x1FE3,0x1F8C,0x1F34,0x1EDC,0x1E84,
	0x1E2B,0x1DD3,0x1D79,0x1D20,0x1CC6,0x1C6C,0x1C12,0x1BB8,
	0x1B5D,0x1B02,0x1AA7,0x1A4B,0x19EF,0x1993,0x1937,0x18DB,
	0x187E,0x1821,0x17C4,0x1766,0x1709,0x16AB,0x164C,0x15EE,
	0x1590,0x1531,0x14D2,0x1473,0x1413,0x13B4,0x1354,0x12F4,
	0x1294,0x1234,0x11D3,0x1173,0x1112,0x10B1,0x1050,0x0FEE,
	0x0F8D,0x0F2B,0x0ECA,0x0E68,0x0E06,0x0DA4,0x0D41,0x0CDF,
	0x0C7C,0x0C1A,0x0BB7,0x0B54,0x0AF1,0x0A8E,0x0A2B,0x09C7,
	0x0964,0x0901,0x089D,0x0839,0x07D6,0x0772,0x070E,0x06AA,
	0x0646,0x05E2,0x057E,0x051A,0x04B5,0x0451,0x03ED,0x0388,
	0x0324,0x02BF,0x025B,0x01F7,0x0192,0x012E,0x00C9,0x0065,
};


/*------------------*
 *    ATAN TABLE    *
 *------------------*/
const Sint8 SMMI_atantbl[] = {
	 0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,
	 3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  4,  5,  5,  5,
	 5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  7,
	 8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9, 10, 10, 10,
        10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12,
	12, 12, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14,
	15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 17, 17,
	17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19,
	19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23,
	23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24,
	25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26,
	26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28,
	28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29,
	29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31,
	31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32,
	};


/*----------------------------*
 *    Sinset(-4096...4096)    *
 *    Cosset(-4096...4096)    *
 *    in 0...3ff              *
 *----------------------------*/
/**** SIN ****/
Sint16 SMMI_Sinset(Sint16 kakudo)
{
 kakudo &= 0x3ff;

 if (kakudo < 0x200) {
     return SMMI_sintbl3[kakudo & 0x1ff];
 }
 return -(SMMI_sintbl3[kakudo & 0x1ff]);

}

/**** COS ****/
Sint16 SMMI_Cosset(Sint16 kakudo)
{
 kakudo += 0x100;
 kakudo &= 0x3ff;
 
 if (kakudo < 0x200) {
     return  SMMI_sintbl3[kakudo & 0x1ff];
 }
 return -(SMMI_sintbl3[kakudo & 0x1ff]);

}



/*----------------------------*
 *    Sinset($ff00...$0100)   *
 *    Cosset($ff00...$0100)   *
 *    in 0...ff               *
 *----------------------------*/
/**** SIN ****/
Sint16 SMMI_Sinset8(Sint16 kakudo)
{
 return SMMI_sintbl8[kakudo & 0xff];
}

/**** COS ****/
Sint16 SMMI_Cosset8(Sint16 kakudo)
{
 kakudo += 0x40;
 return SMMI_sintbl8[kakudo & 0xff];
}




/*------------------------------------*
 *    Atan                            *
 *    dx, dyをセットしてくれ          *
 *    方向が２５６段階で返ってくる    *
 *------------------------------------*/
Sint16 SMMI_atan(Sint16 dx, Sint16 dy)
{
	Uint16 r0;
	Uint16 adx, ady;
	Uint16 d0;
	
	adx = dx;
	ady = dy;
	
	if ((dx != 0) || (dy != 0)) {
           if (dx < 0) adx = 0 - adx;
           if (dy < 0) ady = 0 - ady;

          if (adx >= ady) {
              r0 = ((ady << 8) / adx) & 0xff;
              d0 = (Sint16)SMMI_atantbl[r0];
          } else {
              r0 = ((adx << 8) / ady) & 0xff;
              d0 = (Sint16)(64 - SMMI_atantbl[r0]);
          }
		
          if (dx <= 0) d0 = 128 - d0;
          if (dy <= 0) d0 = 256 - d0;
          return (Sint16)d0;

          } else {
            d0 = 0x40;          /* 同じ位置のとき */ 
            return (Sint16)d0;
          }
}


/* ========================================================================= */
/*     転送
/* ========================================================================= */
/*
 *  LONG LDIR
 */
void SMMI_Ldir32(Uint32 *src, Uint32 *dst, Uint32 len)
{
    do {
        *dst = *src;
        dst++;
        src++;
        len--;
    } while (len != 0);

}


/*
 *  WORD LDIR
 */
void SMMI_Ldir16(Uint16 *src, Uint16 *dst, Uint32 len)
{

    do {
        *dst = *src;
        dst++;
        src++;
        len--;
    } while (len != 0);

}


/*
 *  BYTE LDIR
 */
void SMMI_Ldir8(Uint8 *src, Uint8 *dst, Uint32 len)
{

    do {
        *dst = *src;
        dst++;
        src++;
        len--;
    } while (len != 0);

}




/*===========================================================================
 *    メモリ→メモリ間ロングワードCPUDMA転送 (CH#0 サイクルスチールモード)
 *    srcadd : 転送元アドレス
 *    dstadd : 転送先アドレス
 *    trcnt  : 転送サイズ(バイトサイズ)
 *==========================================================================*/
void SMMI_CPUDmaLdirL0(Uint32 srcadd, Uint32 dstadd, Uint32 trcnt)
{
    Uint32 d0, d1;

    d0 = *(volatile Uint32 *)CDMA_OPR;
    d0 &= 0x1;
    d0 |= 0x1;
    *(volatile Uint32 *)CDMA_OPR = d0;

    *(volatile Uint32 *)CDMA0_SRC = srcadd;
    *(volatile Uint32 *)CDMA0_DST = dstadd;
    *(volatile Uint32 *)CDMA0_LEN = (trcnt+3)>>2;
    d0 = *(volatile Uint32 *)CDMA0_CNT;
    *(volatile Uint32 *)CDMA0_CNT = 0x5a01;        /* src++ dst++ NoINT */
	
    do {
        d0 = *(volatile Uint32 *)CDMA0_CNT;
        d1 = *(volatile Uint16 *)dstadd;          /* debug for scu error */
    } while ((d0 & 2) == 0);
	
}


/*===========================================================================
 *    メモリ→メモリ間ワードCPUDMA転送 (CH#0 サイクルスチールモード)
 *    srcadd : 転送元アドレス
 *    dstadd : 転送先アドレス
 *    trcnt  : 転送サイズ(バイトサイズ)
 *==========================================================================*/
void SMMI_CPUDmaLdirW0(Uint32 srcadd, Uint32 dstadd, Uint32 trcnt)
{
    Uint32 d0, d1;

    d0 = *(volatile Uint32 *)CDMA_OPR;
    d0 &= 0x1;
    d0 |= 0x1;
    *(volatile Uint32 *)CDMA_OPR = d0;

    *(volatile Uint32 *)CDMA0_SRC = srcadd;
    *(volatile Uint32 *)CDMA0_DST = dstadd;
    *(volatile Uint32 *)CDMA0_LEN = (trcnt+1)>>1;
    d0 = *(volatile Uint32 *)CDMA0_CNT;
    *(volatile Uint32 *)CDMA0_CNT = 0x5601;        /* src++ dst++ NoINT */
	
    do {
        d0 = *(volatile Uint32 *)CDMA0_CNT;
        d1 = *(volatile Uint16 *)dstadd;          /* debug for scu error */
    } while ((d0 & 2) == 0);
	
}





/*===========================================================================
 *    メモリ→メモリ間ロングワードCPUDMA転送 (CH#1 サイクルスチールモード)
 *    srcadd : 転送元アドレス
 *    dstadd : 転送先アドレス
 *    trcnt  : 転送サイズ(バイトサイズ)
 *==========================================================================*/
void SMMI_CPUDmaLdirL1(Uint32 srcadd, Uint32 dstadd, Uint32 trcnt)
{
    Uint32 d0, d1;

    d0 = *(Uint32 *)CDMA_OPR;
    d0 &= 0x1;
    d0 |= 0x1;
    *(volatile Uint32 *)CDMA_OPR = d0;

    *(volatile Uint32 *)CDMA1_SRC = srcadd;
    *(volatile Uint32 *)CDMA1_DST = dstadd;
    *(volatile Uint32 *)CDMA1_LEN = (trcnt+3)>>2;
    d0 = *(volatile Uint32 *)CDMA1_CNT;
    *(volatile Uint32 *)CDMA1_CNT = 0x5a01;        /* src++ dst++ NoINT */
	
    do {
        d0 = *(volatile Uint32 *)CDMA1_CNT;
        d1 = *(volatile Uint16 *)dstadd;          /* debug for scu error */
    } while ((d0 & 2) == 0);
	
}


/*===========================================================================
 *    メモリ→メモリ間ワードCPUDMA転送 (CH#1 サイクルスチールモード)
 *    srcadd : 転送元アドレス
 *    dstadd : 転送先アドレス
 *    trcnt  : 転送サイズ(バイトサイズ)
 *==========================================================================*/
void SMMI_CPUDmaLdirW1(Uint32 srcadd, Uint32 dstadd, Uint32 trcnt)
{
    Uint32 d0, d1;

    d0 = *(volatile Uint32 *)CDMA_OPR;
    d0 &= 0x1;
    d0 |= 0x1;
    *(volatile Uint32 *)CDMA_OPR = d0;

    *(volatile Uint32 *)CDMA1_SRC = srcadd;
    *(volatile Uint32 *)CDMA1_DST = dstadd;
    *(volatile Uint32 *)CDMA1_LEN = (trcnt+1)>>1;
    d0 = *(volatile Uint32 *)CDMA1_CNT;
    *(volatile Uint32 *)CDMA1_CNT = 0x5601;        /* src++ dst++ NoINT */
	
    do {
        d0 = *(volatile Uint32 *)CDMA1_CNT;
        d1 = *(volatile Uint16 *)dstadd;          /* debug for scu error */
    } while ((d0 & 2) == 0);
	
}



/*-------------------------------
 *    HEX NUMBER PUTS  32Bit
 *------------------------------*/		
void SMMI_PutHexNum32(Sint16 xposi, Sint16 yposi, Uint32 number)
{		        
    Uint16 hvrev, pmode, color, cgadr, cgsize, growno;
    XyInt posi[4];
    Sint16 scnt[8];
    Sint16 i;

    scnt[0] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x10000000)];
    scnt[1] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x1000000)];
    scnt[2] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x100000)];
    scnt[3] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x10000)];
    scnt[4] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x1000)];
    scnt[5] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x100)];
    scnt[6] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x10)];
    scnt[7] = SMMI_hexchr_tbl[SMMI_getcount(&number, 0x1)];

    hvrev = 0;

    for (i = 0; i < 8; i++) {
        pmode = SPM_ecd + SPM_sdd;
        color = 0x0010;
        cgadr = scnt[i];                         /* SPR OFFSET   */
        cgsize = 0x0108;                         /* CG SIZE      */          
        posi[0].x = xposi + i * 8;
        posi[0].y = yposi;
        SPR_2NormSpr(SPR_2MOST_NEAR, hvrev, pmode, 
                        color, cgadr, &posi[0], 0xffff);
    }
    
}


/*------------------------
 *    HEX NUMBER COUNT
 *-----------------------*/
Sint16 SMMI_getcount(Uint32 *data, Uint32 subdata)
{
    Sint16 scnt = 0;
    
    while (*data >= subdata) {
        *data -= subdata;
	    scnt++;
    }
    return scnt;
}




