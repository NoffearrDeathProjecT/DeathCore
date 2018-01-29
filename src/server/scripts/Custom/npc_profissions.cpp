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

class Professions_NPC : public CreatureScript
{
public:
	Professions_NPC() : CreatureScript("Professions_NPC") {}

	void CreatureWhisperBasedOnBool(const char *text, Creature *_creature, Player *pPlayer, bool value)
	{
		if (value)
			_creature->TextEmote(text, pPlayer);
	}

	uint32 PlayerMaxLevel() const
	{
		return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	}

	static bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId)
	{
		return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
	}

	static bool OnGossipHello(Player *pPlayer, Creature* _creature)
	{
		AddGossipItemFor(pPlayer, 9, "|TInterface\\icons\\inv_inscription_tradeskill01:35:35-15|t Profissões ->", GOSSIP_SENDER_MAIN, 196);
		SendGossipMenuFor(pPlayer, 907, _creature->GetGUID());
		return true;
	}

	static bool PlayerAlreadyHasTwoProfessions(const Player *pPlayer)
	{
		uint32 skillCount = 0;

		if (pPlayer->HasSkill(SKILL_MINING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_HERBALISM))
			skillCount++;
		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;
			if (pPlayer->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}
		return false;
	}

	static bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
	{
		ChatHandler handler(pPlayer->GetSession());
		char* skill_name;

		SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
		skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

		if (!SkillInfo)
		{
			TC_LOG_ERROR("server.loading", "Profession NPC: received non-valid skill ID (LearnAllRecipesInProfession)");
		}

		LearnSkillRecipesHelper(pPlayer, SkillInfo->id);

		pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), 450, 450);
		handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);

		return true;
	}

	static void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
	{
		uint32 classmask = player->getClassMask();

		for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
		{
			SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
			if (!skillLine)
				continue;

			// wrong skill
			if (skillLine->skillId != skill_id)
				continue;

			// not high rank
			if (skillLine->forward_spellid)
				continue;

			// skip racial skills
			if (skillLine->racemask != 0)
				continue;

			// skip wrong class skills
			if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
				continue;

			SpellInfo const * spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
			if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
				continue;

			player->LearnSpell(skillLine->spellId, false);
		}
	}

	static bool IsSecondarySkill(SkillType skill)
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
	}

	static void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
	{
		if (PlayerAlreadyHasTwoProfessions(pPlayer) && !IsSecondarySkill(skill))
			pCreature->TextEmote("Você já possui duas profissões!", pPlayer);
		else
		{
			if (!LearnAllRecipesInProfession(pPlayer, skill))
				pCreature->TextEmote("Ocorreu um erro interno!", pPlayer);
		}
	}

	static bool OnGossipSelect(Player* pPlayer, Creature* _creature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		if (uiSender == GOSSIP_SENDER_MAIN)
		{
			switch (uiAction)
			{
				case 196:
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_alchemy:30|t Alchemy.", GOSSIP_SENDER_MAIN, 1);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Ingot_05:30|t Blacksmithing.", GOSSIP_SENDER_MAIN, 2);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_LeatherScrap_02:30|t Leatherworking.", GOSSIP_SENDER_MAIN, 3);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Fabric_Felcloth_Ebon:30|t Tailoring.", GOSSIP_SENDER_MAIN, 4);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_wrench_01:30|t Engineering.", GOSSIP_SENDER_MAIN, 5);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_engraving:30|t Enchanting.", GOSSIP_SENDER_MAIN, 6);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_gem_01:30|t Jewelcrafting.", GOSSIP_SENDER_MAIN, 7);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Scroll_08:30|t Inscription.", GOSSIP_SENDER_MAIN, 8);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_Herb_07:30|t Herbalism.", GOSSIP_SENDER_MAIN, 9);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_pelt_wolf_01:30|t Skinning.", GOSSIP_SENDER_MAIN, 10);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_mining:30|t Mining.", GOSSIP_SENDER_MAIN, 11);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_food_15:30|t Cooking", GOSSIP_SENDER_MAIN, 12);
                	AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\spell_holy_sealofsacrifice:30|t First Aid", GOSSIP_SENDER_MAIN, 13);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_fishing:30|t Fishing", GOSSIP_SENDER_MAIN, 14);
					AddGossipItemFor(pPlayer, GOSSIP_ICON_TALK, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:30|t Sair!", GOSSIP_SENDER_MAIN, 15);
					SendGossipMenuFor(pPlayer, 1, _creature->GetGUID());
					break;
				case 1:
					if (pPlayer->HasSkill(SKILL_ALCHEMY))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}

					CompleteLearnProfession(pPlayer, _creature, SKILL_ALCHEMY);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 2:
					if (pPlayer->HasSkill(SKILL_BLACKSMITHING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
					CompleteLearnProfession(pPlayer, _creature, SKILL_BLACKSMITHING);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 3:
					if (pPlayer->HasSkill(SKILL_LEATHERWORKING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
					CompleteLearnProfession(pPlayer, _creature, SKILL_LEATHERWORKING);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 4:
					if (pPlayer->HasSkill(SKILL_TAILORING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
					CompleteLearnProfession(pPlayer, _creature, SKILL_TAILORING);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 5:
					if (pPlayer->HasSkill(SKILL_ENGINEERING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
					CompleteLearnProfession(pPlayer, _creature, SKILL_ENGINEERING);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 6:
					if (pPlayer->HasSkill(SKILL_ENCHANTING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
					CompleteLearnProfession(pPlayer, _creature, SKILL_ENCHANTING);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 7:
					if (pPlayer->HasSkill(SKILL_JEWELCRAFTING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
					CompleteLearnProfession(pPlayer, _creature, SKILL_JEWELCRAFTING);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 8:
					if (pPlayer->HasSkill(SKILL_INSCRIPTION))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
					CompleteLearnProfession(pPlayer, _creature, SKILL_INSCRIPTION);

					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 9:
					if (pPlayer->HasSkill(SKILL_HERBALISM))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}

					CompleteLearnProfession(pPlayer, _creature, SKILL_HERBALISM);
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 10:
					if (pPlayer->HasSkill(SKILL_SKINNING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}

					CompleteLearnProfession(pPlayer, _creature, SKILL_SKINNING);
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 11:
					if (pPlayer->HasSkill(SKILL_MINING))
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						break;
					}
				
					CompleteLearnProfession(pPlayer, _creature, SKILL_MINING);
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 12:
					if(pPlayer->HasSkill(SKILL_COOKING))
                			{
                    				pPlayer->PlayerTalkClass->SendCloseGossip();
                    				break;
                			}
				
					CompleteLearnProfession(pPlayer, _creature, SKILL_COOKING);
                			pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 13:
					if(pPlayer->HasSkill(SKILL_FIRST_AID))
               				{
                    				pPlayer->PlayerTalkClass->SendCloseGossip();
                    				break;
                			}
				
					CompleteLearnProfession(pPlayer, _creature, SKILL_FIRST_AID);
                			pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 14:
					if(pPlayer->HasSkill(SKILL_FISHING))
                			{
                    				pPlayer->PlayerTalkClass->SendCloseGossip();
                    				break;
                			}
				
					CompleteLearnProfession(pPlayer, _creature, SKILL_FISHING);
                			pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 15:
					pPlayer->PlayerTalkClass->SendCloseGossip();
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

void AddSC_Professions_NPC()
{
	new Professions_NPC();
}
