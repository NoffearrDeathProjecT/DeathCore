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

const uint32 RANK_VIP = (uint32)SEC_VIP;

uint32 vAuras[] = { 59908,21562, 20217, 6673, 57330, 3714, 43499, 5862, 24705, 26035, 22888, 26393, 35076, 34410, 24425, 19740 };

using namespace std;
using namespace rbac;

class VipSystemCommands : public CommandScript
{
public:
    VipSystemCommands() : CommandScript("VipSystemCommands") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> VipManagerCommandTable =
        {
            { "adicionar", RBAC_PERM_COMMAND_CUSTOM_STAFF, true, &HandleVipManagerAddCommand, "" },
            { "remover", RBAC_PERM_COMMAND_CUSTOM_STAFF, true, &HandleVipManagerDeleteCommand, "" },
            { "listar", RBAC_PERM_COMMAND_CUSTOM_STAFF, true, &HandleVipManagerListCommand, "" },
        };

        static std::vector<ChatCommand> VipCommandTable =
        {
            { "info", RBAC_PERM_COMMAND_VIP, false, &HandleVipInfoCommand, "" },
            //{ "buffs", RBAC_PERM_COMMAND_VIP, false, &HandleVipBuffCommand, "" },
            //{ "teletransportar", RBAC_PERM_COMMAND_VIP, false, &HandleVipTeleCommand, "" },
            { "tamanho", RBAC_PERM_COMMAND_VIP, false, &HandleVipScaleCommand, "" },
            { "sala",          RBAC_PERM_COMMAND_VIP,    true,   &HandleVipMallCommand,          "" },
            { "mudar-visual", RBAC_PERM_COMMAND_VIP, false, &HandleVipCustomizeCommand, "" },
            //{ "mudar-raça", RBAC_PERM_COMMAND_VIP, false, &HandleVipChangeRaceCommand, "" },
            //{ "mudar-facção", RBAC_PERM_COMMAND_VIP, false, &HandleVipChangeFactionCommand, "" },
        };

        static std::vector<ChatCommand> CommandTable =
        {
            { "vips", RBAC_PERM_COMMAND_CUSTOM_STAFF, true, NULL, "", VipManagerCommandTable },
            { "vip", RBAC_PERM_COMMAND_VIP, true, NULL, "", VipCommandTable },
        };

        return CommandTable;
    }

    static bool IsAccountVip(uint32 accountId)
    {
        QueryResult result = LoginDatabase.PQuery("SELECT id FROM account_access WHERE id = %u AND gmlevel >= %u", accountId, RANK_VIP);

        if (result)
            return true;
        else
            return false;
    }

    static void SetAccountVip(uint32 accountId, char* vipTime, char* vipComment)
    {
        uint32 _vipTime = time(NULL) + TimeStringToSecs(vipTime);

        LoginDatabase.PQuery("INSERT INTO account_access (id, gmlevel, RealmID, vipTime, vipComment) VALUES ('%u','%u','-1','%u','%s')", accountId, RANK_VIP, _vipTime, vipComment);
    }

    static void UnsetAccountVip(uint32 accountId)
    {
        LoginDatabase.PQuery("DELETE FROM account_access WHERE id = %u AND gmlevel = %u", accountId, RANK_VIP);
    }

    static void ListAccountVip(ChatHandler* handler)
    {
        QueryResult result = LoginDatabase.PQuery("SELECT id, vipTime, vipComment FROM account_access WHERE gmlevel = %u", RANK_VIP);

        if (!result)
        {
            handler->PSendSysMessage("Sem jogadores V.I.Ps!");
            handler->SetSentErrorMessage(true);
            return;
        }

        handler->PSendSysMessage("======================================");
        do
        {
            Field* field = result->Fetch();

            uint32 accountId = field[0].GetUInt32();
            uint64 vipTime = field[1].GetUInt64();
            string vipComment = field[2].GetString();

            string accountName;
            AccountMgr::GetName(accountId, accountName);

            uint64 timeLeft;
            string vipTimeLeft;

            timeLeft = (vipTime - time(NULL));
            vipTimeLeft = secsToTimeString(timeLeft);

            char msg[250];
            snprintf(msg, 250, "Conta: %s.\nTermina em: %s\nComentário: %s.", accountName.c_str(), vipTimeLeft.c_str(), vipComment.c_str());

            handler->PSendSysMessage(msg);
            handler->PSendSysMessage("======================================");

        } while (result->NextRow());
    }

    static bool IsValidToUse(Player* player, ChatHandler* handler)
    {
        if (player->IsInFlight() || player->IsInCombat())
        {
            handler->SendSysMessage("Impossivel usar o comando em combate ou voando.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->isDead() || player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
        {
            player->GetSession()->SendNotification("Impossivel falar enquanto estiver morto!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        return true;
    }

    static bool HandleVipManagerAddCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
        {
            handler->PSendSysMessage("Syntax: .vips adicionar #Conta #Tempo #Comentário");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* accountStr = strtok((char*)args, " ");
        char* vipTimeStr = strtok(NULL, " ");
        char* vipCommentStr = strtok(NULL, "\r");

        if (!accountStr || !vipTimeStr || !vipCommentStr)
        {
            handler->PSendSysMessage("Syntax: .vips adicionar #Conta #Tempo #Comentário");
            handler->SetSentErrorMessage(true);
            return false;
        }

        string accountName = accountStr;
        uint32 accountId = AccountMgr::GetId(accountName);

        if (!accountId)
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (IsAccountVip(accountId))
        {
            handler->PSendSysMessage("Essa conta já é V.I.P!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        SetAccountVip(accountId, vipTimeStr, vipCommentStr);
        handler->PSendSysMessage("Adicionado V.I.P com Sucesso!");

        return true;
    }

    static bool HandleVipManagerDeleteCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
        {
            handler->PSendSysMessage("Syntax: .vips remover #Conta");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* accountStr = strtok((char*)args, " ");

        if (!accountStr)
        {
            handler->PSendSysMessage("Syntax: .vips remover #Conta");
            handler->SetSentErrorMessage(true);
            return false;
        }

        string accountName = accountStr;
        uint32 accountId = AccountMgr::GetId(accountName);

        if (!accountId)
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!IsAccountVip(accountId))
        {
            handler->PSendSysMessage("Essa conta já não é mais V.I.P!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        UnsetAccountVip(accountId);
        handler->PSendSysMessage("Removido V.I.P com Sucesso!");

        return true;
    }

    static bool HandleVipManagerListCommand(ChatHandler* handler, char const* /*args*/)
    {
        ListAccountVip(handler);
        return true;
    }

    static bool HandleVipInfoCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        QueryResult result = LoginDatabase.PQuery("SELECT vipTime FROM account_access WHERE id = %u", player->GetSession()->GetAccountId());

        if (result)
        {
            handler->PSendSysMessage("======================================");
            do
            {
                Field* field = result->Fetch();

                uint64 vipTime = field[0].GetUInt64();

                string accountName;
                AccountMgr::GetName(player->GetSession()->GetAccountId(), accountName);

                uint64 timeLeft;
                string vipTimeLeft;

                timeLeft = (vipTime - time(NULL));
                vipTimeLeft = secsToTimeString(timeLeft);

                char msg[250];
                snprintf(msg, 250, "Conta: %s.\nTermina em: %s.", accountName.c_str(), vipTimeLeft.c_str());

                handler->PSendSysMessage(msg);
                handler->PSendSysMessage("======================================");

            } while (result->NextRow());
        }
        return true;
    }

    static bool HandleVipBuffCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (IsValidToUse(player, handler))
        {
            for (string::size_type i = 0; i < (sizeof(vAuras) / sizeof(*vAuras)); i++)
                player->AddAura(vAuras[i], player);
        }

        handler->PSendSysMessage("|cffB400B4[|cffFFA500BUFF V.I.P|cffB400B4] |cffFF0000Você está quase Imortal!");
        return true;
    }

    static bool HandleVipTeleCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!*args)
        {
            handler->SendSysMessage("Syntax: .vip tele #mapname");
            handler->SetSentErrorMessage(true);
            return false;
        }

        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);

        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->SendSysMessage(LANG_CANNOT_TELE_TO_BG);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (IsValidToUse(player, handler))
            player->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);

        return true;
    }

    static bool HandleVipScaleCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!*args)
        {
            handler->SendSysMessage("Syntax: .vip tamanho #Tamanho(3.00/0.80)");
            handler->SetSentErrorMessage(true);
            return false;
        }

        float Scale = (float)atof((char*)args);

        if (Scale > 3.00f || Scale < 0.80f)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (IsValidToUse(player, handler))
            player->SetFloatValue(OBJECT_FIELD_SCALE_X, Scale);

        return true;
    }

    static bool HandleVipMallCommand(ChatHandler* handler, const char* /*args*/)
    {

        Player* me = handler->GetSession()->GetPlayer();

        if (me->IsInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->IsInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();

        me->TeleportTo(0, -11216.884766f, -1719.028931f, -2.722186f, 4.527766f); // MapId, X, Y, Z, O
        return true;
    }

    static bool HandleVipCustomizeCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (IsValidToUse(player, handler))
        {
            player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
            handler->SendSysMessage("Relogue para mudar o seu visual!");
        }

        return true;
    }

    static bool HandleVipChangeRaceCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (IsValidToUse(player, handler))
        {
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
            handler->SendSysMessage("Relogue para mudar sua raça!");
        }

        return true;
    }

    static bool HandleVipChangeFactionCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (IsValidToUse(player, handler))
        {
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
            handler->SendSysMessage("Relogue para mudar sua facção!");
        }

        return true;
    }
};

void AddSC_VipSystemCommands()
{
    new VipSystemCommands();
}
