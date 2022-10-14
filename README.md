# PLT RISK

[![Actions Status](https://github.com/cbares/plt/workflows/PLT%20build/badge.svg)](https://github.com/cbares/plt/actions)

![RIsk](rapport/risk.jpg)

## Equipe 

* [Lasme Sam Florent DIBY](https://github.com/SaSamSa)

* [Uriel Jesussindjlo DJENONTIN AGOSSOU](https://github.com/jdjenontin)

* [Yann RICUR](https://github.com/RicurY)

* [Xiaoyu ZHAO](https://github.com/Xiaoyu367)


# 1 Objectif
## 1.1 Présentation générale
Notre projet porte sur la réalisation du jeu Risk. C’est un jeu de stratégie au tour par tour qui permet à deux à six joueurs de s’affronter. Pour notre projet nous nous limiterons à des parties à trois joueurs.

## 1.2 Règles du jeu

Le jeu se déroule sur un plateau représentant la carte du monde et divisée en plusieurs territoires, chaque joueur commence la partie avec un certain nombre de troupes placées sur la carte, et la condition de victoire la plus classique est assez simple : il faut conquérir le monde en conquérant les territoires de ses adversaires ! Il existe cependant d’autres conditions de victoire imposées par des cartes additionnelles et faisant appels à des troupes spéciales, conditions que nous n’implémenterons pas dans notre première version du jeu.

Le tour de chaque joueur se déroule en trois parties. Tout d’abord la phase de fortification, durant cette phase, le joueur a un certain nombre de troupes à répartir entre les territoires qu’il possède déjà, ce nombre est déterminé par le nombre de territoire que le joueur possède déjà. Puis il passe à la phase d’attaque, durant cette phase le joueur peut attaquer à partir de n’importe lequel de ses territoires possédant deux troupes ou plus, tout territoire adversaire avec qui il partage une frontière. Le joueur choisi ensuite s’il veut attaquer avec une, deux ou trois troupes en sachant qu’il doit laisser au moins une troupe sur son territoire, le défenseur choisi s’il veut défendre avec une ou deux troupes. Les deux joueurs lancent un nombre de dés correspondant au nombre de troupes qu’ils mettent chacun en jeu (3 max pour l’attaquant et 2 max pour le défenseur donc) et ils comparent leur plus haut lancé et le vaincu perd une troupe, puis leurs deuxième plus haut lancés s’il y a deux défenseurs, noté qu’en cas d’égalité des lancés le défenseur l’emporte. S’il ne reste plus de troupes sur le territoire du défenseur, l’attaquant s’empare de ce territoire et y déplace au moins autant de troupes qu’il a utilisé pour son attaque. Pour limiter la durée des parties, nous implémenterons une seule forme d’attaque qui consiste en des lancés successives de dés impliquant la totalité des troupes moins 1 sur le territoire attaquant et la totalité des troupes sur le territoire attaqué. La dernière phase est la phase de manœuvres. Durant cette phase, le joueur peut faire un déplacement d’autant de troupes qu’il veut d’un de ses territoires vers un autre territoire qui lui appartient et qui est frontalier à ce premier territoire en n’oubliant pas qu’il faut toujours au moins une troupe sur chaque territoire à tout moment de la partie.

## 1.3 Environnement de développement

Nous développons notre jeu en C++ dans un environnement Linux Ubuntu avec l'IDE Visual Studio Code. 


