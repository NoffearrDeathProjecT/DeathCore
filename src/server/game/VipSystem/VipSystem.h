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
#include "World.h"
#include "Language.h"

#ifndef VIPSYSTEM_H
#define VIPSYSTEM_H

enum RateType
{
    TYPE_RATE_XP_KILL,
    TYPE_RATE_XP_QUEST,
    TYPE_RATE_XP_EXPLORE,
    TYPE_RATE_HONOR,
    TYPE_RATE_REPUTATION,
    TYPE_RATE_SKILL,
    TYPE_RATE_CRAFTING,
    TYPE_RATE_GATHERING,
};

class VipSystem
{
public:
    static VipSystem* instance()
    {
        static VipSystem instance;
        return &instance;
    }

    void VipFill(AccountTypes accountRank, uint8 type, float &value);
    void VipFill(AccountTypes accountRank, uint8 type, uint32 &value);
    void VipFill(AccountTypes accountRank, uint8 type, int32 &value);
};

#define sVipSystem VipSystem::instance()

#endif
