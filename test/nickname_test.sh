#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
	echo "NICK theo"
	sleep 0.2
    echo "PASS theo"
    sleep 0.2
	echo "NICK"
    sleep 0.2
	echo "NICK theo"
    sleep 0.2
    echo "NICK nickname_too_long"
	sleep 0.2
    echo "NICK bot"
	sleep 0.2
    echo "NICK #nick"
	sleep 0.2
    echo "NICK &nick"
	sleep 0.2
    echo "NICK 67nick"
	sleep 0.2
    echo "NICK @nick"
	sleep 0.2
    echo "NICK theo"
	sleep 0.2
    echo "USER nick_tester 0 * :realname_theo"
    sleep 0.2
	echo "NICK nicomok"
	sleep 0.2
	echo "JOIN #chips"
	sleep 0.2
    echo "NICK new-nick"
} | nc -C $HOST $PORT
