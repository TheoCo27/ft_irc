#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
	echo "USER theo" #not enough args
	sleep 0.2
    echo "USER USER_tester 0 * :realname_theo" #before PASS
	sleep 0.2
    echo "PASS theo"
	sleep 0.2
    echo "NICK tester"
	sleep 0.2
    echo "USER use@rna!me_too_long 0 * :realname_really fucking long that support spaces but no more than 50 char"
} | nc -C $HOST $PORT
