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

# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#

include ../Makefile.master

MANPAGES8 = distro_const.8

FILEMODE = 0444

ROOTMANPAGES8 = $(MANPAGES8:%=$(ROOTMAN8)/%)
ROOTMANPAGES4 = $(MANPAGES4:%=$(ROOTMAN4)/%)

MANPAGES = $(MANPAGES1M) $(MANPAGES4)

all :=		TARGET = all
clean :=	TARGET = clean
clobber :=	TARGET = clobber
install :=	TARGET = install
headers :=	TARGET = headers

all:

headers:

clean:
	rm -f $(MANPAGES)

clobber: clean

install: all $(ROOTMANPAGES8) $(ROOTMANPAGES4)

$(ROOTMAN8)/%: %.txt
	$(INS.rename)

$(ROOTMAN4)/%: %.txt
	$(INS.rename)
