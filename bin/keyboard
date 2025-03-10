#!/bin/sh

choice="Cancel\nEN\nSE"

prompt(){
	PROMPT=$1
	CHOICE=$2
	CMD=$3

	numchoices=$(echo -e "$CHOICE" | wc -l)
	chosen=$(echo -e "$CHOICE" | dmenu -p "$PROMPT" -l "$numchoices")
	echo "$chosen"

	case $chosen in 
		"SE")
			setxkbmap fi
			;;
		"EN")
			setxkbmap us 
			;;
	esac
}

prompt "KBLayout?" $choice 
