#include "Move.h"
#include "Tiles.h"
#include <array>

const int gameboardSize = 7;

class Gameboard
{
  public:
	Gameboard();

	const std::array<std::array<Tile, gameboardSize>, gameboardSize> &getGameboard() const
	{
		return gameboard;
	}
	Tile getTile(int x, int y) const;
	bool validateMoves(const std::array<Move, 5> &moves);
	bool isConnected(std::array<Move, 5>);
	void applyMoves(const std::array<Move, 5> &moves);

  private:
	bool tilesConnect(Tile t1, Tile t2, int direction) const;
	void dfs(int x,
	  int y,
	  bool &tileTouchesExit,
	  std::array<std::array<bool, gameboardSize>, gameboardSize> &visited);

	void unapplyMoves(const std::array<Move, 5> &moves);
	std::array<std::array<Tile, gameboardSize>, gameboardSize> gameboard;
	bool touchesExit[gameboardSize][gameboardSize];
};
