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

cd $1

if ! [ -f "c-wire_v00.dat" ] ; then
	echo -e "le fichier de données n'existe pas\n"
	exit 4
fi

cd ..

nomType=$2
nomConsommateur=$3
numeroCentrale=$4
difference="0"

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
			cat $1/c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 2-8 | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7 | tr "-" "0" | ./exec > hvb_comp_$4.csv
		else
			cut -d ';' -f 2-8 $1/c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7 | tr "-" "0" | ./exec > hvb_comp.csv 
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
			cat $1/c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 3-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-" | cut -d ';' -f 1,5,6 | tr "-" "0" | ./exec > hva_comp_$4.csv
		else
			cut -d ';' -f 3-8 $1/c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-;[0-9]+" | cut -d ';' -f 1,5,6 | tr "-" "0" | ./exec > hva_comp.csv
		fi
	fi
fi

if [ "$nomType" = "lv" ] ; then
	if [ "$nomConsommateur" = "all" ] ; then
		if ! [ -z "$4" ]; then
			cat $1/c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec > lv_all_$4.csv
			awk -F ';' '{print $0 ";" $2 - $3}' lv_all_$4.csv | tr "," "." > fichier_modifie.csv
			sort -t ';' -k4 -n fichier_modifie.csv | head -10 > lv_all_minmax_$4.csv
			sort -t ';' -k4 -n fichier_modifie.csv | tail -n10 >> lv_all_minmax_$4.csv
		else
			cut -d ';' -f 4-8 $1/c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec > lv_all.csv
			awk -F ';' '{print $0 ";" $2 - $3}' lv_all.csv | tr "," "." > fichier_modifie.csv
			sort -t ';' -k4 -n fichier_modifie.csv | head -10 > lv_all_minmax.csv
			sort -t ';' -k4 -n fichier_modifie.csv | tail -n10 >> lv_all_minmax.csv
		fi
	fi
	if [ "$nomConsommateur" = "indiv" ] ; then
		if ! [ -z "$4" ]; then
			cat $1/c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec > lv_indiv_$4.csv
		else
			cut -d ';' -f 4-8 $1/c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec > lv_indiv.csv
		fi	
	fi
	if [ "$nomConsommateur" = "comp" ] ; then
		if ! [ -z "$4" ]; then
			cat $1/c-wire_v00.dat | grep -E "^[$4]" | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec > lv_comp_$4.csv
		else
			cut -d ';' -f 4-8 $1/c-wire_v00.dat | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec > lv_comp.csv
		fi	
	fi	
fi

#awk : s'informer rajouter colonne
#tee : doc pour combiner
