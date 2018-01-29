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

#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "ScriptedGossip.h"
#include "GossipDef.h"
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

class VIP_NPC : public CreatureScript 
{
    public:
		VIP_NPC() : CreatureScript("VIP_NPC") { }
     
    static bool OnGossipHello(Player * me, Creature * pCreature)
    {
		if (me->GetSession()->GetSecurity() >= 1)
			AddGossipItemFor(me, 6, "Vendedor V.I.P", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
		else
			AddGossipItemFor(me, 6, "Até Mais", GOSSIP_SENDER_MAIN,1);

        me->PlayerTalkClass->SendGossipMenu(9452, pCreature->GetGUID());
        return true;
    }
           
    static bool OnGossipSelect(Player *player, Creature * m_creature, uint32 /*sender*/, uint32 action)
	{
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
			case GOSSIP_OPTION_VENDOR:
				player->GetSession()->SendListInventory(m_creature->GetGUID());
				break;
			case 1:
				//m_creature->MonsterSay("Por que você está aqui? Você não é um Personagem VIP! Volte já para Dalaran!", player->GetGUID());
				player->TeleportTo(0, -1818.969971f, -4149.790039f, 31.984400f, 3.091680f); // Where you get teleported.
				CloseGossipMenuFor(player);
				break;
		}
        return true;
    }
    struct MyAI : public ScriptedAI
    {
        MyAI(Creature* creature) : ScriptedAI(creature) { }
        bool GossipHello(Player* player) override
        {
            return OnGossipHello(player, me);
        }
        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            return OnGossipSelect(player, me, sender, action);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new MyAI(creature);
    }
 
};
 
void AddSC_VIP_NPC()
{
    new VIP_NPC();
}