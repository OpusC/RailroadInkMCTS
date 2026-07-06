#pragma once
enum TileType {
	Empty = 0,
	StraightRail,
	CurvedRail,
	TRail,
	StraightRoad,
	CurvedRoad,
	TRoad,
	RoadToRail,
	CurvedRoadToRail,
	RoadRailUnderpass,
	Special1,
	Special2,
	Special3,
	Special4,
	Special5,
	Special6,
	Border,
	NumTiles,
};

enum Rotation { Zero = 0, Ninety, OneEighty, TwoSeventy };

enum ConnectionType { None = 0, Road, Rail };

enum Direction { Up = 0, Right, Down, Left, NumDirections };

inline bool isRouteTile(TileType t)
{
	return t == TileType::StraightRail || t == TileType::CurvedRail
	       || t == TileType::TRail || t == TileType::StraightRoad
	       || t == TileType::CurvedRoad || t == TileType::TRoad;
}

inline bool isSpecialTile(TileType t)
{
	return t == TileType::Special1 || t == TileType::Special2
	       || t == TileType::Special3 || t == TileType::Special4
	       || t == TileType::Special5 || t == TileType::Special6;
}
