//-------------------------------------------------------------------------
/*
Copyright (C) 2010-2019 EDuke32 developers and contributors
Copyright (C) 2019 sirlemonhead, Nuke.YKT

This file is part of PCExhumed.

PCExhumed is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------

#ifndef __queen_h__
#define __queen_h__

#include "aistuff.h"

void InitQueens();
int BuildQueen(int nSprite, int x, int y, int z, int nSector, int nAngle, int nChannel);
void FuncQueenEgg(int, int, int);
void FuncQueenHead(int, int, int);
void FuncQueen(int, int, int);

#endif
