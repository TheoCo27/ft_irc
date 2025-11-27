#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK tester"
    sleep 0.2
    echo "USER user_theo 0 * :realname_theo"
    sleep 0.2
    echo "JOIN #test"
    sleep 0.2
    echo "PART"
    sleep 0.2
    echo "PART #no_channel"
    sleep 0.2
    echo "PART #chips"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.2
    echo "PART #chips ain't gott no reason okay ?! I just want to leave"
} | nc -C $HOST $PORT
