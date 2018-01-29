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

class NDP_NpcMorph : public CreatureScript
{
public:
	NDP_NpcMorph() : CreatureScript("NDP_NpcMorph") { }

	static bool OnGossipHello(Player * player, Creature * creature)
	{
		if (player->IsInCombat())
		{
			CloseGossipMenuFor(player);
			player->GetSession()->SendNotification("Você está em combate!");
			return false;
		}
		
		AddGossipItemFor(player, 10, "|TInterface\\icons\\inv_bannerpvp_02:35:35:-14|tAlliance Morphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		AddGossipItemFor(player, 10, "|TInterface\\icons\\inv_bannerpvp_01:35:35:-14|tHorde Morphs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_boss_kiljaedan:35:35:-14|tBosses Morph", GOSSIP_SENDER_MAIN, 10);
		AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_kickandfrick:35:35:-14|tCreature Morph", GOSSIP_SENDER_MAIN, 11);
		AddGossipItemFor(player, 10, "|TInterface\\icons\\spell_holy_dispelmagic:35:35:-14|t Demorph", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
		//AddGossipItemFor(player, 1, "|cffFF0000|TInterface\\icons\\achievement_reputation_01:35|tNevermind...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		SendGossipMenuFor(player, 1, creature->GetGUID());
		return true;
	}
	static bool OnGossipSelect(Player * player, Creature * creature, uint32 /*sender*/, uint32 actions)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (actions)
		{
			case GOSSIP_ACTION_INFO_DEF + 1: /* Shows the Alliance Morphs menu */
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_human_male:35:35:-14|tHuman Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_human_female:35:35:-14|tHuman Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_dwarf_male:35:35:-14|tDwarf Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_dwarf_female:35:35:-14|tDwarf Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_nightelf_male:35:35:-14|tNightelf Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_nightelf_female:35:35:-14|tNightelf Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_gnome_male:35:35:-14|tGnome Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_gnome_female:35:35:-14|tGnome Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_draenei_male:35:35:-14|tDraenei Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_draenei_female:35:35:-14|tDraenei Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
				AddGossipItemFor(player, 10, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-14|tVoltar", GOSSIP_SENDER_MAIN, 300);
				//AddGossipItemFor(player, 1, "|cffFF0000|TInterface\\icons\\achievement_reputation_01:35|tNevermind...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
				player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
				break;

				/* Alliance Morph List */
			case GOSSIP_ACTION_INFO_DEF + 5: /* Human Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(19723);
				break;

			case GOSSIP_ACTION_INFO_DEF + 6: /* Human Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(19724);
				break;

			case GOSSIP_ACTION_INFO_DEF + 7: /* Dwarf Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20317);
				break;

			case GOSSIP_ACTION_INFO_DEF + 8: /* Dwarf Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(37918);
				break;

			case GOSSIP_ACTION_INFO_DEF + 9: /* Nightelf Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20318);
				break;

			case GOSSIP_ACTION_INFO_DEF + 10:/* Nightelf Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(37919);
				break;

			case GOSSIP_ACTION_INFO_DEF + 11:/* Gnome Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20580);
				break;

			case GOSSIP_ACTION_INFO_DEF + 12:/* Gnome Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20320);
				break;

			case GOSSIP_ACTION_INFO_DEF + 13:/* Draenei Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(37916);
				break;

			case GOSSIP_ACTION_INFO_DEF + 14:/* Draenei Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20323);
				break;

			case GOSSIP_ACTION_INFO_DEF + 2: /* Shows the Horde Morphs menu */
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_orc_male:35:35:-14|tOrc Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_orc_female:35:35:-14|tOrc Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_undead_male:35:35:-14|tUndead Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_undead_female:35:35:-14|tUndead Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_tauren_male:35:35:-14|tTauren Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_tauren_female:35:35:-14|tTauren Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_troll_male:35:35:-14|tTroll Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_troll_female:35:35:-14|tTroll Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_bloodelf_male:35:35:-14|tBloodelf Male", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_bloodelf_female:35:35:-14|tBloodelf Female", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
				AddGossipItemFor(player, 10, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-14|tVoltar", GOSSIP_SENDER_MAIN, 300);
				//AddGossipItemFor(player, 1, "|cffFF0000|TInterface\\icons\\achievement_reputation_01:35|tNevermind...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
				SendGossipMenuFor(player, 1, creature->GetGUID());
				break;
			
				/* Horde Morph List */
			case GOSSIP_ACTION_INFO_DEF + 17:/* Orc Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(37920);
				break;

			case GOSSIP_ACTION_INFO_DEF + 18:/* Orc Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20316);
				break;

			case GOSSIP_ACTION_INFO_DEF + 19:/* Undead Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(37923);
				break;

			case GOSSIP_ACTION_INFO_DEF + 20:/* Undead Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(37924);
				break;

			case GOSSIP_ACTION_INFO_DEF + 21:/* Tauren Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20319);
				break;

			case GOSSIP_ACTION_INFO_DEF + 22:/* Tauren Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20584);
				break;

			case GOSSIP_ACTION_INFO_DEF + 23:/* Troll Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20321);
				break;

			case GOSSIP_ACTION_INFO_DEF + 24:/* Troll Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(37922);
				break;

			case GOSSIP_ACTION_INFO_DEF + 26:/* Bloodelf Female Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20370);
				break;

			case GOSSIP_ACTION_INFO_DEF + 25:/* Bloodelf Male Morph*/
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(20368);
				break;

			case 10:	// BOSSES MORPH
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_leader_ thrall:35:35:-14|tThrall", GOSSIP_SENDER_MAIN, 20);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_leader_prophet_velen:35:35:-14|tLady Sylvanas", GOSSIP_SENDER_MAIN, 21);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_tauren_male:35:35:-14|tCairne Bloodhoof", GOSSIP_SENDER_MAIN, 22);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_leader_lorthemar_theron:35:35:-14|tLorthemar Theron", GOSSIP_SENDER_MAIN, 23);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_leader_king_magni_bronzebeard:35:35:-14|tKing Magni Bronzebeard", GOSSIP_SENDER_MAIN, 24);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_boss_kingymiron_02:35:35:-14|tHighlord Bolvar Fordragon", GOSSIP_SENDER_MAIN, 25);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_character_gnome_male:35:35:-14|tHigh Tinker Mekkatorque", GOSSIP_SENDER_MAIN, 26);
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_leader_sylvanas:35:35:-14|tTyrande Whisperwind", GOSSIP_SENDER_MAIN, 27);
				AddGossipItemFor(player, 10, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-14|tVoltar", GOSSIP_SENDER_MAIN, 300);
				SendGossipMenuFor(player, 1, creature->GetGUID());
				break;

			case 20: // Thrall
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(4527);
				break;

			case 21: //Lady Sylvanas
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(11657);
				break;

			case 22: // Cairne Bloodhoof
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(4307);
				break;

			case 23: // Lor´themar Theron
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(17122);
				break;


			case 24: // King Magni Bronzebeard
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(3597);
				break;


			case 25: // Highlord Bolvar Fordragon
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(5566);
				break;

			case 26: // High Tinker Mekkatorque
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(7006);
				break;

			case 27: // Tyrande Whisperwind
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(7274);
				break;

			case 11:
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_boss_kargathbladefist_01:35:35:-14|tFel Orc", GOSSIP_SENDER_MAIN, 30);	// 21267 
				AddGossipItemFor(player, 10, "|TInterface\\icons\\Achievement_Boss_LichKing:35:35:-14|tLich King", GOSSIP_SENDER_MAIN, 31); // 22235 
				AddGossipItemFor(player, 10, "|TInterface\\icons\\achievement_boss_jedogashadowseeker:35:35:-14|tWarchief", GOSSIP_SENDER_MAIN, 32); // 19799
				AddGossipItemFor(player, 10, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:35:35:-14|tVoltar", GOSSIP_SENDER_MAIN, 300);
				SendGossipMenuFor(player, 1, creature->GetGUID());
				break;

			case 30: // Fel Orc
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(21267);
				break;

			case 31: // Lich King
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(22235);
				break;

			case 32: // Warchief
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->SetDisplayId(19799);
				break;
// -------------------------------------------------------//
			case GOSSIP_ACTION_INFO_DEF + 27: // DEMORPH
				player->PlayerTalkClass->SendCloseGossip();
				player->CastSpell(player, 19484);
				player->DeMorph();
				break;

			case GOSSIP_ACTION_INFO_DEF + 4: 
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case 300:
				OnGossipHello(player, creature);
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

void AddSC_NDP_NpcMorph()
{
	new NDP_NpcMorph;
}
