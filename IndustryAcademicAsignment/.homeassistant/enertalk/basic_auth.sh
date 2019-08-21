#!/bin/bash

# create by eminat
# 2017. 7. 2

# clientId 와 clientSecret 수정필요
CLIENTID='Y3dzMDE3M0BnbWFpbC5jb21fSEdVaW90'
CLIENTSECRET='vt1gp54g0x354l6id5426p534t1b91838t16cb7'


BASE64=$(echo -n "$CLIENTID:$CLIENTSECRET" | base64)
echo $BASE64 | sed -e 's/\ //g' > /home/pi/.homeassistant/enertalk/Basic_Auth.txt

