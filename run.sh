#!/bin/bash

output=$( sudo g++ -pthread -Wall -I /usr/include/mysql/ -o out main.cpp src/*  -L /usr/lib -lmysqlclient -I /home/authenticator/Desktop/FINAL_PRODUCE/includes/)
echo $output

if [[ $output == "" ]]; then 
	./out
fi
