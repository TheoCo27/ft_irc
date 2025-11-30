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
    echo "JOIN #topic_restrict"
	sleep 0.2
    echo "JOIN #t2_restrict"
	sleep 10
    echo "TOPIC"
	sleep 0.2
    echo "TOPIC #no_channel"
	sleep 0.2
    echo "TOPIC #chips"
	sleep 0.2
    echo "JOIN #chips"
	sleep 0.2
    echo "TOPIC #chips"
	sleep 0.2
    echo "TOPIC #chips Ici sa parle de chips ok ?!"
	sleep 0.2
    echo "TOPIC #chips"
	sleep 0.2
    echo "TOPIC #topic_restrict I GOT THE POWER"
	sleep 0.2
    echo "TOPIC #t2_restrict NOW I GOT THE POWER"
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
    echo \"JOIN #topic_restrict\"
    sleep 0.3
    echo \"JOIN #t2_restrict\"
    sleep 2
    echo \"MODE #topic_restrict +t\"
    sleep 0.3
    echo \"MODE #t2_restrict +t\"
    sleep 0.3
	echo \"MODE #t2_restrict +o tester\"

} | nc -C $HOST $PORT
exec bash
"
