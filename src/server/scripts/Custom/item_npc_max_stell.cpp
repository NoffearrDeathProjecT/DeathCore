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

#include "ScriptPCH.h"
#include "Chat.h"

class item_spawn_teleporter : public ItemScript
{
public:
	item_spawn_teleporter() : ItemScript("item_spawn_teleporter") { }

	bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const&) override
	{
  		player->SummonCreature(77777,player->GetPositionX() ,player->GetPositionY()+10, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,60000);
		ChatHandler(player->GetSession()).SendSysMessage("Você sumonou Max Stell, você tem 60 segundos para usa-lo!");
        player->CastSpell(player, 59908);
  		return true;
	}

};

void AddSC_item_spawn_teleporter()
{
	new item_spawn_teleporter();
}