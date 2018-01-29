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

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "ArenaTeamMgr.h"
#include "CellImpl.h"
#include "CharacterCache.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "DisableMgr.h"
#include "GridNotifiers.h"
#include "Group.h"
#include "GroupMgr.h"
#include "InstanceSaveMgr.h"
#include "Item.h"
#include "Language.h"
#include "LFG.h"
#include "Log.h"
#include "MMapFactory.h"
#include "MovementGenerator.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Pet.h"
#include "Player.h"
#include "Realm.h"
#include "SpellAuras.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "TargetedMovementGenerator.h"
#include "Transport.h"
#include "Weather.h"
#include "WeatherMgr.h"
#include "World.h"
#include "WorldSession.h"
#include <boost/asio/ip/address_v4.hpp>

const uint32 RANK_VIP = (uint32)SEC_VIP;

class VIP_Item : public ItemScript
{
	public:
		VIP_Item() : ItemScript("VIP_Item") {}

    void SetAccountVip(Player* player, uint32 accountId, char const* vipTime, char const* vipComment)
    {
		uint32 _time = time(NULL);
        uint32 _vipTime = TimeStringToSecs(vipTime);

        if (player->GetSession()->GetSecurity() == RANK_VIP)
            LoginDatabase.PQuery("UPDATE account_access SET vipTime = vipTime + %u WHERE id = %u", _vipTime, accountId);
        else
            LoginDatabase.PQuery("REPLACE INTO account_access (id, gmlevel, RealmID, vipTime, vipComment) VALUES ('%u','%u','-1','%u','%s')", accountId, RANK_VIP, _time + _vipTime, vipComment);
    }

    bool OnUse(Player* player, Item* item, SpellCastTargets const&) override
    {
        ChatHandler(player->GetSession()).SendSysMessage("Agora sua conta é V.I.P!");
        player->DestroyItemCount(item->GetEntry(), 1, true, false);
        player->CastSpell(player, 59908);
        SetAccountVip(player, player->GetSession()->GetAccountId(), "30d", "VIP 30 Dias");
        return true;
    }
};

void AddSC_VIP_Item()
{
    new VIP_Item();
}