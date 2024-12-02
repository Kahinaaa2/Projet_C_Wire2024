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


