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

#include "Define.h"
#include "MovementGenerator.h"

#ifndef SC_ACDATA_H
#define SC_ACDATA_H

class AntihackerData
{
public:
	AntihackerData();
	~AntihackerData();

	const uint32 GetLastOpcode();
	void SetLastOpcode(uint32 opcode);

	const MovementInfo& GetLastMovementInfo();
	void SetLastMovementInfo(MovementInfo& moveInfo);

	const uint8 GetReports();
	void IncrementReports();

	const uint32 GetRefreshTime();
	void SetRefreshTime(uint32 time);

	void ResetPlayerData();

private:
	uint32 lastOpcode;
	MovementInfo lastMovementInfo;
	uint8 totalReports;
	uint32 refreshTime;
};

#endif
