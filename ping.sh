#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "PING renvoie un PONG batard"
    sleep 0.2
    echo "PING"
} | nc -C $HOST $PORT
