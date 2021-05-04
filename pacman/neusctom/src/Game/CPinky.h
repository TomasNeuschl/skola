#pragma once

#include <Game/CPlayer.h>
#include <Game/CGhost.h>
#include <Game/CBoard.h>
#include <Engine/CWindow.h>

///his target is 3 tiles ahead of player bases on player direction
class CPinky : public CGhost
	{
	public:
		CPinky ( int x, int y );
		virtual ~CPinky ();
		
		virtual void draw ( CWindow * window );
		virtual void update ( CBoard * board, CPlayer * player );
	};