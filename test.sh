
#!/bin/bash


#verif que le fichier csv existe 
#verif sue l'éxécutable du c exste et s'il n'existe pas éxécuter le makefile
 
if [ "$#" -ne 4 ] ; then
	echo "Vous n'avez pas entré le bon nombre d'arguments"
	cat help.txt
	exit 2
fi

if ! [ -f "help.txt" ] ; then
	echo "le fichier d'aide n'existe pas"
	exit 1
fi	

if ! [ -f "c-wire_v00.dat" ] ; then
	echo "le fichier de données n'existe pas"
	exit 1
fi

nomCentrale=$2
nomConsommateur=$3
type="0"


if [ "$nomCentrale" = "hvb" ] ; then
	type="1"
fi	


if [ "$nomCentrale" = "hva" ] ; then
	type="2"
fi

if [ "$nomCentrale" = "lv" ] ; then
	type="3"
fi

echo $type



echo "$nomCentrale"
echo "$nomConsommateur"

