#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK tester"
    sleep 0.2
    echo "USER user_theo 0 * :realname_theo"
    sleep 0.2
    echo "PRIVMSG"
    sleep 0.2
    echo "PRIVMSG theo"
    sleep 0.2
    echo "PRIVMSG no_one hey baby sa dit quoi t as du feu ?"
    sleep 0.2
    echo "PRIVMSG #chips Yoh l equipe si yen a un instalock je dodge direct"
    sleep 0.2
    echo "PRIVMSG #no_chan Yoh l equipe si yen a un instalock je dodge direct"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.2
    echo "PRIVMSG #chips Yoh l equipe si yen a un instalock je dodge direct"
    sleep 0.2
    echo "PRIVMSG theo hey baby sa dit quoi ?"
    sleep 0.2
    echo "PRIVMSG bot help please"
} | nc -C $HOST $PORT & 

########################################
# CLIENT 2 : observer (nouveau terminal)
########################################
gnome-terminal -- bash -c "
{
    sleep 1
    echo \"PASS theo\"
    sleep 0.2
    echo \"NICK theo\"
    sleep 0.2
    echo \"USER u2 0 * :WatcherUser\"

    sleep 0.3
    echo \"JOIN #chips\"
    sleep 0.3

} | nc -C $HOST $PORT
exec bash
"
