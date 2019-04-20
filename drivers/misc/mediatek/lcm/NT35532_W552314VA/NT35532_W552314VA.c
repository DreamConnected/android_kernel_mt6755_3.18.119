/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#include <agold_lcm_drv.h>

#if defined(BUILD_LK)
	#define LCM_DEBUG  printf
	#define LCM_FUNC_TRACE() printf("huyl [uboot] %s\n",__func__)
#else
	#define LCM_DEBUG  printk
	#define LCM_FUNC_TRACE() printk("huyl [kernel] %s\n",__func__)
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (1080)
#define FRAME_HEIGHT (1920)


#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

//static unsigned int lcm_esd_test = FALSE;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#define REGFLAG_DELAY             							0XFE
#define REGFLAG_END_OF_TABLE      							0x100   // END OF REGISTERS MARKER

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)   

#define   LCM_DSI_CMD_MODE							0

struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static struct LCM_setting_table lcm_initialization_setting[] = {

{0xFF, 1, {0x01}},
{0xFB, 1, {0x01}},
{0x6E, 1, {0x80}}, //Add video drop cmd

{0xFF, 1, {0x02}},
{0xFB, 1, {0x01}},
{0xFF, 1, {0x03}},
{0xFB, 1, {0x01}},
{0xFF, 1, {0x04}},
{0xFB, 1, {0x01}},
{0xFF, 1, {0x05}},
{0xFB, 1, {0x01}},
{0xD7, 1, {0x31}},
{0xD8, 1, {0x7E}},
{REGFLAG_DELAY, 30, {}},          
{0xFF, 1, {0x00}},
{0xFB, 1, {0x01}},
{0xBA, 1, {0x03}},
{0x36, 1, {0x00}},
{0xB0, 1, {0x00}},
{0xD3, 1, {0x08}},
{0xD4, 1, {0x0E}},
{0xD5, 1, {0x0F}},
{0xD6, 1, {0x48}},
{0xD7, 1, {0x00}},
{0xD9, 1, {0x00}},
{0xFB, 1, {0x01}},
{0xFF, 1, {0xEE}},
{0x40, 1, {0x00}},
{0x41, 1, {0x00}},
{0x42, 1, {0x00}},

{0xFB, 1, {0x01}},

{0xFF, 1, {0x01}},
{0xFB, 1, {0x01}},
{0x01, 1, {0x55}},
{0x04, 1, {0x0C}},
{0x05, 1, {0x3A}},
{0x06, 1, {0x50}},	//VGH
{0x07, 1, {0xD0}},	//VGL
{0x0A, 1, {0x0F}},
{0x0C, 1, {0x06}},
{0x0D, 1, {0x7F}},
{0x0E, 1, {0x7F}},
{0x0F, 1, {0x70}},
{0x10, 1, {0x63}},
{0x11, 1, {0x3C}},
{0x12, 1, {0x5C}},
{0x13, 1, {0x55}},	//VCOM	5c
{0x14, 1, {0x55}},	//VCOM	5c
{0x15, 1, {0x60}},
{0x16, 1, {0x15}},	//AVDD
{0x17, 1, {0x15}},	//AVEE
{0x23, 1, {0x10}},//any value
{0x24, 1, {0x10}},//any value
{0x25, 1, {0x10}},//any value
{0x26, 1, {0x10}},//any value
{0x27, 1, {0x10}},//any value
{0x28, 1, {0x10}},//any value
{0x44, 1, {0x10}},//any value
{0x45, 1, {0x10}},//any value
{0x46, 1, {0x10}},//any value
{0x5B, 1, {0xCA}},
{0x5C, 1, {0x00}},
{0x5D, 1, {0x00}},
{0x5E, 1, {0x15}}, //value B
{0x5F, 1, {0x1B}},
{0x60, 1, {0xD5}},
{0x61, 1, {0xF7}},
{0x6C, 1, {0xAB}},
{0x6D, 1, {0x44}},

//3Gamma2.0

{0xFF, 1, {0x05}},

{0xFB, 1, {0x01}},
{0x00, 1, {0x3F}},
{0x01, 1, {0x3F}},
{0x02, 1, {0x3F}},
{0x03, 1, {0x3F}},
{0x04, 1, {0x38}},
{0x05, 1, {0x3F}},
{0x06, 1, {0x3F}},
{0x07, 1, {0x19}},
{0x08, 1, {0x1D}},
{0x09, 1, {0x3F}},
{0x0A, 1, {0x3F}},
{0x0B, 1, {0x1B}},
{0x0C, 1, {0x17}},
{0x0D, 1, {0x3F}},
{0x0E, 1, {0x3F}},
{0x0F, 1, {0x08}},
{0x10, 1, {0x3F}},
{0x11, 1, {0x10}},
{0x12, 1, {0x3F}},
{0x13, 1, {0x3F}},
{0x14, 1, {0x3F}},
{0x15, 1, {0x3F}},
{0x16, 1, {0x3F}},
{0x17, 1, {0x3F}},
{0x18, 1, {0x38}},
{0x19, 1, {0x18}},
{0x1A, 1, {0x1C}},
{0x1B, 1, {0x3F}},
{0x1C, 1, {0x3F}},
{0x1D, 1, {0x1A}},
{0x1E, 1, {0x16}},
{0x1F, 1, {0x3F}},
{0x20, 1, {0x3F}},
{0x21, 1, {0x3F}},
{0x22, 1, {0x3F}},
{0x23, 1, {0x06}},
{0x24, 1, {0x3F}},
{0x25, 1, {0x0E}},
{0x26, 1, {0x3F}},
{0x27, 1, {0x3F}},
{0x54, 1, {0x06}},
{0x55, 1, {0x05}},
{0x56, 1, {0x04}},
{0x58, 1, {0x03}},
{0x59, 1, {0x1B}},
{0x5A, 1, {0x1B}},
{0x5B, 1, {0x01}},
{0x5C, 1, {0x32}},
{0x5E, 1, {0x18}},
{0x5F, 1, {0x20}},
{0x60, 1, {0x2B}},
{0x61, 1, {0x2C}},
{0x62, 1, {0x18}},
{0x63, 1, {0x01}},
{0x64, 1, {0x32}},
{0x65, 1, {0x00}},
{0x66, 1, {0x44}},
{0x67, 1, {0x11}},
{0x68, 1, {0x01}},
{0x69, 1, {0x01}},
{0x6A, 1, {0x04}},
{0x6B, 1, {0x2C}},
{0x6C, 1, {0x08}},
{0x6D, 1, {0x08}},
{0x78, 1, {0x00}},
{0x79, 1, {0x00}},
{0x7E, 1, {0x00}},
{0x7F, 1, {0x00}},
{0x80, 1, {0x00}},
{0x81, 1, {0x00}},
{0x8D, 1, {0x00}},
{0x8E, 1, {0x00}},
{0x8F, 1, {0xC0}},
{0x90, 1, {0x73}},
{0x91, 1, {0x10}},
{0x92, 1, {0x07}},
{0x96, 1, {0x11}},
{0x97, 1, {0x14}},
{0x98, 1, {0x00}},
{0x99, 1, {0x00}},
{0x9A, 1, {0x00}},
{0x9B, 1, {0x61}},
{0x9C, 1, {0x15}},
{0x9D, 1, {0x30}},
{0x9F, 1, {0x0F}},
{0xA2, 1, {0xB0}},
{0xA7, 1, {0x0A}},
{0xA9, 1, {0x00}},
{0xAA, 1, {0x70}},
{0xAB, 1, {0xDA}},
{0xAC, 1, {0xFF}},
{0xAE, 1, {0xF4}},
{0xAF, 1, {0x40}},
{0xB0, 1, {0x7F}},
{0xB1, 1, {0x16}},
{0xB2, 1, {0x53}},
{0xB3, 1, {0x00}},
{0xB4, 1, {0x2A}},
{0xB5, 1, {0x3A}},
{0xB6, 1, {0xF0}},
{0xBC, 1, {0x85}},
{0xBD, 1, {0xF4}},
{0xBE, 1, {0x33}},
{0xBF, 1, {0x13}},
{0xC0, 1, {0x77}},
{0xC1, 1, {0x77}},
{0xC2, 1, {0x77}},
{0xC3, 1, {0x77}},
{0xC4, 1, {0x77}},
{0xC5, 1, {0x77}},
{0xC6, 1, {0x77}},
{0xC7, 1, {0x77}},
{0xC8, 1, {0xAA}},
{0xC9, 1, {0x2A}},
{0xCA, 1, {0x00}},
{0xCB, 1, {0xAA}},
{0xCC, 1, {0x92}},
{0xCD, 1, {0x00}},
{0xCE, 1, {0x18}},
{0xCF, 1, {0x88}},
{0xD0, 1, {0xAA}},
{0xD1, 1, {0x00}},
{0xD2, 1, {0x00}},
{0xD3, 1, {0x00}},
{0xD6, 1, {0x02}},
{0xED, 1, {0x00}},
{0xEE, 1, {0x00}},
{0xEF, 1, {0x70}},
{0xFA, 1, {0x03}},
{0xFF, 1, {0x00}},



//page selection cmd start
{0xFF,1,{0x01}},
{0x68,1,{0x13}},
{0xFB,1,{0x01}},
//page selection cmd end
//R(+) MC cmd
{0x75,1,{0x00}},
{0x76,1,{0x00}},
{0x77,1,{0x00}},
{0x78,1,{0x27}},
{0x79,1,{0x00}},
{0x7A,1,{0x52}},
{0x7B,1,{0x00}},
{0x7C,1,{0x70}},
{0x7D,1,{0x00}},
{0x7E,1,{0x88}},
{0x7F,1,{0x00}},
{0x80,1,{0x9D}},
{0x81,1,{0x00}},
{0x82,1,{0xAE}},
{0x83,1,{0x00}},
{0x84,1,{0xBE}},
{0x85,1,{0x00}},
{0x86,1,{0xCD}},
{0x87,1,{0x00}},
{0x88,1,{0xFD}},
{0x89,1,{0x01}},
{0x8A,1,{0x23}},
{0x8B,1,{0x01}},
{0x8C,1,{0x5F}},
{0x8D,1,{0x01}},
{0x8E,1,{0x8F}},
{0x8F,1,{0x01}},
{0x90,1,{0xD9}},
{0x91,1,{0x02}},
{0x92,1,{0x13}},
{0x93,1,{0x02}},
{0x94,1,{0x14}},
{0x95,1,{0x02}},
{0x96,1,{0x48}},
{0x97,1,{0x02}},
{0x98,1,{0x7E}},
{0x99,1,{0x02}},
{0x9A,1,{0x9F}},
{0x9B,1,{0x02}},
{0x9C,1,{0xCC}},
{0x9D,1,{0x02}},
{0x9E,1,{0xEC}},
{0x9F,1,{0x03}},
{0xA0,1,{0x19}},
{0xA2,1,{0x03}},
{0xA3,1,{0x26}},
{0xA4,1,{0x03}},
{0xA5,1,{0x35}},
{0xA6,1,{0x03}},
{0xA7,1,{0x47}},
{0xA9,1,{0x03}},
{0xAA,1,{0x5C}},
{0xAB,1,{0x03}},
{0xAC,1,{0x79}},
{0xAD,1,{0x03}},
{0xAE,1,{0xA4}},
{0xAF,1,{0x03}},
{0xB0,1,{0xC9}},
{0xB1,1,{0x03}},
{0xB2,1,{0xD0}},
//R(-) MC cmd
{0xB3,1,{0x00}},
{0xB4,1,{0x00}},
{0xB5,1,{0x00}},
{0xB6,1,{0x27}},
{0xB7,1,{0x00}},
{0xB8,1,{0x52}},
{0xB9,1,{0x00}},
{0xBA,1,{0x70}},
{0xBB,1,{0x00}},
{0xBC,1,{0x88}},
{0xBD,1,{0x00}},
{0xBE,1,{0x9D}},
{0xBF,1,{0x00}},
{0xC0,1,{0xAE}},
{0xC1,1,{0x00}},
{0xC2,1,{0xBE}},
{0xC3,1,{0x00}},
{0xC4,1,{0xCD}},
{0xC5,1,{0x00}},
{0xC6,1,{0xFD}},
{0xC7,1,{0x01}},
{0xC8,1,{0x23}},
{0xC9,1,{0x01}},
{0xCA,1,{0x5F}},
{0xCB,1,{0x01}},
{0xCC,1,{0x8F}},
{0xCD,1,{0x01}},
{0xCE,1,{0xD9}},
{0xCF,1,{0x02}},
{0xD0,1,{0x13}},
{0xD1,1,{0x02}},
{0xD2,1,{0x14}},
{0xD3,1,{0x02}},
{0xD4,1,{0x48}},
{0xD5,1,{0x02}},
{0xD6,1,{0x7E}},
{0xD7,1,{0x02}},
{0xD8,1,{0x9F}},
{0xD9,1,{0x02}},
{0xDA,1,{0xCC}},
{0xDB,1,{0x02}},
{0xDC,1,{0xEC}},
{0xDD,1,{0x03}},
{0xDE,1,{0x19}},
{0xDF,1,{0x03}},
{0xE0,1,{0x26}},
{0xE1,1,{0x03}},
{0xE2,1,{0x35}},
{0xE3,1,{0x03}},
{0xE4,1,{0x47}},
{0xE5,1,{0x03}},
{0xE6,1,{0x5C}},
{0xE7,1,{0x03}},
{0xE8,1,{0x79}},
{0xE9,1,{0x03}},
{0xEA,1,{0xA4}},
{0xEB,1,{0x03}},
{0xEC,1,{0xC9}},
{0xED,1,{0x03}},
{0xEE,1,{0xD0}},
//G(+) MC cmd
{0xEF,1,{0x00}},
{0xF0,1,{0x00}},
{0xF1,1,{0x00}},
{0xF2,1,{0x27}},
{0xF3,1,{0x00}},
{0xF4,1,{0x52}},
{0xF5,1,{0x00}},
{0xF6,1,{0x70}},
{0xF7,1,{0x00}},
{0xF8,1,{0x88}},
{0xF9,1,{0x00}},
{0xFA,1,{0x9D}},
//page selection cmd start
{0xFF,1,{0x02}},
{0xFB,1,{0x01}},
//page selection cmd end
{0x00,1,{0x00}},
{0x01,1,{0xAE}},
{0x02,1,{0x00}},
{0x03,1,{0xBE}},
{0x04,1,{0x00}},
{0x05,1,{0xCD}},
{0x06,1,{0x00}},
{0x07,1,{0xFD}},
{0x08,1,{0x01}},
{0x09,1,{0x23}},
{0x0A,1,{0x01}},
{0x0B,1,{0x5F}},
{0x0C,1,{0x01}},
{0x0D,1,{0x8F}},
{0x0E,1,{0x01}},
{0x0F,1,{0xD9}},
{0x10,1,{0x02}},
{0x11,1,{0x13}},
{0x12,1,{0x02}},
{0x13,1,{0x14}},
{0x14,1,{0x02}},
{0x15,1,{0x48}},
{0x16,1,{0x02}},
{0x17,1,{0x7E}},
{0x18,1,{0x02}},
{0x19,1,{0x9F}},
{0x1A,1,{0x02}},
{0x1B,1,{0xCC}},
{0x1C,1,{0x02}},
{0x1D,1,{0xEC}},
{0x1E,1,{0x03}},
{0x1F,1,{0x19}},
{0x20,1,{0x03}},
{0x21,1,{0x26}},
{0x22,1,{0x03}},
{0x23,1,{0x35}},
{0x24,1,{0x03}},
{0x25,1,{0x47}},
{0x26,1,{0x03}},
{0x27,1,{0x5C}},
{0x28,1,{0x03}},
{0x29,1,{0x79}},
{0x2A,1,{0x03}},
{0x2B,1,{0xA4}},
{0x2D,1,{0x03}},
{0x2F,1,{0xC9}},
{0x30,1,{0x03}},
{0x31,1,{0xD0}},
//G(-) MC cmd
{0x32,1,{0x00}},
{0x33,1,{0x00}},
{0x34,1,{0x00}},
{0x35,1,{0x27}},
{0x36,1,{0x00}},
{0x37,1,{0x52}},
{0x38,1,{0x00}},
{0x39,1,{0x70}},
{0x3A,1,{0x00}},
{0x3B,1,{0x88}},
{0x3D,1,{0x00}},
{0x3F,1,{0x9D}},
{0x40,1,{0x00}},
{0x41,1,{0xAE}},
{0x42,1,{0x00}},
{0x43,1,{0xBE}},
{0x44,1,{0x00}},
{0x45,1,{0xCD}},
{0x46,1,{0x00}},
{0x47,1,{0xFD}},
{0x48,1,{0x01}},
{0x49,1,{0x23}},
{0x4A,1,{0x01}},
{0x4B,1,{0x5F}},
{0x4C,1,{0x01}},
{0x4D,1,{0x8F}},
{0x4E,1,{0x01}},
{0x4F,1,{0xD9}},
{0x50,1,{0x02}},
{0x51,1,{0x13}},
{0x52,1,{0x02}},
{0x53,1,{0x14}},
{0x54,1,{0x02}},
{0x55,1,{0x48}},
{0x56,1,{0x02}},
{0x58,1,{0x7E}},
{0x59,1,{0x02}},
{0x5A,1,{0x9F}},
{0x5B,1,{0x02}},
{0x5C,1,{0xCC}},
{0x5D,1,{0x02}},
{0x5E,1,{0xEC}},
{0x5F,1,{0x03}},
{0x60,1,{0x19}},
{0x61,1,{0x03}},
{0x62,1,{0x26}},
{0x63,1,{0x03}},
{0x64,1,{0x35}},
{0x65,1,{0x03}},
{0x66,1,{0x47}},
{0x67,1,{0x03}},
{0x68,1,{0x5C}},
{0x69,1,{0x03}},
{0x6A,1,{0x79}},
{0x6B,1,{0x03}},
{0x6C,1,{0xA4}},
{0x6D,1,{0x03}},
{0x6E,1,{0xC9}},
{0x6F,1,{0x03}},
{0x70,1,{0xD0}},
//B(+) MC cmd
{0x71,1,{0x00}},
{0x72,1,{0x00}},
{0x73,1,{0x00}},
{0x74,1,{0x27}},
{0x75,1,{0x00}},
{0x76,1,{0x52}},
{0x77,1,{0x00}},
{0x78,1,{0x70}},
{0x79,1,{0x00}},
{0x7A,1,{0x88}},
{0x7B,1,{0x00}},
{0x7C,1,{0x9D}},
{0x7D,1,{0x00}},
{0x7E,1,{0xAE}},
{0x7F,1,{0x00}},
{0x80,1,{0xBE}},
{0x81,1,{0x00}},
{0x82,1,{0xCD}},
{0x83,1,{0x00}},
{0x84,1,{0xFD}},
{0x85,1,{0x01}},
{0x86,1,{0x23}},
{0x87,1,{0x01}},
{0x88,1,{0x5F}},
{0x89,1,{0x01}},
{0x8A,1,{0x8F}},
{0x8B,1,{0x01}},
{0x8C,1,{0xD9}},
{0x8D,1,{0x02}},
{0x8E,1,{0x13}},
{0x8F,1,{0x02}},
{0x90,1,{0x14}},
{0x91,1,{0x02}},
{0x92,1,{0x48}},
{0x93,1,{0x02}},
{0x94,1,{0x7E}},
{0x95,1,{0x02}},
{0x96,1,{0x9F}},
{0x97,1,{0x02}},
{0x98,1,{0xCC}},
{0x99,1,{0x02}},
{0x9A,1,{0xEC}},
{0x9B,1,{0x03}},
{0x9C,1,{0x19}},
{0x9D,1,{0x03}},
{0x9E,1,{0x26}},
{0x9F,1,{0x03}},
{0xA0,1,{0x35}},
{0xA2,1,{0x03}},
{0xA3,1,{0x47}},
{0xA4,1,{0x03}},
{0xA5,1,{0x5C}},
{0xA6,1,{0x03}},
{0xA7,1,{0x79}},
{0xA9,1,{0x03}},
{0xAA,1,{0xA4}},
{0xAB,1,{0x03}},
{0xAC,1,{0xC9}},
{0xAD,1,{0x03}},
{0xAE,1,{0xD0}},
//B(-) MC cmd
{0xAF,1,{0x00}},
{0xB0,1,{0x00}},
{0xB1,1,{0x00}},
{0xB2,1,{0x27}},
{0xB3,1,{0x00}},
{0xB4,1,{0x52}},
{0xB5,1,{0x00}},
{0xB6,1,{0x70}},
{0xB7,1,{0x00}},
{0xB8,1,{0x88}},
{0xB9,1,{0x00}},
{0xBA,1,{0x9D}},
{0xBB,1,{0x00}},
{0xBC,1,{0xAE}},
{0xBD,1,{0x00}},
{0xBE,1,{0xBE}},
{0xBF,1,{0x00}},
{0xC0,1,{0xCD}},
{0xC1,1,{0x00}},
{0xC2,1,{0xFD}},
{0xC3,1,{0x01}},
{0xC4,1,{0x23}},
{0xC5,1,{0x01}},
{0xC6,1,{0x5F}},
{0xC7,1,{0x01}},
{0xC8,1,{0x8F}},
{0xC9,1,{0x01}},
{0xCA,1,{0xD9}},
{0xCB,1,{0x02}},
{0xCC,1,{0x13}},
{0xCD,1,{0x02}},
{0xCE,1,{0x14}},
{0xCF,1,{0x02}},
{0xD0,1,{0x48}},
{0xD1,1,{0x02}},
{0xD2,1,{0x7E}},
{0xD3,1,{0x02}},
{0xD4,1,{0x9F}},
{0xD5,1,{0x02}},
{0xD6,1,{0xCC}},
{0xD7,1,{0x02}},
{0xD8,1,{0xEC}},
{0xD9,1,{0x03}},
{0xDA,1,{0x19}},
{0xDB,1,{0x03}},
{0xDC,1,{0x26}},
{0xDD,1,{0x03}},
{0xDE,1,{0x35}},
{0xDF,1,{0x03}},
{0xE0,1,{0x47}},
{0xE1,1,{0x03}},
{0xE2,1,{0x5C}},
{0xE3,1,{0x03}},
{0xE4,1,{0x79}},
{0xE5,1,{0x03}},
{0xE6,1,{0xA4}},
{0xE7,1,{0x03}},
{0xE8,1,{0xC9}},
{0xE9,1,{0x03}},
{0xEA,1,{0xD0}},

{0xFF, 1, {0x00}}, 
{0x35, 1, {0x00}},
                                  
{0x11,1,{0x00}},                   
{REGFLAG_DELAY, 120, {}},         
                                  
{0x29,1,{0x00}},                  
                                  
{REGFLAG_DELAY, 20, {}}, 
         
{REGFLAG_END_OF_TABLE, 0x00, {}}   

};




static struct LCM_setting_table lcm_sleep_mode_in_setting[] = {
// Display off sequence
	{0x28, 0, {0x00}},
	{REGFLAG_DELAY, 20, {}},
	
    // Sleep Mode On
	{0x10, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
/*
static struct LCM_setting_table lcm_compare_id_setting[] = {
	// Display off sequence
	
	{REGFLAG_DELAY, 10, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
*/

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {
		
        unsigned cmd;
        cmd = table[i].cmd;
		
        switch (cmd) {
			
            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;
				
            case REGFLAG_END_OF_TABLE :
                break;
				
            default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
				//MDELAY(2);
       	}
    }
	
}




// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{

	memset(params, 0, sizeof(LCM_PARAMS));

	params->type = LCM_TYPE_DSI;

	params->width = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

	params->dsi.mode = BURST_VDO_MODE;
	params->dsi.switch_mode = CMD_MODE;
	params->dsi.switch_mode_enable = 0;

	/* DSI */
	/* Command mode setting */
	params->dsi.LANE_NUM = LCM_FOUR_LANE;
	/* The following defined the fomat for data coming from LCD engine. */
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;
	params->dbi.io_driving_current      = LCM_DRIVING_CURRENT_4MA;

	/* Highly depends on LCD driver capability. */
	params->dsi.packet_size = 256;
	/* video mode timing */

	params->dsi.PS = LCM_PACKED_PS_24BIT_RGB888;

	params->physical_width = 62;
	params->physical_height = 110;

	params->dsi.vertical_sync_active = 2;//
	params->dsi.vertical_backporch = 6;
	params->dsi.vertical_frontporch = 16;//
	params->dsi.vertical_active_line = FRAME_HEIGHT;

	params->dsi.horizontal_sync_active = 10;//20
	params->dsi.horizontal_backporch = 60;//100
	params->dsi.horizontal_frontporch = 60;//110
	params->dsi.horizontal_active_pixel = FRAME_WIDTH;
	params->dsi.PLL_CLOCK = 430;//460//450

}

static void lcm_init(void)
{


	agold_lcm_power_on();
	MDELAY(60);
	SET_RESET_PIN(1);
	MDELAY(10); 
	SET_RESET_PIN(0);
	MDELAY(20);
	
	SET_RESET_PIN(1);
	MDELAY(120);      

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}



static void lcm_suspend(void)
{
	push_table(lcm_sleep_mode_in_setting, sizeof(lcm_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
	MDELAY(60);
//	SET_RESET_PIN(1);
//	MDELAY(20); 
	SET_RESET_PIN(0);
	MDELAY(20); 
	
	SET_RESET_PIN(1);
	MDELAY(120);   
	agold_lcm_power_down();  
}


static void lcm_resume(void)
{
	//lcm_initialization_setting[18].para_list[0]+=0x01;
	
   // LCM_DEBUG("VCOM is :%d",lcm_initialization_setting[18].para_list[0]);
	lcm_init();
}
         
#if (LCM_DSI_CMD_MODE)
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(data_array, 3, 1);

	data_array[0]= 0x00290508; //HW bug, so need send one HS packet
	dsi_set_cmdq(data_array, 1, 1);
	
	data_array[0]= 0x002c3909;
	dsi_set_cmdq(data_array, 1, 0);

}
#endif
/*
static unsigned int lcm_compare_id(void)
{
	 unsigned int id1 = 0, id2 = 0,id;
    unsigned char buffer[4];
    unsigned int data_array[16];
     
    SET_RESET_PIN(1);    //NOTE:should reset LCM firstly
    MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(20);
    SET_RESET_PIN(1);
    MDELAY(100);

    data_array[0] = 0x00023700;
    dsi_set_cmdq(data_array, 1, 1);
    MDELAY(10);

    read_reg_v2(0x04, buffer, 2);
    id1= buffer[0]; //0x93
    id2= buffer[1]; //0x67
    
    id=(id1 << 8) | id2;

#if defined(BUILD_LK)
    printf("jd9365 id=%x, %x %x\n", id, id1, id2);
#else
    printk("jd9365 id=%x, %x %x\n", id, id1, id2);
#endif
    return (LCM_ID_JD9365 == id) ? 1 : 0;


   return 1;

}
*/
LCM_DRIVER NT35532_W552314VA_lcm_drv = 
{
    .name			= "NT35532_W552314VA",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
//	.compare_id     = lcm_compare_id,
#if (LCM_DSI_CMD_MODE)
    .update         = lcm_update,
#endif
    };
