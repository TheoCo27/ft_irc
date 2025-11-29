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
    sleep 5
    echo "JOIN"
    sleep 0.2
    echo "JOIN #chan1"
    sleep 0.2
    echo "JOIN #chan2"
	sleep 0.2
    echo "JOIN 0"
	sleep 0.2
    echo "JOIN 0"
	sleep 0.2
    echo "JOIN #channel_way_too_fucking_to_be_created_i_mean_who_could_possibly_enter_a_name_this_long"
	sleep 0.2
    echo "JOIN guess_who_forgot_something"
	sleep 0.2
    echo "JOIN puttting_some		tabs"
	sleep 0.2
    echo "JOIN #chan1"
    sleep 0.2
    echo "JOIN #chan2"
	sleep 0.2
    echo "JOIN #chan3"
    sleep 0.2
    echo "JOIN #chan4"
	sleep 0.2
    echo "JOIN #chan5"
    sleep 0.2
    echo "JOIN #chan6"
	sleep 0.2
    echo "JOIN #chan7"
    sleep 0.2
    echo "JOIN #chan8"
	sleep 0.2
    echo "JOIN #chan9"
    sleep 0.2
    echo "JOIN #chan10"
	sleep 0.2
    echo "JOIN #chan11"
    sleep 0.2
    echo "JOIN #chan12"
	sleep 0.2
    echo "JOIN 0"
	sleep 0.2
    echo "JOIN #chips"
    sleep 0.2
    echo "JOIN #not_invited"
    sleep 0.2
    echo "JOIN #invited"
    sleep 0.2
    echo "JOIN #too_many_user"
    sleep 0.2
    echo "JOIN #guess_pass bambi" #wrong_pass
    sleep 0.2
    echo "JOIN #guess_pass" #no_pass
    sleep 0.2
    echo "JOIN #guess_pass bambino" #good_pass
} | nc -C $HOST $PORT
