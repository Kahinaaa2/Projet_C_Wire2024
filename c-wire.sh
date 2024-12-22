#!/bin/bash

date1=$(date +%s) #Récupération de la date en seconde au début du programme shell

for i in `seq 1 $#` #Vérification de la présence de l'option -h
do 
	if [ ${!i} = "-h" ] ; then #Si -h est présent -> afficher le fichier d'aide et arrêter le programme
		cat aide.txt
		exit 1
	fi	
done
 
if [ "$#" -ne 3 ] && [ "$#" -ne 4 ] ; then #Vérification du nombre d'argument (minimum 3 si il n'y a pas l'option de la centrale, pas besoin de vérifier la présence de l'option -h, si le programme arrive jusqu'ici cela veut dire qu'il n'y a pas cette option 
	echo -e "Vous n'avez pas entré le bon nombre d'arguments\n" #Le -e permet de faire un retour à la ligne quand on utilise le \n
	cat aide.txt | head -8 #Affiche que la partie de l'aide qui correspond aux détails des arguements
	exit 2
fi

if ! [ -f "$1" ] ; then #Vérification si le chemin vers le fichier de données qu'on souhaite étudier existe bien
	echo -e "Le chemin que vous nous avez indiquer n'existe pas :'$1'\n"
	cat aide.txt | head -8 #Affiche que la partie de l'aide qui correspond aux détails des arguements
	exit 3
fi

cd codeC #Pour se placer dans le dossier qui contient le programme C

if ! [ -f "Makefile" ] ; then #Vérification de l'existence du Makefile
	echo -e "Le Makefile pour compiler le code C n'est pas présent dans le dossier codeC, veuillez le mettre dedans pour le fonctionnement du programme\n"
	exit 4
else
	if [ -f "exec" ] ; then #Si l'exécutable existe déjà, le programme va venir l'effacer
		rm exec
	fi
	
	make #Lancement du Makefile, s'il existe, pour créer exec
	
	if ! [ -f "exec" ] ; then #Vérifiation que le exec a bien été créé
		echo -e "Problème lors de l'exécution du Makefile, le programme C n'a pas pu être compilé\n"
		exit 5
	fi	
fi

cd .. #Sortie du dossier codeC

mv codeC/exec . #Deplacement de l'exécutable dans le dossier qui précède codeC, le dossier où se trouve le code shell, fichier d'aide...			

if ! [ -f "aide.txt" ] ; then #Vérification de l'exsitence du fichier d'aide
	echo -e "le fichier d'aide n'existe pas\n"
	exit 6
fi

if ! [ -d "graphs" ] ; then #Si le dossier graphs n'existe pas, le programme va venir le créer
 	mkdir "graphs"
fi

if ! [ -d "tmp" ] ; then #Si le dossier tmp n'existe pas, le programme va venir le créer
 	mkdir "tmp"
else 
	if [ "$(ls -A tmp)" ]; then #Si le fichier existe, le programme va venir le vider si il contient des choses
	rm -r tmp/* #Efface les fichiers que si on a les droits sur ses fichiers, sinon le programme va demander une validation auprès de l'utilisateur
	fi
fi

nomType=$2
nomConsommateur=$3
numeroCentrale=$4

if ! [ "$2" = "hvb" ] && ! [ "$2" = "hva" ] && ! [ "$2" = "lv" ] ; then #Vérification de la bonne saisie pour le deuxième argument
	echo -e "le type de centrale que vous souhaitez étudier n'existe pas\n"
	cat aide.txt | head -2
	cat aide.txt | head -10 | tail -n+9
	exit 7
fi

if ! [ "$3" = "all" ] && ! [ "$3" = "comp" ] && ! [ "$3" = "indiv" ] ; then #Vérification de la bonne saisie pour le troisième argument
	echo -e "le type de consommateurs que vous souhaitez étudier n'existe pas\n"
	cat aide.txt | head -2 #Affiche le titre du fichier d'aide
	cat aide.txt | head -12 | tail -n+11 #Affiche la partie du fichier d'aide qui correspond à l'erreur
	exit 8
fi

if ! [ -z "$4" ]; then #Si un numéro de Centrale a été donné
	if [ "$4" -gt 5 ] || [ "$4" -lt 1 ] ; then #Vérification que ce numéro soit entre 1 et 5 compris
		echo -e "Le numéro de centrale n'existe pas\n"
		cat aide.txt | head -2 #Affiche le titre du fichier d'aide
		cat aide.txt | head -14 | tail -n+13 #Affiche la partie du fichier d'aide qui correspond à l'erreur
		exit 9
	fi
fi	

date2=$(date +%s) #Récupération du temps
echo "le temps des vérifications est de :"
echo $((date2 - date1)) #Calcule le temps qu'a mis le programme à faire les vérifications
			
if [ "$nomType" = "hvb" ] ; then #Etudier le cas où c'est HVB
	if [ "$nomConsommateur" = "all" ] || [ "$nomConsommateur" = "indiv" ] ; then #Vérifiez que le type de comsommateur est bien possible avec les HVB
		echo -e "Les HV-B ne sont pas reliés à des consommateurs individuels, veuillez changer de paramètre\n"
		cat aide.txt | head -2 #Affiche le titre du fichier d'aide
		cat aide.txt | head -17 | tail -n+15 #Affiche la partie du fichier d'aide qui correspond à l'erreur
		exit 10
	else
		if ! [ -z "$4" ]; then #Cas où un numéro de Centrale a été donné
			#tri du fichier donné avec le chemin ($1) selon le numéro de Centrale ($4) | récupération des colonnes de 2 à 8 du fichier | Enlever la première ligne qui contient la légende du fichier csv | récupération des lignes qui correspondent à des certaines formes (ligne du HVB + les lignes des compagnies reliées directement au HVB | récupération des colonnes correspondant à l'identifiant + la capacité + la consommation | transformation du '-' en '0' pour le C | Envoie des données dans l'exécutable du programme C | tri croissant selon la capacité des HVB > créaion d'un fichier
			grep -E "^[$4]" $1 | cut -d ';' -f 2-8 | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7 | tr "-" "0"  | ./exec | sort -t ':' -k2,2n > hvb_comp_$4.csv

			echo "Station $2 :Capacité :Consommateurs (entreprises)" | cat - hvb_comp_$4.csv > tmp.csv && mv tmp.csv hvb_comp_$4.csv #Rajout d'une légende au début du fichier
		else
			#Même chose mais sans le tri des centrales
			cut -d ';' -f 2-8 $1 | tail -n+2 | grep -E "^[0-9]+;-;-;[0-9]+;-|^[0-9]+;-;-;-;-" | cut -d ';' -f 1,6,7 | tr "-" "0" |  ./exec | sort -t ':' -k2,2n > hvb_comp.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - hvb_comp.csv > tmp.csv && mv tmp.csv hvb_comp.csv #Rajout d'une légende au début du fichier
		fi
	fi
	date3=$(date +%s)
	echo "le temps d'éxécution pour les hvb est :"
	echo $((date3 - date2)) #Calcul pour obtenir le temps de tri du fichier + de l'exécution du programme c	
fi	


if [ "$nomType" = "hva" ] ; then #Etudier le cas où c'est HVA
	if [ "$nomConsommateur" = "all" ] || [ "$nomConsommateur" = "indiv" ] ; then #Vérifiez que le type de comsommateur est bien possible avec les HVA
		echo -e "Les HV-A ne sont pas reliés à des consommateurs individuels, veuillez changer de paramètre\n"
		cat aide.txt | head -2 #Affiche le titre du fichier d'aide
		cat aide.txt | head -17 | tail -n+15 #Affiche la partie du fichier d'aide qui correspond à l'erreur
		exit 11
	else
		if ! [ -z "$4" ]; then #Cas où un numéro de Centrale a été donné
			#Même tri que pour les HVB mais en changeant la colonne d'identifiant à étudier
			grep -E "^[$4]" $1 | cut -d ';' -f 3-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-" | cut -d ';' -f 1,5,6 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > hva_comp_$4.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - hva_comp_$4.csv > tmp.csv && mv tmp.csv hva_comp_$4.csv #Rajout d'une légende au début du fichier
		else
			cut -d ';' -f 3-8 $1 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+;-|^[0-9]+;-;-;-;[0-9]+" | cut -d ';' -f 1,5,6 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > hva_comp.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - hva_comp.csv > tmp.csv && mv tmp.csv hva_comp.csv #Rajout d'une légende au début du fichier
		fi
	fi
	date4=$(date +%s)
	echo "le temps d'éxécution pour les hva est :"
	echo $((date4 - date2)) #Calcul pour obtenir le temps de tri du fichier + de l'exécution du programme c	
fi

if [ "$nomType" = "lv" ] ; then #Etudier le cas où c'est LV
	if [ "$nomConsommateur" = "all" ] ; then #Cas où c'est avec tous les consommateurs
		if ! [ -z "$4" ]; then #Cas avec un numéro de Centrale donné
			#Même tri que pour les HVB au départ mais après l'exécution du C le programme ajoute une quatrième colonne avec la différence entre capacité et consommation | tri selon le
			grep -E "^[$4]" $1 | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | awk -F ':' '{print $0 ":" $2 - $3}' | sort -t ':' -k4 -n | tee | (head -10 ; tail -n10) > tmp/intermediaire.csv
			cut -d ':' -f 1-3 tmp/intermediaire.csv > lv_all_minmax_$4.csv #on ne garde que les trois premières colonnes dans le fichier final
			echo "Station $2 :Capacite :Consommateurs (tous)" | cat - lv_all_minmax_$4.csv > tmp.csv && mv tmp.csv lv_all_minmax_$4.csv #Rajout d'une légende au début du fichier
   			#fichier gnuplot pour le graphique
			echo "set terminal png" > gnuplot_script #fichier PNG comme sortie
			echo "set output 'graphs/postesLV_$4_graph.png'" >> gnuplot_script #fichier sauvegardé dans le dossier graphs
			echo "set style data histogram" >> gnuplot_script #style du graphique (histogramme)
			echo "set style fill solid border -1" >> gnuplot_script #remplissage des barres du graphique
			echo "set boxwidth 0.8" >> gnuplot_script #largeur des barres
			echo "unset border" >> gnuplot_script #pas de bords autour du graphique
			echo "set ytics" >> gnuplot_script #affichage des marques sur l'axe des ordonnées
			echo "set ylabel 'Quantité énergie consommée'" >> gnuplot_script #légende de l'axe des ordonnées
			echo "set xtics rotate by -45" >> gnuplot_script #les marques de l'axe des abscisses sont affichés avec une rotation de 45 degres (pour éviter que les numéros se chevauchent)
			echo "set xtics nomirror" >> gnuplot_script #permet d'éviter l'affichage des marques sur un autre axe plus haut
			echo "set xlabel 'Identifiant'" >> gnuplot_script #légende de l'axe des abscisses
			echo "set grid y" >> gnuplot_script #affichage d'une grille sur l'axe des ordonnées
			echo "set arrow from screen 0, first 0 to screen 1, first 0 nohead lw 1 lc rgb 'black'" >> gnuplot_script #affichage d'une ligne noire sur l'axe des abscisses
			echo "set datafile separator ':'" >> gnuplot_script #indique le séparateur de colonnes du fichier csv
			echo "plot 'tmp/intermediaire.csv' using 4:xtic(1) with boxes lc rgb 'green' title 'Surproduction', 'tmp/intermediaire.csv' using 4:xtic(1) with boxes lc rgb 'red' title 'Sous-production'" >> gnuplot_script #trace le graphiques avec les données de la première et quatrième colonnes du fichier csv, légende des couleurs
			gnuplot gnuplot_script #éxécute le script
			rm gnuplot_script #supprime le fichier après son utilisation
			

		else
			cut -d ';' -f 4-8 $1 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | awk -F ':' '{print $0 ":" $2 - $3}' | sort -t ':' -k4 -n | tee | (head -10 ; tail -n10) > tmp/intermediaire.csv
			cut -d ':' -f 1-3 tmp/intermediaire.csv > lv_all_minmax.csv
			echo "Station $2 :Capacite :Consommateurs (tous)" | cat - lv_all_minmax.csv > tmp.csv && mv tmp.csv lv_all_minmax.csv
			#fichier gnuplot pour le graphique
			echo "set terminal png" > gnuplot_script #fichier PNG comme sortie
			echo "set output 'graphs/postesLV_graph.png'" >> gnuplot_script #fichier sauvegardé dans le dossier graphs
			echo "set style data histogram" >> gnuplot_script #style du graphique (histogramme)
			echo "set style fill solid border -1" >> gnuplot_script #remplissage des barres du graphique
			echo "set boxwidth 0.8" >> gnuplot_script #largeur des barres
			echo "unset border" >> gnuplot_script #pas de bords autour du graphique
			echo "set ytics" >> gnuplot_script #affichage des marques sur l'axe des ordonnées
			echo "set ylabel 'Quantité énergie consommée'" >> gnuplot_script #légende de l'axe des ordonnées
			echo "set xtics rotate by -45" >> gnuplot_script #les marques de l'axe des abscisses sont affichés avec une rotation de 45 degres (pour éviter que les numéros se chevauchent)
			echo "set xtics nomirror" >> gnuplot_script #permet d'éviter l'affichage des marques sur un autre axe plus haut
			echo "set xlabel 'Identifiant'" >> gnuplot_script #légende de l'axe des abscisses
			echo "set grid y" >> gnuplot_script #affichage d'une grille sur l'axe des ordonnées
			echo "set arrow from screen 0, first 0 to screen 1, first 0 nohead lw 1 lc rgb 'black'" >> gnuplot_script #affichage d'une ligne noire sur l'axe des abscisses
			echo "set datafile separator ':'" >> gnuplot_script #indique le séparateur de colonnes du fichier csv
			echo "plot 'tmp/intermediaire.csv' using 4:xtic(1) with boxes lc rgb 'green' title 'Surproduction', 'tmp/intermediaire.csv' using 4:xtic(1) with boxes lc rgb 'red' title 'Sous-production'" >> gnuplot_script #trace le graphiques avec les données de la première et quatrième colonnes du fichier csv, légende des couleurs
			gnuplot gnuplot_script #éxécute le script
			rm gnuplot_script #supprime le fichier après son utilisation
		fi
	fi
	if [ "$nomConsommateur" = "indiv" ] ; then
		if ! [ -z "$4" ]; then
			grep -E "^[$4]" $1 | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_indiv_$4.csv
			echo "Station $2 :Capacite :Consommateurs (particuliers)" | cat - lv_indiv_$4.csv > tmp.csv && mv tmp.csv lv_indiv_$4.csv
		else
			cut -d ';' -f 4-8 $1 | tail -n+2 | grep -E "^[0-9]+;-;[0-9]+|^[0-9]+;-;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_indiv.csv
			echo "Station $2 :Capacite :Consommateurs (particuliers)" | cat - lv_indiv.csv > tmp.csv && mv tmp.csv lv_indiv.csv
		fi	
	fi
	if [ "$nomConsommateur" = "comp" ] ; then
		if ! [ -z "$4" ]; then
			grep -E "^[$4]" $1 | cut -d ';' -f 4-8 | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_comp_$4.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - lv_comp_$4.csv > tmp.csv && mv tmp.csv lv_comp_$4.csv
		else
			cut -d ';' -f 4-8 $1 | tail -n+2 | grep -E "^[0-9]+;-;-|^[0-9]+;[0-9]+;-" | cut -d ';' -f 1,4,5 | tr "-" "0" | ./exec | sort -t ':' -k2,2n > lv_comp.csv
			echo "Station $2 :Capacite :Consommateurs (entreprises)" | cat - lv_comp.csv > tmp.csv && mv tmp.csv lv_comp.csv
		fi	
	fi
	date5=$(date +%s)
	echo "le temps d'éxécution pour les lv est :"
	echo $((date5 - date2))		
fi

if [ -f "exec" ] ; then
	mv exec codeC/
fi	

date6=$(date +%s)
echo "Le programme a mis (en secondes) : "
echo $((date6 - date1))
