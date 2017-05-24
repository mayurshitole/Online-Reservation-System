CREATE DATABASE  IF NOT EXISTS `test` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `test`;

DROP TABLE IF EXISTS `batman`;
CREATE TABLE `batman` (
  `seat` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`seat`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES `batman` WRITE;

INSERT INTO `batman` VALUES (1,''),(2,''),(3,''),(4,''),(5,''),(6,''),(7,''),(8,''),(9,''),(10,'');

UNLOCK TABLES;

DROP TABLE IF EXISTS `superman`;
CREATE TABLE `superman` (
  `seat` int(11) NOT NULL,
  `name` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`seat`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES `superman` WRITE;

INSERT INTO `superman` VALUES (1,''),(2,''),(3,''),(4,''),(5,''),(6,''),(7,''),(8,''),(9,''),(10,'');

UNLOCK TABLES;

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `name` varchar(45) NOT NULL,
  `password` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES `users` WRITE;
INSERT INTO `users` VALUES ('hardik','admin'),('isha','admin'),('mayur','admin'),('mridula','admin'),('ved','admin');
UNLOCK TABLES;
