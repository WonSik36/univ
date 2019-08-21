#!/bin/bash

# create by eminat
# 2017. 7. 2

ACCESS=`cat /home/pi/.homeassistant/enertalk/access_token.txt`

YY=`date "+%Y"`
MM=`date "+%m"`
TIMESTAMP=`date -d "$MM/01/$YY 00:00:00" +%s`


PRICE=$(curl -X GET -H "Authorization: Bearer $ACCESS" -H "accept-version: 2.0.0" "https://api2.enertalk.com/sites/d4996c06/usages/realtime" | sed s/\,/\\n/g | grep Bill | cut -d : -f2 | rev | cut -c 2- | rev)
/usr/bin/printf "%'d" $PRICE
