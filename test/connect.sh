#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK theo"
    sleep 0.2
    echo "USER user_theo 0 * :realname_theo"
} | nc -C $HOST $PORT
