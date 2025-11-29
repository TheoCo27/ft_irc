#!/bin/bash

HOST="localhost"
PORT="6667"

########################################
# CLIENT 1 : celui qui QUIT (terminal actuel)
########################################
{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK quitter"
    sleep 0.2
    echo "USER u1 0 * :QuitUser"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.3
    echo "JOIN #snacks"
    sleep 0.4

    # TEST 1 : QUIT sans raison
    echo "QUIT"
    sleep 1

} | nc -C $HOST $PORT &


########################################
# CLIENT 2 : observer (nouveau terminal)
########################################
gnome-terminal -- bash -c "
{
    sleep 1
    echo \"PASS theo\"
    sleep 0.2
    echo \"NICK watcher\"
    sleep 0.2
    echo \"USER u2 0 * :WatcherUser\"

    sleep 0.3
    echo \"JOIN #chips\"
    sleep 0.3
    echo \"JOIN #snacks\"
    sleep 3

    # TEST 2 : QUIT avec raison
    echo \"QUIT Leaving_the_server_bye!\"
    sleep 2

} | nc -C $HOST $PORT
exec bash
"


########################################
# CLIENT 3 : user dans #snacks (nouveau terminal)
########################################
gnome-terminal -- bash -c "
{
    sleep 1
    echo \"PASS theo\"
    sleep 0.2
    echo \"NICK snacky\"
    sleep 0.2
    echo \"USER u3 0 * :SnackUser\"
    sleep 0.3
    echo \"JOIN #snacks\"

    sleep 6

} | nc -C $HOST $PORT
exec bash
"
