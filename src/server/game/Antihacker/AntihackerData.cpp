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

#include ".../server/game/Antihacker/AntihackerData.h"

AntihackerData::AntihackerData() {}
AntihackerData::~AntihackerData() {}

const uint32 AntihackerData::GetLastOpcode()
{
	return lastOpcode;
}

void AntihackerData::SetLastOpcode(uint32 opcode)
{
	lastOpcode = opcode;
}

const MovementInfo& AntihackerData::GetLastMovementInfo()
{
	return lastMovementInfo;
}

void AntihackerData::SetLastMovementInfo(MovementInfo& moveInfo)
{
	lastMovementInfo = moveInfo;
}

const uint8 AntihackerData::GetReports()
{
	return totalReports;
}

void AntihackerData::IncrementReports()
{
	totalReports++;
}

const uint32 AntihackerData::GetRefreshTime()
{
	return refreshTime;
}

void AntihackerData::SetRefreshTime(uint32 time)
{
	refreshTime = time;
}

void AntihackerData::ResetPlayerData()
{
	totalReports = 0;
	refreshTime = 0;
}
