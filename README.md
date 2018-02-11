# FILLER - @42Born2Code

Algorithm project with graphical interface.

![](https://github.com/jon-finkel/filler/blob/master/visu.gif)

## About

Filler is a game where two programs fight on a board, and the second project of the algorithm branch at [42][1].
A virtual machine organizes the game :
- calls the players alternatively
- give each a random piece

Every turn, the current player have to put his piece on the map, if he cannot place a piece, then he won't have the ability to play for the remainder of the match.
To put a piece, the player have to write its coordinates on the standard input. 

The game appears on the standard input. 

The aim of the game is to put more pieces on the map than the ennemy. 

Refer to the [project instructions][2] for more details.

## Bonus

Reading the game on the terminal isn't very user-friendly.
A visualizer made with the minilibx (a graphical library made for our graphical projects at 42) makes the game much more intuitive to follow. It is the combined efforts of [fsabatie][3] and I.

## Installation

`make`

## Running

Standard mode : 

`./filler_vm -f [map] -p1 [player1] -p2 [player2]`

Visualizer mode :

`./filler_vm -f [map] -p1 [player1] -p2 [player2] | ./visualizer/visualizer`

Example from the root folder : 
`./filler_vm -f ./maps/map03 -p1 ./nfinkel.filler -p2 ./players/carli.filler | ./visualizer/visualizer`

## Final Mark

`No grade yet`

[1]: http://42.fr "42 Paris"
[2]: https://github.com/jon-finkel/filler/blob/master/project_instructions/filler.en.pdf "filler"
[3]: https://github.com/fabiensabatie "this guy"
