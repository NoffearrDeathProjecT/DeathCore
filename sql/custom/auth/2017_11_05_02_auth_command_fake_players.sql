-- Added Command Fake Players
-- By Bodeguero for DeathCore.

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1003, 'Command: fake');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(191, 1003);
