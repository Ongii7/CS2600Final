#!/bin/bash
#
# mqtt_data.sh - send game data to MQTT broker
#

server = "192.168.1.194"
pause = 2

echo "ESP32 detected, game start?"

mosquitto_sub -h $server -t game_start
if[game_start == '1']
then
   ./a.exe
fi

sleep $pause
