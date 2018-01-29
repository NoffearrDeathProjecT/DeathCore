-- Added Command Reload NPC Template
-- By Bodeguero for DeathCore.

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1005, 'Command: Reload NPC Template');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(191, 1005);