/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _TI_DM_H
#define	_TI_DM_H

/*
 * Module:	ti_dm.h
 * Group:
 * Description:	This module contains the Target Instantiation disk module
 *		data structures, constants, and function prototypes.
 */

#include "ti_api.h"
#include "ls_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	IDM_DEBUG	idm_debug_print

/* type definitions */

/* return codes */

typedef enum idm_errno_t {
	IDM_E_SUCCESS,

	/* creating fdisk Solari2 partition on whole disk failed */
	IDM_E_FDISK_WDISK_FAILED,

	IDM_E_VTOC_INVALID,		/* VTOC sanity checking failed */
	IDM_E_VTOC_MODIFIED,		/* VTOC succesfully modified */
	IDM_E_VTOC_ADJUST_FAILED,	/* VTOC can't be adjusted */
	IDM_E_VTOC_ATTR_INVALID,	/* invalid VTOC set of attribtues */
	IDM_E_VTOC_FAILED,		/* VTOC creation failed */
	IDM_E_UNMOUNT_FAILED		/* unmount process failed */
} idm_errno_t;

/* constants */

#define	IDM_MAXCMDLEN		1024

#define	IDM_DBGLVL_ERROR	LS_DBGLVL_ERR
#define	IDM_DBGLVL_WARNING	LS_DBGLVL_WARN
#define	IDM_DBGLVL_NOTICE	LS_DBGLVL_INFO

/* system slice index specifiers */

#define	IDM_ALL_SLICE		2	/* all user accessible space */
#define	IDM_BOOT_SLICE		8	/* fdisk boot block slice */
#define	IDM_ALT_SLICE		9	/* fdisk alternate sector slice */
#define	IDM_LAST_STDSLICE	7	/* last user accessible slice */

/* 1st cylinder is dedicated to BOOT slice on x86 */
#ifdef sparc
#define	IDM_BOOT_SLICE_RES_CYL	0
#else
#define	IDM_BOOT_SLICE_RES_CYL	1
#endif

/* macros */

/* translate cylinders to sectors */

#define	idm_cyls_to_secs(c, nsec)	((c)*(nsec))

/*
 * translate megabytes to cylinders - round appropriately
 * cyls = (mb * 1024 * 1024) / (nsecs * 512)
 * TODO: find appropriate symbolic constant for 512
 * which represents # of bytes per sector
 */

#define	idm_mbs_to_cyls(mb, nsec)	((2048ULL*(mb)+(nsecs)/2)/(nsec))

/*
 * translate cylinders to megabytes - round appropriately
 * mbs = (cyls * nsecs * 512) / (1024*1024)
 * TODO: find appropriate symbolic constant for 512
 * which represents # of bytes per sector
 */

#define	idm_cyls_to_mbs(cyls, nsec)	(((cyls)*(nsecs)+1)/2048ULL)

/* global variables */

/* function prototypes */

idm_errno_t idm_fdisk_whole_disk(char *disk_name);
idm_errno_t idm_create_vtoc(nvlist_t *attrs);
idm_errno_t idm_unmount_all(char *disk_name);

/* Makes TI disk module work in dry run mode */

void idm_dryrun_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* _TI_DM_H */
