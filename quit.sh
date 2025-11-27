#!/bin/bash

HOST="localhost"
PORT="6667"

########################################
# CLIENT 1 : celui qui QUIT
########################################
{
    sleep 1
    echo "PASS pass1"
    sleep 0.2
    echo "NICK quitter"
    sleep 0.2
    echo "USER u1 0 * :QuitUser"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.3
    echo "JOIN #snacks"
    sleep 0.4

    ####################################
    # TEST 1 : QUIT sans raison
    ####################################
    echo "QUIT"
    sleep 1

} | nc -C $HOST $PORT &


########################################
# CLIENT 2 : observer (doit recevoir le QUIT du client 1)
########################################
{
    sleep 1
    echo "PASS pass2"
    sleep 0.2
    echo "NICK watcher"
    sleep 0.2
    echo "USER u2 0 * :WatcherUser"

    sleep 0.3
    echo "JOIN #chips"
    sleep 0.3
    echo "JOIN #snacks"
    sleep 3

    ####################################
    # TEST 2 : QUIT avec raison explicite
    ####################################
    echo "QUIT Leaving_the_server_bye!"
    sleep 2

} | nc -C $HOST $PORT &


########################################
# CLIENT 3 : un autre user dans #snacks
########################################
{
    sleep 1
    echo "PASS pass3"
    sleep 0.2
    echo "NICK snacky"
    sleep 0.2
    echo "USER u3 0 * :SnackUser"
    sleep 0.3
    echo "JOIN #snacks"

    sleep 6
} | nc -C $HOST $PORT
