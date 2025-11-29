#!/bin/bash

HOST="localhost"
PORT="6667"

########################################
# 1) CLIENT 1 : OPERATEUR / INVITEUR
########################################
{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK inviter"
    sleep 0.2
    echo "USER u1 0 * :inviter"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.5

    ####################################
    # TEST 1 : inviter un nick inexistant
    ####################################
    echo "INVITE randomnick #chips"
    sleep 0.5

    ####################################
    # TEST 2 : inviter dans un channel inexistant
    ####################################
    echo "INVITE tester #nochannel"
    sleep 0.5

    ####################################
    # TEST 3 : inviter quelqu’un mais on n’est PAS dans le channel
    ####################################
    echo "PART #chips"
    sleep 0.3
    echo "INVITE tester #chips"
    sleep 0.5

    ####################################
    # TEST 4 : remettre inviter dans #chips
    ####################################
    echo "JOIN #chips"
    sleep 0.5

    ####################################
    # TEST 5 : tester déjà dans le channel
    ####################################
    echo "INVITE tester #chips"
    sleep 0.5

    ####################################
    # TEST 6 : channel en mode +i sans être opérateur
    ####################################
    echo "MODE #chips +i"
    sleep 0.3
    echo "INVITE tester #chips"
    sleep 0.5

    ####################################
    # TEST 7 : être opérateur et inviter OK
    ####################################
    echo "MODE #chips -i"
    sleep 0.3
    echo "MODE #chips +o inviter"
    sleep 0.3
    echo "INVITE tester #chips"
    sleep 1

} | nc -C $HOST $PORT &



########################################
# 2) CLIENT 2 : LA PERSONNE A INVITER
########################################
{
    sleep 1
    echo "PASS theo2"
    sleep 0.2
    echo "NICK tester"
    sleep 0.2
    echo "USER u2 0 * :tester"
    sleep 2

    ####################################
    # Attendre l’invitation
    ####################################
    sleep 5
    echo "JOIN #chips"

    sleep 2
} | nc -C $HOST $PORT
