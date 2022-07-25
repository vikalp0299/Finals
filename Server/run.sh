#!/bin/bash

output=$( sudo g++ -std=c++0x -pthread -Wall -I /usr/include/mysql/ -o out main2.cpp src/*  -L /usr/lib -lmysqlclient -I /home/authenticator/Desktop/FINAL_PRODUCE/Server/includes/ -I /usr/include/mysql -I /usr/local/crypto  -lstdc++fs  -lcrypto -lssl -L /usr/local/crypto -lcryptopp)
echo $output

if [[ $output == "" ]]; then 
	./out
fi
