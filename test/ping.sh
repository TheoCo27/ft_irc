#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "Voici un PONG Mon Seigneur"
    sleep 0.2
    echo "PING"
} | nc -C $HOST $PORT
