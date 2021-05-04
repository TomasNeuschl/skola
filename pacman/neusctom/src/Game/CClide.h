#pragma once

#include <Game/CPlayer.h>
#include <Game/CGhost.h>
#include <Game/CBoard.h>
#include <Engine/CWindow.h>

class CClide : public CGhost
	{
	public:
		CClide ( int x, int y );
		virtual ~CClide ();
		
		virtual void draw ( CWindow * window );
		virtual void update ( CBoard * board, CPlayer * player );
	};