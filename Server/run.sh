#!/bin/bash

output=$( sudo g++ -std=c++0x -pthread -Wall -I /usr/include/mysql/ -o out main2.cpp src/*  -L /usr/lib -lmysqlclient -I /home/authenticator/Desktop/FINAL_PRODUCE/Server/includes/ -I /usr/include/mysql -lstdc++fs  -lcrypto -lssl)
echo $output

if [[ $output == "" ]]; then 
	./out
fi
