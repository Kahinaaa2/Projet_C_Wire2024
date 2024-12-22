

# Présentation du Sujet : 

Nous devions faire un programme qui est capable de trier un fichier de données pour ensuite faire des opérations dessus et de stocker les nouvelles données dans de nouveaux fichiers.

Le sujet est sur les centrales électriques de France. Des stations sont reliées à ces centrales, nous avons trois types de station, les HV-B, les HV-A et les LV. Et des consommateurs sont reliés à ces stations, pour les HV-B et HV-A ce sont des entreprises et pour le LV cela peut être des entreprises mais aussi des logements de particuliers. 

Le sujet nous donne un fichier de données à partir duquel on doit trier. Et ce tri doit se faire à l’aide d’un programme shell et un programme C.

# Présentation du Projet : 
	
Notre projet a pour but de créer un fichier qui contient toutes les données sur les HV-B, les HV-A ou les LV qui sont reliés à des centrales. Le fichier créé contient l’identifiant, la capacité et la consommation de toutes les stations en fonction d’un type de consommateurs. 

Pour créer ce fichier, le programme utilise un fichier existant qui contient toutes les données générales. Notre projet est divisé en deux parties, la partie shell qui va venir trier le fichier de données existant, puis le programme C va venir créer un AVL pour stocker les données de toutes les stations étudiées. Avec l’AVL, le programme peut faire une somme de toutes les consommations d’une station pour avoir une donnée qui regroupe tous les consommateurs.

# Objectif : 

Notre projet a pour objectif de calculer toutes les consommations de chaque station pour pouvoir identifier si elles sont en surproduction ou en sous-production. 

Pour les LV, notre projet vise aussi à créer un fichier qui contient les dix LV les plus en surproduction et les dix qui sont le plus en sous production.

# Contenu du Projet : 

c-wire.sh :  Le programme shell qui va venir trier et créer de nouve	aux fichiers
codeC : Le dossier qui contient toutes les éléments reliés au programme C
tmp : Le dossier qui va contenir tous les fichiers qui ont été créés pour des étapes intermédiaires
test : Le dossier qui contient tous les fichiers qu’on a obtenu en utilisant le fichier c-wire_v25.dat
Graphs : Le dossier qui va contenir le graphe que le programme va créer pour les LV all (entreprises + particulier)
Makefile : Contenu dans codeC et va venir compiler le programme C qui a été divisé en plusieurs partie
main.h, main.c, insertionavl.h, insertionavl.c, rotationavl.h, rotationavl.c, fonction.h, fonction.c : Contenus dans codeC et ce sont tous les fichiers dont a besoin le Makefile pour s’exécuter
c-wire.c : Le programme C en entier
aide.txt : fichier d’aide qui explique comment utiliser notre Projet
rapport.txt : le rapport qui détaille toutes les étapes de notre Projet et les difficultés qu’on a pu rencontrer.

# Utilisation du Projet : 

Dans un terminal, vous devez exécuter le programme c-wire.sh, si vous n’avez pas les droits il suffit d’utiliser la commande : chmod +x c-wire.sh
Lorsque vous exécutez le programme il faut rajouter des paramètres avec, il faut que vous indiquiez le chemin qui conduit au fichier de données que vous souhaitez traiter, puis le type de station que vous voulez étudier et le type de consommateurs. 

Si vous souhaitez vous pouvez préciser sur quelle centrale vous voulez vous concentrer. Et si vous souhaitez afficher le fichier d’aide il suffit de mettre un argument -h.
exemple : ./c-wire.sh dossier/fichier.csv hvb comp 1 -> va faire un fichier qui contient tous les identifiants des hvb reliés à la centrale numéro une, et qui contient toute leur consommation d’entreprise et leur capacité. 

argument 1 : chemin du fichier de données.

argument 2 : type de stations “hvb” ou “hva” ou “lv”.

argument 3 : type de consommateurs “comp” si le type de station est un hvb ou un hva sinon “comp” ou “indiv” ou “all” (comp = entreprises, indiv = logements de particuliers, all = tous les consommateurs).

argument 4 : (pas obligatoire) numéro de la centrale allant de 1 à 5.

autre argument : -h pour afficher l’aide, cet argument peut être mis à n’importe quelle place.

Si l’utilisateur ne saisit pas correctement les arguments, le programme va s’arrêter et le fichier d’aide va s’afficher.

A la fin du programme un fichier va se créer, exemple : hvb_comp.csv.

# Partie Shell : 

Le programme en shell va venir vérifier les arguments et afficher des messages d’erreurs et le fichier d’aide en cas d’erreur lors de la saisie des arguments. Le shell va venir compiler le programme C et créer un exécutable du nom de exec.

Ensuite il va venir trier le fichier que l’utilisateur souhaite étudié pour envoyer dans le programme C que les données utiles. Après le traitement dans le C il va faire un nouveau tri pour que les fichiers soient triés dans l’ordre croissant au niveau de la capacité des stations. Dans le cas des LV all, le shell va faire un tri supplémentaire. 

Le shell va créer des nouveaux fichiers qui contiennent l’identifiant, la capacité et le consommation de chaque station. Le shell va aussi calculer le temps d’exécution du programme. 

# Partie C : 

A partir des données qu’il reçoit, le programme C va venir vérifier le type de données reçu et va créer un arbre AVL avec ses données, il reçoit plusieurs lignes qui correspondent à une même station alors le programme va venir faire la somme de sa consommation. Avec l’AVL le programme C peut faire des recherches plus facilement avec une complexité plus simple.

Et le programme C va renvoyer chaque station avec sa capacité et sa consommation totale.

# Présentation de l’équipe : 
	
L’équipe du Projet est constituée de trois étudiantes en Pré-ing 2 à CY Tech. Hammad Kahina, Maheswaran Ashana et Avel Mélanie en MI2.
