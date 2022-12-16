#!/bin/bash
MQTTSUB="C:/Program Files/mosquitto/mosquitto_sub.exe"
while true
do
   "$MQTTSUB" -t "Paredes/ESP32" | while read -r payload
   do
      if [[ "payload" == "1pmode" ]]; then
         echo "1p"
         ./script.sh
         echo "Game finished"
         break
      elif [[ "payload" == "2pmode" ]]; then
         echo "2p"
         ./script.sh
         echo "Game finished"
      fi
   done

done