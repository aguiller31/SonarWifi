# Sonar WiFi
Ceci est un projet de Sonar Wifi. Il est programmé sur 2 esp8266 (Wemos D1 Mini et NodeMCU), l'un servant à la rotation d'un moteur et l'autre à la mesure des distances via un capteur LiDAR.

<p align="center">
  <img width="460"  src="https://github.com/aguiller31/SonarWifi/assets/128867138/a90ea6bf-9c80-44ae-a215-5af07b197aa0">
</p>

## Compilation
Nous avons utiliser VS Code associé à l'extension PlatformIO pour écrire et compiler les programmes.

**Pourquoi PlatformIO plutôt que Arduino IDE ?**

Il semble que l'IDE d'Arduino n'intégre pas de compilateur pouvant compiler certaines bibliothèques écrites en C dont nous avons besoin pour ce projet. Nous aurions pu les ré-écrire en C++ mais cela aurait pris beaucoup de temps, ressource limitée pour ce BE. PlatformIO nous a permis de gagner du temps en nous soustrayant à ce problème.
### Compilation de la partie moteur
Le moteur est uploadé sur le Wemos D1 Mini.

Pour cette partie, nous avons fait le choix de renvoyer la mesure de l'angle actuel du moteur vers le serveur. Dès lors pour ne pas ralentir la rotation du moteur, nous avons décidé de faire des requêtes GET asynchrones. Pour ce faire nous avons utiliser la bibliothèque [AsyncHTTPRequest_Generic](https://github.com/khoih-prog/AsyncHTTPRequest_Generic), qui nécessite une configuration particulière de fichier platform.ini :
```
[platformio]
default_envs = ESP8266

[env]
lib_compat_mode = strict
lib_ldf_mode = chain+
build_flags = 
	-D DEBUG_ESP_PORT=Serial

[env:ESP8266]
platform = espressif8266
framework = arduino
lib_deps = khoih-prog/AsyncHTTPRequest_Generic@^1.13.0
board = d1_mini

[env:d1_mini]
platform = espressif8266
board = d1_mini
framework = arduino
lib_deps = khoih-prog/AsyncHTTPRequest_Generic@^1.13.0
```

Par ailleurs cette bibliothèque nécessite d'être incluse une première fois dans le *.ino* : `#include <AsyncHTTPRequest_Generic.h>`. Ensuite on l'inclus dans le service `#include <AsyncHTTPRequest_Generic.hpp>` sinon il y a une erreur à la compilation (rédefintion), ce comportement est décrit dans la documentation de la bibliothèque.
#### Les bibliothèques utilisées :
* [AsyncHTTPRequest_Generic](https://github.com/khoih-prog/AsyncHTTPRequest_Generic) (Cette librairie installe automatiquement les librairies dont elle dépend)

### Compilation de la partie LiDAR
Le LiDAR est uploadé sur le NodeMCU.

Dans cette partie, nous avons ajouté la gestion de certaines exceptions (il n'était pas possible de le faire dans la partie précédente). Pour ce faire il faut ajouter un flag à la compilation : `-fexceptions`
Ce fichier platform.ini est testé et fonctionnel :
```
[env:LIDAR_WIFI]
platform = espressif8266
framework = arduino
lib_deps = 
	stm32duino/STM32duino VL53L4CD@^1.0.3
	ottowinter/ESPAsyncTCP-esphome@^1.2.3
	ottowinter/ESPAsyncWebServer-esphome@^3.1.0
build_flags = -fexceptions
build_unflags = -fno-exceptions
```
#### Les bibliothèques utilisées :
* [VL53L4CD](https://github.com/stm32duino/VL53L4CD) *pour l'utilisation du LiDAR éponyme*.
* [ESPAsyncTCP](https://github.com/OttoWinter/ESPAsyncTCP) *pour la communication TCP du serveur*
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) *pour la création du serveur*

## Exécution du programme
1. alimenter le moteur avec source de tension 5V (1A min)
2. alimenter la board NodeMCU en premier avec une source de 5 ou 3.3V; en effet le WiFi est "créé" par cette board, il faut donc lui laisser le temps de l'émettre.
3. alimenter la board Wemos dans un second temps avec une source de 5 ou 3.3V. Après quelques secondes, elle dervait être connectée au réseau : **LidarSonarWifi** et le moteur doit commencer à tourner.
4. avec un appareil externe, se connecter au réseau : **LidarSonarWifi** dont le mot de passe est **987654321**.
5. se rendre à l'adresse : [http://192.168.4.22/](http://192.168.4.22/), vous devriez voir l'interface du Sonar et des points rouges correspondants aux distances mesurées par le LiDAR à un angle donné.
6. placer des objets à une distance entre 0 et 45 cm (valeur arbitraire) et observer

<p align="center">
  <img src="https://github.com/aguiller31/Voilier/assets/128867138/25cf6177-a44c-4c8d-8e5d-af7f1caad1ea" width=10% height=10%>
  <br />
<b>INSA Toulouse 2023-2024 - 4ème année : Automatique et Electronique / Systèmes Embarqués<br />Antoine Guillermin et Paul Gadanho</b>
</p>

