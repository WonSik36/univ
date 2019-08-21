#!/bin/bash

# create by eminat
# 2017. 7. 2

ACCESS=`cat /home/pi/.homeassistant/enertalk/access_token.txt`

YY=`date "+%Y"`
MM=`date "+%m"`
TIMESTAMP=`date -d "$MM/01/$YY 00:00:00" +%s`

curl -X GET -H "Authorization: Bearer $ACCESS" -H "accept-version: 2.0.0" "https://api2.enertalk.com/sites/737e0393/usages/periodic/?period=day" | sed  s/\,/\\n/g | grep usage | cut -d : -f2 

