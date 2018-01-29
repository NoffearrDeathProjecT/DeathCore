-- Added Command Vip
-- By Bodeguero for DeathCore.

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1001, 'Command: vip');

INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(193, 1001);
