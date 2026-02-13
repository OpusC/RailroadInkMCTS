#include "Move.h"
#include "Tiles.h"
#include <array>

const int gameboard_size = 7;

class Gameboard
{
  private:
	std::array<std::array<Tile, gameboard_size>, gameboard_size> gameboard;

  public:
	Gameboard();
	Gameboard(const Gameboard &gameboard);
	Gameboard(Gameboard &&gameboard);
	const std::array<std::array<Tile, gameboard_size>, gameboard_size> &getGameboard() const
	{
		return gameboard;
	}
	bool validateMoves(const std::array<Move, 4> &moves);
	bool isConnected(int x, int y) const;
	void applyMoves(const std::array<Move, 4> &moves);
};
