#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "PASS"
    sleep 0.2
    echo "PASS theo"
    sleep 0.2
    echo "NICK tester"
    sleep 0.2
    echo "USER user_theo 0 * :realname_theo"
    sleep 0.2
    echo "JOIN #chips"
	sleep 0.2
	echo "PASS chips"
} | nc -C $HOST $PORT