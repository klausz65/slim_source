#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2007, 2011, Oracle and/or its affiliates. All rights reserved.
#
# LibOrchestrator Makefile
#

LIBRARY	= liborchestrator.a
VERS	= .1

OBJECTS	= \
	disk_info.o \
	disk_parts.o \
	disk_slices.o \
	disk_target.o \
	disk_util.o \
	locale.o	\
	om_misc.o \
	om_proc.o \
	perform_slim_install.o \
	system_util.o \
	target_discovery.o \
	timezone.o \
	upgrade_targets.o

SRCS = $(OBJECTS:.o=.c)

PRIVHDRS = orchestrator_private.h
EXPHDRS = orchestrator_api.h
HDRS		= $(EXPHDRS) $(PRIVHDRS)

include ../Makefile.lib

INCLUDE		 = -I. \
		   -I$(ROOTINCADMIN) \
		   -I../libtd/ \
		   -I../liblogsvc \
		   -I../libti

CPPFLAGS	+= ${INCLUDE} -D${ARCH}
CFLAGS		+= $(DEBUG_CFLAGS)  ${CPPFLAGS}
LDFLAGS		+=
SOFLAGS		+= -L$(ROOTADMINLIB) -R$(ROOTADMINLIB:$(ROOT)%=%) \
		-ltd -lnvpair -lict \
		-llogsvc -ltransfer -lti -lzoneinfo

LINTERR		= lint_errors
LINTFILES	= ${SRCS:%.c=${ARCH}/%.ln}
LINTFLAGS	= -umx ${CPPFLAGS}

# make validate_pkg happy.
FILEMODE = 0444
$(ROOTADMINLIBDYNLIB):= FILEMODE = 0755

CLOBBERFILES	= *.po *.mo

MSG_DOMAIN	= SUNW_INSTALL_LIBORCHESTRATOR

.KEEP_STATE:


all: $(HDRS) .WAIT static dynamic
	@true

static: $(LIBS)

dynamic: $(DYNLIB) .WAIT $(DYNLIBLINK)

psymlink:
	@cd $(ROOTPYTHONVENDORINSTALL); $(SYMLINK) ../../../../snadm/lib/libtransfer.so.1 libtransfer.so

install:	all .WAIT \
		$(ROOTADMINLIB) .WAIT $(ROOTADMINLIBS) $(ROOTADMINLIBDYNLIB) \
		.WAIT $(ROOTADMINLIBDYNLIBLINK) \
		$(ROOTOPTADMINLIBDYNLIB) .WAIT $(ROOTOPTADMINLIBDYNLIBLINK) \
		.WAIT msgs .WAIT $(INSTMSGS) psymlink

install_h:	$(ROOTUSRINCLEXP)

msgs: ${MSG_DOMAIN}.po

${MSG_DOMAIN}.po: ${SRCS} ${HDRS}
	@echo "Making messages file ${MSG_DOMAIN}.po"
	@${COMPILE.c} -C -E ${SRCS} 2>/dev/null | \
		xgettext -d ${MSG_DOMAIN} -s \
			-c "i18n:" - >/dev/null 2>&1
 
lint:  ${SRCS} ${HDRS}
	${LINT.c} ${SRCS}

cstyle:	$(SRCS) $(PRIVHDRS) $(PUBHDRS)
	cstyle $(SRCS) $(PRIVHDRS) $(PUBHDRS)

include ../Makefile.targ
