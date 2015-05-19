SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `ESD` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `ESD` ;

-- -----------------------------------------------------
-- Table `ESD`.`Client`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ESD`.`Client` (
  `idClient` INT NOT NULL AUTO_INCREMENT,
  `forename` VARCHAR(50) NOT NULL,
  `surname` VARCHAR(50) NOT NULL,
  `mobilePhone` VARCHAR(20) NOT NULL,
  `address` VARCHAR(300) NOT NULL,
  PRIMARY KEY (`idClient`))
ENGINE = InnoDB
COMMENT = 'Client Details';


-- -----------------------------------------------------
-- Table `ESD`.`Transaction`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ESD`.`Transaction` (
  `idTransaction` INT NOT NULL AUTO_INCREMENT,
  `transaction` VARCHAR(20) NULL,
  `paymentType` VARCHAR(30) NULL,
  PRIMARY KEY (`idTransaction`))
ENGINE = InnoDB
COMMENT = 'Stores transaction details';


-- -----------------------------------------------------
-- Table `ESD`.`Language`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ESD`.`Language` (
  `idLanguage` INT NOT NULL AUTO_INCREMENT,
  `language` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`idLanguage`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ESD`.`KnowledgeLvl`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ESD`.`KnowledgeLvl` (
  `idKnowledgeLvl` INT NOT NULL AUTO_INCREMENT,
  `knowledgeLvl` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`idKnowledgeLvl`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ESD`.`Session`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `ESD`.`Session` (
  `idSession` INT NOT NULL AUTO_INCREMENT,
  `idClient` INT NOT NULL,
  `idTransaction` INT NULL,
  `RPU` VARCHAR(4) NOT NULL,
  `timeOut` TIMESTAMP NULL,
  `idLanguage` INT NULL,
  `idKnowledegeLvl` INT NULL,
  `timeIn` TIMESTAMP NOT NULL DEFAULT NOW(),
  PRIMARY KEY (`idSession`),
  INDEX `fk_Session_Client_idx` (`idClient` ASC),
  INDEX `fk_Session_Transaction_idx` (`idTransaction` ASC),
  INDEX `fk_Session_Language_idx` (`idLanguage` ASC),
  INDEX `fk_Session_KnowledgeLvl_idx` (`idKnowledegeLvl` ASC),
  CONSTRAINT `fk_Session_Client`
    FOREIGN KEY (`idClient`)
    REFERENCES `ESD`.`Client` (`idClient`)
    ON DELETE NO ACTION
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_Transaction`
    FOREIGN KEY (`idTransaction`)
    REFERENCES `ESD`.`Transaction` (`idTransaction`)
    ON DELETE NO ACTION
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_Language`
    FOREIGN KEY (`idLanguage`)
    REFERENCES `ESD`.`Language` (`idLanguage`)
    ON DELETE NO ACTION
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Session_KnowledgeLvl`
    FOREIGN KEY (`idKnowledegeLvl`)
    REFERENCES `ESD`.`KnowledgeLvl` (`idKnowledgeLvl`)
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB
COMMENT = 'Clients session, references: client, transaction, rpu.';


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
