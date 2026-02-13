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
