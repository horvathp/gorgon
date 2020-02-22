#!/bin/bash
#json source directory
JSON_DIR="./json"
SUCCESS_DIR="./sent"
REJECTED_DIR="./rejected"
SERVER_ADDRESS="https://gnd.bme.hu:8080"
#unsuccess json send, retry time in seconds
RETRY=1
#main loop, wait time in seconds
CYCLE=1
#gndupload user name
USER="user"
#gndupload password
PASSWORD="password"
#json file successfully sent or not
SUCCESS=0

mkdir -p ${SUCCESS_DIR}
mkdir -p ${REJECTED_DIR}


#This function send the json files array to the server
send_json_bulk () {
	TOKEN=$(curl -u ${USER}:${PASSWORD} -X POST ${SERVER_ADDRESS}/api/tokens -s | sed -e 's/{"token":"\(.*\)"}/\1/')
	if [ "${TOKEN}" = "" ]
	then
		echo "Packets send failed"
		SUCCESS=0
	else
		echo "Token: "${TOKEN}
		OUTPUT="$(curl -d @$1 ${SERVER_ADDRESS}/api/packets/bulk -H "Authorization: Bearer ${TOKEN}" -H "Content-Type: application/json" -s | tail -1)"
		echo $OUTPUT
		if [[ "$OUTPUT" == *"results"* ]] || [[ "$OUTPUT" == *"first_submitted_at"* ]]
		then
			echo "Packets send success"
			SUCCESS=1
		elif [[ "$OUTPUT" == *"Bad Request"* ]]
		then
			echo "bad request"
			SUCCESS=-1
		else
			echo "Packets send failed"
			SUCCESS=0
		fi
	fi
}

send_json_one () {
	TOKEN=$(curl -u ${USER}:${PASSWORD} -X POST ${SERVER_ADDRESS}/api/tokens -s | sed -e 's/{"token":"\(.*\)"}/\1/')
	if [ "${TOKEN}" = "" ]
	then
		echo "Packets send failed"
		SUCCESS=0
	else
		echo "Token: "${TOKEN}
		OUTPUT="$(curl -d @$1 ${SERVER_ADDRESS}/api/packets -H "Authorization: Bearer ${TOKEN}" -H "Content-Type: application/json" -s | tail -1)"
		echo $OUTPUT
		if [[ "$OUTPUT" == *"results"* ]] || [[ "$OUTPUT" == *"first_submitted_at"* ]]
		then
			echo "Packets send success"
			SUCCESS=1
		else
			echo "Packets send failed"
			SUCCESS=0
		fi
	fi
}


#Main program
while [ 1 ]
do
	ls $JSON_DIR/*.json -r -1 2>/dev/null > ./fajlok.txt
	#line numbering
	SOR=$(cat -n ./fajlok.txt | grep -e " " -c)
	SOR=$(expr $SOR "+" 2)
	#line numbering
	cat -n ./fajlok.txt > ./fajlok2.txt
	#remove tab 'szam' append
	sed 's/\t/szam/g' ./fajlok2.txt > ./fajlok.txt
	rm "./fajlok2.txt"
	AKTSOR=1
	while [ $SOR -gt $AKTSOR ]
	do
		LAST_JSON=$(cat ./fajlok.txt | grep -e ${AKTSOR}szam -m 1 | sed s/${AKTSOR}szam//g | sed s/' '//g | xargs -r -n 1 basename)
		if [ "$LAST_JSON" != "" ]
		then
			echo $LAST_JSON
		fi
		if [ "${LAST_JSON}" != "" ]
		then
			MAX_COUNT=0
			while [[ "${SUCCESS}" = 0 ]] && [[ "${MAX_COUNT}" -lt "10" ]]
			do
				send_json_one $JSON_DIR/$LAST_JSON
				MAX_COUNT=$(expr $MAX_COUNT "+" 1 )
				sleep $RETRY
			done
			if [ "$SUCCESS" = -1 ]
			then
				echo "REJECTED ${LAST_JSON}"
				mv "$JSON_DIR"/${LAST_JSON} ${REJECTED_DIR}
			else
				echo "SUCCESS ${LAST_JSON}"
				mv "$JSON_DIR"/${LAST_JSON} ${SUCCESS_DIR}
			fi
			SUCCESS=0
		fi
		AKTSOR=$(expr $AKTSOR "+" 1 )
	done
	sleep $CYCLE
done
