#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 3
    echo "PASS theo"
    sleep 0.2
    echo "NICK tester"
    sleep 0.2
    echo "USER user_theo 0 * :realname_theo"
    sleep 0.2
    echo "JOIN #test"
    sleep 0.2
    echo "PART"
    sleep 0.2
    echo "PART #no_channel"
    sleep 0.2
    echo "PART #chips"
    sleep 0.2
    echo "PART #test"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.2
    echo "PART #chips ain't gott no reason okay ?! I just want to leave"
} | nc -C $HOST $PORT &

########################################
# CLIENT 2 : watcher (nouveau terminal)
########################################
gnome-terminal -- bash -c "
{
    sleep 1
    echo \"PASS theo\"
    sleep 0.2
    echo \"NICK watcher\"
    sleep 0.2
    echo \"USER u3 0 * :WatchingYourAss\"
    sleep 0.3
    echo \"JOIN #chips\"
    sleep 0.3
    echo \"JOIN #test\"

} | nc -C $HOST $PORT
exec bash
"
