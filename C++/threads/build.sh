#!/bin/bash

gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS threadHello.c -c -o threadHello.o
gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS thread.c -c -o thread.o
gcc threadHello.o thread.o -lpthread -o threadHello
./threadHello
