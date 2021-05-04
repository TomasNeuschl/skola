#pragma once

#include <utility>
#include <Engine/CWindow.h>
#include <Game/CBoard.h>
#include <Engine/CCharacter.h>

class CPlayer: public CCharacter
{
public:
	/// Constructs player, `x` `y` are starting
	/// coordinates.
	CPlayer(int x, int y);
	CPlayer(std::pair<int, int> coords);
	~CPlayer();

	/// moves player one tile to direction where
	/// he heads.
	void move(Direction dir);

	/// Tells if player is alive.
	bool is_alive() const;
	void update(CBoard *board);

	/// Draws player to `window`.
	virtual void draw(CWindow *window);

	std::pair<int, int> next_coords;

	Direction next_dir;
};