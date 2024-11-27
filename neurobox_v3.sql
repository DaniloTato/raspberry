-- MariaDB dump 10.19  Distrib 10.11.6-MariaDB, for debian-linux-gnu (aarch64)
--
-- Host: localhost    Database: neurobox
-- ------------------------------------------------------
-- Server version	10.11.6-MariaDB-0+deb12u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `especialista`
--

DROP TABLE IF EXISTS `especialista`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `especialista` (
  `ID_Especialista` int(11) NOT NULL AUTO_INCREMENT,
  `Correo Electrónico` varchar(50) NOT NULL,
  `Nombre` varchar(50) NOT NULL,
  `Especialidad` varchar(50) NOT NULL,
  PRIMARY KEY (`ID_Especialista`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `especialista`
--

LOCK TABLES `especialista` WRITE;
/*!40000 ALTER TABLE `especialista` DISABLE KEYS */;
/*!40000 ALTER TABLE `especialista` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `juego`
--

DROP TABLE IF EXISTS `juego`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `juego` (
  `ID_Juego` int(11) NOT NULL AUTO_INCREMENT,
  `Propósito` varchar(50) NOT NULL,
  `Nombre` varchar(50) NOT NULL,
  `Notas adicionales` varchar(50) NOT NULL,
  `Duracion` int(11) DEFAULT NULL,
  `Fecha` date DEFAULT NULL,
  PRIMARY KEY (`ID_Juego`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `juego`
--

LOCK TABLES `juego` WRITE;
/*!40000 ALTER TABLE `juego` DISABLE KEYS */;
INSERT INTO `juego` VALUES
(1,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(2,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(3,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(4,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(5,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(6,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(7,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(8,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(9,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(10,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(11,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(12,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(13,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(14,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(15,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(16,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(17,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(18,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(19,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(20,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(21,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(22,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(23,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL);
/*!40000 ALTER TABLE `juego` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `paciente`
--

DROP TABLE IF EXISTS `paciente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paciente` (
  `ID_Paciente` int(11) NOT NULL AUTO_INCREMENT,
  `Nombre` varchar(20) NOT NULL,
  `Edad` int(11) NOT NULL,
  `Diagnóstico` varchar(50) NOT NULL,
  `Dirección` varchar(50) NOT NULL,
  PRIMARY KEY (`ID_Paciente`)
) ENGINE=InnoDB AUTO_INCREMENT=1002 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paciente`
--

LOCK TABLES `paciente` WRITE;
/*!40000 ALTER TABLE `paciente` DISABLE KEYS */;
INSERT INTO `paciente` VALUES
(1001,'Default Name',0,'Default Diagnosis','Default Address');
/*!40000 ALTER TABLE `paciente` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `paciente_a_especialista`
--

DROP TABLE IF EXISTS `paciente_a_especialista`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paciente_a_especialista` (
  `ID_Paciente` int(11) NOT NULL,
  `ID_Especialista` int(11) NOT NULL,
  PRIMARY KEY (`ID_Paciente`,`ID_Especialista`),
  KEY `paciente_a_especialista_ibfk_1` (`ID_Especialista`),
  CONSTRAINT `paciente_a_especialista_ibfk_1` FOREIGN KEY (`ID_Especialista`) REFERENCES `especialista` (`ID_Especialista`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `paciente_a_especialista_ibfk_2` FOREIGN KEY (`ID_Paciente`) REFERENCES `paciente` (`ID_Paciente`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paciente_a_especialista`
--

LOCK TABLES `paciente_a_especialista` WRITE;
/*!40000 ALTER TABLE `paciente_a_especialista` DISABLE KEYS */;
/*!40000 ALTER TABLE `paciente_a_especialista` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `paciente_a_juego`
--

DROP TABLE IF EXISTS `paciente_a_juego`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paciente_a_juego` (
  `ID_Paciente` int(11) NOT NULL,
  `ID_Juego` int(11) NOT NULL,
  PRIMARY KEY (`ID_Paciente`,`ID_Juego`),
  KEY `paciente_a_juego_ibfk_1` (`ID_Juego`),
  CONSTRAINT `paciente_a_juego_ibfk_1` FOREIGN KEY (`ID_Juego`) REFERENCES `juego` (`ID_Juego`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `paciente_a_juego_ibfk_2` FOREIGN KEY (`ID_Paciente`) REFERENCES `paciente` (`ID_Paciente`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paciente_a_juego`
--

LOCK TABLES `paciente_a_juego` WRITE;
/*!40000 ALTER TABLE `paciente_a_juego` DISABLE KEYS */;
INSERT INTO `paciente_a_juego` VALUES
(1001,3),
(1001,4),
(1001,5),
(1001,6),
(1001,7),
(1001,8),
(1001,9),
(1001,10),
(1001,11),
(1001,12),
(1001,13),
(1001,14),
(1001,15),
(1001,16),
(1001,17),
(1001,18),
(1001,19),
(1001,20),
(1001,21),
(1001,22),
(1001,23);
/*!40000 ALTER TABLE `paciente_a_juego` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `paciente_a_resultado`
--

DROP TABLE IF EXISTS `paciente_a_resultado`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paciente_a_resultado` (
  `ID_Paciente` int(11) NOT NULL,
  `ID_Resultado` int(11) NOT NULL,
  PRIMARY KEY (`ID_Paciente`,`ID_Resultado`),
  KEY `paciente_a_resultado_ibfk_1` (`ID_Resultado`),
  CONSTRAINT `paciente_a_resultado_ibfk_1` FOREIGN KEY (`ID_Resultado`) REFERENCES `resultados` (`ID_Resultado`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `paciente_a_resultado_ibfk_2` FOREIGN KEY (`ID_Paciente`) REFERENCES `paciente` (`ID_Paciente`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `paciente_a_resultado`
--

LOCK TABLES `paciente_a_resultado` WRITE;
/*!40000 ALTER TABLE `paciente_a_resultado` DISABLE KEYS */;
INSERT INTO `paciente_a_resultado` VALUES
(1001,1),
(1001,2),
(1001,3),
(1001,4),
(1001,5),
(1001,6),
(1001,7),
(1001,8),
(1001,9),
(1001,10),
(1001,11),
(1001,12),
(1001,13),
(1001,14),
(1001,15),
(1001,16),
(1001,17),
(1001,18),
(1001,19),
(1001,20),
(1001,21),
(1001,22),
(1001,23),
(1001,24),
(1001,25),
(1001,26),
(1001,27),
(1001,28),
(1001,29),
(1001,30),
(1001,31),
(1001,32),
(1001,33),
(1001,34),
(1001,35),
(1001,36),
(1001,37),
(1001,38),
(1001,39),
(1001,40),
(1001,41),
(1001,42),
(1001,43),
(1001,44),
(1001,45),
(1001,46),
(1001,47),
(1001,48),
(1001,49),
(1001,50),
(1001,51),
(1001,52),
(1001,53),
(1001,54);
/*!40000 ALTER TABLE `paciente_a_resultado` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `resultados`
--

DROP TABLE IF EXISTS `resultados`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `resultados` (
  `ID_Resultado` int(11) NOT NULL AUTO_INCREMENT,
  `Puntuación` double NOT NULL,
  `ID_Juego` int(11) NOT NULL,
  `Tipo` int(11) NOT NULL,
  PRIMARY KEY (`ID_Resultado`),
  KEY `resultados_ibfk_1` (`ID_Juego`),
  CONSTRAINT `resultados_ibfk_1` FOREIGN KEY (`ID_Juego`) REFERENCES `juego` (`ID_Juego`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=55 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `resultados`
--

LOCK TABLES `resultados` WRITE;
/*!40000 ALTER TABLE `resultados` DISABLE KEYS */;
INSERT INTO `resultados` VALUES
(1,2.4210526943206787,4,0),
(2,3.1052632331848145,4,0),
(3,1.456140398979187,4,0),
(4,2.2280702590942383,4,0),
(5,1.9298245906829834,4,0),
(6,1.4736841917037964,4,0),
(7,1.5964912176132202,4,0),
(8,1.1403508186340332,4,0),
(9,2.2456140518188477,4,0),
(10,1.3508771657943726,4,0),
(11,1.3508771657943726,4,0),
(12,1.5789474248886108,4,0),
(13,2.4561402797698975,16,1),
(14,2.5964913368225098,16,1),
(15,2.6666667461395264,18,1),
(16,1.0701754093170166,18,1),
(17,1.5263158082962036,18,1),
(18,1.736842155456543,18,1),
(19,1.017543911933899,18,1),
(20,1.8771929740905762,18,1),
(21,1.3157894611358643,18,1),
(22,1.0701754093170166,18,1),
(23,2.21052622795105,18,1),
(24,1.7719298601150513,18,1),
(25,1.4912281036376953,18,1),
(26,1.719298243522644,18,1),
(27,3.824561357498169,20,1),
(28,1.6315789222717285,20,1),
(29,1.7543859481811523,20,1),
(30,2.4035086631774902,20,1),
(31,0.8771929740905762,20,1),
(32,1.4912281036376953,20,1),
(33,1.7894736528396606,20,1),
(34,0.7543859481811523,20,1),
(35,1.2982456684112549,20,1),
(36,2.912280797958374,20,1),
(37,1.5964912176132202,20,1),
(38,1.543859601020813,20,1),
(39,4.789473533630371,22,1),
(40,2.385964870452881,22,1),
(41,2.736842155456543,22,1),
(42,1.4210525751113892,22,1),
(43,1.8771929740905762,22,1),
(44,3.3333332538604736,22,1),
(45,1.1578947305679321,22,1),
(46,7.228070259094238,22,1),
(47,2.0701754093170166,22,1),
(48,2.2280702590942383,22,1),
(49,1.456140398979187,22,1),
(50,1.2456140518188477,22,1),
(51,1.9298245906829834,23,1),
(52,2.4210526943206787,23,1),
(53,1.5087718963623047,23,1),
(54,1.9298245906829834,23,1);
/*!40000 ALTER TABLE `resultados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `testing`
--

DROP TABLE IF EXISTS `testing`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `testing` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `fecha` date NOT NULL,
  `puntaje` double DEFAULT NULL,
  `juego` varchar(255) NOT NULL,
  `nivel` int(11) DEFAULT NULL,
  `tipo` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `testing`
--

LOCK TABLES `testing` WRITE;
/*!40000 ALTER TABLE `testing` DISABLE KEYS */;
INSERT INTO `testing` VALUES
(1,'2024-11-17',4.684210300445557,'lotería',0,'tiempo_de_reacción'),
(2,'2024-11-17',7.614035129547119,'lotería',0,'tiempo_de_reacción'),
(3,'2024-11-17',2.2807016372680664,'lotería',0,'tiempo_de_reacción'),
(4,'2024-11-17',1.6140351295471191,'lotería',0,'tiempo_de_reacción'),
(5,'2024-11-17',41.77193069458008,'lotería',0,'tiempo_de_reacción'),
(6,'2024-11-17',3.3157894611358643,'lotería',0,'tiempo_de_reacción'),
(7,'2024-11-17',2.21052622795105,'lotería',0,'tiempo_de_reacción'),
(8,'2024-11-17',1.6315789222717285,'lotería',0,'tiempo_de_reacción'),
(9,'2024-11-17',2.6315789222717285,'lotería',0,'tiempo_de_reacción'),
(10,'2024-11-17',1.4912281036376953,'lotería',0,'tiempo_de_reacción'),
(11,'2024-11-17',1.6140351295471191,'lotería',0,'tiempo_de_reacción'),
(12,'2024-11-17',1.5964912176132202,'lotería',0,'tiempo_de_reacción');
/*!40000 ALTER TABLE `testing` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tutor`
--

DROP TABLE IF EXISTS `tutor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tutor` (
  `ID_Paciente` int(11) NOT NULL,
  `Nombre` varchar(50) NOT NULL,
  `Edad` int(11) NOT NULL,
  `Correo_Electronico` varchar(50) NOT NULL,
  PRIMARY KEY (`ID_Paciente`),
  CONSTRAINT `tutor_ibfk_1` FOREIGN KEY (`ID_Paciente`) REFERENCES `paciente` (`ID_Paciente`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tutor`
--

LOCK TABLES `tutor` WRITE;
/*!40000 ALTER TABLE `tutor` DISABLE KEYS */;
/*!40000 ALTER TABLE `tutor` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-11-27 10:20:19
