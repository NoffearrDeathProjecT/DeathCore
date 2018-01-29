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

/* -- NPC SQL EXAMPLE
 *
 * DEVELOPED BY: Natureknight
 * UPDATE BY: Noffearr
 *
 * REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`)
 * VALUES('700010','0','0','0','0','0','736','0','0','0','Weapons Transmog NPC','BattleArenas','','0','80','80','1','35','35','1','1','1.14286','2','0','5000','5000','0','35000','10','1','0','1','512','0','0','0','0','0','0','10000','10000','68','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','20','20','20','0','0','0','0','0','0','0','0','255','0','0','0','weptransmog','0');
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

class weptransmog : public CreatureScript
{
	public:
		weptransmog() : CreatureScript("weptransmog") { }

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
			if (player->getClass() == CLASS_ROGUE)  
			{
				AddGossipItemFor(player,  3, "|cff3300FFWarglaive of Azzinoth (Combat, Sublety)"     , GOSSIP_SENDER_MAIN, 100);
				AddGossipItemFor(player,  3, "|cff3300FFWarblade of the Hakkari (Combat, Sublety)"   , GOSSIP_SENDER_MAIN, 101);
				AddGossipItemFor(player,  3, "|cff3300FFGutgore Ripper (Assasin, Sublety)"           , GOSSIP_SENDER_MAIN, 102);
				AddGossipItemFor(player,  3, "|cff3300FFFist of Molten Fury (Combat, Sublety)"       , GOSSIP_SENDER_MAIN, 103);
				AddGossipItemFor(player,  3, "|cff3300FFThunderfury (Combat, Sublety)"               , GOSSIP_SENDER_MAIN, 104);
				AddGossipItemFor(player,  3, "|cff3300FFJaded Crystal Dagger (All Spec)"             , GOSSIP_SENDER_MAIN, 113);
				AddGossipItemFor(player,  3, "|cff3300FFStarshard Edge (All Spec)"                   , GOSSIP_SENDER_MAIN, 117);
			}
			if (player->getClass() == CLASS_PALADIN) 
			{
				AddGossipItemFor(player,  3, "|cff3300FFIce Spire Scepter (Holy)"                     , GOSSIP_SENDER_MAIN, 105);
                AddGossipItemFor(player,  3, "|cff3300FFVal'anyr, Hammer of Ancient Kings (Holy)"     , GOSSIP_SENDER_MAIN, 106);
                AddGossipItemFor(player,  3, "|cff3300FFZin'rokh, Destroyer of Worlds (Retri)"        , GOSSIP_SENDER_MAIN, 107);
                AddGossipItemFor(player,  3, "|cff3300FFHigh Warlord's Greatsword (Retri)"            , GOSSIP_SENDER_MAIN, 108);
                AddGossipItemFor(player,  3, "|cff3300FFGrand Marshal's Claymore (Retri)"             , GOSSIP_SENDER_MAIN, 109);
                AddGossipItemFor(player,  3, "|cff3300FFSulfuras, Hand of Ragnaros (Retri)"           , GOSSIP_SENDER_MAIN, 110);
                AddGossipItemFor(player,  3, "|cff3300FFWarglaive of Azzinoth (Prot)"                 , GOSSIP_SENDER_MAIN, 100);	
                AddGossipItemFor(player,  3, "|cff3300FFThunderfury (Prot)"                           , GOSSIP_SENDER_MAIN, 104);				
			}
			if (player->getClass() == CLASS_WARRIOR) 
			{
                AddGossipItemFor(player,  3, "|cff3300FFZin'rokh, Destroyer of Worlds(Arms/Fury)"        , GOSSIP_SENDER_MAIN, 107);
                AddGossipItemFor(player,  3, "|cff3300FFHigh Warlord's Greatsword(Arms/Fury)"            , GOSSIP_SENDER_MAIN, 108);
                AddGossipItemFor(player,  3, "|cff3300FFGrand Marshal's Claymore(Arms/Fury)"             , GOSSIP_SENDER_MAIN, 109);
                AddGossipItemFor(player,  3, "|cff3300FFSulfuras, Hand of Ragnaros(Arms/Fury)"           , GOSSIP_SENDER_MAIN, 110);	
                AddGossipItemFor(player,  3, "|cff3300FFAshbringer(Arms/Fury)"                           , GOSSIP_SENDER_MAIN, 111);	
                AddGossipItemFor(player,  3, "|cff3300FFDraconic Avenger(Arms/Fury)"                     , GOSSIP_SENDER_MAIN, 112);
                AddGossipItemFor(player,  3, "|cff3300FFWarglaive of Azzinoth (Prot)"                    , GOSSIP_SENDER_MAIN, 100);	
                AddGossipItemFor(player,  3, "|cff3300FFThunderfury (Prot)"                              , GOSSIP_SENDER_MAIN, 104);				
			}
			if (player->getClass() == CLASS_DEATH_KNIGHT) 
			{
				AddGossipItemFor(player,  3, "|cff3300FFZin'rokh, Destroyer of Worlds (Blood/Unholy)"        , GOSSIP_SENDER_MAIN, 107);
                AddGossipItemFor(player,  3, "|cff3300FFHigh Warlord's Greatsword (Blood/Unholy)"            , GOSSIP_SENDER_MAIN, 108);
                AddGossipItemFor(player,  3, "|cff3300FFGrand Marshal's Claymore (Blood/Unholy)"             , GOSSIP_SENDER_MAIN, 109);
                AddGossipItemFor(player,  3, "|cff3300FFSulfuras, Hand of Ragnaros (Blood/Unholy)"           , GOSSIP_SENDER_MAIN, 110);	
                AddGossipItemFor(player,  3, "|cff3300FFAshbringer (Blood/Unholy)"                           , GOSSIP_SENDER_MAIN, 111);	
                AddGossipItemFor(player,  3, "|cff3300FFDraconic Avenger (Blood/Unholy)"                     , GOSSIP_SENDER_MAIN, 112);
                AddGossipItemFor(player,  3, "|cff3300FFWarglaive of Azzinoth (Frost)"                       , GOSSIP_SENDER_MAIN, 100);
                AddGossipItemFor(player,  3, "|cff3300FFThunderfury (Frost)"                                 , GOSSIP_SENDER_MAIN, 104);				
			}
			if (player->getClass() == CLASS_HUNTER) 
			{
				AddGossipItemFor(player,  3, "|cff3300FFSulfuras, Hand of Ragnaros (All Spec)"           , GOSSIP_SENDER_MAIN, 110);
                AddGossipItemFor(player,  3, "|cff3300FFWarglaive of Azzinoth (All Spec)"               , GOSSIP_SENDER_MAIN, 100);
                AddGossipItemFor(player,  3, "|cff3300FFThunderfury (All Spec)"                         , GOSSIP_SENDER_MAIN, 104);
                AddGossipItemFor(player,  3, "|cff3300FFGolden Bow of Quel'Thalas (Bow)"                , GOSSIP_SENDER_MAIN, 114);
                AddGossipItemFor(player,  3, "|cff3300FFArcanite Steam-Pistol (Gun)"                    , GOSSIP_SENDER_MAIN, 115);	
                AddGossipItemFor(player,  3, "|cff3300FFLegionkiller (Crossbow)"                        , GOSSIP_SENDER_MAIN, 116);
				AddGossipItemFor(player,  3, "|cff3300FFHalberd of Smiting (All Spec)"                  , GOSSIP_SENDER_MAIN, 120);
			}
			if (player->getClass() == CLASS_PRIEST) 
			{
				AddGossipItemFor(player,  3, "|cff3300FFJaded Crystal Dagger (All Spec)"                 , GOSSIP_SENDER_MAIN, 113);
                AddGossipItemFor(player,  3, "|cff3300FFStarshard Edge (All Spec)"                       , GOSSIP_SENDER_MAIN, 117);
                AddGossipItemFor(player,  3, "|cff3300FFVal'anyr, Hammer of Ancient Kings (All Spec)"    , GOSSIP_SENDER_MAIN, 106);
				AddGossipItemFor(player,  3, "|cff3300FFWarblade of the Hakkari (All Spec)"              , GOSSIP_SENDER_MAIN, 119);
				AddGossipItemFor(player,  3, "|cff3300FFRoyal Scepter of Terenas (All Spec)"             , GOSSIP_SENDER_MAIN, 118);
			}
			if (player->getClass() == CLASS_MAGE) 
			{
				AddGossipItemFor(player,  3, "|cff3300FFJaded Crystal Dagger (All Spec)"                 , GOSSIP_SENDER_MAIN, 113);
                AddGossipItemFor(player,  3, "|cff3300FFStarshard Edge (All Spec)"                       , GOSSIP_SENDER_MAIN, 117);	
                AddGossipItemFor(player,  3, "|cff3300FFVal'anyr, Hammer of Ancient Kings (All Spec)"    , GOSSIP_SENDER_MAIN, 106);
                AddGossipItemFor(player,  3, "|cff3300FFWarblade of the Hakkari (All Spec)"              , GOSSIP_SENDER_MAIN, 119);				
			}
			if (player->getClass() == CLASS_WARLOCK) 
			{
				AddGossipItemFor(player,  3, "|cff3300FFJaded Crystal Dagger (All Spec)"                 , GOSSIP_SENDER_MAIN, 113);
                AddGossipItemFor(player,  3, "|cff3300FFStarshard Edge (All Spec)"                       , GOSSIP_SENDER_MAIN, 117);	
                AddGossipItemFor(player,  3, "|cff3300FFVal'anyr, Hammer of Ancient Kings (All Spec)"    , GOSSIP_SENDER_MAIN, 106);
                AddGossipItemFor(player,  3, "|cff3300FFRoyal Scepter of Terenas (All Spec)"             , GOSSIP_SENDER_MAIN, 118);
                AddGossipItemFor(player,  3, "|cff3300FFWarblade of the Hakkari (All Spec)"              , GOSSIP_SENDER_MAIN, 119);				
			}
			if (player->getClass() == CLASS_DRUID) 
			{
                AddGossipItemFor(player,  3, "|cff3300FFRoyal Scepter of Terenas (Resto/Ballance)"         , GOSSIP_SENDER_MAIN, 118);
                AddGossipItemFor(player,  3, "|cff3300FFJaded Crystal Dagger (Resto/Ballance)"             , GOSSIP_SENDER_MAIN, 113);
				AddGossipItemFor(player,  3, "|cff3300FFSulfuras, Hand of Ragnaros (Feral)"                , GOSSIP_SENDER_MAIN, 110);
                AddGossipItemFor(player,  3, "|cff3300FFStarshard Edge (Resto/Ballance)"                   , GOSSIP_SENDER_MAIN, 117);
                AddGossipItemFor(player,  3, "|cff3300FFWarblade of the Hakkari (Resto/Ballance)"          , GOSSIP_SENDER_MAIN, 119);
				AddGossipItemFor(player,  3, "|cff3300FFHalberd of Smiting (Feral)"                        , GOSSIP_SENDER_MAIN, 120);
			}
			if (player->getClass() == CLASS_SHAMAN)
			{
				AddGossipItemFor(player,  3, "|cff3300FFRoyal Scepter of Terenas (Ele/Resto)"         , GOSSIP_SENDER_MAIN, 118);
				AddGossipItemFor(player,  3, "|cff3300FFJaded Crystal Dagger (Ele/Resto)"             , GOSSIP_SENDER_MAIN, 113);
				AddGossipItemFor(player,  3, "|cff3300FFStarshard Edge (Ele/Resto)"                   , GOSSIP_SENDER_MAIN, 117);
				AddGossipItemFor(player,  3, "|cff3300FFVal'anyr, Hammer of Ancient Kings (Ele/Resto)" , GOSSIP_SENDER_MAIN, 106);
				AddGossipItemFor(player,  3, "|cff3300FFZin'rokh, Destroyer of Worlds (Enhcant)"        , GOSSIP_SENDER_MAIN, 107);
				AddGossipItemFor(player,  3, "|cff3300FFDraconic Avenger (Enhcant)"                     , GOSSIP_SENDER_MAIN, 112);
			}
	    }

        SendGossipMenuFor(player, 60007, _creature->GetGUID());         
        return true;
    }

    static bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            ClearGossipMenuFor(player);
            switch(uiAction)
            {
				case 999:
					CloseGossipMenuFor(player);
					_creature->Whisper("Venha novamente, amigo!", LANG_UNIVERSAL, player);
				break;
			
			  case 100: //Rogue
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 28524); // main hand*/
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 32838); // offhand
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 101:
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 5191); // main hand*/
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19866); // offhand
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 102:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 17071); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19866); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 103:
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 17071); // main hand*/
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 32945); // offhand
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 104:
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 17071); // main hand*/
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 105: // Paladin
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 40488); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 106:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 46017); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 107:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 19854); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 108:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 18877); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 109:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 18876); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 110:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 17182); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 111:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 13262); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 112:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 19354); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 113:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 34604); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 114:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_18_ENTRYID, 34196); // ranged
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 115:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_18_ENTRYID, 29949); // ranged
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 116:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_18_ENTRYID, 32253); // ranged
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 117:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 45620); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 118:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 50428); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;
	  
			  case 119:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 19866); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
			  break;

			  case 120:
				  player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID, 19874); // main hand
				  /*player->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID, 19019); // offhand*/
				  CloseGossipMenuFor(player);
				  _creature->Whisper("Seus items foram modificados com sucesso!", LANG_UNIVERSAL, player);
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

void AddSC_weptransmog()
{
    new weptransmog();
}
