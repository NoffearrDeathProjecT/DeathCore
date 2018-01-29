REVOKE ALL PRIVILEGES ON * . * FROM 'deathcore'@'localhost';

REVOKE ALL PRIVILEGES ON `world` . * FROM 'deathcore'@'localhost';

REVOKE GRANT OPTION ON `world` . * FROM 'deathcore'@'localhost';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'deathcore'@'localhost';

REVOKE GRANT OPTION ON `characters` . * FROM 'deathcore'@'localhost';

REVOKE ALL PRIVILEGES ON `auth` . * FROM 'deathcore'@'localhost';

REVOKE GRANT OPTION ON `auth` . * FROM 'deathcore'@'localhost';

DROP USER 'deathcore'@'localhost';

DROP DATABASE IF EXISTS `world`;

DROP DATABASE IF EXISTS `characters`;

DROP DATABASE IF EXISTS `auth`;
