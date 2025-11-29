#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
	echo "PASS chips"
} | nc -C $HOST $PORT

