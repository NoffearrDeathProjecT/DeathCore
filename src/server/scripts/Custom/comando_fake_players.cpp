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

#include "ScriptPCH.h"
#include "AccountMgr.h"
#include "Language.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "CharacterCache.h"

class fake_commandscript : public CommandScript
{
public:
   fake_commandscript() : CommandScript("fake_commandscript") { }

   std::vector<ChatCommand> GetCommands() const override
   {
	   static std::vector<ChatCommand> fakeCommandTable =
       {
           { "conta",  rbac::RBAC_PERM_COMMAND_FAKE,   true, &HandleFakeAccount,  "" },
           { "jogador",   rbac::RBAC_PERM_COMMAND_FAKE,   true,  &HandleFakePlayer,  "" },
       };

	   static std::vector<ChatCommand> commandTable =
       {
           { "fake",    rbac::RBAC_PERM_COMMAND_FAKE,  true,                NULL,  "", fakeCommandTable },

       };

       return commandTable;
   }

   static bool HandleFakeAccount(ChatHandler* handler, char const* args)
   {
       if (!*args)
           return false;

       char* account = strtok((char*)args, " ");
       char* toggle = strtok(NULL, " ");
       if (!account || !toggle)
           return false;

       std::string accountName = account;
       std::string online = toggle;

	  if (!Utf8ToUpperOnlyLatin(accountName))
       {
           handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
           handler->SetSentErrorMessage(true);
           return false;
       }

       uint32 accountId = AccountMgr::GetId(accountName);
       if (!accountId)
       {
           handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
           handler->SetSentErrorMessage(true);
           return false;
       }

       if (handler->HasLowerSecurityAccount(NULL, accountId, true))
           return false;

       if (online == "on")
       {
           CharacterDatabase.PExecute("UPDATE characters SET online = 2 WHERE account = '%u'", accountId);
           handler->PSendSysMessage("Todos os personagens da conta %s esta online agora.", accountName.c_str());
           return true;
       }

       if (online == "off")
       {
           CharacterDatabase.PExecute("UPDATE characters SET online = 0 WHERE account = '%u'", accountId);
           handler->PSendSysMessage("Todos os personagens da conta %s esta off-line agora.", accountName.c_str());
           return true;
       }

       handler->SendSysMessage(LANG_USE_BOL);
       handler->SetSentErrorMessage(true);
       return false;
   }

   static bool HandleFakePlayer(ChatHandler* handler, char const* args)
   {
       if (!*args)
           return false;

       char* name = strtok((char*)args, " ");
       char* toggle = strtok(NULL, " ");
       if (!name || !toggle)
           return false;

       std::string playerName = handler->extractPlayerNameFromLink(name);
       if (playerName.empty())
       {
           handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
           handler->SetSentErrorMessage(true);
           return false;
       }

       std::string online = toggle;
       ObjectGuid guid = sCharacterCache->GetCharacterGuidByName(playerName);
       uint32 accountId = sCharacterCache->GetCharacterAccountIdByGuid(guid);

       if (handler->HasLowerSecurityAccount(NULL, accountId, true))
           return false;

       if (online == "on")
       {
           CharacterDatabase.PExecute("UPDATE characters SET online = 2 WHERE guid = '%u'", guid);
           handler->PSendSysMessage("Personagem da conta %s esta online agora.", playerName.c_str());
           return true;
       }

       if (online == "off")
       {
           CharacterDatabase.PExecute("UPDATE characters SET online = 0 WHERE guid = '%u'", guid);
           handler->PSendSysMessage("Personagem da conta %s esta off-line agora.", playerName.c_str());
           return true;
       }

       handler->SendSysMessage(LANG_USE_BOL);
       handler->SetSentErrorMessage(true);
       return false;
   }
};

void AddSC_fake_commandscript()
{
   new fake_commandscript();
}
