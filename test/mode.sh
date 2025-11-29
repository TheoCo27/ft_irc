#!/bin/bash

HOST="localhost"
PORT="6667"
# CLIENT 1 : opérateur / testeu####
{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK op"
    sleep 0.2
    echo "USER user1 0 * :OpUser"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.2

    # MODE : pas assez de paramètres
    echo "MODE"
    sleep 0.2

    # MODE : channel inexistant
    echo "MODE #nochan +i"
    sleep 0.5

	# MODE : vous etes pas op
	echo "JOIN #not_op"
    sleep 0.5
    echo "MODE #not_op +i"
    sleep 0.5

    # MODE : pas dans le channel
    echo "MODE #not_invited +i"
    sleep 0.5

    # MODE : afficher les modes d’un channel
    echo "MODE #chips"
    sleep 0.5

    # MODE : mode invalide
    echo "MODE #chips +x"
    sleep 0.5

    # MODE : +i (invite only)
    echo "MODE #chips +i"
    sleep 0.5

    # MODE : -i
    echo "MODE #chips -i"
    sleep 0.5

    # MODE : +t (topic lock)
    echo "MODE #chips +t"
    sleep 0.5

    # MODE : -t
    echo "MODE #chips -t"
    sleep 0.5

    # MODE : +k password
    echo "MODE #chips +k secretpass"
    sleep 0.5

    # MODE : -k
    echo "MODE #chips -k"
    sleep 0.5

    # MODE : +l limit OK
    echo "MODE #chips +l 10"
    sleep 0.5

    # MODE : +l ERROR limit invalide
    echo "MODE #chips +l 0"
    sleep 0.5

    # MODE : -l
    echo "MODE #chips -l"
    sleep 0.5

    # MODE : +l no arg
    echo "MODE #chips +l"
    sleep 0.5

    # MODE : +o no arg
    echo "MODE #chips +o"
    sleep 0.5

    # MODE : +k no arg
    echo "MODE #chips +k"
    sleep 0.5

    # MODE : +o donner op au client 2
    echo "MODE #chips +o guest"
    sleep 0.5

    # MODE : -o retirer op au client 2
    echo "MODE #chips -o guest"
    sleep 0.5

    # MODE : +o ERROR user pas dans channel
    echo "MODE #chips +o nothere"
    sleep 0.5

} | nc -C $HOST $PORT