#include "Gameboard.h"
#include "Tiles.h"
#include <array>
#include <random>
#include <vector>

class Game
{

  public:
	Game();
	explicit Game(uint32_t seed);
	Game(const Game &game);
	Game(Game &&game);
	/*
	 * Returns the score of the game as if the game finished and end
	 * of game scoring is applied
	 */
	int getScore() const;
	/*
	 * Rolls the four dice to determine which dice must be used for the upcoming move
	 */
	const std::array<TileType, 4> rollDice();
	Gameboard getGameboard() const;

	/*
	 * Param: the result of a rollDice call
	 * Outputs a vector containing all of the possible moves with the inputted dice roll,
	 * including possible uses of the special tile
	 */
	std::vector<Move> generateValidMoves(std::array<TileType, 4>);
	bool validateMove(const std::array<Move, 5> &moves);
	void playMove(std::array<Move, 5>);
	int getSpecialTilesUsed() const;

  private:
	Gameboard gameboard;
	int turn;
	std::array<bool, 6> specialTileUsed;
	std::mt19937 rng;
};
