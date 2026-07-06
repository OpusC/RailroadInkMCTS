# Tier 1
- [*] Finish tile rules
- [ ] Dice system
- [ ] **Legal move generation**
- [ ] Turn application
- [ ] Scoring
- [ ] Game-over detection

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

# Overall Goals - [ ] Complete game logic
- [ ]  Implement MCTS
- [ ]  Add performance metrics
    - simulations per second
    - win rate vs random policy, greedy heuristic, or fewer simulations
- [ ]  Optimize
    - bit-packed board representation
    - multithreaded simulations
    - memory pool for nodes
    - avoiding allocations in rollout
