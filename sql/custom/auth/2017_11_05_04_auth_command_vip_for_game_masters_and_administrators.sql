-- Added Command Vip - for Game Masters and Administrators
-- By Bodeguero for DeathCore.

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1004, 'Command: vips');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(191, 1004);
