#pragma once

#include <Game/CBoard.h>
#include <Game/CPlayer.h>
#include <Engine/CWindow.h>
#include <Engine/CCharacter.h>

#include <stdlib.h>
#include <set>
#include <algorithm>
#include <utility>

/// Entity of ghost, on crossroads goes random way.
class CGhost : public CCharacter
{
public:
	CGhost(int x, int y);
	virtual ~CGhost();

	void set_frightened_mode(bool option);

	/// Tells if ghost is vulnerable.
	bool is_frightened() const;

	/// Updates ghost on board.
	virtual void update(CBoard *board, CPlayer *player);

	/// Draws ghost with default colours.
	virtual void draw(CWindow *window);

	/// Draws ghost with colours you choose.
	virtual void draw(CWindow *window, int colour_pair);

	/// Checks if ghost is on crossroad, if so, returns set od directions
	/// where he can go.
	std::pair<bool, std::set<Direction>> on_crossroad(CBoard *board);

	/// Tells if ghost is frightened.
	bool frightened;
};