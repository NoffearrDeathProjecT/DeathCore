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
#include <boost/asio/ip/address_v4.hpp>

using namespace std;

uint32 auras[] = { 59908,21562, 20217, 6673, 57330, 3714, 43499, 5862 };

class buffcommand : public CommandScript
{
public:
    buffcommand() : CommandScript("buffcommand") { }

    vector<ChatCommand> GetCommands() const override
    {
        static vector<ChatCommand> IngameCommandTable =
        {
            { "buff",   rbac::RBAC_PERM_COMMAND_BUFF,   true,   &HandleBuffCommand,     "" }
        };
        return IngameCommandTable;
    }

    static bool HandleBuffCommand(ChatHandler * handler, const char * /*args*/)
    {
        Player * pl = handler->GetSession()->GetPlayer();
        if (pl->InArena())
        {
            pl->GetSession()->SendNotification("Você não pode usar isso em uma arena!");
            return false;
        }

        pl->RemoveAurasByType(SPELL_AURA_MOUNTED);
        for (int i = 0; i < 7; i++)
            pl->AddAura(auras[i], pl);
        handler->PSendSysMessage("|cffB400B4[|cffFFA500BUFF FREE|cffB400B4] |cffFF0000Você agora é um Grande Guerreiro!");
        return true;

    }
};

void AddSC_buffcommand()
{
    new buffcommand();
}
