-- Added Command Buff
-- By Bodeguero for DeathCore.

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1002, 'Command: buff');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(194, 1002);
