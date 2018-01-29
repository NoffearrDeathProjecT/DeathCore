-- Added System Reforge
-- By Bodeguero for DeathCore.

DROP TABLE IF EXISTS `custom_reforging`;
CREATE TABLE `custom_reforging` (
  `GUID` int(10) unsigned NOT NULL COMMENT 'item guid low',
  `increase` int(10) unsigned NOT NULL COMMENT 'stat_type',
  `decrease` int(10) unsigned NOT NULL COMMENT 'stat_type',
  `stat_value` int(10) NOT NULL DEFAULT '0' COMMENT 'stat change',
  `Owner` int(10) unsigned DEFAULT NULL COMMENT 'player guid',
  PRIMARY KEY (`GUID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
