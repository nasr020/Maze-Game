# Maze-Game

## Description of the project

This project aims to create an interactive game that generates mazes randomly, with the same starting and ending points, where the user can move in four directions to reach the checkpoint. To achieve this, I implemented the well-known **Depth First Search algorithm (DFS)** for the generation of random mazes in the C language.

For the graphical aspect, I used the external library **ncurses**, which allows to visualize the created mazes and execute user commands (moving up, down, left, right) and display the movements on the maze.

## Installation of requirements

After cloning this project to your local machine, you will need to install a compiler and the ncurses library to launch and play the game

In a Debian based linux environment, you can install the gcc compiler using the command:

```
sudo apt update
sudo apt install gcc
```

After completion of the installation, you can verify that gcc is installed by running:

```
gcc --version
```

Now, you can install the ncurses library using the command:

```
sudo apt-get install libncurses5-dev
```

Now that you are done with all the required installations, you can compile the main file by running the following command:

```
gcc main.c -o main -lncurses 
```

## Depth First Search algorithm for the generation of the maze

To randomly generate a maze and ensure that there is a path between the starting point and the goal, I used the Depth First Search algorithm. The function of this algorithm in my code starts from a point (x, y), and if this point has already been visited, the function does nothing. However, if it hasn't been visited, it calculates the number of unvisited neighboring cells (cells that can be reached by moving 2 steps up, down, left, or right). As long as this number is greater than 0, the function simultaneously remains on the current cell (x, y) and executes itself for one of the previously mentioned cells (it's a recursive function). By using this program to generate the maze, we ensure that there is a path between any two cells, especially between the starting point (width-2, length-2) and the goal (1,1).





