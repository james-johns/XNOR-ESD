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
-- Table structure for table `Client`
--

DROP TABLE IF EXISTS `Client`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Client` (
  `idClient` int(11) NOT NULL AUTO_INCREMENT,
  `forename` varchar(50) NOT NULL,
  `surname` varchar(50) NOT NULL,
  `mobilePhone` varchar(20) NOT NULL,
  `suggestedLanguage` int(11) NOT NULL,
  `suggestedKnowledgeLvl` int(11) NOT NULL,
  PRIMARY KEY (`idClient`),
  KEY `fk_Client_KnowledgeLvl_idx` (`suggestedKnowledgeLvl`),
  KEY `fk_Client_Language_idx` (`suggestedLanguage`),
  CONSTRAINT `fk_Client_KnowledgeLvl` FOREIGN KEY (`suggestedKnowledgeLvl`) REFERENCES `KnowledgeLvl` (`idKnowledgeLvl`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Client_Language` FOREIGN KEY (`suggestedLanguage`) REFERENCES `Language` (`idLanguage`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Client Details';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Client`
--

/*!40000 ALTER TABLE `Client` DISABLE KEYS */;
/*!40000 ALTER TABLE `Client` ENABLE KEYS */;

--
-- Table structure for table `KnowledgeLvl`
--

DROP TABLE IF EXISTS `KnowledgeLvl`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `KnowledgeLvl` (
  `idKnowledgeLvl` int(11) NOT NULL AUTO_INCREMENT,
  `knowledgeLvl` varchar(20) NOT NULL,
  PRIMARY KEY (`idKnowledgeLvl`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `KnowledgeLvl`
--

/*!40000 ALTER TABLE `KnowledgeLvl` DISABLE KEYS */;
INSERT INTO `KnowledgeLvl` VALUES (1,'Child'),(2,'Teenager'),(3,'Adult'),(4,'Advanced');
/*!40000 ALTER TABLE `KnowledgeLvl` ENABLE KEYS */;

--
-- Table structure for table `Language`
--

DROP TABLE IF EXISTS `Language`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Language` (
  `idLanguage` int(11) NOT NULL AUTO_INCREMENT,
  `language` varchar(20) NOT NULL,
  PRIMARY KEY (`idLanguage`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Language`
--

/*!40000 ALTER TABLE `Language` DISABLE KEYS */;
INSERT INTO `Language` VALUES (1,'English'),(2,'Russian'),(3,'Filipino'),(4,'Latvian');
/*!40000 ALTER TABLE `Language` ENABLE KEYS */;

--
-- Table structure for table `PaymentType`
--

DROP TABLE IF EXISTS `PaymentType`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PaymentType` (
  `idPaymentType` int(11) NOT NULL AUTO_INCREMENT,
  `paymentType` varchar(30) NOT NULL,
  PRIMARY KEY (`idPaymentType`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 COMMENT='Holds available payment types';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PaymentType`
--

/*!40000 ALTER TABLE `PaymentType` DISABLE KEYS */;
INSERT INTO `PaymentType` VALUES (1,'Visa'),(2,'MasterCard');
/*!40000 ALTER TABLE `PaymentType` ENABLE KEYS */;

--
-- Table structure for table `RPU`
--

DROP TABLE IF EXISTS `RPU`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `RPU` (
  `idRPU` int(11) NOT NULL,
  `pin` varchar(4) NOT NULL,
  PRIMARY KEY (`idRPU`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='RPU';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `RPU`
--

/*!40000 ALTER TABLE `RPU` DISABLE KEYS */;
/*!40000 ALTER TABLE `RPU` ENABLE KEYS */;

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
  CONSTRAINT `fk_Session_KnowledgeLvl` FOREIGN KEY (`idKnowledegeLvl`) REFERENCES `KnowledgeLvl` (`idKnowledgeLvl`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_Language` FOREIGN KEY (`idLanguage`) REFERENCES `Language` (`idLanguage`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_RPU` FOREIGN KEY (`idRPU`) REFERENCES `RPU` (`idRPU`) ON DELETE NO ACTION ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_Transaction` FOREIGN KEY (`idTransaction`) REFERENCES `Transaction` (`idTransaction`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Clients session, references: client, transaction, rpu.';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Session`
--

/*!40000 ALTER TABLE `Session` DISABLE KEYS */;
/*!40000 ALTER TABLE `Session` ENABLE KEYS */;

--
-- Table structure for table `Transaction`
--

DROP TABLE IF EXISTS `Transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Transaction` (
  `idTransaction` int(11) NOT NULL AUTO_INCREMENT,
  `transaction` varchar(20) NOT NULL,
  `idPaymentType` int(11) NOT NULL,
  `date` date NOT NULL,
  `time` time NOT NULL,
  PRIMARY KEY (`idTransaction`),
  KEY `fk_Transaction_PaymentType_idx` (`idPaymentType`),
  CONSTRAINT `fk_Transaction_PaymentType` FOREIGN KEY (`idPaymentType`) REFERENCES `PaymentType` (`idPaymentType`) ON DELETE NO ACTION ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Stores transaction details';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Transaction`
--

/*!40000 ALTER TABLE `Transaction` DISABLE KEYS */;
/*!40000 ALTER TABLE `Transaction` ENABLE KEYS */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-02-08 13:57:48
