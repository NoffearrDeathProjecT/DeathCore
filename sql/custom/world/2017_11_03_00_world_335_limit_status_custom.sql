﻿-- Added System Limit Status Custom
-- By Ericks Oliveira for DeathCore.

ALTER TABLE `world`.`item_template` CHANGE `stat_value1` `stat_value1` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value2` `stat_value2` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value3` `stat_value3` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value4` `stat_value4` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value5` `stat_value5` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value6` `stat_value6` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value7` `stat_value7` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value8` `stat_value8` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value9` `stat_value9` INT(10) DEFAULT 0 NOT NULL, CHANGE `stat_value10` `stat_value10` INT(10) DEFAULT 0 NOT NULL;
UPDATE `item_template` SET `StatsCount`='10';