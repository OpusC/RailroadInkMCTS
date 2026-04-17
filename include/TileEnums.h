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
