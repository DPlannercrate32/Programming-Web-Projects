-- +----------+-----------------+------+-----+-------------------+-----------------------------+
-- | Field    | Type            | Null | Key | Default           | Extra                       |
-- +----------+-----------------+------+-----+-------------------+-----------------------------+
-- | id       | int(8) unsigned | YES  |     | NULL              |                             |
-- | name     | varchar(64)     | YES  |     | NULL              |                             |
-- | question | varchar(256)    | YES  |     | NULL              |                             |
-- | answer   | varchar(256)    | YES  |     | NULL              |                             |
-- | time     | timestamp       | NO   |     | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
-- +----------+-----------------+------+-----+-------------------+-----------------------------+


DROP TABLE IF EXISTS `QA`;
CREATE TABLE `QA` (
  `id`		int(8)		UNSIGNED NOT NULL AUTO_INCREMENT,
  `name`	varchar(64)	NOT NULL DEFAULT '',
  `question`	varchar(256)	NOT NULL DEFAULT '',
  `answer`	varchar(256)	NOT NULL DEFAULT '',
  PRIMARY KEY ( `id` )
);

