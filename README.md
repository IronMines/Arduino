# Arduino
Le code des deux cartes Arduino qui communiquent via Rosserial :
- Arduino Uno gère et transmet les distances mesurées par les 5 capteurs ultrasons
- Arduino Mega est connectée au contacteur de départ (envoie le message du début de la partie) et gère les deux servos.

Pour lancer l'exécution manuellement :
"rosrun rosserial_python serial_node.py /dev/ttyACM0 __name:=uno" (vérifier dans Arduino IDE le port correspondant à chaque carte)
