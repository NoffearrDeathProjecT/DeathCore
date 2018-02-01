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

// This is where scripts' loading functions should be declared:

void AddSC_VipSystemCommands();
void AddSC_System_Censure();
void AddSC_fake_commandscript();
void AddSC_buffcommand();
void AddSC_XpWeekend();
//void AddSC_Script_Encantamentos();
void AddSC_Tools_NPC();
void AddSC_NDP_NpcMorph();
void AddSC_Professions_NPC();
void AddSC_npc_promo();
void AddSC_REFORGER_NPC();
void AddSC_transmogriefer();
void AddSC_TemplateNPC();
void AddSC_npc_trainer_master();
void AddSC_Npc_Beastmaster();
void AddSC_Transmogrification();
void AddSC_NPC_TransmogDisplayVendor();
void AddSC_VIP_NPC();
void AddSC_NPC_VisualWeapon();
void AddSC_weptransmog();
void AddSC_Reset();
void AddSC_VIP_Item();
void AddSC_VIP_Item_60d();
void AddSC_VIP_Item_120d();
void AddSC_VIP_Item_240d();
void AddSC_VIP_Item_480d();
void AddSC_VIP_Item_960d();

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddCustomScripts()
{
    AddSC_VipSystemCommands();
    AddSC_System_Censure();
    AddSC_fake_commandscript();
    AddSC_buffcommand();
    AddSC_XpWeekend();
    //AddSC_Script_Encantamentos();
    AddSC_Tools_NPC();
    AddSC_NDP_NpcMorph();
    AddSC_Professions_NPC();
    AddSC_npc_promo();
    AddSC_REFORGER_NPC();
    AddSC_transmogriefer();
	AddSC_TemplateNPC();
    AddSC_npc_trainer_master();
	AddSC_Npc_Beastmaster();
    AddSC_Transmogrification();
    AddSC_NPC_TransmogDisplayVendor();
    AddSC_VIP_NPC();
    AddSC_NPC_VisualWeapon();
    AddSC_weptransmog();
    AddSC_Reset();
    AddSC_VIP_Item();
    AddSC_VIP_Item_60d();
    AddSC_VIP_Item_120d();
    AddSC_VIP_Item_240d();
    AddSC_VIP_Item_480d();
    AddSC_VIP_Item_960d();
}