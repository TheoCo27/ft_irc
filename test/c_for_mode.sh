#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK guest"
    sleep 0.2
    echo "USER user_theo 0 * :realname_theo"
    sleep 0.2
    echo "JOIN #not_invited"
	sleep 0.2
    echo "JOIN #not_op"
	sleep 0.2
	echo "JOIN #your_op"
	sleep 0.2
	echo "JOIN #chips"
	sleep 2
	echo "MODE #your_op +o op"
	sleep 0.2
	echo "MODE #chips +o op"
} | nc -C $HOST $PORT
