/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

#include "camera_custom_nvram.h"
#include "camera_custom_lens.h"

NVRAM_LENS_PARA_STRUCT DW9714AF_LENS_PARA_DEFAULT_VALUE =
{
    //Version
    NVRAM_CAMERA_LENS_FILE_VERSION,

    // Focus Range NVRAM
    {0, 1023},

    // AF NVRAM
    {
        // ------------------------------ sAF_Coef -----------------------------------------
        {
            {
                110,  // i4Offset
                15,  // i4NormalNum
                15,  // i4MacroNum
                1,   // i4InfIdxOffset
                1,   // i4MacroIdxOffset
                {
                       0,  10,  20,  31,  44,  60,  80, 100, 125, 150,
                     180, 210, 240, 270, 310,   0,   0,   0,   0,   0,
                       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                }
        },
        15,  // i4THRES_MAIN
        10,  // i4THRES_SUB
        1,  // i4AFC_FAIL_CNT
        0,  // i4FAIL_POS
        4,  // i4INIT_WAIT
        {500, 500, 500, 500, 500},  // i4FRAME_WAIT
        0,  // i4DONE_WAIT
        },
        // ------------------------------ sVAFC_Coef -----------------------------------------
        {
            {
                110,  // i4Offset
                15,  // i4NormalNum
                15,  // i4MacroNum
                1,   // i4InfIdxOffset
                1,   // i4MacroIdxOffset
                {
                       0,  10,  20,  31,  44,  60,  80, 100, 125, 150,
                     180, 210, 240, 270, 310,   0,   0,   0,   0,   0,
                       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                }
        },
        15,  // i4THRES_MAIN
        10,  // i4THRES_SUB
        1,  // i4AFC_FAIL_CNT
        -1,  // i4FAIL_POS
        4,  // i4INIT_WAIT
        {0, 0, 500, 500, 500},  // i4FRAME_WAIT
        0,  // i4DONE_WAIT
        },
        // -------------------- sAF_TH ---------------------
        {
            8,  // i4ISONum;
            {100, 150, 200, 300, 400, 600, 800, 1600},
            // SGG1~7
            {
             {20, 20, 17, 14, 11, 11, 10, 8},
             {30, 29, 27, 23, 20, 19, 17, 15},
             {43, 43, 40, 36, 32, 31, 30, 27},
             {62, 62, 59, 55, 51, 50, 48, 45},
             {89, 88, 86, 82, 79, 78, 76, 73},
             {127, 126, 125, 122, 119, 118, 116, 113},
             {180, 180, 179, 177, 176, 175, 174, 172},
            },
            // horizontal FV baseline
            {0, 0, 0, 0, 0, 0, 0, 0},

            // horizontal FV min. threshold
            {4000, 3500, 3500, 3000, 2000, 2000, 1000, 1000},

            // horizontal FV threshold
            {3, 3, 3, 3, 3, 3, 3, 2},

            // vertical FV baseline
            {0, 0, 0, 0, 0, 0, 0, 0},

            // vertical FV min. threshold
            {0, 0, 0, 0, 0, 0, 0, 0},

            // vertical FV threshold
            {3, 3, 3, 3, 3, 3, 3, 2},

        },
        // -------------------- sZSD_AF_TH ---------------------
        {
            8,  // i4ISONum;
            {100, 150, 200, 300, 400, 600, 800, 1600},
            // SGG1~7
            {
             {20, 20, 17, 14, 11, 11, 10, 8},
             {30, 29, 27, 23, 20, 19, 17, 15},
             {43, 43, 40, 36, 32, 31, 30, 27},
             {62, 62, 59, 55, 51, 50, 48, 45},
             {89, 88, 86, 82, 79, 78, 76, 73},
             {127, 126, 125, 122, 119, 118, 116, 113},
             {180, 180, 179, 177, 176, 175, 174, 172},
            },
            // horizontal FV baseline
            {0, 0, 0, 0, 0, 0, 0, 0},

            // horizontal FV min. threshold
            {4000, 3500, 3500, 3000, 2000, 2000, 1000, 1000},

            // horizontal FV threshold
            {3, 3, 3, 3, 3, 3, 3, 2},

            // vertical FV baseline
            {0, 0, 0, 0, 0, 0, 0, 0},

            // vertical FV min. threshold
            {0, 0, 0, 0, 0, 0, 0, 0},

            // vertical FV threshold
            {3, 3, 3, 3, 3, 3, 3, 2},
        },
        // ------------------- sVID_AF_TH -----------------------------------
        {
            0,  // i4ISONum;
            {0, 0, 0, 0, 0, 0, 0, 0},
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sVID1_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sVID2_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sIHDR_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sREV1_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sREV2_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sREV3_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sREV4_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // -------------------- sREV5_AF_TH ---------------------
        {
            0,  // i4ISONum;
            {0,0,0,0,0,0,0,0}, // i4ISO[ISO_MAX_NUM];
            // SGG1~7
            {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            },
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0},// i4MIN_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4HW_TH[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4FV_DC2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0}, // i4MIN_TH2[ISO_MAX_NUM];
            {0, 0, 0, 0, 0, 0, 0, 0} // i4HW_TH2[ISO_MAX_NUM];
        },
        // --- Common use ---        
        1,  // i4ReadOTP; 				// 0: disable, 1:enable
        3,  // i4StatGain;
        0,  // i4LV_THRES;
        299,  // i4InfPos;
        33,  // i4FRAME_TIME;
        {0, 100, 200, 350, 500}, // back jump
        500,//i4BackJumpPos
        20, // i4AFC_STEP_SIZE
        18, // i4SPOT_PERCENT_W;        // AFC window location
        24, // i4SPOT_PERCENT_H;        // AFC window location
        0, // i4CHANGE_CNT_DELTA
        1, // i4AFS_STEP_MIN_ENABLE
        4, // i4AFS_STEP_MIN_NORMAL
        4, // i4AFS_STEP_MIN_MACRO
        5, // i4FIRST_FV_WAIT
        12, // i4FV_1ST_STABLE_THRES
        10000, // i4FV_1ST_STABLE_OFFSET
        6, // i4FV_1ST_STABLE_NUM
        6, // i4FV_1ST_STABLE_CNT
        50, // i4FV_SHOCK_THRES
        30000, // i4FV_SHOCK_OFFSET
        5, // i4FV_VALID_CNT
        20, // i4FV_SHOCK_FRM_CNT
        5, // i4FV_SHOCK_CNT
        // --- FaceAF ---
        90, // i4FDWinPercent
        40, // i4FDSizeDiff
        20, // i4FD_DETECT_CNT
        5, // i4FD_NONE_CNT
        // --- AFv1.1/AFv1.2 ---
        1, // i4LeftSearchEnable
        0, // i4LeftJumpStep
        0, // No use
        0, // i4AfDoneDelay
        0, // i4VdoAfDoneDelay
        0, // i4ZoomInWinChg
        1, // i4SensorEnable
        0, // i4PostureComp
        2, // i4SceneMonitorLevel
        1, // i4VdoSceneMonitorLevel

        // Scene Monitor                                                  
        // {Type, Off, Thr{by level}, Cnt{by level}}                      
        // Type: 1 is &&, 0 is ||                                         
        // Off : value, min=0 is more sensitive                           
        // Thr : percentage(value for gyro/acce), min=0 is more sensitive 
        // Cnt : value, max=30 is more stable                             
        // preview params                                                 
        {1,                                       // FV 0:disable, 1:enable
         0, 10000, { 40, 40, 30}, { 15, 10, 10},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,  5000, { 25, 25, 25}, { 10,  7,  5} }, //    stb; stbT should fix, stbN bigger to stable      
        {1,                                       // GS 0:disable, 1:enable
         0,    15, { 20, 20, 15}, { 15, 10, 10},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,     5, {  5, 10, 10}, { 10,  7,  5} }, //    stb; stbT should fix, stbN bigger to stable      
        {1,                                       // AEB 0:disable, 1:enable
         0,    15, { 30, 30, 25}, { 33, 30, 30},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,     5, { 10, 10, 10}, { 10,  7,  5} }, //    stb; stbT should fix, stbN bigger to stable      
        {1,                                       // GYRO 0:disable, 1:enable
         0,     0, { 40, 40, 20}, {  5,  3,  3},    //    chg; off=0, chgT lower to sensitive, chgN bigger to stable
         1,     0, { 10, 10, 10}, { 10,  7,  5} },    //    stb; off=0, stbT should fix, stbN bigger to stable
        {1,                                       // ACCE 0:disable, 1:enable
         0,     0, { 80, 80, 60}, { 15, 12, 12},   //    chg; off=0, chgT lower to sensitive, chgN bigger to stable
         1,     0, { 50, 50, 50}, { 10,  7,  5} }, //    stb; off=0, stbT should fix, stbN bigger to stable
        {1,                                       //   0:disable, 1:enable
         0, 10000, { 40, 40, 30}, { 20, 15, 15},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,  5000, { 20, 20, 20}, { 20, 15, 10} }, //    stb; stbT should fix, stbN bigger to stable      
        {1,                                       //   0:disable, 1:enable
         0,    15, { 20, 20, 15}, { 28, 25, 25},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,     5, {  5,  5,  5}, { 15, 13, 10} }, //    stb; stbT should fix, stbN bigger to stable      
        {1,                                       //   0:disable, 1:enable
         0,    15, { 30, 30, 25}, { 33, 30, 30},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,     5, { 10, 10, 10}, { 15, 13, 10} }, //    stb; stbT should fix, stbN bigger to stable      
        {1,                                       //   0:disable, 1:enable
         0,     0, { 40, 40, 20}, {  7,  5,  5},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,     0, { 10, 10, 10}, { 15, 13, 10} }, //    stb; stbT should fix, stbN bigger to stable      
        {1,                                       //   0:disable, 1:enable
         0,     0, { 80, 80, 60}, { 15, 12, 12},   //    chg; chgT lower to sensitive, chgN bigger to stable  
         1,     0, { 50, 50, 50}, { 13, 13, 10} }, //    stb; stbT should fix, stbN bigger to stable      
        // --- AFv2.0 ---     
        1,  // i4FvExtractEnable;           // 0:disable, 1:enable (for faceAF)
        40, // i4FvExtractThr               // percentage, fixed
        1,  // i4DampingCompEnable;         // 0:disable, 1:enable
        {8, 15, 23, 31, 39, 46, 54, 62, 69, 77, 0, 0, 0, 0, 0, },        // { step1, step2, ... , step 15(atmost) }
        {
            {  -2, -4, -4, -6, -5, -5, -13, -8, -10, -20, 0, 0, 0, 0, 0, },// prerun0:{rComp1, rComp2, ..., rComp15(atmost)}
            {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }   // prerun1:{rComp1, rComp2, ..., rComp15(atmost)}
        },
        {
            {  2, 4, 4, 6, 5, 5, 13, 8, 10, 20, 0, 0, 0, 0, 0, },// prerun0:{rComp1, rComp2, ..., rComp15(atmost)}
            {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }   // prerun1:{rComp1, rComp2, ..., rComp15(atmost)}
        },
        1,  // i4DirSelectEnable;           // 0:disable, 1:enable
        -1, // i4InfDir;                    // 1:right, -1:left, 2:reverse, 0:keep
        -1, // i4MidDir;                    // 
        -1, // i4MacDir;                    // 
        40, // i4RatioInf;                  // below % of tableLength belongs to INF
        70, // i4RatioMac;                  // above % of tableLength belongs to MAC ; should be larger than i4RatioInf          
        1,  // i4StartBoundEnable;          // 0:disable, 1:enable
        3,  // i4StartCamCAF;               // 0:keep current, -1:force to INF, X:set to boundary if within X steps
        3,  // i4StartCamTAF;               // 
        0,  // i4StartVdoCAF;               // 
        0,  // i4StartVdoTAF;               // 
        1,  // i4FpsRemapTblEnable;         // 0:disable, 1:enable
        {10, 12}, // i4FpsThres[2];        // two fps threshold {very-low, low}
        {0, 0},   // i4TableClipPt[2];     // clip pts at macro side
        {80, 90}, // i4TableRemapPt[2];    // percentage of new/org table length

        // --- Easytuning ---   
        {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        },// i4EasyTuning[100]

        // --- DepthAF ---      
        {
             12, 120,  10,  30,  70, 100,   1, 100, 100, 100,  -1,   1,   1,   1,   1,   1,   1,   1,  -1,   1, 
              0,   0,  -2,   0,  -2,  -1,   0,  -1,  -1,   0,   2, 100, 100, 100,   1,   1,   1,   0,   0,   0, 
              0,   0,   0,   0,   1,   1,   1,  -1,  -1,  -1,   0,   0,  -1,   0,   3, 100, 100, 100,  -6,  -8, 
            -10, -14, -22, -20, -32, -41, -32, -63,   2,   6,  11,  17,  17,  29,  25,  22,  40, -63,   4, 100, 
            100, 100,  -2,   0,   0,   1,   0,  -1,   0,   0,   1,  -1,   1,   0,   0,  -1,  -1,  -1,  14,  -1, 
              0,  -2,   5, 100, 100, 100,  -1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,  11,   0,   0,  -1,   6, 100, 100, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   9,   0,   0,   0,   7, 100, 100, 100,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   7,   0,   0,   0,   8, 100, 100, 100,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   0,   0,   0,   9, 100, 
            100, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   0, 
              0,   0,  10, 100, 100, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   4,   0,   0,   0,  11, 100, 100, 100,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   3,   0,   0,   0,  12, 100, 100, 100,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
              0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
        }, // i4DepthAF[500]

        // --- reserved ---     
        {    
		    // i4Coefs[0]  inclinePeak rejection;   0: is disable, 1: is enable
		    // i4Coefs[1]  fdOffMaxCnt;             fd turnOff maxCnt for exiting faceAF, 0: use default value 10
		    // i4Coefs[41]  isPLenable;             0: is disable, 1: is enable
		    // i4Coefs[42]  plFlashReject;          0: is default, 1: is reject PL when flash
		    // i4Coefs[43]  plThresNsLv;            lv for night scene
		    // i4Coefs[44]  plThresIdLv;            lv for indoor
		    // i4Coefs[45]  plRatioNs;              ratio 0~100, from detect rate high to false alarm low
		    // i4Coefs[46]  plRatioId;              ratio 0~100, from detect rate high to false alarm low
		    // i4Coefs[47]  plRev1;
		    // i4Coefs[48]  plRev2;
		    // i4Coefs[49]  plRev3;
		    // i4Coefs[50]  plRev4;
		    0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // [0]~[10]
		    0,10, 40, 5, 100, 50, 150, 10, 0, 0,     // [11]~[20] for SDAF
		    0,30, 50, 5, 100, 50, 150, 10, 0, 0,     // [21]~[30] for PDAF
		    37,38, 3, 1014, 80030, 5005, 5, 1001, 50, 14,     // [31]~[40] for DAF
		    0,0, 30, 100, 90, 70, 0, 0, 0, 0,     // [41]~[50] for PL detect
		    0,0, 0, 0, 0, 0, 0, 0, 0, 0,     // [51]~[60]
		    0,0, 0, 0, 0, 0, 0, 0, 0, 0,     // [61]~[70] for LaserAF
		    0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,     // [71]~[85] for LaserAF CalibData
		    0, 0, // [86]~[87] for LaserAF CalibData Offset, XTalk; Value = Enable * 10000 + CalibData
        } // i4Coefs[100];    
    },                          
    {//PD_NVRAM_T
        {//PD_CALIBRATION_DATA_T
            {0},
            0,
        },
        {//PD_ALGO_TUNING_T
            32,
            8,
            {30, 100, 200, 300, 400},
            {384, 410, 435, 461, 486},
            {
                {0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0},
                {0, 20, 20, 20, 20, 20},
                {0, 20, 60, 60, 60, 60},
                {0, 20, 60, 60, 60, 60},
                {0, 20, 60, 60, 60, 100},
            },
            230,
            8,
            10,
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        },
    },
    {0}                         
};
