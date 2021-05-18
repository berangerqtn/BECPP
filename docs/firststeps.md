# SJC Project
## Premiers Pas
##### Mise en place des composants
Pour mettre en place l'appareil, il est nécessaire de mettre en place le cablâge électronique des différents composants. Nous vous recommandons de suivre les instructions d'[Assemblage électronique](elec.md).

##### Avant la compilation
Ce projet a été mis en place via le module PlatformIO de VSCode, nous vous recommandons donc d'utiliser cet environnement de travail pour éditer et compiler le projet. 

__VSCode__ : https://code.visualstudio.com/

__PlatformIO__ : Plug In téléchargeable depuis VSCode.

Après avoir ouvert le dossier via VSCode, vous pourrez compiler et téléverser en utilisant le bouton dédié (flèche en bas de l'interface VSCode PlatformIO).

__Autre point important__, vous pouvez mettre à jour votre SSID ainsi que le mot de passe de votre routeur, dans le fichier MyWebServer.h afin que l'ESP8266 puisse vous proposer ses services connectés.   

#### Utilisation du module
Pour accéder au menu il faut appuyer sur le bouton poussoir. Pour naviguer dans le menu, utilisez le potentiomètre et validez vos choix par un appui sur le bouton poussoir.

#### Utilisation classique du module
Pour accéder au menu, appuyez une première fois sur le bouton poussoir. 
D'ici, vous pourrez accéder à trois sections : 
- Ajouter un Utilisateur
- Voir le bilan des Utilisateurs
- Consommer

L'onglet consommation vous permettra de rajouter un verre au bilan d'un utilisateur