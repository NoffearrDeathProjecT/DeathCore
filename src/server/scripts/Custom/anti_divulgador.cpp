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
 
#include "../../../scripts/ScriptPCH.h"
#include "../../../game/Chat/Channels/Channel.h"
#include "Chat.h"
 
class System_Censure : public PlayerScript
{
public:
        System_Censure() : PlayerScript("System_Censure") {}
 
        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg)
        {
                CheckMessage(player, msg, lang, NULL, NULL, NULL, NULL);
        }
 
        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver)
        {
                CheckMessage(player, msg, lang, receiver, NULL, NULL, NULL);
        }
 
        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* group)
        {
                CheckMessage(player, msg, lang, NULL, group, NULL, NULL);
        }
 
        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild)
        {
                CheckMessage(player, msg, lang, NULL, NULL, guild, NULL);
        }
 
        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel)
        {
                CheckMessage(player, msg, lang, NULL, NULL, NULL, channel);
        }
 
void CheckMessage(Player* player, std::string& msg, uint32 lang, Player* /*receiver*/, Group* /*group*/, Guild* /*guild*/, Channel* channel)
{
    //if (player->isGameMaster() || lang == LANG_ADDON)
            //return;
 
    // transform to lowercase (for simpler checking)
    std::string lower = msg;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
 
    uint8 cheksSize = 118;//Change these if you want to add more words to the array.
    std::string checks[118];//Change these if you want to add more words to the array.
    // Strony (Sites)
    // Strony (Sites)
	checks[0] ="http://";
	checks[1] =".com";
	checks[2] =".net";
	checks[3] =".org";
	checks[4] ="www.";
	checks[5] ="wow-";
	checks[6] ="-wow";
	checks[7] ="no-ip";
	checks[8] =".zapto";
	checks[9] =".biz";
	checks[10] =".servegame";
	checks[11] =".br";
	checks[12] ="com.br";

	checks[13] ="h t t p : / /";
	checks[14] =". c o m";
	checks[15] =". n e t";
	checks[16] =". o r g";
	checks[17] ="w w w .";
	checks[18] =" w o w -";
	checks[19] ="- w o w";
	checks[20] ="n o - i p";
	checks[21] =". z a p t o";
	checks[22] =". b i z";
	checks[23] =". s e r v e g a m e";
	checks[24] =". b r";
	checks[25] ="c o m . b r";

	checks[26] ="h  t  t  p  :  /  /";
	checks[27] =".  c  o  m";
	checks[28] =".  n  e  t";
	checks[29] =".  o  r  g";
	checks[30] ="w  w  w  .";
	checks[31] =" w  o  w  -";
	checks[32] ="-  w  o  w";
	checks[33] ="n  o  -  i  p";
	checks[34] =".  z  a  p  t  o";
	checks[35] =".  b  i  z";
	checks[36] =".  s  e  r  v  e  g  a  m  e";
	checks[37] =".  b  r";
	checks[38] ="c  o  m  .  b  r";
	
	checks[39] ="h   t   t   p   :   /   /";
	checks[40] =".   c   o   m";
	checks[41] =".   n   e   t";
	checks[42] =".   o   r   g";
	checks[43] ="w   w   w   .";
	checks[44] =" w   o   w   -";
	checks[45] ="-   w   o   w";
	checks[46] ="n   o   -   i   p";
	checks[47] =".   z   a   p   t   o";
	checks[48] =".   b   i   z";
	checks[49] =".   s   e   r   v   e   g   a   m   e";
	checks[50] =".   b   r";
	checks[51] ="   c   o   m   .   b   r";
	
	checks[52] ="h    t    t    p   :   /   /";
	checks[53] =".    c    o    m";
	checks[54] =".    n    e   t";
	checks[55] =".    o    r    g";
	checks[56] ="w    w    w    .";
	checks[57] ="w    o    w    -";
	checks[58] ="-    w    o    w";
	checks[59] ="n    o    -    i    p";
	checks[60] =".    z    a    p    t    o";
	checks[61] =".    b    i     z";
	checks[62] =".    s    e    r    v    e    g    a    m    e";
	checks[63] =".    b    r";
	checks[64] ="c    o    m    .    b    r";
	
	checks[65] ="trevonwow";
	checks[66] ="megawow";
	checks[67] ="fatalwow";
	checks[68] ="uniforgiven-wow";
	checks[69] ="wow-autolouco";
	checks[70] ="heaven-wow";
	checks[71] ="fireballwow";
	checks[72] ="wowbrasilpa";
	checks[73] ="fatalitywow";
	checks[74] ="demonic-wow";
	checks[75] ="revenge-wow";
	checks[76] ="heavenwow";
	checks[77] ="undead-wow";
	checks[78] ="linebr";
	checks[79] ="azralon";
	checks[80] ="black-wow";
	checks[81] ="trevonwow";
	
	checks[82] ="t r e v o n w o w";
	checks[83] ="m e g a w o w";
	checks[84] ="f a t a l w o w";
	checks[85] ="u n i f o r g i v e n - w o w";
	checks[86] ="w o w - a u t o l o u c o";
	checks[87] ="h e a v e n - w o w";
	checks[88] ="f i r e b a l l w o w";
	checks[89] ="w o w b r a s i l  p a";
	checks[90] ="f a t a l i t y w o w";
	checks[91] ="d e m o n i c - w o w";
	checks[92] ="r e v e n g e - w o w";
	checks[93] ="h e a v e n w o w";
	checks[94] ="u n d e a d - w o w";
	checks[95] ="l i n e b r";
	checks[96] ="a z r a l o n";
	checks[97] ="b l a c k - w o w";
	checks[98] ="t r e v o n w o w";
	
	checks[99] ="t  r  e  v  o  n  w  o  w";
	checks[100] ="m  e  g  a  w  o  w";
	checks[101] ="f  a  t  a  l  w  o  w";
	checks[102] ="u  n  i  f  o  r  g  i  v  e  n  -  w  o  w";
	checks[103] ="w  o  w  -  a  u  t  o   l o  u  c  o";
	checks[104] ="h  e  a  v  e  n  -  w  o  w";
	checks[105] ="f  i  r  e  b  a  l  l  w  o  w";
	checks[106] ="w  o  w  b  r  a  s  i  l  p  a";
	checks[107] ="f  a  t  a  l  i  t  y  w  o  w";
	checks[108] ="d  e  m  o  n  i  c  -  w  o  w";
	checks[109] ="r  e  v  e  n  g  e  -  w  o  w";
	checks[110] ="h  e  a  v  e  n  w  o  w";
	checks[111] ="u  n  d  e  a  d  -  w  o  w";
	checks[112] ="l  i  n  e  b  r";
	checks[113] ="a  z  r  a  l  o  n";
	checks[114] ="b  l  a  c  k  -  w  o  w";
	checks[115] ="t  r  e  v  o  n  w  o  w";
	
	checks[116] =" [The Lightbringer's Redemption]";
    checks[117] ="[The Lightbringer's Redemption]";
 
    for (int i = 0; i < cheksSize; ++i)
        if (lower.find(checks[i]) != std::string::npos)
        {
            msg = "";
            ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000[!] PROIBIDO DIVULGAR LINKS.");
            return;
        }
}
};
 
void AddSC_System_Censure()
{
    new System_Censure();
}