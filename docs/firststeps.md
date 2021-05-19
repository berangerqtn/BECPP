![Logo](./logo/logo_large.png)
[Retour à l'accueil](../readme.md)

## Premiers Pas
### Mise en place des composants
Pour mettre en place l'appareil, il est nécessaire de mettre en place le cablâge électronique des différents composants. Nous vous recommandons de suivre les instructions d'[Assemblage électronique](elec.md)

### Avant la compilation
Ce projet a été mis en place via le module PlatformIO de VSCode, nous vous recommandons donc d'utiliser cet environnement de travail pour éditer et compiler le projet. 

__VSCode__ : https://code.visualstudio.com/

__PlatformIO__ : Plug In téléchargeable depuis VSCode.

Après avoir ouvert le dossier via VSCode, vous pourrez compiler et téléverser en utilisant le bouton dédié (flèche en bas de l'interface VSCode PlatformIO).

__Autre point important__, vous pouvez mettre à jour votre SSID ainsi que le mot de passe de votre routeur, dans le fichier MyWebServer.h afin que l'ESP8266 puisse vous proposer ses services connectés.   

### Utilisation du module
Pour accéder au menu il faut appuyer sur le bouton poussoir. Pour naviguer dans le menu, utilisez le potentiomètre et validez vos choix par un appui sur le bouton poussoir.

### Utilisation classique du module
Pour accéder au menu, appuyez une première fois sur le bouton poussoir. 
D'ici, vous pourrez accéder à trois sections : 
- Ajouter un Utilisateur
- Voir les Utilisateurs
- Consommer
- Retour

### Naviguer dans les menus
Pour naviguer dans les menus, cela se fait via le potentiomètre. Jouer sur le portneiomètre vous permettra de faire évoluer les valeurs affichées à l'écran et vous pourrez ainsi valider votre choix en appuyant sur le bouton poussoir.

### Ajouter un utilisateur
Cet onglet vous permet d'ajouter un participant à la soirée, il sera désormais proposé dans la liste des personnes qui pourront consommer, et le calcul de son taux d'alcool par litre de sang se fera au fur et à mesure de la soirée

### Voir les utilisateurs
Cet onglet vous permet d'accéder à la liste des utilisateurs ainsi que leur taux d'alcool par litre de sang à l'heure actuelle. Pour vous faciliter la lecture de ce chiffre, l'écran s'allumera en vert ou en rouge selon si vous pouvez prendre le volant à un instant T ou non.

### Consommer
Depuis cet onglet vous pourrez sélectionner un utilisateur pour ajouter une consommation lorsqu'il reprend un verre d'alcool. Cet action ajoutera la quantité d'aclcool qui l'intégrera au taux d'alcool actuellement restant dans son corps.

NB : La navigation dans l'ongloet Consommer est un peu différente, pour naviguer, le potentiomètre vous permettra d'atteindre 3 possibilités : 
- Previous user : qui vous fera accéder à l'utilisateur précédent dans la liste (s'il existe)
- This user : qui s'il est choisi ajoutera immédiatement une dose d'alcool à l'utilisateur pointé
- Next User : qui vous permettra de passer à l'utilisateur suivant. 

__IMPORTANT__ : Pour valider un ajojut de dose à un utilisateur il est important une fois sur le bon utilisateur d'appuyer sur l'option This User, autrement la dose ne sera pas ajoutée. Un bon moyen d'être sur que la dose est ajoutée est de vérifier si l'on est revenu au menu principal. Si c'est le cas, alors tout est en ordre ! 

### Retour
En cliquant sur le choix retour, vous retrouverez l'affichage précédent et vous pourrez ainsi revenir en arrière.

[Retour à l'accueil](../readme.md)
