#!/bin/bash

output=$( sudo g++ -pthread -Wall -o out main.cpp src/*   -I /home/authenticator/Desktop/FINAL_PRODUCE/Client/includes/)
echo $output

if [[ $output == "" ]]; then 
	./out
fi
