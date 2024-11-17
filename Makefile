#! /usr/bin/make -f

## @file
# @brief Makefile for gprof_sample.
# @copyright
#   Copyright (c) 2024 Mitsutoshi Nakano
#   SPDX-License-Identifier: GPL-3.0-or-later

TARGETS=gprof_sample
gprof_sample_SRCS=gprof_sample.c
gprof_sample_OBJS=$(gprof_sample_SRCS:.c=.o)
OBJS=$(gprof_sample_OBJS)

CFLAGS=$(PROFILE) -Wall -Wextra -Werror -std=gnu23 -pedantic
CC=gcc-14

.PHONY: all gproff check clean
all gprof: $(TARGETS)
gprof: PROFILE=-pg -g -O0
gprof_sample: $(gprof_sample_OBJS)
	$(CC) $(CFLAGS) -o gprof_sample $(gprof_sample_OBJS)
check: clean gprof
	./gprof_sample -r 100000
	gprof ./gprof_sample gmon.out > gprof.txt
	gprof -A ./gprof_sample gmon.out > gprof-A.txt
clean:
	$(RM) $(TARGETS) $(OBJS) gprof.txt gprof-A.txt gmon.out
