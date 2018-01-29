/*
 * Copyright (C) 2016-2018 DeathCore <http://www.noffearrdeathproject.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "AntihackerData.h"
#include <map>

#ifndef SC_ACMGR_H
#define SC_ACMGR_H

enum HackTypes
{
	SPEED_HACK,
	FLY_HACK,
	WALL_CLIMB_HACK,
	WALK_ON_WATER_HACK,
	JUMP_HACK,
};

typedef std::map<uint32, AntihackerData> AntihackerPlayersDataMap;

class AntihackerMgr
{
public:
	AntihackerMgr();
	~AntihackerMgr();

	static AntihackerMgr* instance()
	{
		static AntihackerMgr instance;
		return &instance;
	}

	void StartDetection(Player* player, MovementInfo movementInfo, uint32 opcode);

	AntihackerPlayersDataMap m_Players;

private:
	void Punish(Player* player, uint8 hackType);
	void Report(Player* player, uint8 hackType);
	void SpeedHackDetection(Player* player, MovementInfo movementInfo);
	void FlyHackDetection(Player* player, MovementInfo movementInfo);
	void WallClimbHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode);
	void WalkOnWaterHackDetection(Player* player, MovementInfo movementInfo);
	void JumpHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode);
};

#define sAntihackerMgr AntihackerMgr::instance()

#endif
