#include "Move.h"
#include "Tiles.h"
#include <array>
#include <vector>

const int gameboard_size = 7;

class Gameboard
{
  private:
	std::array<std::array<Tile, gameboard_size>, gameboard_size> gameboard;

  public:
	Gameboard();
	Gameboard(const Gameboard &gameboard);
	Gameboard(Gameboard &&gameboard);
	const std::array<std::array<Tile, gameboard_size>, gameboard_size> &getGameboard() const;
	bool validateMove(const Move &move);
	void applyMoves(const std::vector<Move> &moves);
};
