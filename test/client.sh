#!/bin/bash

HOST="localhost"
PORT="6667"

{
    sleep 1
    echo "PASS theo"
    sleep 0.2
    echo "NICK theo"
    sleep 0.2
    echo "USER user_theo 0 * :realname_theo"
    sleep 0.2
    echo "JOIN #chips"
    sleep 0.2
    echo "JOIN #not_invited"
    sleep 0.2
    echo "MODE #not_invited +i"
    sleep 0.2
    echo "JOIN #invited"
    sleep 0.2
    echo "MODE #invited +i"
    sleep 20
    echo "INVITE tester #invited"
    sleep 0.2
    echo "JOIN #too_many_user"
    sleep 0.2
    echo "MODE #too_many_user +l 1"
    sleep 0.2
    echo "JOIN #guess_pass"
    sleep 0.2
    echo "MODE #guess_pass +k bambino"
    sleep 0.2
    echo "JOIN #topic_restrict"
    sleep 0.2
    echo "MODE #topic_restrict +t"
    sleep 0.2
    echo "JOIN #t2_restrict"
    sleep 0.2
    echo "MODE #t2_restrict +o tester"
} | nc -C $HOST $PORT
