/*M!999999\- enable the sandbox mode */ 
-- MariaDB dump 10.19-11.5.2-MariaDB, for osx10.19 (arm64)
--
-- Host: localhost    Database: neurobox
-- ------------------------------------------------------
-- Server version	9.0.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*M!100616 SET @OLD_NOTE_VERBOSITY=@@NOTE_VERBOSITY, NOTE_VERBOSITY=0 */;

--
-- Table structure for table `especialista`
--

DROP TABLE IF EXISTS `especialista`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `especialista` (
  `ID_Especialista` int NOT NULL AUTO_INCREMENT,
  `Correo Electrónico` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `Nombre` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `Especialidad` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
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
  `ID_Juego` int NOT NULL AUTO_INCREMENT,
  `Propósito` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `Nombre` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `Notas adicionales` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `Duracion` time DEFAULT NULL,
  `Fecha` date DEFAULT NULL,
  PRIMARY KEY (`ID_Juego`)
) ENGINE=InnoDB AUTO_INCREMENT=109 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
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
(23,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(24,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(25,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(26,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(27,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(28,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(29,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(30,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(31,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(32,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(33,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(34,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(35,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(36,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(37,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(38,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(39,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(40,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(41,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(42,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(43,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(44,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(45,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(46,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(47,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(48,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(49,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(50,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(51,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(52,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(53,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(54,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(55,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(56,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(57,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(58,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(59,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(60,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(61,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(62,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(63,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(64,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(65,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(66,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(67,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(68,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(69,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(70,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(71,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(72,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(73,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(74,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(75,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(76,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(77,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(78,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(79,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(80,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(81,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(82,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(83,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(84,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(85,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(86,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(87,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(88,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(89,'Coordinación mano ojo.','Lotería','Sin notas',NULL,NULL),
(90,'Coordinación mano ojo.','Lotería','Sin notas.',NULL,NULL),
(91,'Coordinación mano ojo.','Lotería','Sin notas.',NULL,NULL),
(92,'Tiempo de reacción.','Cowboy','Sin notas.',NULL,NULL),
(93,'Tiempo de reacción.','Cowboy','Sin notas.',NULL,NULL),
(94,'Coordinación mano ojo.','Lotería','Sin notas.',NULL,NULL),
(95,'Tiempo de reacción.','Cowboy','Sin notas.',NULL,NULL),
(96,'Tiempo de reacción.','Cowboy','Sin notas.','00:00:17',NULL),
(97,'Tiempo de reacción.','Cowboy','Sin notas.','00:00:03','2024-11-27'),
(98,'Tiempo de reacción.','Cowboy','Sin notas.','00:00:09','2024-11-27'),
(99,'Coordinación mano ojo.','Lotería','Sin notas.','00:00:22','2024-11-27'),
(100,'Coordinación mano ojo.','Lotería','Sin notas.',NULL,'2024-11-27'),
(101,'Coordinación mano ojo.','Lotería','Sin notas.',NULL,'2024-11-27'),
(102,'Tiempo de reacción.','Cowboy','Sin notas.','00:00:06','2024-11-27'),
(103,'Tiempo de reacción.','Cowboy','Sin notas.',NULL,'2024-11-27'),
(104,'Tiempo de reacción.','Cowboy','Sin notas.',NULL,'2024-11-27'),
(105,'Tiempo de reacción.','Cowboy','Sin notas.',NULL,'2024-11-27'),
(106,'Tiempo de reacción.','Cowboy','Sin notas.','00:00:02','2024-11-27'),
(107,'Tiempo de reacción.','Cowboy','Sin notas.','00:00:10','2024-11-27'),
(108,'Coordinación mano ojo.','Lotería','Sin notas.',NULL,'2024-11-27');
/*!40000 ALTER TABLE `juego` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `paciente`
--

DROP TABLE IF EXISTS `paciente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paciente` (
  `ID_Paciente` int NOT NULL AUTO_INCREMENT,
  `Nombre` varchar(20) COLLATE utf8mb4_general_ci NOT NULL,
  `Edad` int NOT NULL,
  `Diagnóstico` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `Dirección` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
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
  `ID_Paciente` int NOT NULL,
  `ID_Especialista` int NOT NULL,
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
  `ID_Paciente` int NOT NULL,
  `ID_Juego` int NOT NULL,
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
(1001,54),
(1001,55),
(1001,56),
(1001,57),
(1001,58),
(1001,59),
(1001,60),
(1001,61),
(1001,62),
(1001,63),
(1001,64),
(1001,65),
(1001,66),
(1001,67),
(1001,68),
(1001,69),
(1001,70),
(1001,71),
(1001,72),
(1001,73),
(1001,74),
(1001,75),
(1001,76),
(1001,77),
(1001,78),
(1001,79),
(1001,80),
(1001,81),
(1001,82),
(1001,83),
(1001,84),
(1001,85),
(1001,86),
(1001,87),
(1001,88),
(1001,89),
(1001,90),
(1001,91),
(1001,92),
(1001,93),
(1001,94),
(1001,95),
(1001,96),
(1001,97),
(1001,98),
(1001,99),
(1001,100),
(1001,101),
(1001,102),
(1001,103),
(1001,104),
(1001,105),
(1001,106),
(1001,107),
(1001,108);
/*!40000 ALTER TABLE `paciente_a_juego` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `paciente_a_resultado`
--

DROP TABLE IF EXISTS `paciente_a_resultado`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `paciente_a_resultado` (
  `ID_Paciente` int NOT NULL,
  `ID_Resultado` int NOT NULL,
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
(1001,54),
(1001,55),
(1001,56),
(1001,57),
(1001,58),
(1001,59),
(1001,60),
(1001,61),
(1001,62),
(1001,63),
(1001,64),
(1001,65),
(1001,66),
(1001,67),
(1001,68),
(1001,69),
(1001,70),
(1001,71),
(1001,72),
(1001,73),
(1001,74),
(1001,75),
(1001,76),
(1001,77),
(1001,78),
(1001,79),
(1001,80),
(1001,81),
(1001,82),
(1001,83),
(1001,84),
(1001,85),
(1001,86),
(1001,87),
(1001,88),
(1001,89),
(1001,90),
(1001,91),
(1001,92),
(1001,93),
(1001,94),
(1001,95),
(1001,96),
(1001,97),
(1001,98),
(1001,99),
(1001,100),
(1001,101),
(1001,102),
(1001,103),
(1001,104),
(1001,105),
(1001,106),
(1001,107),
(1001,108),
(1001,109),
(1001,110),
(1001,111),
(1001,112),
(1001,113),
(1001,114),
(1001,115),
(1001,116),
(1001,117),
(1001,118),
(1001,119),
(1001,120),
(1001,121),
(1001,122),
(1001,123),
(1001,124),
(1001,125),
(1001,126),
(1001,127),
(1001,128),
(1001,129),
(1001,130),
(1001,131),
(1001,132),
(1001,133),
(1001,134),
(1001,135),
(1001,136),
(1001,137),
(1001,138),
(1001,139),
(1001,140),
(1001,141),
(1001,142),
(1001,143),
(1001,144),
(1001,145),
(1001,146),
(1001,147),
(1001,148),
(1001,149),
(1001,150),
(1001,151),
(1001,152),
(1001,153),
(1001,154),
(1001,155),
(1001,156),
(1001,157),
(1001,158),
(1001,159),
(1001,160),
(1001,161),
(1001,162),
(1001,163),
(1001,164),
(1001,165),
(1001,166),
(1001,167),
(1001,168),
(1001,169),
(1001,170),
(1001,171),
(1001,172),
(1001,173),
(1001,174),
(1001,175),
(1001,176),
(1001,177),
(1001,178),
(1001,179),
(1001,180),
(1001,181),
(1001,182),
(1001,183),
(1001,184),
(1001,185),
(1001,186),
(1001,187),
(1001,188),
(1001,189),
(1001,190),
(1001,191),
(1001,192),
(1001,193),
(1001,194),
(1001,195),
(1001,196),
(1001,197),
(1001,198),
(1001,199),
(1001,200),
(1001,201),
(1001,202);
/*!40000 ALTER TABLE `paciente_a_resultado` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `resultados`
--

DROP TABLE IF EXISTS `resultados`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `resultados` (
  `ID_Resultado` int NOT NULL AUTO_INCREMENT,
  `Puntuación` double NOT NULL,
  `ID_Juego` int NOT NULL,
  `Tipo` varchar(50) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`ID_Resultado`),
  KEY `resultados_ibfk_1` (`ID_Juego`),
  CONSTRAINT `resultados_ibfk_1` FOREIGN KEY (`ID_Juego`) REFERENCES `juego` (`ID_Juego`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=203 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `resultados`
--

LOCK TABLES `resultados` WRITE;
/*!40000 ALTER TABLE `resultados` DISABLE KEYS */;
INSERT INTO `resultados` VALUES
(1,2.4210526943206787,4,'0'),
(2,3.1052632331848145,4,'0'),
(3,1.456140398979187,4,'0'),
(4,2.2280702590942383,4,'0'),
(5,1.9298245906829834,4,'0'),
(6,1.4736841917037964,4,'0'),
(7,1.5964912176132202,4,'0'),
(8,1.1403508186340332,4,'0'),
(9,2.2456140518188477,4,'0'),
(10,1.3508771657943726,4,'0'),
(11,1.3508771657943726,4,'0'),
(12,1.5789474248886108,4,'0'),
(13,2.4561402797698975,16,'1'),
(14,2.5964913368225098,16,'1'),
(15,2.6666667461395264,18,'1'),
(16,1.0701754093170166,18,'1'),
(17,1.5263158082962036,18,'1'),
(18,1.736842155456543,18,'1'),
(19,1.017543911933899,18,'1'),
(20,1.8771929740905762,18,'1'),
(21,1.3157894611358643,18,'1'),
(22,1.0701754093170166,18,'1'),
(23,2.21052622795105,18,'1'),
(24,1.7719298601150513,18,'1'),
(25,1.4912281036376953,18,'1'),
(26,1.719298243522644,18,'1'),
(27,3.824561357498169,20,'1'),
(28,1.6315789222717285,20,'1'),
(29,1.7543859481811523,20,'1'),
(30,2.4035086631774902,20,'1'),
(31,0.8771929740905762,20,'1'),
(32,1.4912281036376953,20,'1'),
(33,1.7894736528396606,20,'1'),
(34,0.7543859481811523,20,'1'),
(35,1.2982456684112549,20,'1'),
(36,2.912280797958374,20,'1'),
(37,1.5964912176132202,20,'1'),
(38,1.543859601020813,20,'1'),
(39,1.6842105388641357,58,'1'),
(40,1.456140398979187,58,'1'),
(41,2.5789473056793213,58,'1'),
(42,1.6140351295471191,58,'1'),
(43,2.21052622795105,58,'1'),
(44,1.7017543315887451,58,'1'),
(45,1.1929824352264404,58,'1'),
(46,2.2456140518188477,58,'1'),
(47,1.3859648704528809,58,'1'),
(48,2.5964913368225098,58,'1'),
(49,0.8947368264198303,58,'1'),
(50,2.21052622795105,58,'1'),
(51,1.5964912176132202,60,'1'),
(52,2.8421051502227783,62,'1'),
(53,2.035087823867798,62,'1'),
(54,1.4912281036376953,62,'1'),
(55,1.2105263471603394,62,'1'),
(56,1.3333333730697632,62,'1'),
(57,1.982456088066101,62,'1'),
(58,1.9122806787490845,62,'1'),
(59,1.1228070259094238,62,'1'),
(60,1.7719298601150513,62,'1'),
(61,1.6315789222717285,62,'1'),
(62,2.2807016372680664,62,'1'),
(63,5.491228103637695,62,'1'),
(64,16.40350914001465,72,'1'),
(65,2.5087718963623047,72,'1'),
(66,1.3157894611358643,72,'1'),
(67,2.298245668411255,72,'1'),
(68,1.6666666269302368,72,'1'),
(69,2.5789473056793213,72,'1'),
(70,2.912280797958374,72,'1'),
(71,2.473684310913086,72,'1'),
(72,1.8596491813659668,72,'1'),
(73,1.438596487045288,72,'1'),
(74,0.9298245906829834,72,'1'),
(75,1.4210525751113892,72,'1'),
(76,8.473684310913086,76,'1'),
(77,1.8771929740905762,76,'1'),
(78,1.2105263471603394,76,'1'),
(79,0.9122806787490845,76,'1'),
(80,2.087719202041626,76,'1'),
(81,1.3333333730697632,76,'1'),
(82,1.7543859481811523,76,'1'),
(83,1.3333333730697632,76,'1'),
(84,1.4736841917037964,76,'1'),
(85,2.0701754093170166,76,'1'),
(86,0.8245614171028137,76,'1'),
(87,1.0350877046585083,76,'1'),
(88,7.473684310913086,77,'1'),
(89,1.1929824352264404,77,'1'),
(90,1.6842105388641357,77,'1'),
(91,2.140350818634033,77,'1'),
(92,2.122807025909424,77,'1'),
(93,1.3157894611358643,77,'1'),
(94,1.2982456684112549,77,'1'),
(95,1.736842155456543,77,'1'),
(96,1.2280701398849487,77,'1'),
(97,1.3859648704528809,77,'1'),
(98,0.9649122953414917,77,'1'),
(99,0.7368420958518982,77,'1'),
(100,5.824561595916748,78,'1'),
(101,1.7017543315887451,78,'1'),
(102,1.280701756477356,78,'1'),
(103,1.6842105388641357,78,'1'),
(104,45.140350341796875,78,'1'),
(105,1.894736886024475,78,'1'),
(106,1.6140351295471191,78,'1'),
(107,0.859649121761322,78,'1'),
(108,3.736842155456543,78,'1'),
(109,1.719298243522644,78,'1'),
(110,2.5087718963623047,78,'1'),
(111,1.0350877046585083,78,'1'),
(112,4.526315689086914,79,'1'),
(113,1.719298243522644,79,'1'),
(114,1.894736886024475,79,'1'),
(115,1.438596487045288,79,'1'),
(116,1.8070175647735596,79,'1'),
(117,1.2105263471603394,79,'1'),
(118,1.5789474248886108,79,'1'),
(119,1.3684210777282715,79,'1'),
(120,0.9473684430122375,79,'1'),
(121,2.6842105388641357,79,'1'),
(122,1.456140398979187,79,'1'),
(123,2.859649181365967,79,'1'),
(124,85.7368392944336,81,'1'),
(125,4.087719440460205,81,'1'),
(126,1.6140351295471191,81,'1'),
(127,1.9298245906829834,81,'1'),
(128,1.6315789222717285,81,'1'),
(129,1.561403512954712,81,'1'),
(130,1.4035087823867798,81,'1'),
(131,2.1929824352264404,81,'1'),
(132,1.5263158082962036,81,'1'),
(133,1.8596491813659668,81,'1'),
(134,1.2456140518188477,81,'1'),
(135,1.0350877046585083,81,'1'),
(136,11.859648704528809,82,'1'),
(137,1.017543911933899,82,'1'),
(138,1.105263113975525,82,'1'),
(139,2.0701754093170166,82,'1'),
(140,1.3859648704528809,82,'1'),
(141,1.7543859481811523,82,'1'),
(142,1.280701756477356,82,'1'),
(143,1.894736886024475,82,'1'),
(144,1.456140398979187,82,'1'),
(145,1.6842105388641357,82,'1'),
(146,1.1228070259094238,82,'1'),
(147,1.017543911933899,82,'1'),
(148,22.140350341796875,89,'1'),
(149,1.5263158082962036,89,'1'),
(150,1.8771929740905762,89,'1'),
(151,2.350877285003662,89,'1'),
(152,1.2280701398849487,89,'1'),
(153,1.280701756477356,89,'1'),
(154,1.280701756477356,89,'1'),
(155,1.543859601020813,89,'1'),
(156,1.1403508186340332,89,'1'),
(157,1.4736841917037964,89,'1'),
(158,1.105263113975525,89,'1'),
(159,1.9649122953414917,89,'1'),
(160,6.59649133682251,90,'1'),
(161,1.7017543315887451,90,'1'),
(162,1.3859648704528809,90,'1'),
(163,1.4736841917037964,90,'1'),
(164,2.0526316165924072,90,'1'),
(165,2.6666667461395264,90,'1'),
(166,3.8947367668151855,90,'1'),
(167,0.3214285671710968,92,'1'),
(168,0.4285714328289032,92,'1'),
(169,0.375,92,'1'),
(170,0.375,93,'tiempo de reacción'),
(171,0.375,93,'tiempo de reacción promedio'),
(172,12.491228103637695,94,'tiempo de selección correcta'),
(173,1.0701754093170166,94,'tiempo de selección correcta'),
(174,21.40350914001465,94,'tiempo de selección correcta'),
(175,1.1578947305679321,94,'tiempo de selección correcta'),
(176,1.3508771657943726,94,'tiempo de selección correcta'),
(177,5.824561595916748,94,'tiempo de selección correcta'),
(178,0.3392857015132904,95,'tiempo de reacción'),
(179,0.3392857015132904,95,'tiempo de reacción'),
(180,0.3392857015132904,95,'tiempo de reacción promedio'),
(181,0.3928571343421936,96,'tiempo de reacción'),
(182,0.5535714030265808,96,'tiempo de reacción'),
(183,0.4732142686843872,96,'tiempo de reacción promedio'),
(184,0.3928571343421936,98,'tiempo de reacción'),
(185,0.3928571343421936,98,'tiempo de reacción promedio'),
(186,2.4035086631774902,99,'tiempo de selección correcta'),
(187,3,99,'tiempo de selección correcta'),
(188,1.6491228342056274,99,'tiempo de selección correcta'),
(189,2.5789473056793213,99,'tiempo de selección correcta'),
(190,2.561403512954712,99,'tiempo de selección correcta'),
(191,1.3508771657943726,99,'tiempo de selección correcta'),
(192,1.9122806787490845,99,'tiempo de selección correcta'),
(193,1.7017543315887451,99,'tiempo de selección correcta'),
(194,1.561403512954712,99,'tiempo de selección correcta'),
(195,1.438596487045288,99,'tiempo de selección correcta'),
(196,1.2105263471603394,99,'tiempo de selección correcta'),
(197,0,99,'errores totales'),
(198,1.175438642501831,99,'tiempo de selección correcta'),
(199,0.2857142984867096,107,'tiempo de reacción'),
(200,0.2857142984867096,107,'tiempo de reacción promedio'),
(201,36.543861389160156,108,'tiempo de selección correcta'),
(202,2.6842105388641357,108,'tiempo de selección correcta');
/*!40000 ALTER TABLE `resultados` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tutor`
--

DROP TABLE IF EXISTS `tutor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tutor` (
  `ID_Paciente` int NOT NULL,
  `Nombre` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
  `Edad` int NOT NULL,
  `Correo_Electronico` varchar(50) COLLATE utf8mb4_general_ci NOT NULL,
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
/*M!100616 SET NOTE_VERBOSITY=@OLD_NOTE_VERBOSITY */;

-- Dump completed on 2024-11-28  1:07:44
