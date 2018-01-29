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

class transmogriefer : public CreatureScript
{
	public:
		transmogriefer() : CreatureScript("transmogriefer") { }

	static bool OnGossipHello(Player *player, Creature *_creature)
	{
		if (player->IsInCombat())
		{
			CloseGossipMenuFor(player);
			_creature->Whisper("Você está em combate!", LANG_UNIVERSAL, player);
			return true;
		}
		else
		{
			//AddGossipItemFor(player,  10, "Show my Personal Rating (2v2)"                      , GOSSIP_SENDER_MAIN, 9999); 
			if (player->getClass() == CLASS_WARLOCK)
			{
				AddGossipItemFor(player,  4, "Warlock Season 1"                      , GOSSIP_SENDER_MAIN, 100); //S1
				AddGossipItemFor(player,  4, "Warlock Season 2"                      , GOSSIP_SENDER_MAIN, 200); //S2
				AddGossipItemFor(player,  4, "Warlock Season 3"                      , GOSSIP_SENDER_MAIN, 300); //S3
				AddGossipItemFor(player,  4, "Warlock Season 4"                      , GOSSIP_SENDER_MAIN, 400); //S4
				AddGossipItemFor(player,  4, "Warlock Season 5"                      , GOSSIP_SENDER_MAIN, 500); //S5
				AddGossipItemFor(player,  4, "Warlock Tier 2"                        , GOSSIP_SENDER_MAIN, 600);
				AddGossipItemFor(player,  4, "Warlock Tier 3"                        , GOSSIP_SENDER_MAIN, 700);
				AddGossipItemFor(player,  4, "Warlock Tier 4"                        , GOSSIP_SENDER_MAIN, 800);
				AddGossipItemFor(player,  4, "Warlock Tier 5"                        , GOSSIP_SENDER_MAIN, 900);
				AddGossipItemFor(player,  4, "Nemesis Raiment"                       , GOSSIP_SENDER_MAIN, 1009);
			}
			if (player->getClass() == CLASS_WARRIOR)
			{
				AddGossipItemFor(player,  4, "Warrior Season 1"                    , GOSSIP_SENDER_MAIN, 101);
				AddGossipItemFor(player,  4, "Warrior Season 2"                    , GOSSIP_SENDER_MAIN, 201);
				AddGossipItemFor(player,  4, "Warrior Season 3"                    , GOSSIP_SENDER_MAIN, 301);
				AddGossipItemFor(player,  4, "Warrior Season 4"                    , GOSSIP_SENDER_MAIN, 401);
				AddGossipItemFor(player,  4, "Warrior Season 5"                    , GOSSIP_SENDER_MAIN, 501);
				AddGossipItemFor(player,  4, "Warrior Tier 2"                      , GOSSIP_SENDER_MAIN, 601);
				AddGossipItemFor(player,  4, "Warrior Tier 3"                      , GOSSIP_SENDER_MAIN, 701);
				AddGossipItemFor(player,  4, "Warrior Tier 4"                      , GOSSIP_SENDER_MAIN, 801);
				AddGossipItemFor(player,  4, "Warrior Tier 5"                      , GOSSIP_SENDER_MAIN, 901);
				AddGossipItemFor(player,  4, "Hellscream's Battlegear"             , GOSSIP_SENDER_MAIN, 1010);
			}
			if (player->getClass() == CLASS_SHAMAN)
			{
				AddGossipItemFor(player,  4, "Shaman Season 1"                     , GOSSIP_SENDER_MAIN, 106);
				AddGossipItemFor(player,  4, "Shaman Season 2"                     , GOSSIP_SENDER_MAIN, 206);
				AddGossipItemFor(player,  4, "Shaman Season 3"                     , GOSSIP_SENDER_MAIN, 306);
				AddGossipItemFor(player,  4, "Shaman Season 4"                     , GOSSIP_SENDER_MAIN, 406);
				AddGossipItemFor(player,  4, "Shaman Season 5"                     , GOSSIP_SENDER_MAIN, 506);
				AddGossipItemFor(player,  4, "Shaman Tier 2"                       , GOSSIP_SENDER_MAIN, 606);
				AddGossipItemFor(player,  4, "Shaman Tier 3"                       , GOSSIP_SENDER_MAIN, 706);
				AddGossipItemFor(player,  4, "Shaman Tier 4"                       , GOSSIP_SENDER_MAIN, 806);
				AddGossipItemFor(player,  4, "Shaman Tier 5"                       , GOSSIP_SENDER_MAIN, 906);
				AddGossipItemFor(player,  4, "Conqueror's Worldbreaker Battlegear" , GOSSIP_SENDER_MAIN, 1008);
			}
			if (player->getClass() == CLASS_PALADIN)
			{
				AddGossipItemFor(player,  4, "Paladin Season 1"                      , GOSSIP_SENDER_MAIN, 103);
				AddGossipItemFor(player,  4, "Paladin Season 2"                      , GOSSIP_SENDER_MAIN, 203);
				AddGossipItemFor(player,  4, "Paladin Season 3"                      , GOSSIP_SENDER_MAIN, 303);
				AddGossipItemFor(player,  4, "Paladin Season 4"                      , GOSSIP_SENDER_MAIN, 403);
				AddGossipItemFor(player,  4, "Paladin Season 5"                      , GOSSIP_SENDER_MAIN, 503);
				AddGossipItemFor(player,  4, "Paladin Tier 2"                        , GOSSIP_SENDER_MAIN, 603);
				AddGossipItemFor(player,  4, "Paladin Tier 3"                        , GOSSIP_SENDER_MAIN, 703);
				AddGossipItemFor(player,  4, "Paladin Tier 4"                        , GOSSIP_SENDER_MAIN, 803);
				AddGossipItemFor(player,  4, "Paladin Tier 5"                        , GOSSIP_SENDER_MAIN, 903);
				AddGossipItemFor(player,  4, "Liadrin's Battlegear"                  , GOSSIP_SENDER_MAIN, 1005);
			}
			if (player->getClass() == CLASS_MAGE)
			{
				AddGossipItemFor(player,  4, "Mage Season 1"                    , GOSSIP_SENDER_MAIN, 104);
				AddGossipItemFor(player,  4, "Mage Season 2"                    , GOSSIP_SENDER_MAIN, 204);
				AddGossipItemFor(player,  4, "Mage Season 3"                    , GOSSIP_SENDER_MAIN, 304);
				AddGossipItemFor(player,  4, "Mage Season 4"                    , GOSSIP_SENDER_MAIN, 404);
				AddGossipItemFor(player,  4, "Mage Season 5"                    , GOSSIP_SENDER_MAIN, 504);
				AddGossipItemFor(player,  4, "Mage Tier 2"                      , GOSSIP_SENDER_MAIN, 604);
				AddGossipItemFor(player,  4, "Mage Tier 3"                      , GOSSIP_SENDER_MAIN, 704);
				AddGossipItemFor(player,  4, "Mage Tier 4"                      , GOSSIP_SENDER_MAIN, 804);
				AddGossipItemFor(player,  4, "Mage Tier 5"                      , GOSSIP_SENDER_MAIN, 904);
				AddGossipItemFor(player,  4, "Netherwind Regalia"               , GOSSIP_SENDER_MAIN, 1004);
			}
			if (player->getClass() == CLASS_ROGUE)
			{
				AddGossipItemFor(player,  4, "Rogue Season 1"                      , GOSSIP_SENDER_MAIN, 105);
				AddGossipItemFor(player,  4, "Rogue Season 2"                      , GOSSIP_SENDER_MAIN, 205);
				AddGossipItemFor(player,  4, "Rogue Season 3"                      , GOSSIP_SENDER_MAIN, 305);
				AddGossipItemFor(player,  4, "Rogue Season 4"                      , GOSSIP_SENDER_MAIN, 405);
				AddGossipItemFor(player,  4, "Rogue Season 5"                      , GOSSIP_SENDER_MAIN, 505);
				AddGossipItemFor(player,  4, "Rogue Tier 2"                        , GOSSIP_SENDER_MAIN, 605);
				AddGossipItemFor(player,  4, "Rogue Tier 3"                        , GOSSIP_SENDER_MAIN, 705);
				AddGossipItemFor(player,  4, "Rogue Tier 4"                        , GOSSIP_SENDER_MAIN, 805);
				AddGossipItemFor(player,  4, "Rogue Tier 5"                        , GOSSIP_SENDER_MAIN, 905);
				AddGossipItemFor(player,  4, "Garona's Battlegear"                 , GOSSIP_SENDER_MAIN, 1007);
			}
			if (player->getClass() == CLASS_DRUID)
			{
				AddGossipItemFor(player,  4, "Druid Season 1"                      , GOSSIP_SENDER_MAIN, 107);
				AddGossipItemFor(player,  4, "Druid Season 2"                      , GOSSIP_SENDER_MAIN, 207);
				AddGossipItemFor(player,  4, "Druid Season 3"                      , GOSSIP_SENDER_MAIN, 307);
				AddGossipItemFor(player,  4, "Druid Season 4"                      , GOSSIP_SENDER_MAIN, 407);
				AddGossipItemFor(player,  4, "Druid Season 5"                      , GOSSIP_SENDER_MAIN, 507);
				AddGossipItemFor(player,  4, "Druid Tier 2"                        , GOSSIP_SENDER_MAIN, 607);
				AddGossipItemFor(player,  4, "Druid Tier 3"                        , GOSSIP_SENDER_MAIN, 707);
				AddGossipItemFor(player,  4, "Druid Tier 4"                        , GOSSIP_SENDER_MAIN, 807);
				AddGossipItemFor(player,  4, "Druid Tier 5"                        , GOSSIP_SENDER_MAIN, 907);
				AddGossipItemFor(player,  4, "Choking Winter's Garb"               , GOSSIP_SENDER_MAIN, 1002);
			}
			if (player->getClass() == CLASS_PRIEST)
			{
				AddGossipItemFor(player,  4, "Priest Season 1"                      , GOSSIP_SENDER_MAIN, 102);
				AddGossipItemFor(player,  4, "Priest Season 2"                      , GOSSIP_SENDER_MAIN, 202);
				AddGossipItemFor(player,  4, "Priest Season 3"                      , GOSSIP_SENDER_MAIN, 302);
				AddGossipItemFor(player,  4, "Priest Season 4"                      , GOSSIP_SENDER_MAIN, 402);
				AddGossipItemFor(player,  4, "Priest Season 5"                      , GOSSIP_SENDER_MAIN, 502);
				AddGossipItemFor(player,  4, "Priest Tier 2"                        , GOSSIP_SENDER_MAIN, 602);
				AddGossipItemFor(player,  4, "Priest Tier 3"                        , GOSSIP_SENDER_MAIN, 702);
				AddGossipItemFor(player,  4, "Priest Tier 4"                        , GOSSIP_SENDER_MAIN, 802);
				AddGossipItemFor(player,  4, "Priest Tier 5"                        , GOSSIP_SENDER_MAIN, 902);
				AddGossipItemFor(player,  4, "Kirin Tor Garb"                       , GOSSIP_SENDER_MAIN, 1006);
			}
			if (player->getClass() == CLASS_HUNTER)
			{
				AddGossipItemFor(player,  4, "Hunter Season 1"                      , GOSSIP_SENDER_MAIN, 108);
				AddGossipItemFor(player,  4, "Hunter Season 2"                      , GOSSIP_SENDER_MAIN, 208);
				AddGossipItemFor(player,  4, "Hunter Season 3"                      , GOSSIP_SENDER_MAIN, 308);
				AddGossipItemFor(player,  4, "Hunter Season 4"                      , GOSSIP_SENDER_MAIN, 408);
				AddGossipItemFor(player,  4, "Hunter Season 5"                      , GOSSIP_SENDER_MAIN, 508);
				AddGossipItemFor(player,  4, "Hunter Tier 2"                        , GOSSIP_SENDER_MAIN, 608);
				AddGossipItemFor(player,  4, "Hunter Tier 3"                        , GOSSIP_SENDER_MAIN, 708);
				AddGossipItemFor(player,  4, "Hunter Tier 4"                        , GOSSIP_SENDER_MAIN, 808);
				AddGossipItemFor(player,  4, "Hunter Tier 5"                        , GOSSIP_SENDER_MAIN, 908);
				AddGossipItemFor(player,  4, "Beast Lord Armor"                     , GOSSIP_SENDER_MAIN, 1003);
			}
			if (player->getClass() == CLASS_DEATH_KNIGHT)
			{
				AddGossipItemFor(player,  4, "DK Season 1"                    , GOSSIP_SENDER_MAIN, 101);
				AddGossipItemFor(player,  4, "DK Season 2"                    , GOSSIP_SENDER_MAIN, 201);
				AddGossipItemFor(player,  4, "DK Season 3"                    , GOSSIP_SENDER_MAIN, 301);
				AddGossipItemFor(player,  4, "DK Season 4"                    , GOSSIP_SENDER_MAIN, 401);
				AddGossipItemFor(player,  4, "DK Season 5"                    , GOSSIP_SENDER_MAIN, 501);
				AddGossipItemFor(player,  4, "DK Tier 2"                      , GOSSIP_SENDER_MAIN, 601);
				AddGossipItemFor(player,  4, "DK Tier 3"                      , GOSSIP_SENDER_MAIN, 701);
				AddGossipItemFor(player,  4, "DK Tier 4"                      , GOSSIP_SENDER_MAIN, 801);
				AddGossipItemFor(player,  4, "DK Tier 5"                      , GOSSIP_SENDER_MAIN, 901);
				AddGossipItemFor(player,  4, "Heroes Scourgeborne Battlegear"           , GOSSIP_SENDER_MAIN, 1000);
				AddGossipItemFor(player,  4, "Darkruned Battlegear"                     , GOSSIP_SENDER_MAIN, 1001);
			}
		}

		SendGossipMenuFor(player, 60001, _creature->GetGUID());         
		return true;
	}

	static bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
	{
		// criteria 451 - max personal 2v2 rate
		// criteria 330 - max personal 3v3 rate // Not used for now

		QueryResult select = CharacterDatabase.PQuery("SELECT counter FROM character_achievement_progress WHERE criteria = '451' AND guid = '%u'", player->GetGUID());

		if (!select)
		{
			player->GetSession()->SendAreaTriggerMessage("Você precisa alcançar 1750 personal rating em 2vs2 para usar isso.");
			CloseGossipMenuFor(player);
			return false;
		}

		Field* fields = select->Fetch();
		uint32 personalRating = fields[0].GetUInt32(); // counter

		// Min achievement of 1750 rating (2v2) to use this feature
		if (personalRating <= 1750)
		{
			player->GetSession()->SendAreaTriggerMessage("Você precisa alcançar 1750 personal rating em 2vs2 para usar isso.");
			CloseGossipMenuFor(player);
			return false;
		}

		if (sender == GOSSIP_SENDER_MAIN)
		{
			player->PlayerTalkClass->ClearMenus();

			switch(uiAction)
			{
			case 999:
				CloseGossipMenuFor(player);
				_creature->Whisper("Venha novamente, amigo!", LANG_UNIVERSAL, player);
				break;

			case 100: //Season 1 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 24553); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 24554); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 24552); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 24555); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 24556); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 101://Season 1 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 24545); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 24546); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 24544); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 24547); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 24549); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 102://Season 1 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 27708); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 27710); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 27711); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 27709); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 27707); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 103://Season 1 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 27704); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 27706); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 27702); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 27705); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 27703); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 104://Season 1 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 25855); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 25854); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 25856); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 25858); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 25857); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 105://Season 1 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 25830); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 25832); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 25831); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 25833); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 25834); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 106://Season 1 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 25998); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 25999); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 25997); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 26001); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 26000); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 107://Season 1 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 31376); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 31378); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 31379); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 28443); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 31377); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 28444); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 31375); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 108://Season 1 Hunter
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 28331); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 28333); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 28334); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 28332); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 28335); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

				// Arena Season 2

			case 200://Season 2 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 31974); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 31976); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 31977); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 31975); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 31973); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 201://Season 2 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30488); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30490); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30486); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30489); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30487); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 202://Season 2 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 32016); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 32018); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 32019); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 32017); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 32015); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 203://Season 2 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 31997); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 31996); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 31992); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 31995); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 31993); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 204://Season 2 Mage 
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 32048); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 32047); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 32050); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 32051); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 32049); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 205://Season 2 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 31999); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 32001); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 32002); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 32000); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 31998); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 206://Season 2 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 32006); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 32008); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 32004); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 32007); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 32005); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 207://Season 2 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 31998); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 31990); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 31991); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 31989); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 31987); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 208://Season 2 Hunter
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 31962); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 31964); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 31960); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 31963); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 31961); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

				// Arena Season 3

			case 300://Season 3 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33677); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33679); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33680); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33678); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33676); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 301://Season 3 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33730); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33732); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33728); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33731); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33729); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 302://Season 3 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33718); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33720); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33721); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33719); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33717); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 303://Season 3 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33697); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33699); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33695); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33698); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33696); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 304://Season 3 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33758); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33757); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33760); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33761); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33759); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 305://Season 3 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33701); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33703); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33704); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33702); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33700); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 306://Season 3 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33708); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33710); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33706); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33709); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33707); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 307://Season 3 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33691); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33693); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33694); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33692); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33690); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 308://Season 3 Hunter	
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 33666); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 33668); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 33664); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 33667); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 33665); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

				// Arena Season 4

			case 400: // Season 4 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35010); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35009); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35012); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35013); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35011); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35138); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 401: // Season 4 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35068); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35070); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35066); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35069); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35067); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35146); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 402: // Season 4 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35084); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35086); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35087); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35085); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35083); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35144); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 403: // Season 4 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35090); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35092); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35088); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35091); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35089); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35148); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 404: // Season 4 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35097); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35096); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35099); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35100); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35098); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35149); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 405: // Season 4 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35033); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35035); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35036); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35034); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35032); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35141); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 406: // Season 4 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35079); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35081); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35077); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35080); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35078); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35147); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 407: // Season 4 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 35112); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 35114); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 35115); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 35113); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 35111); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35150); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 408: // Season 4 Hunter
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 34992); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 34994); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 34990); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 34993); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 34991); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 35136); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

				// Arena Season 5

			case 500: // Season 5 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 41992); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 42010); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 41997); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 42004); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 42016); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 501: // Season 5 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 40823); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 40862); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 40786); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 40844); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 40804); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 502: // Season 5 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 41853); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 41868); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 41858); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 41863); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 41873); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 503: // Season 5 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 40825); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 40864); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 40785); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 40846); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 40805); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 504: // Season 5 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 41945); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 41964); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 41951); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 41958); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 41970); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 505: // Season 5 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 41671); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 41682); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 41649); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 41654); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 41766); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 506: // Season 5 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 41150); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 41210); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 41080); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 41198); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 41136); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 507: // Season 5 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 41677); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 41714); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 41660); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 41666); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 41772); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 508: // Season 5 Hunter
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 41156); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 41216); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 41086); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 41204); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 41142); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 600://tier 2 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16929); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16932); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16931); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16930); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16928); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16927); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 601://tier 2 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16963); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16961); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16966); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16964); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16964); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16965); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 602://tier 2 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16921); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16924); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16923); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16922); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16920); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16919); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 603://tier 2 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16955); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16953); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16958); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16954); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16956); // gloves	
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16957); // Boots		  
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 604://tier 2 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16914); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16917); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16916); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16915); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16913); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16912); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 605://tier 2 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16908); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16832); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16905); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16909); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16907); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16906); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 606://tier 2 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16947); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16945); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16950); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16946); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16948); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16949); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 607://Tier 2 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16900); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16902); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16897); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16901); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16899); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16898); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 608://Tier 2 Hunter
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16900); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16902); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16897); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16901); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16899); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16898); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 700://tier 3 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22506); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22507); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22504); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22505); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22509); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22508); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 701://tier 3 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22418); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22419); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22416); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22417); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22421); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22420); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 702://tier 3 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22514); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22515); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22512); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22513); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22517); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22516); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 703://tier 3 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22428); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22429); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22425); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22427); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22426); // gloves	
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22430); // Boots		  
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 704://tier 3 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22498); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22499); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22496); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22497); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22501); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22500); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 705://tier 3 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22478); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22479); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22476); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22477); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22481); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22480); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 706://tier 3 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22466); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22467); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22464); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22465); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22469); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22468); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 707://Tier 3 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22490); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22491); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22488); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22489); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22493); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22492); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 708://Tier 3 Hunter -- trqbva vqrni idta
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 22490); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 22491); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 22488); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 22489); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 22493); // gloves
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 22492); // Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 800://tier 4 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 28963); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 28967); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 28964); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 28966); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 28968); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 801://tier 4 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 29021); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 29023); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 29019); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 29022); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 29020); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 802://tier 4 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 29049); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 29054); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 29050); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 29053); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 29055); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 803://tier 4 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 29073); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 29075); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 29071); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 29074); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 29072); // gloves		  
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 804://tier 4 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 29076); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 29079); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 29077); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 29078); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 29080); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 805://tier 4 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16908); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16832); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16905); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16909); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16907); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 806://tier 4 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 29035); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 29037); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 29033); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 29036); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 29034); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 807://Tier 4 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 29086); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 29089); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 29087); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 28655); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 29088); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 28752); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 29090); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 808://Tier 4 hunter -- trqq prepravqne
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 29081); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 29084); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 29082); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 29083); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 29085); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 900://tier 5 Warlock
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30115); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30215); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30113); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30213); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30211); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 901://tier 5 Warrior
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30115); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30122); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30113); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30116); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30114); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 902://tier 5 Priest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30152); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30154); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30150); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30153); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30151); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 903://tier 5 Paladin
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30131); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30133); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30129); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30132); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30130); // gloves		  
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 904://tier 5 Mage
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30206); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30210); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30196); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30207); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30205); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 905://tier 5 Rogue
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30146); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30149); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30144); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30148); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30145); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 906://tier 5 Shaman
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30190); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30194); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30185); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30192); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30189); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 907://Tier 5 Druid
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30228); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30230); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30222); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30229); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30223); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 908://Tier 5 Druid -- trqq prepravqne
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 30228); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 30230); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 30222); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 30229); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 30223); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1000://Heroes Scourgeborne Battlegear
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 39619); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 39621); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 39617); // chest		  
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 39620); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 39618); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1001://Darkruned Battlegear
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 45472); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 45320); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 45225); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 45241); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 45248); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 45599); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 45481); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1002://Choking Winter's Garb
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 50206); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 50293); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 50300); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 50269); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 50308); //Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1003://Beast Lord Armor
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 28275); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 27801); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 28228); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 29261); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 27874); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 29262); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 27474); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1004://Netherwind Regalia
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 16914); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 16917); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 16916); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 16818); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 16915); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 16912); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 16913); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1005://Liadrin's Battlegear
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 47682); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 47699); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 47471); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 47484); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 47440); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 47424); //Boots
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1006://Kirin Tor Garb
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 45464); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 46344); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 45865); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 45306); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 45894); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 46030); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 46045); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1007://Garona's Battlegear
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 48245); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 48247); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 48243); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 47460); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 48246); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 47445); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 48244); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1008://Conqueror's Worldbreaker Battlegear
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 46201); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 46203); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 46198); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 46202); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 46199); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1009://Nemesis Raiment 
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 27781); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 27994); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 27799); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 27795); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 28338); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 27821); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 27493); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

			case 1010:// Hellscream Battlegear
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID, 47678); // helm
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_3_ENTRYID, 48016); // shoulder
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_5_ENTRYID, 47415); // chest
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_6_ENTRYID, 47444); //Belt
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_7_ENTRYID, 47434); // pants
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_8_ENTRYID, 47473); //Boots
				player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_10_ENTRYID, 47492); // gloves
				CloseGossipMenuFor(player);
				player->GetSession()->SendAreaTriggerMessage("Seus items foram modificados com sucesso.");
				break;

				case 9999: // Show my personal rating
				          player->GetSession()->SendAreaTriggerMessage("Seu Personal Rating: %u", personalRating);
				          CloseGossipMenuFor(player);
				         break;
			default:
				break;                   
			}
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

void AddSC_transmogriefer()
{
    new transmogriefer();
}