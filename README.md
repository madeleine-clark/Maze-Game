# Maze Game
This project allows users to navigate through a simple 2-dimensional maze on their terminal.

## Rules
There are a few different maze boards to select from (see `boards' dir). Each board looks similar to this:
```
---- ---
|..#@.|
|#.#..|
|....#|
|#.#.$|
---- ---
```
* The `@` indicates the user's current position
* The `$` indicates the goal postion
* The '#' indicate walls that the user cannot pass through

## User Mode
The default mode is user-mode. This mode displays the current board to the terminal and requests the user make a move. The user can enter one of the following commands: 
* `'a'` : move left
* `'w'` : move up
* `'d'` : move right
* `'s'` : move down
* `'q'` : quit

If the user enters an unsupported command, a warning message is printed and they're asked to enter a new command.
The user can continue making moves until they win or quit the game. 

Here's an example of a typical user-mode game:

$ cat boards / board1 . txt
2 ..# @ .
3 #.#..
4 ....#
5 #.#. $
6 $ ./ maze boards / board1 . txt
7 ---- ---
8 |..# @ .|
9 |#.#..|
10 |....#|
11 |#.#. $ |
12 ---- ---
13 > d
14 ---- ---
15 |..#. @ |
16 |#.#..|
17 |....#|
18 |#.#. $ |
19 ---- ---
20 > w
21 You can ’ t move there .
22 ---- ---
23 |..#. @ |
24 |#.#..|
25 |....#|
26 |#.#. $ |
27 ---- ---
28 > s
29 ---- ---
30 |..#..|
31 |#.#. @ |
32 |....#|
33 |#.#. $ |
34 ---- ---
35 > a
36 ---- ---
37 |..#..|
38 |#.# @ .|
39 |....#|
40 |#.#. $ |
41 ---- ---
42 > w
43 ---- ---
44 |..# @ .|
45 |#.#..|
46 |....#|
47 |#.#. $ |
48 ---- ---
49 > s
50 ---- ---
51 |..#..|
52 |#.# @ .|
53 |....#|
54 |#.#. $ |
55 ---- ---
56 > s
57 ---- ---
58 |..#..|
59 |#.#..|
60 |... @ #|
61 |#.#. $ |
62 ---- ---
63 > d
64 You can ’ t move there .
65 ---- ---
66 |..#..|
67 |#.#..|
68 |... @ #|
69 |#.#. $ |
70 ---- ---
71 > s
72 ---- ---
73 |..#..|

## File Mode
