i#!bin/sh

feh --bg-scale Background.png
xcompmgr &
setxkbmap -layout fi
setxkbmap -option caps:escape &
bash .time.sh &
exec dwm 
