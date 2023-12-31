CC = gcc
CPP = g++
LIB = ./lib
PROCESSPOOL = ./processpool
TIMER = ./timer
LOCKER = ./locker
HTTP = ./http
CFLAGS = -O0 -I$(LIB) -I$(PROCESSPOOL) -I$(TIMER) -I$(LOCKER) -I$(HTTP) -Wall -Wextra -g
SHARED_FLAGS = -shared -fpic

target = $(patsubst $(LIB)/%.c,%.so,$(wildcard $(LIB)/*.c))

.PHONY: all clean

all: ${target} server
	@echo "compile all shared library"
	@echo ${target}
# 编译动态库

%.so: $(LIB)/%.c $(LIB)/%.h
	$(CC) $(CFLAGS) $(SHARED_FLAGS) -o $(LIB)/$@ $<

error_functions.so: $(LIB)/error_functions.c $(LIB)/error_functions.h $(LIB)/tlsp_hdr.h $(LIB)/ename.c.inc
	$(CC) $(CFLAGS) $(SHARED_FLAGS) -o $(LIB)/$@ $<

signal_functions.so: $(LIB)/signal_functions.c $(LIB)/signal_functions.h error_functions.so $(LIB)/tlsp_hdr.h
	$(CC) $(CFLAGS) $(SHARED_FLAGS) -o $(LIB)/$@ $< $(LIB)/error_functions.so

server: server.cc $(LIB)/* $(PROCESSPOOL)/* $(TIMER)/*
	$(CPP) $< $(CFLAGS) -lpthread -o $@
clean:
	-rm $(LIB)/*.so server
