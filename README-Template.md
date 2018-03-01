# Polyominoes puzzle by Simulated Annealing Algorithm in C++

Polyominoes puzzle is one of the most famous single player games that can be played in so many forms. One of these forms consists of an n × m board that should be covered by some of a given collection of tiles in some certain order.
This project aims to build an efficient solver to solve a simpler version of Polyomino, where each one of its tiles contain some numbers that matches the main board position numbers. The player should find the best collection of tiles that covers all the board (if possible) without any overlapping.

## Problem Description
### The input:

Given a set X and a collection S of subsets of X.

### The goal...

Find a sub-collection S* of S that satisfies the two conditions:
  The intersection of any two distinct subsets in S* is empty (no overlapping) .
     The union of the subsets in S* is X.

### For example,
Let set X = {1, 2, 3, 4, 5}, and S ={A, B, C, D, E} be a collection ofsubsets:
  A={1, 5}
  B={1, 3, 4}
  C={3, 4}
  D={2, 4}
  E={3}
The sub-collection S* = {A, D, E} is exact covering solution for X.
