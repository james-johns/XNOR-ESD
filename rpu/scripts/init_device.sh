#!/bin/sh

IPADDR=" "
menuInput=" " 
INITIAL="0"

# Specify Device
export DEVICE=wlan0

# Specify SSID and Channel
export SSID1=NETGEAR
export SSID2=NETGEAR2
export SSID3=NETGEAR3
export CHANNEL=6

#Specify CDD Address
export CDDIP=8.8.8.8

CRON= "1 * * * * /root/home/init_device.sh"
#cat < ( crontab -l) |grep -v "${CRON}" < ( echo "${CRON}")

modprobe snd-soc-igep0020
modprobe snd-soc-omap
modprobe snd-soc-omap-mcbsp
modprobe snd-soc-twl4030
amixer set -D hw:0 'Headset' 0dB echo "\n"
amixer set -D hw:0 'HeadsetL Mixer AudioL2' on echo "\n"
amixer set -D hw:0 'HeadsetR Mixer AudioR2' on echo "\n"



while true; do 
	
	ping -q -c5 $CDDIP > /dev/null
 
	if [ $? -eq 0 ]
		then
		echo "Connection to $CDDIP succesfull "

	
		IPADDR="$( ifconfig wlan0 | grep 'inet addr:' | cut -d: -f2 | awk '{print $1}' )"	
		echo "Selected IP address:$IPADDR"
		break

		#read -p "Do you want to run Gstreamer  (y/n)?" menuInput 

		#if [ "$menuInput" = "n" ]; then
		#		break;
		#else
		#	gst-launch-1.0 tcpserversrc host=$IPADDR port=3000 ! decodebin ! audioconvert ! alsasink
					
		#fi
	
	else
		echo "Cannot connect no connection available"	
		# Enable wifi-adapter
		ifconfig $DEVICE up
		# Associate with AP
		iwconfig $DEVICE essid $SSID1 channel $CHANNEL

		if [ $? -eq 0 ]
		then
			iwconfig $DEVICE essid $SSID2 channel $CHANNEL	
		else
			iwconfig $DEVICE essid $SSID3 channel $CHANNEL	
		fi
	
		# Obtain IP address
		ifconfig wlan0 | grep "inet " | awk -F'[: ]+' '{ print $4 }'	

	fi		

done
   





