# Finish connectionType boolean refactor
rotate4 -> rotate


# Allow arbitrary exits on construction
- We need an exit Struct
```cpp
struct Exit {
    board_x: int;
    board_y: int;
    exitDirection: Direction;
    connectionType: ConnectionType // Can re-use connection type, but assert it is only road or rail
}
```

- Exit cells use straight road/rail tiles. The outward edge points into a border cell and is ignored by BFS traversal.
- Constructor should take in a list of Exit structs to place the exits on initialization.
    - Assert no two exits are identical, and that board_x and board_y are valid (on the perimiter
    of the playable area)
    - No two exits share the same board_x and board_y, even if direction is different

- Change board representation to be n + 1 board size from the playable representation to allow
placing actual exits
- Border tiles should be of TileType Non-Playable / Border. Connections array will be empty.
This is needed to avoid the "dead end" problem. We cannot place a tile if it causes one of the
ends of a tile to become a "dead end" (blocked by another tile / border tile and does not connect,
meaning that it is impossible to connect that tile in the future)
- This also enables easier testing for the valid move generation, as with less exits, less moves are possible,
making it easier for a human to write the tests

# Valid move generation

```cpp
struct ValidPlacement {
    int board_x;
    int board_y;
    Direction fromDirection;
    ConnectionType requiredConnection;
}
```
- Invariants: Every placed tile is valid and does not create any new dead ends
    - Dead end detection: for each outgoing edge, ensure it it either connects to a matching connection, or
    that the TileType is None. Else it will create a new dead-end
- Maintain a list of ValidPlacements from Board construction and on every newly placed move
- On move placement, remove the used ValidPlacement from the list and add a new one for its
outgoing edges, only if the outgoing edge faces to a None tileType as if it connects it will not be a ValidPlacement

# Goals
1. Complete game logic
2. Implement MCTS
3. Add performance metrics
    - simulations per second
    - win rate vs random policy, greedy heuristic, or fewer simulations
4. Optimize
    - bit-packed board representation
    - multithreaded simulations
    - memory pool for nodes
    - avoiding allocations in rollout
