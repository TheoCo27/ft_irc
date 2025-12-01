#!/bin/bash

HOST="localhost"
PORT="6667"

########################################
# CLIENT 1 : opérateur / celui qui kick
########################################
{
    sleep 2
    echo "PASS theo"
    sleep 0.2
    echo "NICK op"
    sleep 0.2
    echo "USER u1 0 * :Operator"
    sleep 1
    echo "JOIN #chips"
    sleep 0.5
    echo "JOIN #alone"
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
    # TEST 3 : Channel inexistant ou pas dans le channel
    ####################################
    echo "KICK #nochannel guest"
    sleep 0.5
    echo "KICK #not_in_channel guest"
    sleep 0.5
    ####################################
    # TEST 4 : cible pas dans channel
    ####################################
    echo "KICK #alone guest"
    sleep 0.5

    ####################################
    # TEST 5 : nous ne sommes PAS opérateur
    ####################################
    echo "JOIN #not_op"
    sleep 0.5
    echo "KICK #not_op guest"
    sleep 0.5

    ####################################
    # TEST 6 : kick normal
    ####################################
    echo "KICK #chips g1"
    sleep 1

    ####################################
    # TEST 7 : kick avec raison
    ####################################
    echo "KICK #chips g2 :because I can"
    sleep 1

    ####################################
    # TEST 8 : kick d’un opérateur
    ####################################
    echo "KICK #chips guest :bye operator"
    sleep 1

} | nc -C $HOST $PORT &



########################################
# CLIENT 2 : guest (doit être kické)
########################################

gnome-terminal -- bash -c "
{
    sleep 1
    echo \"PASS theo\"
    sleep 0.2
    echo \"NICK guest\"
    sleep 0.2
    echo \"USER u2 0 * :GuestUser\"
    sleep 0.3
    echo \"JOIN #chips\"
	sleep 0.3
    echo \"JOIN #not_op\"
	sleep 0.3
    echo \"JOIN #not_in_channel\"
	sleep 2
	echo \"MODE #chips +o op\"
    sleep 6

} | nc -C $HOST $PORT
exec bash
"

########################################
# CLIENT 2 : guest (doit être kické)
########################################

gnome-terminal -- bash -c "
{
    sleep 2
    echo \"PASS theo\"
    sleep 0.2
    echo \"NICK g1\"
    sleep 0.2
    echo \"USER u3 0 * :GuestUser\"
    sleep 0.3
    echo \"JOIN #chips\"
	sleep 0.3

} | nc -C $HOST $PORT
exec bash
"

########################################
# CLIENT 2 : guest (doit être kické)
########################################

gnome-terminal -- bash -c "
{
    sleep 2
    echo \"PASS theo\"
    sleep 0.2
    echo \"NICK g2\"
    sleep 0.2
    echo \"USER u4 0 * :GuestUser\"
    sleep 0.3
    echo \"JOIN #chips\"
	sleep 0.3

} | nc -C $HOST $PORT
exec bash
"