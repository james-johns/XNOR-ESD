#!/bin/sh


# Specify Device
export DEVICE=wlan0

# Specify SSID and Channel
export SSID1=NETGEAR
export SSID2=NOTGEAR
export SSID3=LANGEAR

export CHANNEL1=6
export CHANNEL2=6
export CHANNEL3=6

#Specify CDD Address
export CDDIP=8.8.8.8

modprobe snd-soc-igep0020
modprobe snd-soc-omap
modprobe snd-soc-omap-mcbsp
modprobe snd-soc-twl4030
amixer set -D hw:0 'Headset' 0dB echo "\n"
amixer set -D hw:0 'HeadsetL Mixer AudioL2' on echo "\n"
amixer set -D hw:0 'HeadsetR Mixer AudioR2' on echo "\n"

# Enable wifi-adapter
ifconfig $DEVICE up


while true; do 
		
	
	#	IPADDR="$( ifconfig wlan0 | grep 'inet addr:' | cut -d: -f2 | awk '{print $1}' )"	
	#	echo "Selected IP address:$IPADDR"
		

		#read -p "Do you want to run Gstreamer  (y/n)?" menuInput 

		#if [ "$menuInput" = "n" ]; then
		#		break;
		#else
		#	gst-launch-1.0 tcpserversrc host=$IPADDR port=3000 ! decodebin ! audioconvert ! alsasink
					
		#fi
	
	ping -q -c2 $CDDIP > /dev/null 
	if [ $? -eq 1 ]; then
		ifconfig wlan0 up;
		echo "connecting with $SSID1 on channel $CHANNEL1"
		# Associate with AP
		if  iwconfig $DEVICE essid $SSID1 channel $CHANNEL1; then 
			udhcpc -i $DEVICE
			echo "Connection to $SSID1 succesfull "
		fi
	fi	
			
	ping -q -c2 $CDDIP > /dev/null  
	if [ $? -eq 1 ]; then
		ifconfig wlan0 up;
		echo "connecting with $SSID2 on channel $CHANNEL2"
		# Associate with AP			
		if  iwconfig $DEVICE essid $SSID2 channel $CHANNEL2; then
			udhcpc -i $DEVICE
			echo "Connection to $SSID2 succesfull "
		fi
	fi
			
	ping -q -c2 $CDDIP > /dev/null  
	if [ $? -eq 1 ]; then
		ifconfig wlan0 up;
		echo "connecting with $SSID3 on channel $CHANNEL3"
		# Associate with AP
		if  iwconfig $DEVICE essid $SSID3 channel $CHANNEL3; then
			udhcpc -i $DEVICE
			echo "Connection to $SSID3 succesfull "
		fi
	fi
			
	ping -q -c2 $CDDIP > /dev/null  
	if [ $? -eq 1 ]; then
		echo "No networks detected"

	else
	# Obtain IP address
	echo "Selected IP address:"		
	ifconfig wlan0 | grep "inet " | awk -F'[: ]+' '{ print $4 }'	
	echo "Connected to Router with MAC Address:"	
	iwlist wlan0 scan | awk '/Address:/ {print $5}'	
	fi
		
		
	
	
		
	sleep 1
done
   





