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

#include "AntihackerMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

AntihackerMgr::AntihackerMgr() {}
AntihackerMgr::~AntihackerMgr() {}

void AntihackerMgr::StartDetection(Player* player, MovementInfo movementInfo, uint32 opcode)
{
	uint32 key = player->GetGUID().GetCounter();

	uint32 MaxReports = sWorld->getIntConfig(CONFIG_ANTIHACKER_MAX_REPORTS);
	uint32 RefreshTime = sWorld->getIntConfig(CONFIG_ANTIHACKER_REFRESH_TIME);
	AccountTypes IgnoreAccountRank = (AccountTypes)sWorld->getIntConfig(CONFIG_ANTIHACKER_IGNORE_ACCOUNT_RANK);
	uint32 IgnoreLatency = sWorld->getIntConfig(CONFIG_ANTIHACKER_IGNORE_LATENCY);

	if (player->GetSession()->GetSecurity() > IgnoreAccountRank)
		return;

	if (player->GetSession()->GetLatency() > IgnoreLatency)
		return;

	if (m_Players[key].GetRefreshTime() <= getMSTime() || m_Players[key].GetReports() >= MaxReports)
		m_Players[key].ResetPlayerData();

	if (m_Players[key].GetRefreshTime() == 0)
		m_Players[key].SetRefreshTime(getMSTime() + RefreshTime);

	if (player->IsInFlight() || player->GetTransport() || player->GetVehicle())
	{
		m_Players[key].SetLastMovementInfo(movementInfo);
		m_Players[key].SetLastOpcode(opcode);
		return;
	}

	SpeedHackDetection(player, movementInfo);
	FlyHackDetection(player, movementInfo);
	WallClimbHackDetection(player, movementInfo, opcode);
	JumpHackDetection(player, movementInfo, opcode);

	m_Players[key].SetLastMovementInfo(movementInfo);
	m_Players[key].SetLastOpcode(opcode);
}

void AntihackerMgr::Punish(Player* player, uint8 hackType)
{
	std::string str;
	AccountTypes IgnoreAccountRank = (AccountTypes)sWorld->getIntConfig(CONFIG_ANTIHACKER_IGNORE_ACCOUNT_RANK);
	SessionMap sessions;

	switch (hackType)
	{
	case SPEED_HACK:
		str = "Speed Hack";
		break;
	case FLY_HACK:
		str = "Fly Hack";
		break;
	case WALL_CLIMB_HACK:
		str = "Wall Climb Hack";
		break;
	case WALK_ON_WATER_HACK:
		str = "Walk On Water Hack";
		break;
	case JUMP_HACK:
		str = "Jump Hack";
		break;
	}

	switch (sWorld->getIntConfig(CONFIG_ANTIHACKER_ACTION))
	{
	case 0:
		sessions = sWorld->GetAllSessions();
		for (SessionMap::const_iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
		{
			if (itr->second->GetSecurity() > IgnoreAccountRank)
				itr->second->SendNotification("|CFFFFFF00[Sistema Anticheat - Antihacker] :: |r |CFFFFFFFF[%s]|r Pode estar usando %s, verifique isso!", player->GetName().c_str(), str.c_str());
		}
		break;
	case 1:
		player->TeleportTo(1, 16217.738281f, 16403.453125f, -64.378838f, 3.121913f);
		player->CastSpell(player, 9454);
		sessions = sWorld->GetAllSessions();
		for (SessionMap::const_iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
		{
			if (itr->second->GetSecurity() < IgnoreAccountRank)
				itr->second->SendNotification("|CFFFFFF00[Sistema Anticheat - Antihacker] :: |r |CFFFFFFFF[%s]|r Foi parado e mandado para a Sala Oficial do Administrador por usar %s!", player->GetName().c_str(), str.c_str());
		}
		break;
	case 2:
		player->GetSession()->KickPlayer();
		sessions = sWorld->GetAllSessions();
		for (SessionMap::const_iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
		{
			if (itr->second->GetSecurity() < IgnoreAccountRank)
				itr->second->SendNotification("|CFFFFFF00[Sistema Anticheat - Antihacker] :: |r |CFFFFFFFF[%s]|r Foi desconectado por usar %s!", player->GetName().c_str(), str.c_str());
		}
		break;
    }
 }

void AntihackerMgr::Report(Player* player, uint8 hackType)
{
	uint32 key = player->GetGUID().GetCounter();

	uint32 MaxReports = sWorld->getIntConfig(CONFIG_ANTIHACKER_MAX_REPORTS);

	if (m_Players[key].GetReports() <= MaxReports)
		m_Players[key].IncrementReports();

	switch (hackType)
	{
	case WALL_CLIMB_HACK:
	case WALK_ON_WATER_HACK:
	case JUMP_HACK:
		Punish(player, hackType);
		break;
	default:
		if (m_Players[key].GetReports() > 1)
			ChatHandler(player->GetSession()).PSendSysMessage("|CFFFF0000[Sistema Anticheat - Antihacker] :: Detectando uso de Cheat - Hacker [ %u / %u ] para ser punido.|r", m_Players[key].GetReports(), MaxReports);
		if (m_Players[key].GetReports() >= MaxReports)
			Punish(player, hackType);
		break;
	}
}

void AntihackerMgr::SpeedHackDetection(Player* player, MovementInfo movementInfo)
{
	uint32 key = player->GetGUID().GetCounter();
	uint32 AverageSpeed = sWorld->getIntConfig(CONFIG_ANTIHACKER_AVERAGE_SPEED);

	// We also must check the map because the movementFlag can be modified by the client.
	// If we just check the flag, they could always add that flag and always skip the speed hacking detection.
	// 369 == DEEPRUN TRAM
	if (m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_ONTRANSPORT) && player->GetMapId() == 369)
		return;

	uint32 distance2D = (uint32)movementInfo.pos.GetExactDist2d(&m_Players[key].GetLastMovementInfo().pos);
	UnitMoveType moveType;

	// we need to know HOW is the player moving
	// TO-DO: Should we check the incoming movement flags?
	if (player->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
		moveType = MOVE_SWIM;
	else if (player->HasUnitMovementFlag(MOVEMENTFLAG_FLYING))
		moveType = MOVE_FLIGHT;
	else if (player->HasUnitMovementFlag(MOVEMENTFLAG_WALKING))
		moveType = MOVE_WALK;
	else
		moveType = MOVE_RUN;

	// how many yards the player can do in one sec.
	uint32 speedRate = (uint32)(player->GetSpeed(UnitMoveType(moveType)) + movementInfo.jump.xyspeed);

	// how long the player took to move to here.
	uint32 timeDiff = getMSTimeDiff(m_Players[key].GetLastMovementInfo().time, movementInfo.time);

	if (!timeDiff)
		timeDiff = 1;

	// this is the distance doable by the player in 1 sec, using the time done to move to this point.
	uint32 clientSpeedRate = distance2D * AverageSpeed / timeDiff;

	// we did the (uint32) cast to accept a margin of tolerance
	if (clientSpeedRate > speedRate)
		Report(player, SPEED_HACK);
}

void AntihackerMgr::FlyHackDetection(Player* player, MovementInfo movementInfo)
{
	uint32 key = player->GetGUID().GetCounter();

	if (!m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING))
		return;

	if (player->HasAuraType(SPELL_AURA_FLY) ||
		player->HasAuraType(SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED) ||
		player->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED) ||
		player->HasAuraType(SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED) ||
		player->HasAuraType(SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS) ||
		player->HasAuraType(SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK))
		return;

	Report(player, FLY_HACK);
}

void AntihackerMgr::WallClimbHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode)
{
	uint32 key = player->GetGUID().GetCounter();

	if (opcode != MSG_MOVE_HEARTBEAT || m_Players[key].GetLastOpcode() != MSG_MOVE_HEARTBEAT)
		return;

	// in this case we don't care if they are "legal" flags, they are handled in another parts of the Antihacker Manager.
	if (player->IsInWater() || player->IsFlying() || player->IsFalling())
		return;

	Position playerPos;

	float deltaZ = fabs(playerPos.GetPositionZ() - movementInfo.pos.GetPositionZ());
	float deltaXY = movementInfo.pos.GetExactDist2d(&playerPos);

	float angle = Position::NormalizeOrientation(tan(deltaZ / deltaXY));

	if (angle > 1.8f)
		Report(player, WALL_CLIMB_HACK);
}

void AntihackerMgr::WalkOnWaterHackDetection(Player* player, MovementInfo movementInfo)
{
	uint32 key = player->GetGUID().GetCounter();

	if (!m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_WATERWALKING))
		return;

	// if we are a ghost we can walk on water
	if (!player->IsAlive())
		return;

	if (player->HasAuraType(SPELL_AURA_FEATHER_FALL) ||
		player->HasAuraType(SPELL_AURA_SAFE_FALL) ||
		player->HasAuraType(SPELL_AURA_WATER_WALK))
		return;

	Report(player, WALK_ON_WATER_HACK);
}

void AntihackerMgr::JumpHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode)
{
	uint32 key = player->GetGUID().GetCounter();

	if (m_Players[key].GetLastOpcode() == MSG_MOVE_JUMP && opcode == MSG_MOVE_JUMP)
		Report(player, JUMP_HACK);
}
