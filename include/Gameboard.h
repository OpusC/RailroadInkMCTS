#include "Move.h"
#include "Tiles.h"
#include <array>
#include <vector>

class Gameboard
{
  public:
	explicit Gameboard(int size);

	const std::vector<std::vector<Tile>> &getGameboard() const
	{
		return gameboard;
	}
	Tile getTile(int x, int y) const;
	bool validateMoves(const std::array<Move, 5> &moves);
	bool isConnected(std::array<Move, 5>);
	void applyMoves(const std::array<Move, 5> &moves);

  private:
	bool tilesConnect(Tile t1, Tile t2, int direction) const;
	void unapplyMoves(const std::array<Move, 5> &moves);
	std::vector<std::vector<Tile>> gameboard;
};
