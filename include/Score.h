struct Score
{
	int connectedExits;
	int longestRoad;
	int longestRail;
	int centreSquares;
	int deadEndPenalty;
	int total() const
	{
		return connectedExits + longestRoad + longestRail + centreSquares
		       + deadEndPenalty;
	}
};
