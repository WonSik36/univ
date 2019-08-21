TIMESTAMP= 'date -d 'today' +%s%N | cut -b1-13'

echo "$TIMESTAMP"
echo $TIMESTAMP > /home/pi/.homeassistant/enertalk/timestamp.txt