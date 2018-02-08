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
#include "Player.h"
#include "Group.h"
#include "ObjectAccessor.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"

class item_res_group : public ItemScript
{
public:
	item_res_group() : ItemScript("item_res_group") { }

	bool DistanceIsValid(Position* playerWhoUsesTheItem, Position* deadPlayersInGroup)
	{
		if (std::abs(deadPlayersInGroup->GetPositionX() - playerWhoUsesTheItem->GetPositionX()) <= 91.44) //91.44 meters = 100 yards
			return true;
		return false;
	}

	bool OnUse(Player* playerWhoUsesTheItem, Item* /*item*/, SpellCastTargets const& /*targets*/)
	{
		Group* group = playerWhoUsesTheItem->GetGroup();
		Group::MemberSlotList const &members = group->GetMemberSlots();

		if (playerWhoUsesTheItem->HasAura(38910)) //Fel Weakness 
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("Você deve esperar 15 minutos, a fim de usar este item novamente");
			return false;
		}

		if (!playerWhoUsesTheItem->GetGroup())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("Você não esta em Raid ou Party!");
			return false;
		}
		/* //What if the leader is dead?
		if (playerWhoUsesTheItem->GetGroup()->GetLeaderGUID() != playerWhoUsesTheItem->GetGUID())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("You are not the group leader!");
			return false;
		}
		*/
		if (playerWhoUsesTheItem->InBattleground())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("Você não pode usar este item em Battleground!");
			return false;
		}

		if (playerWhoUsesTheItem->InArena())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("Você não pode usar este item em Arena!");
			return false;
		}

		if (playerWhoUsesTheItem->IsInCombat())
		{
			playerWhoUsesTheItem->GetSession()->SendNotification("Você não pode usar este item em Combate!");
			return false;
		}
		
		else
		{
			for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
			{
				//Group::MemberSlot const& slot = *itr;
				Player* deadPlayersInGroup = ObjectAccessor::FindPlayer((*itr).guid);

				//skip if player/s is/are offline //--This check is mandatory. the server will crash without it
				if (!deadPlayersInGroup || deadPlayersInGroup->GetSession()->PlayerDisconnected())
				{
					CloseGossipMenuFor(playerWhoUsesTheItem);
				}

				if (deadPlayersInGroup && deadPlayersInGroup->GetSession() && deadPlayersInGroup->isDead() && playerWhoUsesTheItem->GetSession() && DistanceIsValid(playerWhoUsesTheItem, deadPlayersInGroup))
				{
					deadPlayersInGroup->ResurrectPlayer(0.75f, false); //75% hp and mana, don't apply Resurrection Sickness
					deadPlayersInGroup->CastSpell(deadPlayersInGroup, 48171, true); //Visual Spell Resurrect (priest)
					deadPlayersInGroup->DurabilityRepairAll(0, 0, false); //Repair All - upon resurrection
					playerWhoUsesTheItem->CastSpell(playerWhoUsesTheItem, 38910, true); //Fel Weakness //Cast a debuff on player To prevent the item being used over and over again	
				}
			}
		}
		return true;
	}
};

void AddSC_item_res_group()
{
	new item_res_group;
}