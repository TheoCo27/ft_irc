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
    echo "JOIN #chips"
    sleep 0.2
    echo "PRIVMSG #chips Yoh l equipe si yen a un instalock je dodge direct"
    sleep 0.2
    echo "PRIVMSG #no_channel hey"
    sleep 0.2
    echo "PRIVMSG theo hey baby sa dit quoi ?"
    sleep 0.2
    echo "PRIVMSG bot help please"
    sleep 0.2
    echo "PRIVMSG theo hey"
} | nc -C $HOST $PORT
