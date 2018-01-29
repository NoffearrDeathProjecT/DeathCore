-- Added System MultiVendor
-- By Bodeguero for DeathCore.

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(43283, 1298, "Herbert", "MultiVendor", NULL, 65025, 10, 10, 0, 35, 129, 1, 1.14286, 1, 0, 0, 1500, 0, 1, 512, 2048, 8, 0, 0, 0, 0, 0, 7, 138412032, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 0, 0, 1, 0, 2, '');

INSERT INTO `gossip_menu_option` (`MenuID`, `OptionID`, `OptionIcon`, `OptionText`, `OptionBroadcastTextID`, `OptionType`, `OptionNpcFlag`, `ActionMenuID`, `ActionPoiID`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextID`, `VerifiedBuild`) VALUES
(65025, 0, 4, 'VendorTest 465', 0, 3, 128, 465, 0, 0, 0, NULL, 0, 0),
(65025, 1, 9, 'VendorTest 54', 0, 3, 128, 54, 0, 0, 0, NULL, 0, 0,
(65025, 2, 6, 'VendorTest 35574', 0, 3, 128, 35574, 0, 0, 0, 'These goods are special, so pay up!', 0, 0;