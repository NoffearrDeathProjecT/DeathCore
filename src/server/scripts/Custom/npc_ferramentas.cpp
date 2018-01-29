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

uint32 vAuras1[] = {59908,21562, 20217, 6673};

class Tools_NPC : public CreatureScript
{
public:
        Tools_NPC() : CreatureScript("Tools_NPC") { }
 
	static bool OnGossipHello(Player * player, Creature * creature)
    {
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Spell_Nature_Regenerate:30:30:-15|t Buffs - Restaurar Vida/Mana", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Spell_Shadow_UnstableAffliction_1:30:30:-15|t Resetar Instances", GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\SPELL_HOLY_BORROWEDTIME:30:30:-15|t Resetar Cooldowns", GOSSIP_SENDER_MAIN, 3);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_BG_AB_defendflags:30:30:-15|t Resetar Combate", GOSSIP_SENDER_MAIN, 4);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Spell_Shadow_DeathScream:30:30:-15|t Remover Sickness", GOSSIP_SENDER_MAIN, 5);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\INV_Hammer_24:30:30:-15|t Reparar Items", GOSSIP_SENDER_MAIN, 6);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "|TInterface\\icons\\Achievement_WorldEvent_Lunar:30:30:-15|t Resetar Talents", GOSSIP_SENDER_MAIN, 7);
		AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Achievement_WorldEvent_Lunar:30:30:-15|t Sair", GOSSIP_SENDER_MAIN, 8);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
        }
	static bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 actions)
    {
        ClearGossipMenuFor(player);

		switch (actions)
        {
			case 1: // Restaurar HP e MP
					if(player->IsInCombat())
					{
						player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFVocê está em combate!|r");
						player->PlayerTalkClass->SendCloseGossip();
							return false;
					}
					else if(player->getPowerType() == POWER_MANA)
							player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
					for (uint32 i = 0; i < (sizeof(vAuras1) / sizeof(*vAuras1)); i++)
						player->AddAura(vAuras1[i], player);
						player->SetHealth(player->GetMaxHealth());
						player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFRecebeu Buffs e sua Vida/Mana foram restaurados com sucesso!|r");
						player->CastSpell(player, 36400);
						CloseGossipMenuFor(player);
					break;

			case 2: // Resetar Instances
					for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
					{
							Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
							for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
							{
									player->UnbindInstance(itr, Difficulty(i));
							}
					}
					player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFInstances resetados com sucesso!|r");
					player->CastSpell(player, 59908);
					CloseGossipMenuFor(player);
					break;

			case 3: // Resetar Cooldowns
					if(player->IsInCombat())
					{
						player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFVocê está em combate!|r");
						player->PlayerTalkClass->SendCloseGossip();
							return false;
					}
 
					player->GetSpellHistory()->ResetAllCooldowns();
					player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFCooldowns resetados com sucesso!|r");
					player->CastSpell(player, 463);
					CloseGossipMenuFor(player);
					break;

			case 4: // Resetar Combat
					player->CombatStop();
					player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFCombate Removido com Sucesso!|r");
					player->CastSpell(player, 24222);
					CloseGossipMenuFor(player);
					break;

			case 5: // Remover Sickness
					if(player->HasAura(15007))
					player->RemoveAura(15007);
					player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFSickness Removido com Sucesso!|r");
					player->CastSpell(player, 41300);
					CloseGossipMenuFor(player);
					break;

			case 6: // Reparar Items
					player->DurabilityRepairAll(false, 0, false);
					player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFEquipamentos Reparados com Sucesso!|r");
					player->CastSpell(player, 29541);
					CloseGossipMenuFor(player);
					break;

			case 7: // Resetar Talents
					player->ResetTalents(true);
					player->SendTalentsInfoData(false);
					player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFTalentos resetados com sucesso!|r");
					player->CastSpell(player, 19484);
					CloseGossipMenuFor(player);
					break;

			case 8: // Fechar Menu
					player->GetSession()->SendNotification("|cffFFFF00Ferramentas|r \n |cffFFFFFFObrigado, Utilize sempre esta ferramenta assim que precisar!|r");
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
 
void AddSC_Tools_NPC()
{
  new Tools_NPC();
}