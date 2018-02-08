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

/*Class E_Menu*/
#define E_Warrior "Ver os top 5 Warriors com mais mortes"
#define E_Paladin "Ver os top 5 Paladins com mais mortes"
#define E_Hunter "Ver os top 5 Hunters com mais mortes"
#define E_Rogue "Ver os top 5 Rogues com mais mortes"
#define E_Priest "Ver os top 5 Priests com mais mortes"
#define E_Shaman "Ver os top 5 Shamans com mais mortes"
#define E_Mage "Ver os top 5 Mages com mais mortes"
#define E_Warlock "Ver os top 5 Warlocks com mais mortes"
#define E_Druid "Ver os top 5 Druids com mais mortes"
#define E_Death_knight "Ver os top 5 Death knights com mais mortes"
/*Top 5 Message*/
#define M_Warrior "Aqui estão os 5 Warriors com mais mortes"
#define M_Paladin "Aqui estão os 5 Paladins com mais mortes"
#define M_Hunter "Aqui estão os 5 Hunters com mais mortes"
#define M_Rogue "Aqui estão os 5 Rogues com mais mortes"
#define M_Priest "Aqui estão os 5 Priests com mais mortes"
#define M_Shaman "Aqui estão os 5 Shamans com mais mortes"
#define M_Mage "Aqui estão os 5 Mages com mais mortes"
#define M_Warlock "Aqui estão os 5 Warlocks com mais mortes"
#define M_Druid "Aqui estão os 5 Druids com mais mortes"
#define M_Death_knight "Aqui estão os 5 Death knights com mais mortes"

class Top5_Killers : public CreatureScript
{
	public:
		Top5_Killers() : CreatureScript("Top5_Killers") { }

    static bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, 1, E_Warrior, GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, 1, E_Paladin, GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, 1, E_Hunter, GOSSIP_SENDER_MAIN, 3);
        AddGossipItemFor(player, 1, E_Rogue, GOSSIP_SENDER_MAIN, 4);
        AddGossipItemFor(player, 1, E_Priest, GOSSIP_SENDER_MAIN, 5);
        AddGossipItemFor(player, 1, E_Shaman, GOSSIP_SENDER_MAIN, 7);
        AddGossipItemFor(player, 1, E_Mage, GOSSIP_SENDER_MAIN, 8);
        AddGossipItemFor(player, 1, E_Warlock, GOSSIP_SENDER_MAIN, 9);
        AddGossipItemFor(player, 1, E_Druid, GOSSIP_SENDER_MAIN, 11);
        AddGossipItemFor(player, 1, E_Death_knight, GOSSIP_SENDER_MAIN, 6);
        SendGossipMenuFor(player, 1, creature->GetGUID());
        return true;
    }

    static bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (sender != GOSSIP_SENDER_MAIN)
            return true; // wrong sender, something fisy

        switch(action)
        {
			case 1: ChatHandler(player->GetSession()).PSendSysMessage(M_Warrior);       break;
			case 2: ChatHandler(player->GetSession()).PSendSysMessage(M_Paladin);       break;
			case 3: ChatHandler(player->GetSession()).PSendSysMessage(M_Hunter);        break;
			case 4: ChatHandler(player->GetSession()).PSendSysMessage(M_Rogue);         break;
			case 5: ChatHandler(player->GetSession()).PSendSysMessage(M_Priest);        break;
			case 6: ChatHandler(player->GetSession()).PSendSysMessage(M_Death_knight);  break;
			case 7: ChatHandler(player->GetSession()).PSendSysMessage(M_Shaman);        break;
			case 8: ChatHandler(player->GetSession()).PSendSysMessage(M_Mage);          break;
			case 9: ChatHandler(player->GetSession()).PSendSysMessage(M_Warlock);       break;
			case 11: ChatHandler(player->GetSession()).PSendSysMessage(M_Druid);        break;
			default: return true; // invalid class, something fishy
        }

        QueryResult result = CharacterDatabase.PQuery("SELECT name, totalKills FROM characters WHERE class = %u ORDER BY totalKills DESC LIMIT 5", action);
        if(result)
        {
            do
            {
                Field * fields = result->Fetch();
                std::string name = fields[0].GetString();
                uint32 totalKills = fields[1].GetUInt32();
                ChatHandler(player->GetSession()).PSendSysMessage("Nome: %s, com as %u Mortes", name.c_str(), totalKills);
            } 
            while(result->NextRow());
        }
        OnGossipHello(player, creature); // return to main menu
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

void AddSC_Top5_Killers()
{
    new Top5_Killers();
}