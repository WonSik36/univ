#!/bin/bash

# create by eminat
# 2017. 7. 2

OLD_REFRESH=`cat /home/pi/.homeassistant/enertalk/refresh_token.txt`
BASIC_AUTH=`cat /home/pi/.homeassistant/enertalk/Basic_Auth.txt`

curl -X POST -H "Authorization: Basic $BASIC_AUTH" -H "Content-Type: application/json"  -d '{ "grant_type": "refresh_token", "refresh_token": "'$OLD_REFRESH'" }' -ss https://auth.enertalk.com/token  > /home/pi/.homeassistant/enertalk/output.txt

NEW_REFRESH=`cat /home/pi/.homeassistant/enertalk/output.txt | sed -e 's/\,/\\n/g' | grep refresh_token | sed -e 's/\"/\\n/g' | tail -2 | head -1`
NEW_ACCESS=`cat /home/pi/.homeassistant/enertalk/output.txt | sed -e 's/\,/\\n/g' | grep access_token | sed -e 's/\"/\\n/g' | tail -2 | head -1`

echo "$NEW_REFRESH"
echo "$NEW_ACCESS"
echo "$NEW_REFRESH" > /home/pi/.homeassistant/enertalk/refresh_token.txt
echo "$NEW_ACCESS" > /home/pi/.homeassistant/enertalk/access_token.txt
