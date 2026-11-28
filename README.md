# cscb07-chess

A text-based chess game written in C++ for CSCB07 at the University of Toronto Scarborough.

## About

This is the final group project (Assignment 4) for **CSCB07H3: Software Design** at the **University of Toronto Scarborough**, Fall 2026. The goal of the project is to build a complete program using object-oriented design: inheritance and polymorphism for the pieces and players, design patterns such as Strategy, Observer and Factory, separate compilation, and memory managed entirely with smart pointers.

Two players can play each other, play against the computer, or watch two computer players face off. The game follows the full rules of chess, including castling, en passant, pawn promotion, check, checkmate and stalemate. Computer opponents come in several difficulty levels, from random moves up to a search-based engine.

## Build and run

```
make
./chess            # standard text board
./chess -colour    # coloured board with chess symbols
```

## Commands

| Command | What it does |
|---|---|
| `game <white> <black>` | starts a game. Each player is `human` or `computer1` to `computer4` |
| `move e2 e4` | moves a piece (human turn) |
| `move e7 e8 Q` | moves a pawn and promotes it |
| `move e1 g1` | castles (the king moves two squares) |
| `move` | the computer makes its move (computer turn) |
| `resign` | the current player gives up |
| `setup` | builds a custom position before a game (`+ K e1`, `- e1`, `= white`, `done`) |
| `display colour` / `display text` | switches the board style at any time |

Press ctrl-D to quit and see the final score.

## Computer levels

| Level | How it plays |
|---|---|
| 1 | random legal moves |
| 2 | prefers captures and checks |
| 3 | weighs what it wins against what it could lose |
| 4 | looks several moves ahead with alpha-beta search |

## Design overview

| Part | Classes | Pattern |
|---|---|---|
| Pieces | `Piece` (abstract), `King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn` | inheritance and polymorphism |
| Rules engine | `Board`, `Move`, `Position` | legal move generation with apply and undo |
| Computer players | `Strategy` (abstract), `Level1` to `Level4` | Strategy |
| Position scoring | `Evaluator` (abstract), `MaterialEvaluator` | Strategy (swappable evaluation for the search) |
| Players | `Player` (abstract), `HumanPlayer`, `ComputerPlayer` | polymorphism |
| Game flow | `Controller`, `Game`, `ScoreBoard` | |
| Displays | `Observer`, `Subject`, `TextDisplay`, `ColourDisplay` | Observer |
| Piece creation | `makePiece` | Factory |

All memory is managed with `std::unique_ptr`. There is no `new` or `delete` anywhere in the code, and valgrind reports no leaks.

## Testing

Test input files live in `tests/`. Run one by feeding it to the program:

```
./chess < tests/valgrind.txt
valgrind --leak-check=full ./chess < tests/valgrind.txt
```