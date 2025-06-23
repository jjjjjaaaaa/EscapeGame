# Escape Game

## Design

**Escaper Strategy:**  
The `Escaper` generates all possible paths for a given number of steps, then calculates a score for each path. The score increases as the distance to the nearest hunter increases and as the distance to the nearest escape point decreases. The escaper selects the path with the highest score.

**Hunter Strategy:**  
The `Hunters` also generate all possible paths for a given number of steps. Half of the hunters calculate their score based on the distance to the escaper (the closer, the higher the score), while the other half calculate their score based on the distance to the escape points (the closer, the higher the score).

## Optimization Mechanisms

- Both escaper and hunters use heuristic scoring to evaluate possible moves.
- Pathfinding and scoring are optimized by pruning less promising paths and caching repeated calculations where possible.

## TODO

- Introduce machine learning, such as Markov Games, to train the escaper and hunters for more advanced strategies.

## Usage

```sh
cmake .
make EscapeGameTest
./EscapeGameTest
```

