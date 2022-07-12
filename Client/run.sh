#!/bin/bash

output=$(sudo g++ -std=c++0x -pthread -Wall main.cpp src/* -o out -I includes -I /usr/local/crypt/ -lcryptopp -I /usr/local/cpp-httplib-0.10.8/ -I /usr/local -lcrypto -lssl)

echo $output

if [[ $output == "" ]]; then
	./out
fi
