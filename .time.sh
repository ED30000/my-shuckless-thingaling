#!bin/bash

while true; do
	xsetroot -name "$(env TZ=Europe/Stockholm date +"%b, %a, %T")"
	sleep 1m
done
