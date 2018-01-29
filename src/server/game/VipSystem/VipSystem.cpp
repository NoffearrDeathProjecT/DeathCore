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

#include "VipSystem.h"

void VipSystem::VipFill(AccountTypes accountRank, uint8 type, float &value)
{
    if (accountRank >= SEC_VIP)
    {
        switch (type)
        {
        case TYPE_RATE_XP_KILL:
            value *= sWorld->getRate(VIP_RATE_XP_KILL);
            break;

        case TYPE_RATE_XP_QUEST:
            value *= sWorld->getRate(VIP_RATE_XP_QUEST);
            break;

        case TYPE_RATE_XP_EXPLORE:
            value *= sWorld->getRate(VIP_RATE_XP_EXPLORE);
            break;

        case TYPE_RATE_HONOR:
            value *= sWorld->getRate(VIP_RATE_HONOR);
            break;

        case TYPE_RATE_REPUTATION:
            value *= sWorld->getRate(VIP_RATE_REPUTATION);
            break;

        case TYPE_RATE_SKILL:
            value *= sWorld->getRate(VIP_RATE_SKILL);
            break;

        case TYPE_RATE_CRAFTING:
            value *= sWorld->getRate(VIP_RATE_CRAFTING);
            break;

        case TYPE_RATE_GATHERING:
            value *= sWorld->getRate(VIP_RATE_GATHERING);
            break;

        default:
            return;
        }
    }
}

void VipSystem::VipFill(AccountTypes accountRank, uint8 type, uint32 &value)
{
    if (accountRank >= SEC_VIP)
    {
        switch (type)
        {
        case TYPE_RATE_XP_KILL:
            value *= sWorld->getRate(VIP_RATE_XP_KILL);
            break;

        case TYPE_RATE_XP_QUEST:
            value *= sWorld->getRate(VIP_RATE_XP_QUEST);
            break;

        case TYPE_RATE_XP_EXPLORE:
            value *= sWorld->getRate(VIP_RATE_XP_EXPLORE);
            break;

        case TYPE_RATE_HONOR:
            value *= sWorld->getRate(VIP_RATE_HONOR);
            break;

        case TYPE_RATE_REPUTATION:
            value *= sWorld->getRate(VIP_RATE_REPUTATION);
            break;

        case TYPE_RATE_SKILL:
            value *= sWorld->getRate(VIP_RATE_SKILL);
            break;

        case TYPE_RATE_CRAFTING:
            value *= sWorld->getRate(VIP_RATE_CRAFTING);
            break;

        case TYPE_RATE_GATHERING:
            value *= sWorld->getRate(VIP_RATE_GATHERING);
            break;

        default:
            return;
        }
    }
}

void VipSystem::VipFill(AccountTypes accountRank, uint8 type, int32 &value)
{
    if (accountRank >= SEC_VIP)
    {
        switch (type)
        {
        case TYPE_RATE_XP_KILL:
            value *= sWorld->getRate(VIP_RATE_XP_KILL);
            break;

        case TYPE_RATE_XP_QUEST:
            value *= sWorld->getRate(VIP_RATE_XP_QUEST);
            break;

        case TYPE_RATE_XP_EXPLORE:
            value *= sWorld->getRate(VIP_RATE_XP_EXPLORE);
            break;

        case TYPE_RATE_HONOR:
            value *= sWorld->getRate(VIP_RATE_HONOR);
            break;

        case TYPE_RATE_REPUTATION:
            value *= sWorld->getRate(VIP_RATE_REPUTATION);
            break;

        case TYPE_RATE_SKILL:
            value *= sWorld->getRate(VIP_RATE_SKILL);
            break;

        case TYPE_RATE_CRAFTING:
            value *= sWorld->getRate(VIP_RATE_CRAFTING);
            break;

        case TYPE_RATE_GATHERING:
            value *= sWorld->getRate(VIP_RATE_GATHERING);
            break;

        default:
            return;
        }
    }
}
