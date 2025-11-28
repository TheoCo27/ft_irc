#!/bin/bash

HOST="localhost"
PORT="6667"

########################################
# CLIENT 1 : opérateur / testeur
########################################
{
    sleep 1
    echo "PASS pass1"
    sleep 0.2
    echo "NICK op"
    sleep 0.2
    echo "USER user1 0 * :OpUser"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.5

    ####################################
    # MODE : pas assez de paramètres
    ####################################
    echo "MODE"
    sleep 0.5

    ####################################
    # MODE : channel inexistant
    ####################################
    echo "MODE #nochan +i"
    sleep 0.5

    ####################################
    # MODE : afficher les modes d’un channel
    ####################################
    echo "MODE #chips"
    sleep 0.5

    ####################################
    # MODE : mode invalide
    ####################################
    echo "MODE #chips +x"
    sleep 0.5

    ####################################
    # MODE : +i (invite only)
    ####################################
    echo "MODE #chips +i"
    sleep 0.5

    ####################################
    # MODE : -i
    ####################################
    echo "MODE #chips -i"
    sleep 0.5

    ####################################
    # MODE : +t (topic lock)
    ####################################
    echo "MODE #chips +t"
    sleep 0.5

    ####################################
    # MODE : -t
    ####################################
    echo "MODE #chips -t"
    sleep 0.5

    ####################################
    # MODE : +k password
    ####################################
    echo "MODE #chips +k secretpass"
    sleep 0.5

    ####################################
    # MODE : -k
    ####################################
    echo "MODE #chips -k"
    sleep 0.5

    ####################################
    # MODE : +l limit OK
    ####################################
    echo "MODE #chips +l 10"
    sleep 0.5

    ####################################
    # MODE : +l ERROR limit invalide
    ####################################
    echo "MODE #chips +l 0"
    sleep 0.5

    ####################################
    # MODE : -l
    ####################################
    echo "MODE #chips -l"
    sleep 0.5

    ####################################
    # MODE : +o donner op au client 2
    ####################################
    echo "MODE #chips +o guest"
    sleep 0.5

    ####################################
    # MODE : -o retirer op au client 2
    ####################################
    echo "MODE #chips -o guest"
    sleep 0.5

    ####################################
    # MODE : +o ERROR user pas dans channel
    ####################################
    echo "MODE #chips +o nothere"
    sleep 0.5

} | nc -C $HOST $PORT &



########################################
# CLIENT 2 : user normal
########################################
{
    sleep 1
    echo "PASS pass2"
    sleep 0.2
    echo "NICK guest"
    sleep 0.2
    echo "USER user2 0 * :GuestUser"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.2

    sleep 4
} | nc -C $HOST $PORT
