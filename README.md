# PedalGuitar

[![forthebadge](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](http://forthebadge.com) 

Ce projet consiste à devélopper une pédale de guitare multi-effets.

## Pour commencer

### Pré-requis

Matériel :
  - Une raspberry pi 4
  - Un shield Pisound
  - Une enceinte
  - Un câble jack 6.35mm
  - Une guitare
  - Un téléphone ou un ordinateur

Librairie :
  - libjack-jackd2-dev
  - Jackd
  - cmake

Application mobile :
   - Télécharger une application mobile qui permet d'envoyer des commandes TCP à un serveur

### Installation

Sur la raspberry pi allez dans le terminal et faites les commandes :
  - git clone https://github.com/YoanDev/PedalGuitar.git
  - cd PedalGuitar
  - cd Pedal
  - mkdir build
  - cd build
  - cmake ..
  - make 


## Démarrage
Sur la raspberry pi :
- cd build
- ./PedalGuitar

Sur le smartphone :
- Rentrer l'ip de votre raspberry pi
- Rentrer le port de votre serveur TCP

Vous pouvez maintenant envoyer les commandes pour changer les effets de la pédale.

Les commandes sont :
1: Delay
2: Saturation 
3: Rec
4: Stop
5 : Play
6 : Clean 



## Versions
**Dernière version :** 1.0
Liste des versions : [Cliquer pour afficher](https://github.com/YoanDev/PedalGuitar/tags)

## Auteurs
* **Yoan Molia* _alias_ [@YoanDev](https://github.com/YoanDev)


