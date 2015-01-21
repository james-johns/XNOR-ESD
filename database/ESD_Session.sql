CREATE DATABASE  IF NOT EXISTS `ESD` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `ESD`;
-- MySQL dump 10.13  Distrib 5.5.40, for debian-linux-gnu (x86_64)
--
-- Host: 127.0.0.1    Database: ESD
-- ------------------------------------------------------
-- Server version	5.5.40-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Session`
--

DROP TABLE IF EXISTS `Session`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Session` (
  `idSession` int(11) NOT NULL AUTO_INCREMENT,
  `idClient` int(11) NOT NULL,
  `idTransaction` int(11) NOT NULL,
  `idRPU` int(11) NOT NULL,
  `date` date NOT NULL,
  `timeIn` time NOT NULL,
  `timeOut` time DEFAULT NULL,
  `active` tinyint(1) NOT NULL,
  `idLanguage` int(11) NOT NULL,
  `idKnowledegeLvl` int(11) NOT NULL,
  PRIMARY KEY (`idSession`),
  KEY `fk_Session_Client_idx` (`idClient`),
  KEY `fk_Session_RPU_idx` (`idRPU`),
  KEY `fk_Session_Transaction_idx` (`idTransaction`),
  KEY `fk_Session_Language_idx` (`idLanguage`),
  KEY `fk_Session_KnowledgeLvl_idx` (`idKnowledegeLvl`),
  CONSTRAINT `fk_Session_Client` FOREIGN KEY (`idClient`) REFERENCES `Client` (`idClient`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_Transaction` FOREIGN KEY (`idTransaction`) REFERENCES `Transaction` (`idTransaction`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_RPU` FOREIGN KEY (`idRPU`) REFERENCES `RPU` (`idRPU`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_Language` FOREIGN KEY (`idLanguage`) REFERENCES `Language` (`idLanguage`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_KnowledgeLvl` FOREIGN KEY (`idKnowledegeLvl`) REFERENCES `KnowledgeLvl` (`idKnowledgeLvl`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Clients session, references: client, transaction, rpu.';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Session`
--

LOCK TABLES `Session` WRITE;
/*!40000 ALTER TABLE `Session` DISABLE KEYS */;
/*!40000 ALTER TABLE `Session` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-01-21 22:41:05
