/*-----------------------------------------------------------------------------
 * Copyright (c) 2006, MediaTek Inc.
 * All rights reserved.
 *
 * Unauthorized use, practice, perform, copy, distribution, reproduction,
 * or disclosure of this information in whole or in part is prohibited.
 *-----------------------------------------------------------------------------
 *
 * $Author: daowen.deng $
 * $Date: 2014/07/10 $
 * $RCSfile: x_linux.h,v $
 * $Revision: #1 $
 *
 *---------------------------------------------------------------------------*/


#ifndef X_LINUX_H
#define X_LINUX_H


#include "x_os.h"
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/ioport.h>
#include <asm/io.h>


#undef MODULE_NODE_NAME
#undef MODULE_FOPS
#undef MODULE_INIT_FUNC
#undef MODULE_EXIT_FUNC
#undef MODULE_IO_ADDR
#undef MODULE_IO_LEN


#define DECLARE_MODULE_FOPS(mod)                                            \
                                                                            \
static struct fasync_struct *async_queue = NULL;                            \
int mod##_ioctl(struct inode *inode, struct file *file, unsigned int cmd,   \
              unsigned long arg);                                           \
                                                                            \
static int mod##_fasync(int fd, struct file *filp, int mode)                \
{                                                                           \
	return fasync_helper(fd, filp, mode, &async_queue);                     \
}                                                                           \
                                                                            \
static int mod##_release(struct inode *inode, struct file *filp)            \
{																			\
	int ret = 0;															\
	mod##_fasync(-1, filp, 0);                                              \
	return ret;                                                             \
}                                                                           \
                                                                            \
struct file_operations mod##_fops = {                                       \
    .owner   = THIS_MODULE,                                                 \
    .ioctl   = mod##_ioctl,                                                 \
	.release = mod##_release,                                               \
	.fasync  = mod##_fasync,                                                \
};

extern UINT64 u8Div6432(UINT64 u8Dividend, UINT64 u8Divider, UINT64 *pu8Remainder);

#endif //X_LINUX_H

