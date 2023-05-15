# Maze Game
This project allows users to navigate through a simple 2-dimensional maze on their terminal.

## Rules
There are a few different maze boards to select from (see `boards' dir). Each board looks similar to this:
```
|. . # @ .|
|# . # . .|
|. . . . #|
|# . # . $|
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

When playing in user-mode, the desired board must be specified as a command-line argument. Here's an example of a typical user-mode game:
```
$ cat boards/board1.txt
2 . . # @ .
3 # . # . .
4 . . . . #
5 # . # . $
6 $ ./maze boards/board1.txt
7  -----------
8  |. . # @ .|
9  |# . # . .|
10 |. . . . #|
11 |# . # . $|
12 -----------
13 > d
14 -----------
15 |. . # . @|
16 |# . # . .|
17 |. . . . #|
18 |# . # . $|
19 -----------
20 > w
21 You can ’ t move there .
22 -----------
23 |. . # . @|
24 |# . # . .|
25 |. . . . #|
26 |# . # . $|
27 -----------
28 > s
29 -----------
30 |. . # . .|
31 |# . # . @|
32 |. . . . #|
33 |# . # . $|
34 -----------
35 > a
36 -----------
37 |. . # . .|
38 |# . # @ .|
39 |. . . . #|
40 |# . # . $|
41 -----------
42 > w
43 -----------
44 |. . # @ .|
45 |# . # . .|
46 |. . . . #|
47 |# . # . $|
48 -----------
49 > s
50 -----------
51 |. . # . .|
52 |# . # @ .|
53 |. . . . #|
54 |# . # . $|
55 -----------
56 > s
57 -----------
58 |. . # . .|
59 |# . # . .|
60 |. . . @ #|
61 |# . # . $|
62 ---- ---
63 > d
64 You can ’ t move there .
65 -----------
66 |. . # . .|
67 |# . # . .|
68 |. . . @ #|
69 |# . # . $|
70 -----------
71 > s
72 -----------
73 |. . # . .|
74 |# . # . .|
75 |. . . . #|
76 |# . # @ $|
77 -----------
78 > d
79 -----------
80 |. . # . .|
81 |# . # . .|
82 |. . . . #|
83 |# . # . @|
84 -----------
85 You won the game.
```

## File Mode
The second mode Maze Game can be played in is file-input mode. This mode is triggered when the user provides a file as an additional command-line argument after the board. The file is assumed to contains one move command per line. Maze Game runs this list of commands and determine whether it would result in a win or loss. 

### Ex. 1
Here's an example of a winning game in file-input mode:
```
1  $ cat boards/board2.txt
2  # # @ # #
3  . . . . #
4  # # # . .
5  # # . . .
6  # . . # .
7  $ . # # #
8  $ cat inputs/inputs3.txt
9  s
10 d
11 s
12 s
13 a
14 s
15 a
16 s
17 a
18 $ ./maze boards/board2.txt inputs/inputs3.txt
19 That input results in a victory.
### Ex. 2
Here's an example of a losing game in file-input mode:
```
1  $ cat boards/board2.txt
2  # # @ # #
3  . . . . #
4  # # # . .
5  # # . . .
6  # . . # .
7  $ . # # #
8  $ cat inputs/inputs4.txt
9  s
10 d
11 s
12 s
13 a
14 s
15 a
16 s
17 $ ./maze boards/board2.txt inputs/inputs4.txt
18 That input does not reach the end.
```
```
