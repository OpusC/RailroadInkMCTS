# Tier 1
Finish tile rules
Dice system
Legal move generation
Turn application
Scoring
Game-over detection

# Tier 2
Random playouts
Board cloning
Baseline MCTS
UCB1

# Tier 3
Rollout heuristics
Parallelism
Profiling
Memory optimization
Tree reuse/transposition tables

# Game class refactor
- Replace `Game(uint32_t seed)` with `Game(int size, std::vector<BoardExit> exits)` and `Game(int size, std::vector<BoardExit> exits, uint32_t seed)` for optional reproducibility
- Add UI api: `placeTile`, `undoLastPlacement`, `endTurn`
- Add MCTS api: `generateValidTurns`, `applyTurn`
- Add shared api: `getBoard`, `getAvailableTiles`, `getRound`, `isGameOver`, `calculateScore`
- Maintain `std::vector<ValidPlacement>` privately, built from exits on construction and updated incrementally on every placement
- Custom copy constructor: copies all state but re-seeds RNG from `std::random_device` so MCTS rollouts diverge
- Add `Score.h` struct with `exitConnections`, `longestRoad`, `longestRail`, `centerSquares`, `errors`, `total()`
- `Turn` type alias (`using Turn = std::vector<Move>`) belongs in `Move.h`

# Overall Goals
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
