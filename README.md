Perlimpinpin
============

[![Build Status][]][Travis CI Perlimpinpin]

Ceci est un projet à réaliser dans le cadre de l'Unité d'Enseignement intitulée
« [Géométrie pour la 3D][] » faisant partie du programme de
[L3S6 Informatique][] de l'[Université de Strasbourg][].

Il s'agit d'extruder des polygones selon un champ vectoriel généré par un bruit de Perlin.

[Travis CI Perlimpinpin]: https://travis-ci.org/Harenome/perlimpinpin
[Build Status]: https://travis-ci.org/Harenome/perlimpinpin.svg?branch=master
[Géométrie pour la 3D]: http://mathinfo.unistra.fr/offre-de-formation/ue/?spec=17&sem=39&ue=433
[L3S6 Informatique]: http://mathinfo.unistra.fr/offre-de-formation/licences-mathematiques-et-informatique/informatique/
[Université de Strasbourg]: http://www.unistra.fr/

Table des matières
------------------
- [Pré-requis](#pré-requis)
  - [Fedora](#fedora)
    - [Minimum pour Fedora](#minimum-pour-fedora)
  - [Ubuntu](#ubuntu)
    - [Minimum pour Ubuntu](#minimum-pour-ubuntu)
- [Récupérer perlimpinpin](#récupérer-perlimpinpin)
  - [git](#git)
  - [wget](#wget)
- [Compiler perlimpinpin](#compiler-perlimpinpin)
- [Lancer perlimpinpin](#lancer-perlimpinpin)
- [License](#license)

Pré-requis
----------
### Fedora
#### Minimum pour Fedora
```bash
$ yum groupinstall "Development Tools"
$ yum install opengl-devel freeglut-devel git wget
```

### Ubuntu
#### Minimum pour Ubuntu
```bash
$ apt-get install build-essential freeglut3 freeglut3-dev git-core
```

Récupérer perlimpinpin
----------------------
### git
```bash
$ git clone https://github.com/Harenome/perlimpinpin.git
```

### wget
```bash
$ wget https://github.com/Harenome/perlimpinpin/archive/master.zip
```

Compiler perlimpinpin
---------------------
```bash
$ make
```

Lancer perlimpinpin
-------------------
```bash
$ bin/main
```

License
-------
Copyright © 2014 Harenome RAZANAJATO

Ce projet est libre. Vous pouvez le redistribuer ou le modifier selon les termes
de la license « Do What The Fuck You Want To Public License », Version 2, comme
publiée par Sam Hocevar. Pour de plus amples informations, veuillez vous référer
au fichier COPYING, ou bien http://www.wtfpl.net/.
