#!/bin/bash

HOST="localhost"
PORT="6667"

########################################
# CLIENT 1 : opérateur / celui qui kick
########################################
{
    sleep 1
    echo "PASS pass1"
    sleep 0.2
    echo "NICK op"
    sleep 0.2
    echo "USER u1 0 * :Operator"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.5

    ####################################
    # TEST 1 : Pas assez de paramètres
    ####################################
    echo "KICK"
    sleep 0.5

    ####################################
    # TEST 2 : Nick inexistant
    ####################################
    echo "KICK #chips nosuchnick"
    sleep 0.5

    ####################################
    # TEST 3 : Channel inexistant
    ####################################
    echo "KICK #nochannel guest"
    sleep 0.5

    ####################################
    # TEST 4 : cible pas dans channel
    ####################################
    echo "KICK #chips stranger"
    sleep 0.5

    ####################################
    # TEST 5 : nous ne sommes PAS opérateur dans un autre channel
    ####################################
    echo "JOIN #foo"
    sleep 0.5
    echo "KICK #foo guest"
    sleep 0.5

    ####################################
    # Retour sur #chips
    ####################################
    echo "PART #foo"
    echo "JOIN #chips"
    sleep 0.5

    ####################################
    # TEST 6 : kick normal
    ####################################
    echo "KICK #chips guest"
    sleep 1

    ####################################
    # TEST 7 : kick avec raison
    ####################################
    echo "KICK #chips guest2 :because I can"
    sleep 1

    ####################################
    # TEST 8 : kick d’un opérateur
    ####################################
    echo "KICK #chips guestop :bye operator"
    sleep 1

} | nc -C $HOST $PORT &



########################################
# CLIENT 2 : guest (doit être kické)
########################################
{
    sleep 1
    echo "PASS pass2"
    sleep 0.2
    echo "NICK guest"
    sleep 0.2
    echo "USER u2 0 * :GuestUser"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.5

    sleep 8
} | nc -C $HOST $PORT &



########################################
# CLIENT 3 : guest2 (kick avec raison)
########################################
{
    sleep 1
    echo "PASS pass3"
    sleep 0.2
    echo "NICK guest2"
    sleep 0.2
    echo "USER u3 0 * :GuestTwo"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.5

    sleep 10
} | nc -C $HOST $PORT &



########################################
# CLIENT 4 : guestop (opérateur qu’on kick)
########################################
{
    sleep 1
    echo "PASS pass4"
    sleep 0.2
    echo "NICK guestop"
    sleep 0.2
    echo "USER u4 0 * :GuestOP"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.4
    echo "MODE #chips +o guestop"
    sleep 0.5

    sleep 12
} | nc -C $HOST $PORT
