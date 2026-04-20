// #include "Game.h"
// #include "Tiles.h"
// #include <array>
// #include <random>
//
// // Each die is represented as its 6 faces (with repeats where the physical
// // die has duplicate faces).
// static const std::array<TileType, 6> routeDie = {
// 	StraightRail, CurvedRail, TRail, StraightRoad, CurvedRoad, TRoad
// };
//
// static const std::array<TileType, 6> junctionDie = {
// 	TRail, TRail, TRoad, TRoad, RoadToRail, CurvedRoadToRail
// };
//
// static const std::array<TileType, 6> overpassDie = {
// 	RoadRailUnderpass, TRail, TRoad, StraightRail, StraightRoad, CurvedRail
// };
//
// Game::Game() : rng(std::random_device{}())
// {
// 	gameboard = Gameboard();
// 	turn = 0;
// 	specialTileUsed.fill(false);
// }
//
// Game::Game(uint32_t seed) : rng(seed)
// {
// 	gameboard = Gameboard();
// 	turn = 0;
// 	specialTileUsed.fill(false);
// }
//
// Game::Game(const Game &game) = default;
// Game::Game(Game &&game) = default;
//
// int Game::getSpecialTilesUsed() const
// {
// 	int count = 0;
// 	for (bool used : specialTileUsed) {
// 		if (used) count++;
// 	}
// 	return count;
// }
//
// bool Game::validateMove(const std::array<Move, 5> &moves)
// {
// 	for (int i = 0; i < 4; i++) {
// 		if (isSpecialTile(moves[i].tile.getTileType())) { return false; }
// 	}
//
// 	if (isSpecialTile(moves[4].tile.getTileType())) {
// 		int specialIndex = moves[4].tile.getTileType() - Special1;
// 		if (specialTileUsed[specialIndex]) { return false; }
// 		if (getSpecialTilesUsed() >= 3) { return false; }
// 	}
//
// 	return gameboard.validateMoves(moves);
// }
//
// void Game::playMove(std::array<Move, 5> moves)
// {
// 	if (isSpecialTile(moves[4].tile.getTileType())) {
// 		int specialIndex = moves[4].tile.getTileType() - Special1;
// 		specialTileUsed[specialIndex] = true;
// 	}
// 	gameboard.applyMoves(moves);
// 	turn++;
// }
//
// const std::array<TileType, 4> Game::rollDice()
// {
// 	std::uniform_int_distribution<int> d6(0, 5);
//
// 	return {
// 		routeDie[d6(rng)],
// 		routeDie[d6(rng)],
// 		junctionDie[d6(rng)],
// 		overpassDie[d6(rng)],
// 	};
// }
