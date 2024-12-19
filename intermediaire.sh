#!/bin/bash

date1=$(date +%s)
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

fichier=$(find $1/ -type f -name "*.dat" | head -1)
echo $fichier

cd $1

if ! [ -f "c-wire_v25.dat" ] ; then
	echo -e "le fichier de données n'existe pas\n"
	exit 4
fi

if ! [ -d "graphs" ] ; then 
	echo -e "Le dossier graphs n'existe pas\n"
 	mkdir "graphs"
fi

if ! [ -d "tmp" ] ; then
	echo -e "Le dossier tmp n'existe pas\n"
 	mkdir "tmp"
else 
	echo -e "Le dossier tmp existe déjà\n"
 	rm -r tmp/*
  	echo -e "Le dossier tmp a été vidé\n"
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
			grep -E "^[$4]" $fichier | cut -d ';' -f 2-8 | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > tmp.csv && mv tmp.csv hvb_comp_$4.csv

			echo "Station $2 :Capacité :Consommateurs (entreprises)" | cat - hvb_comp_$4.csv > tmp.csv && mv tmp.csv hvb_comp_$4.csv
		else
			cut -d ';' -f 2-8 $fichier | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7 | tr "-" "0" |  ./exec > hvb_comp.csv
			sort -t ':' -k2,2n hvb_comp.csv  > tmp.csv && mv tmp.csv hvb_comp.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - hvb_comp.csv > tmp.csv && mv tmp.csv hvb_comp.csv
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
			grep -E "^[$4]" $1/c-wire_v25.dat | cut -d ';' -f 3-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-" | cut -d ';' -f 1,5,6 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > hva_comp_$4.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - hva_comp_$4.csv > tmp.csv && mv tmp.csv hva_comp_$4.csv
		else
			cut -d ';' -f 3-8 $1/c-wire_v25.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-;[0-9]+" | cut -d ';' -f 1,5,6 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > hva_comp.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - hva_comp.csv > tmp.csv && mv tmp.csv hva_comp.csv
		fi
	fi
fi

if [ "$nomType" = "lv" ] ; then
	if [ "$nomConsommateur" = "all" ] ; then
		if ! [ -z "$4" ]; then
			grep -E "^[$4]" $1/c-wire_v25.dat | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | awk -F ':' '{print $0 ":" $2 - $3}' | sort -t ':' -k4 -n | tee | (head -10 ; tail -n10) > intermediaire.csv
			cut -d ':' -f 1,2,3 intermediaire.csv > lv_all_minmax_$4.csv
			echo "Station $2 :Capacite :Consommateurs (tous)" | cat - lv_all_minmax_$4.csv > tmp.csv && mv tmp.csv lv_all_minmax_$4.csv
			rm intermediaire.csv
		else
			cut -d ';' -f 4-8 $1/c-wire_v25.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | awk -F ':' '{print $0 ":" $2 - $3}' | sort -t ':' -k4 -n | tee | (head -10 ; tail -n10) > intermediaire.csv
			cut -d ':' -f 1,2,3 intermediaire.csv > lv_all_minmax.csv
			echo "Station $2 :Capacite :Consommateurs (tous)" | cat - lv_all_minmax.csv > tmp.csv && mv tmp.csv lv_all_minmax.csv
			rm intermediaire.csv
		fi
	fi
	if [ "$nomConsommateur" = "indiv" ] ; then
		if ! [ -z "$4" ]; then
			grep -E "^[$4]" $1/c-wire_v25.dat | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_indiv_$4.csv
			echo "Station $2 :Capacite :Consommateurs (particuliers)" | cat - lv_indiv_$4.csv > tmp.csv && mv tmp.csv lv_indiv_$4.csv
		else
			cut -d ';' -f 4-8 $1/c-wire_v25.dat | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_indiv.csv
			echo "Station $2 :Capacite :Consommateurs (particuliers)" | cat - lv_indiv.csv > tmp.csv && mv tmp.csv lv_indiv.csv
		fi	
	fi
	if [ "$nomConsommateur" = "comp" ] ; then
		if ! [ -z "$4" ]; then
			grep -E "^[$4]" $1/c-wire_v25.dat | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_comp_$4.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - lv_comp_$4.csv > tmp.csv && mv tmp.csv lv_comp_$4.csv
		else
			cut -d ';' -f 4-8 $1/c-wire_v25.dat | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_comp.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - lv_comp.csv > tmp.csv && mv tmp.csv lv_comp.csv
		fi	
	fi	
fi

date2=$(date +%s)
echo "Le programme a mis (en secondes) : "
echo $((date2 - date1))
