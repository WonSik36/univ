#!/bin/bash

ACCESS=`cat /home/pi/.homeassistant/enertalk/access_token.txt`

OUTPUT=$(curl -X GET -H "Authorization: Bearer $ACCESS" -H "accept-version: 2.0.0" "https://api2.enertalk.com/sites/a4b291b2/usages/realtime" | sed s/\,/\\n/g | grep activePower | grep -v rea | cut -d : -f2)


if [ ! -z "$OUTPUT" ]
then
   echo "$OUTPUT"
else
   ~/.homeassistant/enertalk/renew_tokens.sh > /dev/null 2>&1
   sleep 3
   curl -X GET -H "Authorization: Bearer $ACCESS" -H "accept-version: 2.0.0" "https://api2.enertalk.com/sites/a4b291b2/usages/realtime" | sed s/\,/\\n/g | grep activePower | grep -v rea | cut -d : -f2
fi

