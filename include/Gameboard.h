#include "Move.h"
#include "Tiles.h"
#include <array>

const int gameboard_size = 7;

class Gameboard
{
  public:
	Gameboard();
	Gameboard(const Gameboard &gameboard);
	Gameboard(Gameboard &&gameboard);

	const std::array<std::array<Tile, gameboard_size>, gameboard_size> &getGameboard() const
	{
		return gameboard;
	}
	Tile getTile(int x, int y) const;
	bool validateMoves(const std::array<Move, 4> &moves);
	bool isConnected(std::array<Move, 4>);
	void applyMoves(const std::array<Move, 4> &moves);

  private:
	bool tilesConnect(Tile t1, Tile t2, int direction) const;
	void dfs(int x,
	  int y,
	  bool &tileTouchesExit,
	  std::array<std::array<bool, gameboard_size>, gameboard_size> &visited);

	void unapplyMoves(const std::array<Move, 4> &moves);
	std::array<std::array<Tile, gameboard_size>, gameboard_size> gameboard;
	bool touchesExit[gameboard_size][gameboard_size];
};
