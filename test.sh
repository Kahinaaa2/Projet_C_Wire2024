#!/bin/bash

for i in `seq 1 $#`
do 
	if [ ${!i} = "-h" ] ; then
		cat help.txt
		exit 1
	fi	
done
 
if [ "$#" -ne 4 ] && [ "$#" -ne 3 ] && [ "$#" -ne 5 ] ; then
	echo -e "Vous n'avez pas entré le bon nombre d'arguments\n"
	cat help.txt | head -8
	exit 1
fi

if ! [ -d "$1" ] ; then
	echo -e "'$1' n'est pas un dossier\n"
	exit 2
fi

if ! [ -f "help.txt" ] ; then
	echo -e "le fichier d'aide n'existe pas\n"
	exit 3
fi	

if ! [ -f "c-wire_v00.dat" ] ; then
	echo -e "le fichier de données n'existe pas\n"
	exit 4
fi

nomType=$2
nomConsommateur=$3
numeroCentrale=$4

if ! [ "$2" = "hvb" ] && ! [ "$2" = "hva" ] && ! [ "$2" = "lv" ] ; then
	echo -e "le type de centrale que vous souhaitez étudier n'existe pas\n"
	cat help.txt | head -2
	cat help.txt | head -10 | tail -n+9
	exit 5
fi

if ! [ "$3" = "all" ] && ! [ "$3" = "comp" ] && ! [ "$3" = "indiv" ] ; then	
	echo -e "le type de consommateurs que vous souhaitez étudier n'existe pas\n"
	cat help.txt | head -2
	cat help.txt | head -12 | tail -n+11
	exit 6
fi

if ! [ -z "$4" ]; then
	if [ "$4" -gt 5 ] || [ "$4" -lt 1 ] ; then
		echo -e "Le numéro de centrale n'existe pas\n"
		cat help.txt | head -2
		cat help.txt | head -14 | tail -n+13
		exit 7
	fi
fi				

if [ "$nomType" = "hvb" ] ; then
	if [ "$nomConsommateur" = "all" ] || [ "$nomConsommateur" = "indiv" ] ; then
		echo -e "Les HV-B ne sont pas reliés à des consommateurs individuels, veuillez changer de paramètre\n"
		cat help.txt | head -2
		cat help.txt | head -17 | tail -n+15
	else
		if ! [ -z "$4" ]; then
			cat c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 2-8 | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7
		else
			cut -d ';' -f 2-8 c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7
		fi
	fi	
fi	


if [ "$nomType" = "hva" ] ; then
	if [ "$nomConsommateur" = "all" ] || [ "$nomConsommateur" = "indiv" ] ; then
		echo -e "Les HV-A ne sont pas reliés à des consommateurs individuels, veuillez changer de paramètre\n" #pour afficher un saut de ligne
		cat help.txt | head -2
		cat help.txt | head -17 | tail -n+15
	else
		if ! [ -z "$4" ]; then
			cat c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 3-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-" | cut -d ';' -f 1,5,6
		else
			cut -d ';' -f 3-8 c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-" | cut -d ';' -f 1,5,6
		fi	
	fi
fi

if [ "$nomType" = "lv" ] ; then
	if [ "$nomConsommateur" = "all" ] ; then
		if ! [ -z "$4" ]; then
			cat c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5
		else
			cut -d ';' -f 4-8 c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5
		fi
	fi
	if [ "$nomConsommateur" = "indiv" ] ; then
		if ! [ -z "$4" ]; then
			cat c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5
		else
			cut -d ';' -f 4-8 c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5
		fi	
	fi
	if [ "$nomConsommateur" = "comp" ] ; then
		if ! [ -z "$4" ]; then
			cat c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 4-8 c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5
		else
			cut -d ';' -f 4-8 c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5
		fi	
	fi	
fi


