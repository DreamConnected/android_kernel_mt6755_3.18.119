/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef _LENS_LIST_H

#define _LENS_LIST_H

#define AD5820AF_SetI2Cclient AD5820AF_SetI2Cclient_Main
#define AD5820AF_Ioctl AD5820AF_Ioctl_Main
#define AD5820AF_Release AD5820AF_Release_Main
extern int AD5820AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long AD5820AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int AD5820AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define BU6424AF_SetI2Cclient BU6424AF_SetI2Cclient_Main
#define BU6424AF_Ioctl BU6424AF_Ioctl_Main
#define BU6424AF_Release BU6424AF_Release_Main
extern int BU6424AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long BU6424AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int BU6424AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define BU6429AF_SetI2Cclient BU6429AF_SetI2Cclient_Main
#define BU6429AF_Ioctl BU6429AF_Ioctl_Main
#define BU6429AF_Release BU6429AF_Release_Main
extern int BU6429AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long BU6429AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int BU6429AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define DW9714AF_SetI2Cclient DW9714AF_SetI2Cclient_Main
#define DW9714AF_Ioctl DW9714AF_Ioctl_Main
#define DW9714AF_Release DW9714AF_Release_Main
extern int DW9714AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long DW9714AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int DW9714AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define DW9763AF_SetI2Cclient DW9763AF_SetI2Cclient_Main
#define DW9763AF_Ioctl DW9763AF_Ioctl_Main
#define DW9763AF_Release DW9763AF_Release_Main
extern int DW9763AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long DW9763AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int DW9763AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define DW9763XAF_SetI2Cclient DW9763XAF_SetI2Cclient_Main
#define DW9763XAF_Ioctl DW9763XAF_Ioctl_Main
#define DW9763XAF_Release DW9763XAF_Release_Main
extern int DW9763XAF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long DW9763XAF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int DW9763XAF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define DW9800AF_SetI2Cclient DW9800AF_SetI2Cclient_Main
#define DW9800AF_Ioctl DW9800AF_Ioctl_Main
#define DW9800AF_Release DW9800AF_Release_Main
extern int DW9800AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long DW9800AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int DW9800AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define LC898212AF_SetI2Cclient LC898212AF_SetI2Cclient_Main
#define LC898212AF_Ioctl LC898212AF_Ioctl_Main
#define LC898212AF_Release LC898212AF_Release_Main
extern int LC898212AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long LC898212AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int LC898212AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#define LC898214AF_SetI2Cclient LC898214AF_SetI2Cclient_Main
#define LC898214AF_Ioctl LC898214AF_Ioctl_Main
#define LC898214AF_Release LC898214AF_Release_Main
extern int LC898214AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
extern long LC898214AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
extern int LC898214AF_Release(struct inode *a_pstInode, struct file *a_pstFile);

#endif
