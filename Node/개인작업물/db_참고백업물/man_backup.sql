-- MySQL dump 10.13  Distrib 5.7.27, for Linux (x86_64)
--
-- Host: localhost    Database: theman_data
-- ------------------------------------------------------
-- Server version	5.7.27-0ubuntu0.18.04.1

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
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account` (
  `member_id` int(11) NOT NULL AUTO_INCREMENT,
  `device_id` varchar(64) NOT NULL COMMENT 'diviceID',
  `auth_type` tinyint(1) NOT NULL DEFAULT '0' COMMENT '인증 종류(None: 0, FaceBook: 1,Google: 2,GameCenter: 3,Device: 4)',
  `status` tinyint(1) DEFAULT '0' COMMENT '플레이어 등록 상태(0:미등록, 1:등록)',
  `authority` tinyint(2) DEFAULT '1' COMMENT '권한(1:일반, 2:운영자)',
  `block` tinyint(1) DEFAULT '0' COMMENT '계정 블럭(0:일반, 1:블럭상태)',
  `session_id` varchar(255) DEFAULT NULL COMMENT '세션 아이디',
  `ipaddr` varchar(20) DEFAULT NULL COMMENT '접속 아이피',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`member_id`),
  UNIQUE KEY `idx_divice_uid` (`device_id`,`auth_type`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,'114181832929332816077',2,1,0,0,'OqUrj4bH3JUii-4hhCvEPgmiOSE9ZSLq','218.151.231.194','2019-09-19 13:13:59'),(2,'06c4ad58c1e143cc658375a726b357025521353f_0000000000000000',4,1,0,0,'ghtiMX6lnNxVjwiTEVEA5eqTA7kXAMtk','218.151.231.194','2019-09-19 13:14:58'),(3,'75d70884e7d30ff5a53f4bc01c854517eb06547a_0000000000000000',4,1,0,0,'KZv9LT8fOwNEdd6msab0hn4oBLiX7HoI','218.151.231.194','2019-09-19 13:15:24'),(4,'a4b27b3e150092332f333975a3d00669_83191f977802f523',4,1,0,0,'8crB8hzKeGDJamWHf7sm9X28EhiU5OUi','218.151.231.194','2019-09-19 13:17:06'),(5,'000',2,1,0,0,'PEiCDoUce0O7dz0KIuSwyn5F5S1VA9GJ','218.151.231.194','2019-09-19 13:21:24'),(6,'sfgfdgdgdg',2,1,0,0,'51aM6f3edH05wJOiUW1c4TwOraoV6YD9','218.151.231.194','2019-09-19 13:32:54'),(7,'45674567457',2,1,0,0,'B21p_zgp2mJ3qTx8vio7gA1Nmm-90FH-','218.151.231.194','2019-09-19 13:37:43'),(8,'1111',2,1,0,0,'B21p_zgp2mJ3qTx8vio7gA1Nmm-90FH-','218.151.231.194','2019-09-19 13:38:59'),(9,'67b168e79019e8248e606ea1dc66513525f15da0_0000000000000000',4,1,0,0,'hjYzbBnU4N-BRtFgcY0zG141gGXyt5Bo','218.151.231.194','2019-09-19 13:47:12'),(10,'00',2,0,0,0,'vZRfXEpv_7qiSOBmyzMH5pFkceEaphWY','218.151.231.194','2019-09-19 15:07:39'),(11,'8631789c73f8d583abe7fa04f68b1178_b9821d1a20c425a0',4,1,0,0,'u340uJOpt0l2Ht8stAt5FhY2D599Ihcs','218.151.231.194','2019-09-19 15:13:01'),(12,'105596647659599996066',2,1,0,0,'LwSDsEAtBpv_X2pFTCMLSZ7FTohgHktV','218.151.231.194','2019-09-19 15:56:54'),(13,'c4fee800c3ebf29cb586f9cb91a811e6_ccb09bdbb6dec245',4,1,0,0,'0ULnufWc9x_h1CTg8j36hCtvLZ43GUqm','218.151.231.194','2019-09-19 17:27:24'),(14,'110689108786051755615',2,1,0,0,'m_tVkVHwC5vWTqdKq59OUiIe0kX5n0Iy','218.151.231.194','2019-09-19 17:40:45'),(15,'28569570e9aaf2398e55c302df08e1f1c289634e_0000000000000000',4,1,0,0,'QOIS__S_Pc5Lf55fftXKOXwHwBlCwfr3','218.151.231.194','2019-09-20 09:19:15'),(16,'111552700168808024699',2,1,0,0,'vT3jJJ1CpF4Uz_KxoXAssUS8Q5JfTUMN','106.102.129.161','2019-09-20 09:40:39'),(17,'d80f80b11d8d2a3953454d73643d747f_a15bee3b9f88ddf8',4,1,0,0,'hljtiZXG0QWBLwxnWE2sHfWG1I-Oj9uF','218.151.231.194','2019-09-20 09:56:09'),(18,'812f5de2f34e6e47764b858c1c1a21ce_85091982b204d35b',4,1,0,0,'yoxulfkLO_CCNr6Ypm-Kck-WZtlgsfp4','175.215.97.122','2019-09-21 02:52:01'),(19,'116777572831063891012',2,1,0,0,'_XJ-XpROzOi3sdagDTU5mrqXXuqAuvzV','218.151.231.194','2019-09-23 12:05:32'),(20,'112333',2,1,0,0,'gcyF2qmfzJ2AUfkqGbEiJP7k97C2EOMs','218.151.231.194','2019-09-24 13:33:26'),(21,'3213',2,1,0,0,'gcyF2qmfzJ2AUfkqGbEiJP7k97C2EOMs','218.151.231.194','2019-09-24 13:40:46'),(22,'3344',2,1,0,0,'gcyF2qmfzJ2AUfkqGbEiJP7k97C2EOMs','218.151.231.194','2019-09-24 13:45:09'),(23,'12121',2,1,0,0,'ghtiMX6lnNxVjwiTEVEA5eqTA7kXAMtk','218.151.231.194','2019-09-24 14:57:32');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth`
--

DROP TABLE IF EXISTS `auth`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `auth` (
  `account` varchar(64) NOT NULL,
  `type` int(64) NOT NULL,
  `state` int(255) NOT NULL,
  `userId` int(255) DEFAULT NULL,
  `sessId` varchar(255) DEFAULT NULL,
  UNIQUE KEY `account_type` (`account`,`type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth`
--

LOCK TABLES `auth` WRITE;
/*!40000 ALTER TABLE `auth` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `item`
--

DROP TABLE IF EXISTS `item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `item` (
  `item_id` int(11) NOT NULL COMMENT 'item ID',
  `name` varchar(50) NOT NULL COMMENT 'item name',
  `icon` int(11) DEFAULT NULL COMMENT 'item icon',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT 'item type',
  `comment` varchar(100) NOT NULL COMMENT 'item 설명',
  `overlap` int(11) DEFAULT NULL COMMENT '겹침개수',
  `packnum` int(11) DEFAULT NULL COMMENT '패키지 번호',
  `img` int(11) DEFAULT NULL COMMENT 'item 이미지',
  `chartype` int(11) DEFAULT NULL COMMENT '캐릭터 타입',
  PRIMARY KEY (`item_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `item`
--

LOCK TABLES `item` WRITE;
/*!40000 ALTER TABLE `item` DISABLE KEYS */;
/*!40000 ALTER TABLE `item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `myroom_shop`
--

DROP TABLE IF EXISTS `myroom_shop`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `myroom_shop` (
  `item_id` int(11) NOT NULL COMMENT 'item ID',
  `name` varchar(50) NOT NULL COMMENT 'item name',
  `comment` varchar(100) NOT NULL COMMENT 'item 설명',
  `icon` int(11) DEFAULT NULL COMMENT '아이콘(상점박스에 들어가는 아이콘)',
  `background` int(11) NOT NULL DEFAULT '0' COMMENT '배경 이미지 번호',
  `check` tinyint(1) NOT NULL DEFAULT '0' COMMENT '검수용 여부(0:비검수,1:검수용)',
  `store` tinyint(1) NOT NULL DEFAULT '0' COMMENT '스토어 타입(0:포인트 구매,1:구글,2:원스토어,3:IOS)',
  `store_key` varchar(100) DEFAULT NULL COMMENT '스토어상품 키값',
  `category` tinyint(1) NOT NULL DEFAULT '0' COMMENT '카테고리',
  `order` tinyint(1) NOT NULL DEFAULT '0' COMMENT '카테고리 내 순서',
  `price_type` tinyint(1) NOT NULL DEFAULT '0' COMMENT '재화 타입(0:지정없음,1:골드,2:보석,3:우정,4:현금)',
  `price_value` int(11) NOT NULL DEFAULT '0' COMMENT '재화 값',
  `group` tinyint(1) DEFAULT NULL COMMENT '상품그룹',
  `product` int(11) NOT NULL DEFAULT '0' COMMENT '상품아이디',
  `count` int(11) DEFAULT NULL COMMENT '구매횟수제한',
  `period_use` tinyint(1) DEFAULT NULL COMMENT '구매기간제한',
  `period_start` datetime DEFAULT NULL COMMENT '구매 시작 일자',
  `period_end` datetime DEFAULT NULL COMMENT '구매 종료 일자',
  PRIMARY KEY (`item_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `myroom_shop`
--

LOCK TABLES `myroom_shop` WRITE;
/*!40000 ALTER TABLE `myroom_shop` DISABLE KEYS */;
/*!40000 ALTER TABLE `myroom_shop` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `product`
--

DROP TABLE IF EXISTS `product`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `product` (
  `id` int(11) NOT NULL COMMENT 'item ID',
  `item_id_1` int(11) DEFAULT NULL,
  `count_1` int(11) DEFAULT NULL,
  `discount_1` int(11) DEFAULT NULL,
  `item_id_2` int(11) DEFAULT NULL,
  `count_2` int(11) DEFAULT NULL,
  `discount_2` int(11) DEFAULT NULL,
  `item_id_3` int(11) DEFAULT NULL,
  `count_3` int(11) DEFAULT NULL,
  `discount_3` int(11) DEFAULT NULL,
  `item_id_4` int(11) DEFAULT NULL,
  `count_4` int(11) DEFAULT NULL,
  `discount_4` int(11) DEFAULT NULL,
  `item_id_5` int(11) DEFAULT NULL,
  `count_5` int(11) DEFAULT NULL,
  `discount_5` int(11) DEFAULT NULL,
  `item_id_6` int(11) DEFAULT NULL,
  `count_6` int(11) DEFAULT NULL,
  `discount_6` int(11) DEFAULT NULL,
  `item_id_7` int(11) DEFAULT NULL,
  `count_7` int(11) DEFAULT NULL,
  `discount_7` int(11) DEFAULT NULL,
  `item_id_8` int(11) DEFAULT NULL,
  `count_8` int(11) DEFAULT NULL,
  `discount_8` int(11) DEFAULT NULL,
  `item_id_9` int(11) DEFAULT NULL,
  `count_9` int(11) DEFAULT NULL,
  `discount_9` int(11) DEFAULT NULL,
  `item_id_10` int(11) DEFAULT NULL,
  `count_10` int(11) DEFAULT NULL,
  `discount_10` int(11) DEFAULT NULL,
  `item_id_11` int(11) DEFAULT NULL,
  `count_11` int(11) DEFAULT NULL,
  `discount_11` int(11) DEFAULT NULL,
  `item_id_12` int(11) DEFAULT NULL,
  `count_12` int(11) DEFAULT NULL,
  `discount_12` int(11) DEFAULT NULL,
  `item_id_13` int(11) DEFAULT NULL,
  `count_13` int(11) DEFAULT NULL,
  `discount_13` int(11) DEFAULT NULL,
  `item_id_14` int(11) DEFAULT NULL,
  `count_14` int(11) DEFAULT NULL,
  `discount_14` int(11) DEFAULT NULL,
  `item_id_15` int(11) DEFAULT NULL,
  `count_15` int(11) DEFAULT NULL,
  `discount_15` int(11) DEFAULT NULL,
  `item_id_16` int(11) DEFAULT NULL,
  `count_16` int(11) DEFAULT NULL,
  `discount_16` int(11) DEFAULT NULL,
  `item_id_17` int(11) DEFAULT NULL,
  `count_17` int(11) DEFAULT NULL,
  `discount_17` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `product`
--

LOCK TABLES `product` WRITE;
/*!40000 ALTER TABLE `product` DISABLE KEYS */;
/*!40000 ALTER TABLE `product` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `scene`
--

DROP TABLE IF EXISTS `scene`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scene` (
  `id` int(11) NOT NULL COMMENT 'scene ID',
  `chapter` varchar(20) NOT NULL COMMENT 'chapter',
  `episode_type` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'episode type(0:Prologue,1:Episode,2:Epilogue)',
  `episode_number` int(11) DEFAULT NULL COMMENT '스토어 타입(0:포인트 구매,1:구글,2:원스토어,3:IOS)',
  `chapter_name` varchar(100) DEFAULT NULL,
  `chapter_number` tinyint(1) DEFAULT NULL,
  `chapter_path` varchar(100) DEFAULT NULL,
  `next_id` int(11) DEFAULT NULL COMMENT '다음 scene ID',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `scene`
--

LOCK TABLES `scene` WRITE;
/*!40000 ALTER TABLE `scene` DISABLE KEYS */;
/*!40000 ALTER TABLE `scene` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sessions`
--

DROP TABLE IF EXISTS `sessions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sessions` (
  `session_id` varchar(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  `expires` int(11) unsigned NOT NULL,
  `data` text CHARACTER SET utf8mb4 COLLATE utf8mb4_bin,
  PRIMARY KEY (`session_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sessions`
--

LOCK TABLES `sessions` WRITE;
/*!40000 ALTER TABLE `sessions` DISABLE KEYS */;
/*!40000 ALTER TABLE `sessions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `storebill`
--

DROP TABLE IF EXISTS `storebill`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `storebill` (
  `bId` int(64) NOT NULL AUTO_INCREMENT,
  `keyvalue` varchar(64) NOT NULL,
  `transvalue` varchar(1024) NOT NULL,
  PRIMARY KEY (`bId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `storebill`
--

LOCK TABLES `storebill` WRITE;
/*!40000 ALTER TABLE `storebill` DISABLE KEYS */;
/*!40000 ALTER TABLE `storebill` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `sId` int(64) NOT NULL AUTO_INCREMENT,
  `firstName` varchar(64) NOT NULL,
  `lastName` varchar(64) NOT NULL,
  `time` datetime DEFAULT NULL,
  `data` text NOT NULL,
  PRIMARY KEY (`sId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_album`
--

DROP TABLE IF EXISTS `user_album`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_album` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `actor_id` smallint(6) NOT NULL DEFAULT '0' COMMENT '상대(강태준:0,백현성:1,정재민:2,김동주:3,정석환:4)',
  `album_id` int(11) NOT NULL DEFAULT '0' COMMENT '앨범 ID',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_album_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=76 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_album`
--

LOCK TABLES `user_album` WRITE;
/*!40000 ALTER TABLE `user_album` DISABLE KEYS */;
INSERT INTO `user_album` VALUES (1,1,2,1,'2019-09-19 13:14:45'),(2,2,2,1,'2019-09-19 13:16:05'),(3,3,2,1,'2019-09-19 13:16:13'),(4,2,0,1,'2019-09-19 13:17:00'),(5,2,1,1,'2019-09-19 13:17:00'),(6,5,2,1,'2019-09-19 13:23:29'),(7,5,0,1,'2019-09-19 13:26:11'),(8,5,1,1,'2019-09-19 13:26:12'),(9,5,4,1,'2019-09-19 13:29:34'),(10,5,3,1,'2019-09-19 13:31:22'),(11,6,2,1,'2019-09-19 13:34:32'),(12,7,2,1,'2019-09-19 13:38:28'),(13,8,2,1,'2019-09-19 13:39:45'),(14,2,4,1,'2019-09-19 13:43:28'),(15,3,0,1,'2019-09-19 13:43:56'),(16,3,1,1,'2019-09-19 13:43:56'),(17,3,4,1,'2019-09-19 13:45:19'),(18,3,3,1,'2019-09-19 13:46:13'),(19,2,3,1,'2019-09-19 13:49:32'),(20,9,0,3,'2019-09-19 14:06:39'),(21,11,2,1,'2019-09-19 15:14:09'),(22,12,2,1,'2019-09-19 16:11:47'),(23,12,0,1,'2019-09-19 16:43:06'),(24,12,1,1,'2019-09-19 16:43:06'),(25,1,0,1,'2019-09-20 09:19:56'),(26,1,1,1,'2019-09-20 09:19:56'),(27,1,4,1,'2019-09-20 09:21:23'),(28,1,3,1,'2019-09-20 09:22:14'),(29,16,2,1,'2019-09-20 09:44:33'),(30,5,3,3,'2019-09-20 09:46:21'),(31,16,0,1,'2019-09-20 09:48:38'),(32,16,1,1,'2019-09-20 09:48:38'),(33,12,4,1,'2019-09-20 09:51:58'),(34,5,3,5,'2019-09-20 09:54:26'),(35,16,4,1,'2019-09-20 09:56:20'),(36,12,3,1,'2019-09-20 09:57:12'),(37,17,2,1,'2019-09-20 10:00:00'),(38,16,3,1,'2019-09-20 10:00:20'),(39,17,0,1,'2019-09-20 10:05:12'),(40,17,1,1,'2019-09-20 10:05:12'),(41,17,4,1,'2019-09-20 10:12:40'),(42,5,3,7,'2019-09-20 10:13:11'),(43,17,3,1,'2019-09-20 10:16:57'),(44,17,0,3,'2019-09-20 10:39:58'),(45,17,0,5,'2019-09-20 10:50:03'),(46,5,3,9,'2019-09-20 10:59:46'),(47,17,0,7,'2019-09-20 11:09:23'),(48,17,0,9,'2019-09-20 11:32:10'),(49,17,0,11,'2019-09-20 11:41:35'),(50,12,3,3,'2019-09-20 12:00:23'),(51,12,3,5,'2019-09-20 12:21:35'),(52,17,0,13,'2019-09-20 12:25:54'),(53,17,0,15,'2019-09-20 13:30:38'),(54,5,3,11,'2019-09-20 13:37:42'),(55,17,0,17,'2019-09-20 13:44:49'),(56,17,4,3,'2019-09-20 15:10:15'),(57,17,4,5,'2019-09-20 15:29:50'),(58,17,4,7,'2019-09-20 15:37:13'),(59,5,1,3,'2019-09-20 15:53:13'),(60,12,3,7,'2019-09-20 18:13:27'),(61,12,3,9,'2019-09-20 18:32:16'),(62,18,2,1,'2019-09-21 02:56:16'),(63,18,0,1,'2019-09-21 03:03:33'),(64,18,1,1,'2019-09-21 03:03:33'),(65,18,4,1,'2019-09-21 03:11:45'),(66,18,3,1,'2019-09-21 03:16:29'),(67,19,2,1,'2019-09-23 13:45:10'),(68,19,0,1,'2019-09-23 13:51:10'),(69,19,1,1,'2019-09-23 13:51:10'),(70,2,0,3,'2019-09-24 10:26:37'),(71,1,0,3,'2019-09-24 10:27:08'),(72,20,2,1,'2019-09-24 13:35:13'),(73,21,2,1,'2019-09-24 13:41:39'),(74,22,2,1,'2019-09-24 13:46:12'),(75,23,2,1,'2019-09-24 14:59:15');
/*!40000 ALTER TABLE `user_album` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_buy_album`
--

DROP TABLE IF EXISTS `user_buy_album`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_buy_album` (
  `idxId` int(11) NOT NULL AUTO_INCREMENT,
  `nId` int(11) NOT NULL COMMENT '계정indexID(account.nId)',
  `itemId` int(11) NOT NULL DEFAULT '0' COMMENT '수집한 앨범 ID',
  `regTime` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idxId`),
  KEY `nId` (`nId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_buy_album`
--

LOCK TABLES `user_buy_album` WRITE;
/*!40000 ALTER TABLE `user_buy_album` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_buy_album` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_collection_album`
--

DROP TABLE IF EXISTS `user_collection_album`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_collection_album` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `album_id` int(11) NOT NULL DEFAULT '0' COMMENT '앨범 ID',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_collection_album_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=313 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_collection_album`
--

LOCK TABLES `user_collection_album` WRITE;
/*!40000 ALTER TABLE `user_collection_album` DISABLE KEYS */;
INSERT INTO `user_collection_album` VALUES (1,9,401,'2019-09-19 15:48:22'),(2,9,402,'2019-09-19 15:48:22'),(3,9,403,'2019-09-19 15:48:22'),(4,9,404,'2019-09-19 15:48:22'),(5,9,405,'2019-09-19 15:48:22'),(6,9,406,'2019-09-19 15:48:22'),(7,9,407,'2019-09-19 15:48:22'),(8,9,408,'2019-09-19 15:48:22'),(9,9,409,'2019-09-19 15:48:22'),(10,9,410,'2019-09-19 15:48:22'),(11,9,411,'2019-09-19 15:48:22'),(12,9,412,'2019-09-19 15:48:22'),(13,9,413,'2019-09-19 15:48:22'),(14,9,414,'2019-09-19 15:48:22'),(15,9,401,'2019-09-19 15:48:49'),(16,9,402,'2019-09-19 15:48:49'),(17,9,403,'2019-09-19 15:48:49'),(18,9,404,'2019-09-19 15:48:49'),(19,9,405,'2019-09-19 15:48:49'),(20,9,406,'2019-09-19 15:48:49'),(21,9,407,'2019-09-19 15:48:49'),(22,9,408,'2019-09-19 15:48:49'),(23,9,409,'2019-09-19 15:48:49'),(24,9,410,'2019-09-19 15:48:49'),(25,9,411,'2019-09-19 15:48:49'),(26,9,412,'2019-09-19 15:48:49'),(27,9,413,'2019-09-19 15:48:49'),(28,9,414,'2019-09-19 15:48:49'),(29,9,501,'2019-09-19 15:49:33'),(30,9,502,'2019-09-19 15:49:33'),(31,9,503,'2019-09-19 15:49:33'),(32,9,504,'2019-09-19 15:49:33'),(33,9,505,'2019-09-19 15:49:33'),(34,9,506,'2019-09-19 15:49:33'),(35,9,507,'2019-09-19 15:49:33'),(36,9,508,'2019-09-19 15:49:33'),(37,9,509,'2019-09-19 15:49:33'),(38,9,510,'2019-09-19 15:49:33'),(39,9,511,'2019-09-19 15:49:33'),(40,9,512,'2019-09-19 15:49:33'),(41,9,513,'2019-09-19 15:49:33'),(42,9,514,'2019-09-19 15:49:33'),(43,1,501,'2019-09-20 09:27:03'),(44,1,502,'2019-09-20 09:27:03'),(45,1,503,'2019-09-20 09:27:03'),(46,1,504,'2019-09-20 09:27:03'),(47,1,505,'2019-09-20 09:27:03'),(48,1,506,'2019-09-20 09:27:03'),(49,1,507,'2019-09-20 09:27:03'),(50,1,508,'2019-09-20 09:27:04'),(51,1,509,'2019-09-20 09:27:04'),(52,1,510,'2019-09-20 09:27:04'),(53,1,511,'2019-09-20 09:27:04'),(54,1,512,'2019-09-20 09:27:04'),(55,1,513,'2019-09-20 09:27:04'),(56,1,514,'2019-09-20 09:27:04'),(57,1,401,'2019-09-20 09:59:26'),(58,1,402,'2019-09-20 09:59:26'),(59,1,403,'2019-09-20 09:59:26'),(60,1,404,'2019-09-20 09:59:26'),(61,1,405,'2019-09-20 09:59:26'),(62,1,406,'2019-09-20 09:59:26'),(63,1,407,'2019-09-20 09:59:26'),(64,1,408,'2019-09-20 09:59:26'),(65,1,409,'2019-09-20 09:59:26'),(66,1,410,'2019-09-20 09:59:27'),(67,1,411,'2019-09-20 09:59:27'),(68,1,412,'2019-09-20 09:59:27'),(69,1,413,'2019-09-20 09:59:27'),(70,1,414,'2019-09-20 09:59:27'),(71,1,801,'2019-09-20 09:59:29'),(72,1,802,'2019-09-20 09:59:29'),(73,1,803,'2019-09-20 09:59:29'),(74,1,804,'2019-09-20 09:59:29'),(75,1,805,'2019-09-20 09:59:29'),(76,1,806,'2019-09-20 09:59:29'),(77,1,807,'2019-09-20 09:59:30'),(78,1,808,'2019-09-20 09:59:30'),(79,1,809,'2019-09-20 09:59:30'),(80,1,810,'2019-09-20 09:59:30'),(81,1,811,'2019-09-20 09:59:30'),(82,1,812,'2019-09-20 09:59:30'),(83,1,813,'2019-09-20 09:59:30'),(84,1,814,'2019-09-20 09:59:30'),(85,17,401,'2019-09-20 10:33:50'),(86,17,402,'2019-09-20 10:33:50'),(87,17,403,'2019-09-20 10:33:50'),(88,17,404,'2019-09-20 10:33:50'),(89,17,405,'2019-09-20 10:33:50'),(90,17,406,'2019-09-20 10:33:50'),(91,17,407,'2019-09-20 10:33:50'),(92,17,408,'2019-09-20 10:33:51'),(93,17,409,'2019-09-20 10:33:51'),(94,17,410,'2019-09-20 10:33:51'),(95,17,411,'2019-09-20 10:33:51'),(96,17,412,'2019-09-20 10:33:51'),(97,17,413,'2019-09-20 10:33:51'),(98,17,414,'2019-09-20 10:33:51'),(99,17,501,'2019-09-20 10:33:53'),(100,17,502,'2019-09-20 10:33:53'),(101,17,503,'2019-09-20 10:33:53'),(102,17,504,'2019-09-20 10:33:53'),(103,17,505,'2019-09-20 10:33:53'),(104,17,506,'2019-09-20 10:33:53'),(105,17,507,'2019-09-20 10:33:53'),(106,17,508,'2019-09-20 10:33:53'),(107,17,509,'2019-09-20 10:33:53'),(108,17,510,'2019-09-20 10:33:54'),(109,17,511,'2019-09-20 10:33:54'),(110,17,512,'2019-09-20 10:33:54'),(111,17,513,'2019-09-20 10:33:54'),(112,17,514,'2019-09-20 10:33:54'),(113,17,801,'2019-09-20 10:33:56'),(114,17,802,'2019-09-20 10:33:56'),(115,17,803,'2019-09-20 10:33:56'),(116,17,804,'2019-09-20 10:33:56'),(117,17,805,'2019-09-20 10:33:56'),(118,17,806,'2019-09-20 10:33:57'),(119,17,807,'2019-09-20 10:33:57'),(120,17,808,'2019-09-20 10:33:57'),(121,17,809,'2019-09-20 10:33:57'),(122,17,810,'2019-09-20 10:33:57'),(123,17,811,'2019-09-20 10:33:57'),(124,17,812,'2019-09-20 10:33:57'),(125,17,813,'2019-09-20 10:33:57'),(126,17,814,'2019-09-20 10:33:57'),(127,17,601,'2019-09-20 10:34:00'),(128,17,602,'2019-09-20 10:34:00'),(129,17,603,'2019-09-20 10:34:00'),(130,17,604,'2019-09-20 10:34:00'),(131,17,605,'2019-09-20 10:34:00'),(132,17,606,'2019-09-20 10:34:00'),(133,17,607,'2019-09-20 10:34:00'),(134,17,608,'2019-09-20 10:34:00'),(135,17,609,'2019-09-20 10:34:00'),(136,17,610,'2019-09-20 10:34:00'),(137,17,611,'2019-09-20 10:34:00'),(138,17,612,'2019-09-20 10:34:00'),(139,17,613,'2019-09-20 10:34:00'),(140,17,614,'2019-09-20 10:34:00'),(141,17,701,'2019-09-20 10:34:02'),(142,17,702,'2019-09-20 10:34:02'),(143,17,703,'2019-09-20 10:34:02'),(144,17,704,'2019-09-20 10:34:02'),(145,17,705,'2019-09-20 10:34:02'),(146,17,706,'2019-09-20 10:34:02'),(147,17,707,'2019-09-20 10:34:02'),(148,17,708,'2019-09-20 10:34:02'),(149,17,709,'2019-09-20 10:34:02'),(150,17,710,'2019-09-20 10:34:02'),(151,17,711,'2019-09-20 10:34:02'),(152,17,712,'2019-09-20 10:34:02'),(153,17,713,'2019-09-20 10:34:02'),(154,17,714,'2019-09-20 10:34:02'),(155,1,601,'2019-09-20 15:01:29'),(156,1,602,'2019-09-20 15:01:29'),(157,1,603,'2019-09-20 15:01:29'),(158,1,604,'2019-09-20 15:01:30'),(159,1,605,'2019-09-20 15:01:30'),(160,1,606,'2019-09-20 15:01:30'),(161,1,607,'2019-09-20 15:01:30'),(162,1,608,'2019-09-20 15:01:30'),(163,1,609,'2019-09-20 15:01:30'),(164,1,610,'2019-09-20 15:01:30'),(165,1,611,'2019-09-20 15:01:30'),(166,1,612,'2019-09-20 15:01:30'),(167,1,613,'2019-09-20 15:01:30'),(168,1,614,'2019-09-20 15:01:30'),(169,1,708,'2019-09-20 15:01:57'),(170,1,709,'2019-09-20 15:01:57'),(171,1,710,'2019-09-20 15:01:57'),(172,1,711,'2019-09-20 15:01:57'),(173,12,701,'2019-09-20 18:24:24'),(174,12,702,'2019-09-20 18:24:24'),(175,12,703,'2019-09-20 18:24:24'),(176,12,704,'2019-09-20 18:24:24'),(177,12,705,'2019-09-20 18:24:24'),(178,12,706,'2019-09-20 18:24:24'),(179,12,707,'2019-09-20 18:24:24'),(180,12,708,'2019-09-20 18:24:24'),(181,12,709,'2019-09-20 18:24:24'),(182,12,710,'2019-09-20 18:24:24'),(183,12,711,'2019-09-20 18:24:24'),(184,12,712,'2019-09-20 18:24:24'),(185,12,713,'2019-09-20 18:24:25'),(186,12,714,'2019-09-20 18:24:25'),(187,18,801,'2019-09-21 03:39:13'),(188,18,802,'2019-09-21 03:39:13'),(189,18,803,'2019-09-21 03:39:13'),(190,18,804,'2019-09-21 03:39:13'),(191,18,805,'2019-09-21 03:39:13'),(192,18,806,'2019-09-21 03:39:14'),(193,18,807,'2019-09-21 03:39:14'),(194,18,808,'2019-09-21 03:39:14'),(195,18,809,'2019-09-21 03:39:14'),(196,18,810,'2019-09-21 03:39:14'),(197,18,811,'2019-09-21 03:39:14'),(198,18,812,'2019-09-21 03:39:14'),(199,18,813,'2019-09-21 03:39:14'),(200,18,814,'2019-09-21 03:39:14'),(201,3,401,'2019-09-24 10:36:11'),(202,3,402,'2019-09-24 10:36:11'),(203,3,403,'2019-09-24 10:36:11'),(204,3,404,'2019-09-24 10:36:11'),(205,3,405,'2019-09-24 10:36:11'),(206,3,406,'2019-09-24 10:36:11'),(207,3,407,'2019-09-24 10:36:11'),(208,3,408,'2019-09-24 10:36:11'),(209,3,409,'2019-09-24 10:36:11'),(210,3,410,'2019-09-24 10:36:11'),(211,3,411,'2019-09-24 10:36:11'),(212,3,412,'2019-09-24 10:36:11'),(213,3,413,'2019-09-24 10:36:11'),(214,3,414,'2019-09-24 10:36:11'),(215,3,501,'2019-09-24 10:36:14'),(216,3,502,'2019-09-24 10:36:14'),(217,3,503,'2019-09-24 10:36:14'),(218,3,504,'2019-09-24 10:36:14'),(219,3,505,'2019-09-24 10:36:14'),(220,3,506,'2019-09-24 10:36:14'),(221,3,507,'2019-09-24 10:36:14'),(222,3,508,'2019-09-24 10:36:14'),(223,3,509,'2019-09-24 10:36:14'),(224,3,510,'2019-09-24 10:36:14'),(225,3,511,'2019-09-24 10:36:14'),(226,3,512,'2019-09-24 10:36:14'),(227,3,513,'2019-09-24 10:36:14'),(228,3,514,'2019-09-24 10:36:14'),(229,3,801,'2019-09-24 10:36:15'),(230,3,802,'2019-09-24 10:36:15'),(231,3,803,'2019-09-24 10:36:15'),(232,3,804,'2019-09-24 10:36:15'),(233,3,805,'2019-09-24 10:36:16'),(234,3,806,'2019-09-24 10:36:16'),(235,3,807,'2019-09-24 10:36:16'),(236,3,808,'2019-09-24 10:36:16'),(237,3,809,'2019-09-24 10:36:16'),(238,3,810,'2019-09-24 10:36:16'),(239,3,811,'2019-09-24 10:36:16'),(240,3,812,'2019-09-24 10:36:16'),(241,3,813,'2019-09-24 10:36:16'),(242,3,814,'2019-09-24 10:36:16'),(243,3,601,'2019-09-24 10:36:19'),(244,3,602,'2019-09-24 10:36:19'),(245,3,603,'2019-09-24 10:36:19'),(246,3,604,'2019-09-24 10:36:19'),(247,3,605,'2019-09-24 10:36:19'),(248,3,606,'2019-09-24 10:36:19'),(249,3,607,'2019-09-24 10:36:19'),(250,3,608,'2019-09-24 10:36:19'),(251,3,609,'2019-09-24 10:36:19'),(252,3,610,'2019-09-24 10:36:19'),(253,3,611,'2019-09-24 10:36:19'),(254,3,612,'2019-09-24 10:36:19'),(255,3,613,'2019-09-24 10:36:19'),(256,3,614,'2019-09-24 10:36:19'),(257,3,701,'2019-09-24 10:36:21'),(258,3,702,'2019-09-24 10:36:21'),(259,3,703,'2019-09-24 10:36:21'),(260,3,704,'2019-09-24 10:36:21'),(261,3,705,'2019-09-24 10:36:21'),(262,3,706,'2019-09-24 10:36:21'),(263,3,707,'2019-09-24 10:36:21'),(264,3,708,'2019-09-24 10:36:21'),(265,3,709,'2019-09-24 10:36:21'),(266,3,710,'2019-09-24 10:36:21'),(267,3,711,'2019-09-24 10:36:21'),(268,3,712,'2019-09-24 10:36:21'),(269,3,713,'2019-09-24 10:36:21'),(270,3,714,'2019-09-24 10:36:21'),(271,5,401,'2019-09-24 14:59:19'),(272,5,402,'2019-09-24 14:59:19'),(273,5,403,'2019-09-24 14:59:19'),(274,5,404,'2019-09-24 14:59:19'),(275,5,405,'2019-09-24 14:59:19'),(276,5,406,'2019-09-24 14:59:19'),(277,5,407,'2019-09-24 14:59:19'),(278,5,408,'2019-09-24 14:59:19'),(279,5,409,'2019-09-24 14:59:19'),(280,5,410,'2019-09-24 14:59:19'),(281,5,411,'2019-09-24 14:59:19'),(282,5,412,'2019-09-24 14:59:19'),(283,5,413,'2019-09-24 14:59:19'),(284,5,414,'2019-09-24 14:59:19'),(285,5,501,'2019-09-24 14:59:22'),(286,5,502,'2019-09-24 14:59:22'),(287,5,503,'2019-09-24 14:59:22'),(288,5,504,'2019-09-24 14:59:22'),(289,5,505,'2019-09-24 14:59:22'),(290,5,506,'2019-09-24 14:59:22'),(291,5,507,'2019-09-24 14:59:22'),(292,5,508,'2019-09-24 14:59:22'),(293,5,509,'2019-09-24 14:59:22'),(294,5,510,'2019-09-24 14:59:22'),(295,5,511,'2019-09-24 14:59:22'),(296,5,512,'2019-09-24 14:59:22'),(297,5,513,'2019-09-24 14:59:22'),(298,5,514,'2019-09-24 14:59:22'),(299,5,801,'2019-09-24 14:59:24'),(300,5,802,'2019-09-24 14:59:24'),(301,5,803,'2019-09-24 14:59:24'),(302,5,804,'2019-09-24 14:59:24'),(303,5,805,'2019-09-24 14:59:24'),(304,5,806,'2019-09-24 14:59:24'),(305,5,807,'2019-09-24 14:59:24'),(306,5,808,'2019-09-24 14:59:24'),(307,5,809,'2019-09-24 14:59:24'),(308,5,810,'2019-09-24 14:59:24'),(309,5,811,'2019-09-24 14:59:24'),(310,5,812,'2019-09-24 14:59:25'),(311,5,813,'2019-09-24 14:59:25'),(312,5,814,'2019-09-24 14:59:25');
/*!40000 ALTER TABLE `user_collection_album` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_data`
--

DROP TABLE IF EXISTS `user_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_data` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `first_name` varchar(32) NOT NULL COMMENT '플레이어 이름',
  `last_name` varchar(32) NOT NULL COMMENT '플레이어 성',
  `tutorial_clear` tinyint(1) NOT NULL DEFAULT '0' COMMENT '튜토리얼 완료 여부(미완료: 0, 완료: 1)',
  `gold` int(11) NOT NULL DEFAULT '0' COMMENT '골드 포인트',
  `film` int(11) NOT NULL DEFAULT '0' COMMENT '필름 포인트',
  `heart` int(11) NOT NULL DEFAULT '0' COMMENT '하트 포인트',
  `passion` int(11) NOT NULL DEFAULT '0',
  `happy` int(11) NOT NULL DEFAULT '0',
  `select_actor` smallint(6) NOT NULL DEFAULT '0' COMMENT '선택상대(강태준:0,백현성:1,정재민:2,김동주:3,정석환:4)',
  `cur_story` int(11) NOT NULL DEFAULT '0' COMMENT '현재 스토리 진행 번호',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  `up_date` datetime DEFAULT NULL COMMENT '업데이트 시간',
  PRIMARY KEY (`user_id`),
  KEY `fk_user_data_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_data`
--

LOCK TABLES `user_data` WRITE;
/*!40000 ALTER TABLE `user_data` DISABLE KEYS */;
INSERT INTO `user_data` VALUES (1,1,'정원','하',1,9080,10019,10015,5,5,4,10301,'2019-09-19 13:14:04','2019-09-24 10:31:33'),(2,2,'bc','a',1,22950,10141,9592,0,5,0,10112,'2019-09-19 13:15:03','2019-09-24 10:26:37'),(3,3,'정원','로',1,8000,9994,10000,0,0,2,10400,'2019-09-19 13:15:29','2019-09-24 10:36:21'),(4,4,'정원','민',0,0,1,1,0,0,6,0,'2019-09-19 13:17:29','2019-09-19 13:20:33'),(5,5,'정원','민',1,8800,9966,10006,45,25,1,10204,'2019-09-19 13:21:28','2019-09-24 14:59:24'),(6,6,'정원','계',0,0,9999,0,0,0,6,10101,'2019-09-19 13:33:03','2019-09-19 13:34:32'),(7,7,'정원','계2',0,10000,10000,10001,0,0,6,10101,'2019-09-19 13:37:50','2019-09-19 13:38:30'),(8,8,'정원','계3',0,10000,10000,10001,0,0,6,10101,'2019-09-19 13:39:07','2019-09-19 13:39:47'),(9,9,'정원','민',1,8800,9998,9919,0,10,0,10113,'2019-09-19 13:47:16','2019-09-24 15:30:36'),(10,11,'정원','민',0,10000,10000,10001,0,0,6,10101,'2019-09-19 15:13:06','2019-09-19 15:14:11'),(11,12,'정원','민',1,9500,9968,10002,20,10,3,10516,'2019-09-19 16:08:14','2019-09-23 11:32:45'),(12,13,'정원','민',0,10000,10001,10001,0,0,6,10110,'2019-09-19 17:27:29','2019-09-19 17:28:23'),(13,14,'정원','민',0,10000,10001,10001,0,0,6,10110,'2019-09-19 17:40:48','2019-09-19 17:41:06'),(14,16,'정원','민',1,10000,9991,10001,0,0,0,10110,'2019-09-20 09:40:46','2019-09-20 14:11:57'),(15,17,'정원','민',1,8000,9937,9993,70,50,4,10315,'2019-09-20 09:56:15','2019-09-20 16:03:41'),(16,18,'정원','민',1,9600,10001,10027,0,0,4,10301,'2019-09-21 02:52:10','2019-09-21 03:41:51'),(17,19,'탱구','민',0,10000,9998,10001,0,0,6,10103,'2019-09-23 13:39:47','2019-09-23 14:45:13'),(18,20,'정원','민',0,10000,10000,10001,0,0,6,10101,'2019-09-24 13:33:29','2019-09-24 13:35:15'),(19,21,'정원','민',0,10000,10000,10001,0,0,6,10101,'2019-09-24 13:40:48','2019-09-24 13:41:41'),(20,22,'정원','민',0,10000,10000,10001,0,0,6,10101,'2019-09-24 13:45:12','2019-09-24 13:46:14'),(21,23,'정원','민',0,10000,10000,10001,0,0,6,10101,'2019-09-24 14:57:35','2019-09-24 14:59:16'),(22,15,'정원','민',0,10000,10001,10001,0,0,6,10110,'2019-09-24 15:10:24','2019-09-24 15:27:07');
/*!40000 ALTER TABLE `user_data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_default_setting`
--

DROP TABLE IF EXISTS `user_default_setting`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_default_setting` (
  `idx` int(11) NOT NULL,
  `gold` int(11) NOT NULL DEFAULT '0' COMMENT '기본 골드 포인트',
  `film` int(11) NOT NULL DEFAULT '0' COMMENT '기본 필름 포인트',
  `heart` int(11) NOT NULL DEFAULT '0' COMMENT '기본 하트 포인트',
  `passion` int(11) NOT NULL DEFAULT '0',
  `happy` int(11) NOT NULL DEFAULT '0',
  `first_actor` smallint(6) NOT NULL DEFAULT '0' COMMENT '첫 선택상대(강태준:0,백현성:1,정재민:2,김동주:3,정석환:4)',
  `first_story` int(11) NOT NULL DEFAULT '10110' COMMENT '첫 스토리 진행 번호',
  `base_cloth` int(11) NOT NULL DEFAULT '100' COMMENT '기본 옷',
  `base_shoes` int(11) NOT NULL DEFAULT '200' COMMENT '기본 신발',
  `base_accessory` int(11) NOT NULL DEFAULT '300' COMMENT '기본 악세사리',
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_default_setting`
--

LOCK TABLES `user_default_setting` WRITE;
/*!40000 ALTER TABLE `user_default_setting` DISABLE KEYS */;
INSERT INTO `user_default_setting` VALUES (1,10000,10000,10000,0,0,6,10110,100,200,300);
/*!40000 ALTER TABLE `user_default_setting` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_login_reward`
--

DROP TABLE IF EXISTS `user_login_reward`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_login_reward` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) DEFAULT NULL,
  `reward_count` smallint(6) DEFAULT NULL,
  `reg_date` datetime DEFAULT NULL,
  `first_reward_date` datetime DEFAULT NULL,
  `up_date` datetime DEFAULT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_login_reward`
--

LOCK TABLES `user_login_reward` WRITE;
/*!40000 ALTER TABLE `user_login_reward` DISABLE KEYS */;
INSERT INTO `user_login_reward` VALUES (1,1,3,'2019-09-19 13:14:48','2019-09-19 13:14:48','2019-09-24 10:24:31'),(2,2,4,'2019-09-19 13:16:07','2019-09-19 13:16:07','2019-09-24 10:15:24'),(3,3,3,'2019-09-19 13:16:14','2019-09-19 13:16:14','2019-09-24 10:36:01'),(4,4,1,'2019-09-19 13:20:33','2019-09-19 13:20:33','2019-09-19 13:20:33'),(5,5,4,'2019-09-19 13:23:30','2019-09-19 13:23:30','2019-09-24 10:44:09'),(6,7,1,'2019-09-19 13:38:30','2019-09-19 13:38:30','2019-09-19 13:38:30'),(7,8,1,'2019-09-19 13:39:47','2019-09-19 13:39:47','2019-09-19 13:39:47'),(8,9,3,'2019-09-19 13:47:34','2019-09-19 13:47:34','2019-09-24 09:19:16'),(9,11,1,'2019-09-19 15:14:11','2019-09-19 15:14:11','2019-09-19 15:14:11'),(10,12,3,'2019-09-19 16:11:50','2019-09-19 16:11:50','2019-09-23 11:32:45'),(11,13,1,'2019-09-19 17:28:23','2019-09-19 17:28:23','2019-09-19 17:28:23'),(12,14,1,'2019-09-19 17:41:06','2019-09-19 17:41:06','2019-09-19 17:41:06'),(13,16,1,'2019-09-20 09:44:35','2019-09-20 09:44:35','2019-09-20 09:44:35'),(14,17,1,'2019-09-20 10:00:05','2019-09-20 10:00:05','2019-09-20 10:00:05'),(15,18,11,'2019-09-21 02:56:18','2019-09-21 02:56:18','2019-09-21 03:41:51'),(16,19,1,'2019-09-23 13:45:13','2019-09-23 13:45:13','2019-09-23 13:45:13'),(17,20,1,'2019-09-24 13:35:15','2019-09-24 13:35:15','2019-09-24 13:35:15'),(18,21,1,'2019-09-24 13:41:41','2019-09-24 13:41:41','2019-09-24 13:41:41'),(19,22,1,'2019-09-24 13:46:14','2019-09-24 13:46:14','2019-09-24 13:46:14'),(20,23,1,'2019-09-24 14:59:16','2019-09-24 14:59:16','2019-09-24 14:59:16'),(21,15,1,'2019-09-24 15:27:07','2019-09-24 15:27:07','2019-09-24 15:27:07');
/*!40000 ALTER TABLE `user_login_reward` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_myroom_info`
--

DROP TABLE IF EXISTS `user_myroom_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_myroom_info` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `item_type` smallint(6) NOT NULL DEFAULT '0' COMMENT 'item type(10 : 옷, 100 : 신발, 101 : 액세서리)',
  `item_id` int(11) NOT NULL DEFAULT '0' COMMENT 'item ID',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  `up_date` datetime DEFAULT NULL COMMENT '업데이트 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_myroom_info_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_myroom_info`
--

LOCK TABLES `user_myroom_info` WRITE;
/*!40000 ALTER TABLE `user_myroom_info` DISABLE KEYS */;
INSERT INTO `user_myroom_info` VALUES (1,1,10,0,'2019-09-19 13:14:04',NULL),(2,1,100,0,'2019-09-19 13:14:04',NULL),(3,1,101,0,'2019-09-19 13:14:04',NULL),(4,2,10,0,'2019-09-19 13:15:03',NULL),(5,2,100,0,'2019-09-19 13:15:03',NULL),(6,2,101,0,'2019-09-19 13:15:03',NULL),(7,3,10,0,'2019-09-19 13:15:29',NULL),(8,3,100,0,'2019-09-19 13:15:29',NULL),(9,3,101,0,'2019-09-19 13:15:29',NULL),(10,4,10,0,'2019-09-19 13:17:29',NULL),(11,4,100,0,'2019-09-19 13:17:29',NULL),(12,4,101,0,'2019-09-19 13:17:29',NULL),(13,5,10,0,'2019-09-19 13:21:28',NULL),(14,5,100,0,'2019-09-19 13:21:28',NULL),(15,5,101,0,'2019-09-19 13:21:28',NULL),(16,6,10,0,'2019-09-19 13:33:03',NULL),(17,6,100,0,'2019-09-19 13:33:03',NULL),(18,6,101,0,'2019-09-19 13:33:03',NULL),(19,7,10,100,'2019-09-19 13:37:50',NULL),(20,7,100,200,'2019-09-19 13:37:50',NULL),(21,7,101,300,'2019-09-19 13:37:50',NULL),(22,8,10,100,'2019-09-19 13:39:07',NULL),(23,8,100,200,'2019-09-19 13:39:07',NULL),(24,8,101,300,'2019-09-19 13:39:07',NULL),(25,9,10,101,'2019-09-19 13:47:16','2019-09-19 16:00:20'),(26,9,100,201,'2019-09-19 13:47:16','2019-09-19 16:00:20'),(27,9,101,301,'2019-09-19 13:47:16','2019-09-19 16:00:20'),(28,11,10,100,'2019-09-19 15:13:06',NULL),(29,11,100,200,'2019-09-19 15:13:06',NULL),(30,11,101,300,'2019-09-19 15:13:06',NULL),(31,12,10,105,'2019-09-19 16:08:14','2019-09-20 18:24:36'),(32,12,100,205,'2019-09-19 16:08:14','2019-09-20 18:24:36'),(33,12,101,305,'2019-09-19 16:08:14','2019-09-20 18:24:37'),(34,13,10,100,'2019-09-19 17:27:29',NULL),(35,13,100,200,'2019-09-19 17:27:29',NULL),(36,13,101,300,'2019-09-19 17:27:29',NULL),(37,14,10,100,'2019-09-19 17:40:48',NULL),(38,14,100,200,'2019-09-19 17:40:48',NULL),(39,14,101,300,'2019-09-19 17:40:48',NULL),(40,16,10,100,'2019-09-20 09:40:46',NULL),(41,16,100,200,'2019-09-20 09:40:46',NULL),(42,16,101,300,'2019-09-20 09:40:46',NULL),(43,17,10,100,'2019-09-20 09:56:15',NULL),(44,17,100,200,'2019-09-20 09:56:15',NULL),(45,17,101,300,'2019-09-20 09:56:15',NULL),(46,18,10,100,'2019-09-21 02:52:10',NULL),(47,18,100,200,'2019-09-21 02:52:10',NULL),(48,18,101,300,'2019-09-21 02:52:10',NULL),(49,19,10,100,'2019-09-23 13:39:47',NULL),(50,19,100,200,'2019-09-23 13:39:47',NULL),(51,19,101,300,'2019-09-23 13:39:47',NULL),(52,20,10,100,'2019-09-24 13:33:29',NULL),(53,20,100,200,'2019-09-24 13:33:29',NULL),(54,20,101,300,'2019-09-24 13:33:29',NULL),(55,21,10,100,'2019-09-24 13:40:48',NULL),(56,21,100,200,'2019-09-24 13:40:48',NULL),(57,21,101,300,'2019-09-24 13:40:48',NULL),(58,22,10,100,'2019-09-24 13:45:12',NULL),(59,22,100,200,'2019-09-24 13:45:12',NULL),(60,22,101,300,'2019-09-24 13:45:12',NULL),(61,23,10,100,'2019-09-24 14:57:35',NULL),(62,23,100,200,'2019-09-24 14:57:35',NULL),(63,23,101,300,'2019-09-24 14:57:35',NULL),(64,15,10,100,'2019-09-24 15:10:24',NULL),(65,15,100,200,'2019-09-24 15:10:24',NULL),(66,15,101,300,'2019-09-24 15:10:24',NULL);
/*!40000 ALTER TABLE `user_myroom_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_myroom_item`
--

DROP TABLE IF EXISTS `user_myroom_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_myroom_item` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `item_id` int(11) NOT NULL DEFAULT '0' COMMENT 'item ID',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_myroom_item_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=68 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_myroom_item`
--

LOCK TABLES `user_myroom_item` WRITE;
/*!40000 ALTER TABLE `user_myroom_item` DISABLE KEYS */;
INSERT INTO `user_myroom_item` VALUES (1,9,101,'2019-09-19 15:48:22'),(2,9,201,'2019-09-19 15:48:22'),(3,9,301,'2019-09-19 15:48:22'),(4,9,101,'2019-09-19 15:48:49'),(5,9,201,'2019-09-19 15:48:49'),(6,9,301,'2019-09-19 15:48:49'),(7,9,102,'2019-09-19 15:49:32'),(8,9,202,'2019-09-19 15:49:33'),(9,9,302,'2019-09-19 15:49:33'),(10,1,102,'2019-09-20 09:27:03'),(11,1,202,'2019-09-20 09:27:03'),(12,1,302,'2019-09-20 09:27:03'),(13,1,101,'2019-09-20 09:59:26'),(14,1,201,'2019-09-20 09:59:26'),(15,1,301,'2019-09-20 09:59:26'),(16,1,103,'2019-09-20 09:59:29'),(17,1,203,'2019-09-20 09:59:29'),(18,1,303,'2019-09-20 09:59:29'),(19,17,101,'2019-09-20 10:33:50'),(20,17,201,'2019-09-20 10:33:50'),(21,17,301,'2019-09-20 10:33:50'),(22,17,102,'2019-09-20 10:33:53'),(23,17,202,'2019-09-20 10:33:53'),(24,17,302,'2019-09-20 10:33:53'),(25,17,103,'2019-09-20 10:33:56'),(26,17,203,'2019-09-20 10:33:56'),(27,17,303,'2019-09-20 10:33:56'),(28,17,104,'2019-09-20 10:33:59'),(29,17,204,'2019-09-20 10:34:00'),(30,17,304,'2019-09-20 10:34:00'),(31,17,105,'2019-09-20 10:34:02'),(32,17,205,'2019-09-20 10:34:02'),(33,17,305,'2019-09-20 10:34:02'),(34,1,104,'2019-09-20 15:01:29'),(35,1,204,'2019-09-20 15:01:29'),(36,1,304,'2019-09-20 15:01:29'),(37,1,205,'2019-09-20 15:01:57'),(38,12,105,'2019-09-20 18:24:24'),(39,12,205,'2019-09-20 18:24:24'),(40,12,305,'2019-09-20 18:24:24'),(41,18,103,'2019-09-21 03:39:13'),(42,18,203,'2019-09-21 03:39:13'),(43,18,303,'2019-09-21 03:39:13'),(44,3,101,'2019-09-24 10:36:11'),(45,3,201,'2019-09-24 10:36:11'),(46,3,301,'2019-09-24 10:36:11'),(47,3,102,'2019-09-24 10:36:13'),(48,3,202,'2019-09-24 10:36:13'),(49,3,302,'2019-09-24 10:36:14'),(50,3,103,'2019-09-24 10:36:15'),(51,3,203,'2019-09-24 10:36:15'),(52,3,303,'2019-09-24 10:36:15'),(53,3,104,'2019-09-24 10:36:18'),(54,3,204,'2019-09-24 10:36:18'),(55,3,304,'2019-09-24 10:36:18'),(56,3,105,'2019-09-24 10:36:21'),(57,3,205,'2019-09-24 10:36:21'),(58,3,305,'2019-09-24 10:36:21'),(59,5,101,'2019-09-24 14:59:18'),(60,5,201,'2019-09-24 14:59:18'),(61,5,301,'2019-09-24 14:59:19'),(62,5,102,'2019-09-24 14:59:22'),(63,5,202,'2019-09-24 14:59:22'),(64,5,302,'2019-09-24 14:59:22'),(65,5,103,'2019-09-24 14:59:24'),(66,5,203,'2019-09-24 14:59:24'),(67,5,303,'2019-09-24 14:59:24');
/*!40000 ALTER TABLE `user_myroom_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_scene_clear`
--

DROP TABLE IF EXISTS `user_scene_clear`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_scene_clear` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `actor_id` smallint(6) NOT NULL DEFAULT '0' COMMENT '상대(강태준:0,백현성:1,정재민:2,김동주:3,정석환:4)',
  `scene_id` int(11) NOT NULL DEFAULT '0' COMMENT 'scene ID',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_scene_clear_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=206 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_scene_clear`
--

LOCK TABLES `user_scene_clear` WRITE;
/*!40000 ALTER TABLE `user_scene_clear` DISABLE KEYS */;
INSERT INTO `user_scene_clear` VALUES (1,1,6,10100,'2019-09-19 13:14:45'),(2,2,6,10100,'2019-09-19 13:16:05'),(3,3,6,10100,'2019-09-19 13:16:13'),(4,2,6,10101,'2019-09-19 13:17:01'),(5,5,6,10100,'2019-09-19 13:23:29'),(6,5,6,10101,'2019-09-19 13:26:12'),(7,5,6,10102,'2019-09-19 13:27:49'),(8,5,6,10103,'2019-09-19 13:29:34'),(9,5,6,10104,'2019-09-19 13:31:22'),(10,5,6,10105,'2019-09-19 13:33:22'),(11,6,6,10100,'2019-09-19 13:34:32'),(12,5,6,10106,'2019-09-19 13:35:12'),(13,7,6,10100,'2019-09-19 13:38:28'),(14,5,6,10107,'2019-09-19 13:39:04'),(15,8,6,10100,'2019-09-19 13:39:45'),(16,5,6,10108,'2019-09-19 13:40:56'),(17,2,6,10102,'2019-09-19 13:41:45'),(18,5,6,10109,'2019-09-19 13:43:12'),(19,2,6,10103,'2019-09-19 13:43:28'),(20,3,6,10101,'2019-09-19 13:43:56'),(21,3,6,10102,'2019-09-19 13:44:35'),(22,3,6,10103,'2019-09-19 13:45:19'),(23,3,6,10104,'2019-09-19 13:46:13'),(24,3,6,10105,'2019-09-19 13:46:50'),(25,3,6,10106,'2019-09-19 13:47:22'),(26,3,6,10107,'2019-09-19 13:47:48'),(27,3,6,10108,'2019-09-19 13:48:14'),(28,3,6,10109,'2019-09-19 13:48:40'),(29,2,6,10104,'2019-09-19 13:49:32'),(30,2,6,10105,'2019-09-19 13:52:08'),(31,2,6,10106,'2019-09-19 13:53:22'),(32,2,6,10107,'2019-09-19 13:54:12'),(33,2,6,10108,'2019-09-19 13:54:56'),(34,2,6,10109,'2019-09-19 13:55:39'),(35,9,6,10110,'2019-09-19 14:05:49'),(36,9,6,10111,'2019-09-19 14:06:39'),(37,9,6,10112,'2019-09-19 14:10:55'),(38,2,0,10110,'2019-09-19 14:35:50'),(39,11,6,10100,'2019-09-19 15:14:09'),(40,12,6,10100,'2019-09-19 16:11:48'),(41,12,6,10101,'2019-09-19 16:43:06'),(42,12,6,10102,'2019-09-19 17:00:56'),(43,1,6,10101,'2019-09-20 09:19:57'),(44,1,6,10102,'2019-09-20 09:20:41'),(45,1,6,10103,'2019-09-20 09:21:23'),(46,1,6,10104,'2019-09-20 09:22:14'),(47,1,6,10105,'2019-09-20 09:22:47'),(48,1,6,10106,'2019-09-20 09:23:25'),(49,1,6,10107,'2019-09-20 09:24:03'),(50,1,6,10108,'2019-09-20 09:24:43'),(51,1,6,10109,'2019-09-20 09:25:19'),(52,5,3,10500,'2019-09-20 09:32:11'),(53,5,3,10501,'2019-09-20 09:35:54'),(54,5,3,10502,'2019-09-20 09:38:37'),(55,5,3,10503,'2019-09-20 09:42:57'),(56,16,6,10100,'2019-09-20 09:44:33'),(57,5,3,10504,'2019-09-20 09:46:21'),(58,16,6,10101,'2019-09-20 09:48:38'),(59,5,3,10505,'2019-09-20 09:50:32'),(60,12,6,10103,'2019-09-20 09:51:58'),(61,16,6,10102,'2019-09-20 09:52:24'),(62,5,3,10506,'2019-09-20 09:54:26'),(63,16,6,10103,'2019-09-20 09:56:20'),(64,12,6,10104,'2019-09-20 09:57:12'),(65,17,6,10100,'2019-09-20 10:00:00'),(66,5,3,10507,'2019-09-20 10:00:09'),(67,12,6,10105,'2019-09-20 10:00:12'),(68,16,6,10104,'2019-09-20 10:00:20'),(69,5,3,10508,'2019-09-20 10:03:27'),(70,12,6,10106,'2019-09-20 10:04:23'),(71,16,6,10105,'2019-09-20 10:04:32'),(72,17,6,10101,'2019-09-20 10:05:12'),(73,5,3,10509,'2019-09-20 10:06:43'),(74,12,6,10107,'2019-09-20 10:07:44'),(75,17,6,10102,'2019-09-20 10:08:41'),(76,16,6,10106,'2019-09-20 10:08:46'),(77,5,3,10510,'2019-09-20 10:09:50'),(78,12,6,10108,'2019-09-20 10:11:16'),(79,16,6,10107,'2019-09-20 10:12:37'),(80,17,6,10103,'2019-09-20 10:12:40'),(81,5,3,10511,'2019-09-20 10:13:11'),(82,12,6,10109,'2019-09-20 10:15:37'),(83,5,3,10512,'2019-09-20 10:16:06'),(84,17,6,10104,'2019-09-20 10:16:57'),(85,16,6,10108,'2019-09-20 10:17:00'),(86,5,3,10513,'2019-09-20 10:19:55'),(87,17,6,10105,'2019-09-20 10:20:39'),(88,17,6,10106,'2019-09-20 10:25:40'),(89,17,6,10107,'2019-09-20 10:27:24'),(90,17,6,10108,'2019-09-20 10:28:46'),(91,17,6,10109,'2019-09-20 10:30:09'),(92,17,0,10110,'2019-09-20 10:38:21'),(93,17,0,10111,'2019-09-20 10:39:59'),(94,17,0,10112,'2019-09-20 10:44:23'),(95,17,0,10113,'2019-09-20 10:46:09'),(96,17,0,10114,'2019-09-20 10:47:37'),(97,5,3,10514,'2019-09-20 10:48:00'),(98,17,0,10115,'2019-09-20 10:50:03'),(99,17,0,10116,'2019-09-20 10:52:47'),(100,17,0,10117,'2019-09-20 10:56:02'),(101,17,0,10118,'2019-09-20 10:57:49'),(102,5,3,10515,'2019-09-20 10:59:46'),(103,17,0,10119,'2019-09-20 11:00:26'),(104,17,0,10120,'2019-09-20 11:02:05'),(105,5,3,10516,'2019-09-20 11:02:49'),(106,17,0,10121,'2019-09-20 11:05:51'),(107,17,0,10122,'2019-09-20 11:09:24'),(108,17,0,10123,'2019-09-20 11:13:11'),(109,5,3,10517,'2019-09-20 11:13:42'),(110,17,0,10124,'2019-09-20 11:16:08'),(111,17,0,10125,'2019-09-20 11:18:57'),(112,17,0,10126,'2019-09-20 11:22:16'),(113,5,3,10518,'2019-09-20 11:22:48'),(114,17,0,10127,'2019-09-20 11:25:33'),(115,5,3,10519,'2019-09-20 11:28:20'),(116,17,0,10128,'2019-09-20 11:28:46'),(117,17,0,10129,'2019-09-20 11:32:10'),(118,17,0,10130,'2019-09-20 11:35:05'),(119,5,3,10520,'2019-09-20 11:35:22'),(120,5,3,10521,'2019-09-20 11:38:20'),(121,17,0,10131,'2019-09-20 11:38:20'),(122,5,3,10522,'2019-09-20 11:41:16'),(123,17,0,10132,'2019-09-20 11:41:35'),(124,17,0,10133,'2019-09-20 11:44:28'),(125,17,0,10134,'2019-09-20 11:47:27'),(126,12,3,10500,'2019-09-20 11:49:54'),(127,12,3,10501,'2019-09-20 11:52:55'),(128,12,3,10502,'2019-09-20 11:55:04'),(129,12,3,10503,'2019-09-20 11:57:39'),(130,12,3,10504,'2019-09-20 12:00:23'),(131,12,3,10505,'2019-09-20 12:03:02'),(132,12,3,10506,'2019-09-20 12:21:35'),(133,17,0,10135,'2019-09-20 12:25:54'),(134,12,3,10507,'2019-09-20 12:33:22'),(135,12,3,10508,'2019-09-20 12:35:04'),(136,12,3,10509,'2019-09-20 12:41:31'),(137,12,3,10510,'2019-09-20 12:44:01'),(138,17,0,10136,'2019-09-20 13:11:36'),(139,17,0,10137,'2019-09-20 13:15:23'),(140,17,0,10138,'2019-09-20 13:18:32'),(141,17,0,10139,'2019-09-20 13:21:07'),(142,5,3,10523,'2019-09-20 13:21:55'),(143,17,0,10140,'2019-09-20 13:24:33'),(144,17,0,10141,'2019-09-20 13:27:36'),(145,17,0,10142,'2019-09-20 13:30:39'),(146,17,0,10143,'2019-09-20 13:33:51'),(147,17,0,10144,'2019-09-20 13:37:38'),(148,5,3,10524,'2019-09-20 13:37:42'),(149,17,0,10145,'2019-09-20 13:40:47'),(150,17,0,10146,'2019-09-20 13:44:49'),(151,16,6,10109,'2019-09-20 14:08:58'),(152,17,0,10147,'2019-09-20 14:34:29'),(153,17,0,10148,'2019-09-20 14:37:25'),(154,17,4,10300,'2019-09-20 14:54:51'),(155,17,4,10301,'2019-09-20 14:58:37'),(156,17,4,10302,'2019-09-20 15:01:33'),(157,17,4,10303,'2019-09-20 15:06:17'),(158,17,4,10304,'2019-09-20 15:10:15'),(159,17,4,10305,'2019-09-20 15:13:28'),(160,17,4,10306,'2019-09-20 15:17:22'),(161,17,4,10307,'2019-09-20 15:23:04'),(162,17,4,10308,'2019-09-20 15:26:59'),(163,17,4,10309,'2019-09-20 15:29:50'),(164,17,4,10310,'2019-09-20 15:33:21'),(165,17,4,10311,'2019-09-20 15:37:14'),(166,17,4,10312,'2019-09-20 15:40:13'),(167,5,1,10200,'2019-09-20 15:53:13'),(168,5,1,10201,'2019-09-20 15:56:10'),(169,17,4,10313,'2019-09-20 16:00:39'),(170,17,4,10314,'2019-09-20 16:03:41'),(171,5,1,10202,'2019-09-20 16:33:38'),(172,5,1,10203,'2019-09-20 16:37:18'),(173,12,3,10511,'2019-09-20 18:13:27'),(174,12,3,10512,'2019-09-20 18:23:17'),(175,12,3,10513,'2019-09-20 18:27:39'),(176,12,3,10514,'2019-09-20 18:29:45'),(177,12,3,10515,'2019-09-20 18:32:16'),(178,18,6,10100,'2019-09-21 02:56:16'),(179,18,6,10101,'2019-09-21 03:03:33'),(180,18,6,10102,'2019-09-21 03:07:29'),(181,18,6,10103,'2019-09-21 03:11:45'),(182,18,6,10104,'2019-09-21 03:16:30'),(183,18,6,10105,'2019-09-21 03:20:54'),(184,18,6,10106,'2019-09-21 03:25:17'),(185,18,6,10107,'2019-09-21 03:29:13'),(186,18,6,10108,'2019-09-21 03:33:28'),(187,18,6,10109,'2019-09-21 03:38:26'),(188,18,4,10300,'2019-09-21 03:41:49'),(189,19,6,10100,'2019-09-23 13:45:10'),(190,19,6,10101,'2019-09-23 13:51:11'),(191,19,6,10102,'2019-09-23 14:45:13'),(192,1,0,10110,'2019-09-24 10:26:32'),(193,2,0,10111,'2019-09-24 10:26:37'),(194,1,0,10111,'2019-09-24 10:27:08'),(195,1,0,10112,'2019-09-24 10:27:45'),(196,1,0,10113,'2019-09-24 10:28:36'),(197,1,2,10400,'2019-09-24 10:30:53'),(198,1,4,10300,'2019-09-24 10:31:33'),(199,20,6,10100,'2019-09-24 13:35:14'),(200,21,6,10100,'2019-09-24 13:41:39'),(201,22,6,10100,'2019-09-24 13:46:13'),(202,23,6,10100,'2019-09-24 14:59:15'),(203,9,0,10110,'2019-09-24 15:29:00'),(204,9,0,10111,'2019-09-24 15:29:48'),(205,9,0,10112,'2019-09-24 15:30:36');
/*!40000 ALTER TABLE `user_scene_clear` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_scene_ending`
--

DROP TABLE IF EXISTS `user_scene_ending`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_scene_ending` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) DEFAULT NULL,
  `actor_id` smallint(6) DEFAULT NULL,
  `scene_id` int(11) DEFAULT NULL,
  `reg_date` datetime DEFAULT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_scene_ending`
--

LOCK TABLES `user_scene_ending` WRITE;
/*!40000 ALTER TABLE `user_scene_ending` DISABLE KEYS */;
INSERT INTO `user_scene_ending` VALUES (1,2,0,10181,'2019-09-20 09:53:17'),(2,2,0,10183,'2019-09-20 09:53:22'),(3,2,0,10180,'2019-09-20 09:57:34'),(4,2,0,10182,'2019-09-20 09:57:59'),(5,2,0,10184,'2019-09-20 10:01:29'),(6,2,1,10271,'2019-09-20 10:07:17'),(7,2,1,10272,'2019-09-20 11:17:18'),(8,2,1,10273,'2019-09-20 11:17:39'),(9,2,1,10270,'2019-09-20 11:19:30');
/*!40000 ALTER TABLE `user_scene_ending` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_scene_quiz`
--

DROP TABLE IF EXISTS `user_scene_quiz`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_scene_quiz` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `actor_id` smallint(6) NOT NULL DEFAULT '0' COMMENT '상대(강태준:0,백현성:1,정재민:2,김동주:3,정석환:4)',
  `scene_id` int(11) NOT NULL DEFAULT '0' COMMENT 'scene ID',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_scene_quiz_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_scene_quiz`
--

LOCK TABLES `user_scene_quiz` WRITE;
/*!40000 ALTER TABLE `user_scene_quiz` DISABLE KEYS */;
INSERT INTO `user_scene_quiz` VALUES (1,9,4,10375,'2019-09-19 14:28:18');
/*!40000 ALTER TABLE `user_scene_quiz` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_scene_reset`
--

DROP TABLE IF EXISTS `user_scene_reset`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_scene_reset` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) DEFAULT NULL,
  `actor_id` smallint(6) DEFAULT NULL,
  `reg_date` datetime DEFAULT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_scene_reset`
--

LOCK TABLES `user_scene_reset` WRITE;
/*!40000 ALTER TABLE `user_scene_reset` DISABLE KEYS */;
INSERT INTO `user_scene_reset` VALUES (1,4,0,'2019-09-19 13:21:42');
/*!40000 ALTER TABLE `user_scene_reset` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_soldout_item`
--

DROP TABLE IF EXISTS `user_soldout_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_soldout_item` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `pkg_id` int(11) NOT NULL DEFAULT '0' COMMENT 'soldout package ID',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_soldout_item_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_soldout_item`
--

LOCK TABLES `user_soldout_item` WRITE;
/*!40000 ALTER TABLE `user_soldout_item` DISABLE KEYS */;
INSERT INTO `user_soldout_item` VALUES (1,9,400,'2019-09-19 15:48:22'),(2,9,400,'2019-09-19 15:48:49'),(3,9,401,'2019-09-19 15:49:33'),(4,1,401,'2019-09-20 09:27:04'),(5,1,400,'2019-09-20 09:59:27'),(6,1,402,'2019-09-20 09:59:30'),(7,17,400,'2019-09-20 10:33:51'),(8,17,401,'2019-09-20 10:33:54'),(9,17,402,'2019-09-20 10:33:57'),(10,17,403,'2019-09-20 10:34:00'),(11,17,404,'2019-09-20 10:34:02'),(12,1,403,'2019-09-20 15:01:30'),(13,12,404,'2019-09-20 18:24:25'),(14,18,402,'2019-09-21 03:39:14'),(15,3,400,'2019-09-24 10:36:11'),(16,3,401,'2019-09-24 10:36:14'),(17,3,402,'2019-09-24 10:36:16'),(18,3,403,'2019-09-24 10:36:19'),(19,3,404,'2019-09-24 10:36:21'),(20,5,400,'2019-09-24 14:59:19'),(21,5,401,'2019-09-24 14:59:22'),(22,5,402,'2019-09-24 14:59:25');
/*!40000 ALTER TABLE `user_soldout_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_store_bill`
--

DROP TABLE IF EXISTS `user_store_bill`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_store_bill` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `member_id` int(11) NOT NULL,
  `item_id` int(11) NOT NULL COMMENT '구매아이템',
  `store_type` tinyint(1) NOT NULL COMMENT '스토어 타입(1:구글,2:원 스토어,3:애플)',
  `shop_type` tinyint(1) NOT NULL COMMENT '상점 종류(1:캐쉬상점,2:마이룸상점)',
  `sale_price` int(11) NOT NULL COMMENT '가격',
  `key_value` varchar(64) NOT NULL COMMENT 'orderId',
  `trans_value` varchar(1024) NOT NULL COMMENT '구매 정보',
  `reg_date` datetime DEFAULT NULL COMMENT '등록 시간',
  PRIMARY KEY (`idx`),
  KEY `fk_user_user_store_bill_member_id` (`member_id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_store_bill`
--

LOCK TABLES `user_store_bill` WRITE;
/*!40000 ALTER TABLE `user_store_bill` DISABLE KEYS */;
INSERT INTO `user_store_bill` VALUES (1,14,100,1,1,0,'trans:GPA.3346-1537-0557-37031','{\"type\":\"trans\",\"store\":1,\"Id\":14,\"time\":\"2019-09-19T08:49:37.070Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3346-1537-0557-37031\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1002\\\",\\\"purchaseTime\\\":1568882970221,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"gfjjonadiaocongemkkaplnh.AO-J1Oz4hexjasHYh2tC4KsdhR2WuXa7N60aFIiWWzFsWSpi6kYt_pr9KzufzsnzmSLQqIUcx_PDEHmm7h8t4tu1Xy1cozbzZynxLFLrINBynMuQyslw52oSfMXDvnAEgu3jzb4MdBiNnd7ssIBOzeJlUJ8lgtamZu0YcX29WFiWXPtEc_auygI\\\"}\",\"sign\":\"RV9FJnGxjd0g9cKamtTExTfjbmVezCkSPDG7L8m0ZnD65lwJDsHKZ9jAHrsr9VSfV3RdU6WJOqPdbvpxtMxkaRFDWpuxlVsapfuEcMpvQjAcT0WyxIPHKKHNsJ5Qhro98z4G9AABaTrhXjbShgXbhQJynSIyHC1fEtqBNQi/8wJ5knGeEA+jVzGMa2Oz6TaaVerCO3SPLM9EKJcFI+ehW8eAZma49orjn11spu2g9abHadsFxo2HJ9Du6Vn6eI018xeoyxtuyJkd2sQednF9PwTTDyIWWs8l2fCqaG1Gin10aP4AtuK7rpyDzlVjeAD6wOlWPp3aucCjqBZ5fIwU8A==\"}','2019-09-19 17:49:37'),(2,1,100,1,1,0,'trans:GPA.3343-8113-4382-82790','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T00:18:50.623Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3343-8113-4382-82790\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1002\\\",\\\"purchaseTime\\\":1568938725712,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"elfdaapfbcmobehpfhffkmdh.AO-J1OwXTFOI-4cUDQ5ygnMYFtUIoCe6DRJu9taC_dtfsm3gp5cA_QpKZwXfVrnDhrgUrGCZ-DN4IXAeY8zJeAOQrOypvnJD-fnaL6nKqPiei8D4rp7AIVP1SLGi8Umh-Bsj-1UEp4K6maIGkfcKJZiwB1VCZ8ReTgf23_vJl0P50pRhda16AUQ\\\"}\",\"sign\":\"QXkNssj6jdqP3EmoHG84yfe+6/EWivD0GEogXgiyH2EuiyE9cbjZ481QCE3vvWpHtP+7LJgInbhP8unj41sCTE266ZWDeJP2h7jnIVYhyg56XdRoJEplcLMxTeseYQ3uVi5ypkMapej1mccAhQsGnRjVeESmFTUgK5Iyp+wS6s83+UWYMt/eG7UKtiR5Hp8YCaieu7pP1XpmJRiBjELW6thpC9GIs0EN/dV2NGAKAa0joCX5s0r4hiZXufRerTmwVEBSedLdHdsZMcl7JAQ1ixRgMcvwjRFz1/f5SnhsJBjUCAXG7e+Ho+S+8ELsQMQ1PXaL3Qsb+m7OWkyfLUM8Mg==\"}','2019-09-20 09:18:50'),(3,12,100,1,1,0,'trans:GPA.3324-0661-0632-42450','{\"type\":\"trans\",\"store\":1,\"Id\":12,\"time\":\"2019-09-20T00:47:51.866Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3324-0661-0632-42450\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1002\\\",\\\"purchaseTime\\\":1568940458306,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"ghgeabkifcljlnndkjoofapl.AO-J1OyKBczd95bAQfZ_UP6L3wpzIRuAo8sV6SMMMCC6h64yT6w99_Ggai5ZsIoFDkKOH6KLWLTWDrC-NNYuKrRNp9RDX1Pmvm7kwczLUkwcDMlOTByN6oWae5h9rIwoGQ7doibbEew4wea0XUyo-lf6Eqp724Nvr4KIyo1mHp1JhVbEOA7pcbQ\\\"}\",\"sign\":\"Uk5x1e5km0EImWYazA5gmFDPLohd0XS7ePXZw/JEgi3TgokEFLCoPAeK4hHx+IUdSKN5+9Bl1S3tIbFL8oisgubuG+2XRd5bgeLUpmheUYzOh2YBQj2Gt6sdRV53ViCmIImAwrvNZiQX7VI4/4788vMG866Co5RTsVC9P8X6PaGJIzEdod+dMIkRWI1mVD/+NHckfAdV+PnQmobOs/Wcu/tw2ltAXEgjDlALmEDpGX1JAPutQ5PGoXITZWyN6zMguV57YeSckQmF8I26IC9ymLiq3fimdzWIx5ju4QWw3JmVm6XVK3gk+qCaEqsgF/RPBUPKZY0wzi1D4VhSsDpSbw==\"}','2019-09-20 09:47:51'),(4,12,101,1,1,0,'trans:GPA.3344-2085-1090-18910','{\"type\":\"trans\",\"store\":1,\"Id\":12,\"time\":\"2019-09-20T00:48:06.592Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3344-2085-1090-18910\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1003\\\",\\\"purchaseTime\\\":1568940482895,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"lgdfadgpbdolenheghjjfcej.AO-J1OzpBsJbHCZpxugycgJwiI16NY_SWzXRsxoh-CapYZTe_XfFomWnbrgXOVp_0A5fdr_FYMLHfVpZuwuoSz2_M_k_n-0xumu8s1FPLD6DVNWweVgFqeRAJAdoCk5jIOkfBTPSw4_L2Z_c79Bk5gmxINeDFSTCuVehsfps3w7MQay8ADVR-HQ\\\"}\",\"sign\":\"dN7HW/2Pynu5qCmNGJOet8VMRO71UJ1T/hFD4MBpUQk1CXoqwKgJh2uoNFrchpvEEkb+U10g1LJ19S8zjT7ekkerMKi5j5W/c7P19U6DBIPkBFiTNQswVNLJcQ16AZGSwCZCZqqbhIuN1yCehUQuOILoqh3KBWntk0yK5XKv7F9uWZClp/fxHcvSJcaoqKzEnrUaaBfVMpjleKAAMx8knmL3q/YOTSS4cQUqs4N6AcyiNfeQwMacCSIxDDh5bb9PGFKrl5P2qnC7lkQPHV+kY3hhqk4+P3Ps+d8wURNWOBg6CGig+xenSZJl5QzQOZ+8uKZH8uiATu5yvAvWEEPywg==\"}','2019-09-20 09:48:06'),(5,1,101,1,1,0,'trans:GPA.3356-5221-2839-40007','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T00:51:05.740Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3356-5221-2839-40007\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1003\\\",\\\"purchaseTime\\\":1568940661374,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"jmimkidjccmcoelgngigfocd.AO-J1OyFDnRyf3ljXYOqWGZdZhY0ZKRLY3T_VJurb4CdIoAH0ZWxYngYMhaZ9dv9eDtB2SvljAlspP9P0b2kPGMPMIgV6PNlWd0gEz1peMfi-UU5d6dLTA5sSCC5iXhp3F7s0ZIDEVH1tvvdCplH2YzQ66iJg5mOASK1a0cEqP2znMPNdwKgLR8\\\"}\",\"sign\":\"JTuxvQBjJL1v3F0gmt3crc5AEoKfd00IfVxrMKzgEt2gfMzYUhAiCK2lEvvTYyBx558oIjoy+hZJD4wnI6Ji/9dWTqParHgrb2PWZJ4kIC4kRmRKbMlVCm+QZqn9E8KAn64bKYSb09w/gq/WcTiW5Rw429BeJUeEBlJC7CrjJetlvEGwNriMUtqYqFNX++oQZ9Vsj6u4V9JWm+ttp+aKKSfAeSra+12l2+wBZcmiUpCd0dZwRp9iNuLB3XFLj8prdTyXDGRUggUz0kuLKV41iI3RpNkR6V70+2SCxDBP1d+p/OXt0Ji5ymjnJRExChLLzYuMBIcPArdZX7vWkJhzuQ==\"}','2019-09-20 09:51:05'),(6,1,102,1,1,0,'trans:GPA.3329-1172-9116-46523','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T00:51:14.324Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3329-1172-9116-46523\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568940670627,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"dmminflkfdleambjkmcnbaag.AO-J1OwwuiCXwQtnUYRzkq7Trt4MvblO568V0xADrfzlA2hI9PeNzcZzHdbKp6mj0YZEpZ3IBDUGjNpLhaLgWFXeDN-ZDcbtCLWMnYJ9vjS8bSYjilsQXmzw_OnkIuqXlPb2U0fliaJnwNAO4x7-myZbvAxO5tURbpvSgqNdHx5p36qKyKySkuk\\\"}\",\"sign\":\"Xn+3NdevSas6RmubuReCElQBBzJscwwPbUnHYx0MAeM1MuZZN1+8LkPCj95NMYTIlItdCqliQKmfeCQ0KUMq3OQgR/zgeITzfc2y/lGqTl8Fs454OpCSZDNj6DzM4KUHQ1412ydH+ihfPWg5yOzdlC/up+YxOgaiGyq0O0oUsTINA7TWUEY8McaBsdAjkjOd3oHu/wybwCRlFHXTxbijjvzKyZBiqmC0sJPA0QYecpEJUOgXmqiVnsEcclshkzLfw3fWLDmk9uFBxbk+iP8NfcmEoHEQHbqz4juJ/Az14ta6/FNg9dZk+tnASqeMxinHuSBBAFO2Dq3JEDVGNXv6xw==\"}','2019-09-20 09:51:14'),(7,1,102,1,1,0,'trans:GPA.3393-5668-0549-98580','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T00:51:25.292Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3393-5668-0549-98580\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568940681531,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"omnlmpbcokogohnjplaidohg.AO-J1OzfV4mOIzswmCO6xYJB_OeopQejvh0KH5vpuytCalz7bfZeBLdA5Y9xp4gbjiWjWUZjxtFKbVcsg7PHrO5MzTyKDf4YntZOcrx9EkmIh-c8VLUf0IiOihaKfyRk_njMArVC8FAAA-uxC86RqeDx74P7M7Vw4iYiCXy6utWMuE4waUl8efw\\\"}\",\"sign\":\"Bbf24sGPJOnAZwEaTIZTgfZdWG93PQZTzVnFHTp4zK0+LGt6CoK7azNHJd0B4j5hStkuogrNXxCQKQZC+XRUgA2s0Lw+aRsK1Iu+XnAR0KFEIE9PQ+B7CTYnde4xa5cvNUwqno+5O7ZUV9KhPUAgGYwAiR2hfLcZxHRCsu1KX+evf4jrfHEOyRPCgUPXyat8S4WfT0QquNtgqpt1KSSxyF6MOz4g6TaXMuH1FEBsODb3P9fvDATTvp/1f+zRSDzABkC7AlzrDCP/RTm73itC8Ewga09iCQ+rHQpTIw34fFCkli0ByGZmOp0ujG3XghPE+KNs5UaRE9yuDmtOEdbpRQ==\"}','2019-09-20 09:51:25'),(8,1,102,1,1,0,'trans:GPA.3362-4582-4810-57427','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T00:51:34.421Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3362-4582-4810-57427\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568940690664,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"mmdkcihdpimlmkennolbmmdi.AO-J1OwLv1DuZt5YbyrKCrV8K-3_Beme0M0QdbXb0Npf-KQMI1IrJZkIYpwA4QqdQiN75C1g3LC-8GSGMaNeOxTcTSflzXms62axWDcon7L4KCMD9v8TVjgt5qUYjf4q_Ye6nvQr-l4n6ZcnkwNL7F-NSVUtszMsHodpo-82aeUx4d-tg7UdG_M\\\"}\",\"sign\":\"PcuSaRecsB8AJ7vLeLmkoyEAkT4hx3Ftf2YCB0ohwYLmLcQdJ5ieWsg4ujzjMQS6W/mrdeJRlkrxJukfA3T7BA27B2rLpu1xWGy8475C+XtXbf3xxAaYM0SQRrVpFQA/jun8W2BNU1ALZ3GsAp3y9bGuQNYE4QD3B3xmht8g4wpu3tVfRXqIm7fE8Oa33ZweXi4TJg65L494VCMduEROQMONy+RlvZoVSZ0bYhcxOrc8vdjEQpSp4Rcn7hFIJbtX3cPymspP2+5CFqoEsXq42gygkaDp4gl+ZgCx4a2KqxVtaYA1Z6yxF7aw1kLNZ9EWHpVA+TBxbA87SZKk/DaKLQ==\"}','2019-09-20 09:51:34'),(9,1,100,1,1,0,'trans:GPA.3327-6453-5406-98266','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:02:21.676Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3327-6453-5406-98266\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1002\\\",\\\"purchaseTime\\\":1568941337745,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"knecmijinfjepdihlehmlpho.AO-J1Oyx5zJq_Zpyhlz02azW7ec2eTGccBxpWz_Xz_Ku3N4SVCpFVb1h8uVwe9Q6Qn9PsS-F4VI6LlsMnuvYPgveM-1uuV7Pw2akQMoElMbZI0RrZFQMptgb59Mv-jO5Jcd9QW63DRWj3k5jZ566ne8kqlEsLs9A3ulMA2kLzv3HbpWtVQr_V04\\\"}\",\"sign\":\"HYlEoO9V3Unyu4MFixObVReGCsbGjNQQIxv5SEMjwFyevKhPGPdmtWff2IqofiJWrykn1NH0VLTn4Nrbumm6n+YPhA4N/y3BGuJ29xp+429hdNy+FAWASS3pi0ZHy9b/Ei3IdhSB0p2t8y/XgZJAYR0mc0JrEGjr3F7HGKRJB/vdAqoj7DEXEVDuW3x/Te3qnIZc+ChAT6feUM5HMp2rh3JZveYMM2cKb9s6ymgwe5+YxznBnRkLxvbWl8E8wUICGL3buz165TstUlTzQug4/vXn+hvic6U0TDi7JKsn/hm0n+ucIl++3ZQRu/jkuVH6VOcbxPFUvaBpYNFVfnmIfw==\"}','2019-09-20 10:02:21'),(10,1,101,1,1,0,'trans:GPA.3334-6717-3167-03534','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:02:29.141Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3334-6717-3167-03534\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1003\\\",\\\"purchaseTime\\\":1568941345535,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"anglbhhpgpkjmnhjplbjghkj.AO-J1OypbMJKBbu7CLaKYWtxrMH55cpmUS54vnlmMaOXXrDvfLPOdK8XbWtPJAsUL6IQWfvltAwPIDlXBFlSIDzFkhqnQHzlPxFGyftI63p_6xPDARt7GjWJEfN2barF7RNzI7iwdZRixoCXksWNedVcWdBrZxyjsxCHdemMQbE0GmN8MuAsz_g\\\"}\",\"sign\":\"V97Q+spAxsjEAS56eVhBzZCO4SXZ1rrJ+LxzPP0pIUbHJbuvafpibQONVBa4YmQ6xNrfayhEYs1cwwd1uSjj4WVEVrw/8S7jtqOi6XFMVv78xzZ62Y6iJMiLjwBO+l8LuFDkKWPJWvORFZmJZlgJ8V3IkH5cmonIhAOfpE47NoWEgndFjdUde7tiScaSDnMMp9XoiVxKciMbQ4Er16Ez4KWtnlwFlQUeWWFaQIsdBs9m5icxnQ2vorw35mpY+MGQLeTonaC0q46lPCgDqZJEZylQKRRp1opMryBtpDnO7u2sA6aWPFvsRq/LSeH1HRkVuTxmlFhTJJrI+fWr9FqLFg==\"}','2019-09-20 10:02:29'),(11,1,102,1,1,0,'trans:GPA.3365-5054-8894-49772','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:02:37.624Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3365-5054-8894-49772\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568941353619,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"kefdmachffllgdafacglccap.AO-J1OwOFU8PgDTP1zJgJORe7LI5Q9f51sAlhyPVBZsmoOWJ7ajsd9qybPKvJTQPqazUUn4Q0Wfg1fNPtlGRjPX6pg3TmvsqtN9WdyFgOpNA97YaH9MMuQ_TQZ8WkRj9SbCLs6IzSufk-_HIpMEukMipu1awiIEted6KN8fmT7RFvUvNiOyPpxw\\\"}\",\"sign\":\"AoKQ4mOHK6KNNXd2vF8fkxM8MxYJR8vs0sLz+1TdyWeoDEoyP5WLE2pMC9Xx2mDfBQo2rOHeiACE3fzaSpTVyJp+UXJwIdrN0RnL8WtKPmhsGRtoq3oSr6l1RQ5by63WCUimqjrwOjy5lpuebZwHZLo+vJwuoHcurPd8b8SJd0Y6/bs2OBMuSbmxEmE+L17cb/qIknIxoEYqNZ/Mw+qtyx6CzPsqhf8Q6HyTn6rjCtfrVz235ekUp1OE6L8IYF5sPnVyMPPi/nPiQUCXC1j2EDiqgPleeWD/VV03B4wXUd4zlvhOKZFlcyWvj9k92DMyikJ+fvg/3gi7eda3xhFcxg==\"}','2019-09-20 10:02:37'),(12,1,103,1,1,0,'trans:GPA.3312-9576-1855-53067','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:02:54.375Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3312-9576-1855-53067\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1005\\\",\\\"purchaseTime\\\":1568941370852,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"cegjndkeaaiogfipachjoclc.AO-J1Ox7rLjfsaR8CFHgxe-EG4I7_zrG_ZN9TytCjxFU7iP9jEJH7ydfu6klkdNVr51zzdu6ACjuT_ECY1JPVxJca3X100ntePlGIKdB3ADzH05L5sNCLWNpDswDp4fY9wgNbVQC9RQjLs-9HuLdIs9RMHBVoXtqyLbZsnkrgMGS5HfUGcKLeCY\\\"}\",\"sign\":\"XW9wrwzgcWnrcjJQxMz+YFN/mdSrPyThLnZVeIvxnCb0yQSQZlm975pmnrXG/NPYoH0yXOB/N+2eAWHQrRIwZHlfRrlUaZW85c4vnL9r9lYOKSmtzwveinx3QKZgCdTICI7UlD5l3NSMgFFUbWIsYEYXYub7azTPepzZweGBEqeCIdi8Xz1++egbyj8JW9KTQ7JOCdfmG9EFJb9SkgQprVlsXQUJmfBOWsslvpckvCxB/jWvniDwqi+yRzkhxwHlvGJGy6MddaIWoVUQFtMJS7giu1YWsbju8nM+SFlIpv2pLMJ0rkRqAx8nmHmEB1KspOvhmQ1yqZydAX+0BfrnJA==\"}','2019-09-20 10:02:54'),(13,1,102,1,1,0,'trans:GPA.3310-1948-2726-59726','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:05:35.731Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3310-1948-2726-59726\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568941531915,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"cffnhppchaabgheioehhhmdf.AO-J1OxS83bk5MOffEkgHpBr7o2sqALGGDOZWYXQy7JKvircfMVlhVAFiqJNvTNdwmLt4NPokoAGIEzeF0JSjbsVkfEzvkNXVN8WIhAqQlO3CyOqR24-uGS_P6eyNKPEJi8dytU_2s_od5zq7YkDB695_0YkswO9jm5ujZtN0TnbMERM6TJMUMk\\\"}\",\"sign\":\"WViAzz0krSYICs7dk1Bk3R3caJbbHvfM/xYQiPKDLF3bB8G0DcAVcLQ5i32uHFxAdL6YwepnCAwzchBEo7TYPuhrMB2R/X7OE5Sf8jGgFGhjaRztZyPub01+B4lsJJSMLzHJ58rG/tPZSI2K3ZIdNwl6ZcMiE/uyxcU12yjWJK2U+JaLtEI7jQZQGLCXLWTQlaibpkROYKt5rg3MsM6RL6vqLu7u13g2j2lG9ZO+loaxxwKe1tVoUGtq6cgaFkvQqVuliphGejZAoi5haO+GnuTHfG3/jwrjAwKtnLhJ3oMSCKOLBMR4sEb66yyeJa3/fVngUPXfhA2gqkZWEtH1DQ==\"}','2019-09-20 10:05:35'),(14,1,102,1,1,0,'trans:GPA.3367-2758-5220-98085','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:32:21.820Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3367-2758-5220-98085\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568943137522,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"mbmdgekolplleicjeecojpad.AO-J1OxaMq6eBEXiFk34-r3xcP5lDXoIMotRbRbS9vJxpL2XxEuq7lKH0-wkUrk4YOa_Pxoy_rb9fkB072aoQBiUH7Tp69dmOx5EDnJPxWr_U66AuwokiBp1NZTC79UHSfWq8dMHU0thlnRaoY0uuPctF9Ud7_1fqPhhRUbHm-NKU-UnNwJDG2E\\\"}\",\"sign\":\"ITarhuzEk5r6NfeG23ERI140JJWCRKT4kCAu2EcbhhhvQDx6ZUCGTQ6N9fH9J8LRSXlfo3ScenOIGkF9SkvKVc1GTJs30zkCuey69S0cXWui2OvO9m2s+cKN3YnzCcjB77NUlVA2dvg+xi4uMwf/cInMhE3ADfjL6r5TTm+hwfmwxLS4fTRSNLo1mHhI9d9ZtRLdHoGWTcgYlYxEmVoIfgcBGh2f3LnMYLRt/5RqwO0Jz2SrQO1/FrUJcFjX9asMGO4eFIZyCWlTDwdi+wvk+EACx47Wunar5rrdHxrpG8zBLA/LOSprU/YlxN51P75cbPJy4z3XUVl78coRam9mZg==\"}','2019-09-20 10:32:21'),(15,1,102,1,1,0,'trans:GPA.3321-3196-2888-30946','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:35:18.123Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3321-3196-2888-30946\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568943314128,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"gcbafocdokfedcbbjagpcjla.AO-J1OykTN9-lRbsexzl54_pR_f-T76QOHbl_wggmIEcPzOv1jS-ectc7Gfr8-XHIdYfoBN6dFXBaHtLxDI6dFs2b4OQJk6r1okOUjy_VxLEGfED_qmRWKCXBhoc8vPaK0pBal0py_yd9kXH-9zagOoCjOqeFjH5dBcDFILZxdffd8XviPKhcYw\\\"}\",\"sign\":\"WXD6diP6SmiK6wpsX3upqYiKCug7EY9Eocol9c/EKNGi2S1aOuiaTtX+VRxvzdhvPp4kk9ZZelxXZZz2qFDEtOqgmsL5nM9YHp1bk0NYhkwDpa3BasRk7Qnsj1bpkv6a99r6J1wuQkCgMEwFPn5vKOEESPFyZCHxk4oFXxfhhj17s7sMFz3XbLHIJkQ8xQ4pIeoednnOG/8SXBruTgVhHFQLkBM2k6UgJDFaNqeRSMrNG7E+5nWB0daS+zPZU+ToQBVx8abKkxtJ1e/kwcRS9Q2tyFYp9LgxBXmBnuERl0AVKJBMx9WJV+9ss0g+q1/3OaX9I2Nk2EAq0rDkfONrcg==\"}','2019-09-20 10:35:18'),(16,1,102,1,1,0,'trans:GPA.3351-2714-8033-70241','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T01:59:23.969Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3351-2714-8033-70241\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568944759661,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"kjejpgjnedkhggjajlnmmdno.AO-J1OwReFNri9iI9e9naHITUzb6lNfcqhcyL8-HFnjJxE1fNTjd5wi5V8fJpUtfwaH63BboJvD2KEOc-AOZsaj7-f7hO56w0fdpQczJ6mCz1vfSM-8h14-Jqv1lKiVZ0dDyWO9o8KuU9BGpqCyk8nhug5TaBGJ13trHQB4SqcBjHcx8pERKqyE\\\"}\",\"sign\":\"a1oa5cTt7XGmxzOkz2Ba2bD4g/w7stlq8H/XrW6h664q0cPw3Pxb4bt8Gva8YlqW5w8z8klBjk20FjGbR+OncF8s7IldrFlEjY7GCYxt8H+Hil+lIVuSgA7ZH1y4DNNmy9nMEJ/JhCXiCSbevbEc6BGKIGVL2S2SAqmVjNqdAiuzoNerBmZoPE5N3YTc9H5u734teSYLV4lglYvcKejmG+OljPqdQ0xdS834aeTzZaoq1tyWUDwWPTW/dQUpQEZndv4cY9V03TaJE7WODEKRn6WqURejAQXMc3vLM/1DdfPxsnoz75ZBYQD/FQWGmMbikfBHtzLxGFfvIAe40rj7rA==\"}','2019-09-20 10:59:23'),(17,1,102,1,1,0,'trans:GPA.3370-6269-8670-89144','{\"type\":\"trans\",\"store\":1,\"Id\":1,\"time\":\"2019-09-20T02:03:34.606Z\",\"data\":\"{\\\"orderId\\\":\\\"GPA.3370-6269-8670-89144\\\",\\\"packageName\\\":\\\"com.smartbig.thatmansgarden\\\",\\\"productId\\\":\\\"com.smartbig.thatmansgarden.gold_1004\\\",\\\"purchaseTime\\\":1568945010770,\\\"purchaseState\\\":0,\\\"purchaseToken\\\":\\\"omioodebbodfbbpganiiglck.AO-J1OyQOlqLPsKVmG-NB1S-g0e6eJVuVie8txS4AvSzjbbaFkfNRpm3X6W8FCGae3qBPREpNk0uAxEdQ-SuwZ4u5ANL11RXDaGe7jj5resqUAL05kJNlUoQybi2W8eS25BEW5iXuntNwC7VGl34pp3rwtFWYuTI4XSzVV4gTVGrBiQW6SdA7BA\\\"}\",\"sign\":\"RFOsMPFroZNuKqQ+YtzGBWHE2bCLKF0h0sxf2n3ZqTRI3lrnz8TdEqUEY7YXkTN1auBxugt0dxX4sqaFQJ9uKzJFz7t4ZdWvIkpKRmOwpnxegu7LlGXyuAifrUHv579BF8MFY4RQYEidhgaIiFiC3PRmCjuq9Jfwg3DsVBICqTGIMgy1OHbEBn08l10cVOFizYr8LdX6YofgDE9xddH9Riu9TvgHvx63bV9Fl00kytDorv/2oPbpceW90RhYeQMZobIVDwSqXzM2bNnZ1wWPPG1VREWajh74zcIYgVp1/fR3Z0SMkt5XQvXYAHvROlCkMSBXkl9ae86UWhuUvcse5A==\"}','2019-09-20 11:03:34');
/*!40000 ALTER TABLE `user_store_bill` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'theman_data'
--
/*!50003 DROP PROCEDURE IF EXISTS `checkingAccount` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `checkingAccount`(
  in iDevice_id varchar(64), 
  in iAuth_type tinyint(1), 
  in iIpAddr varchar(20),
  in iSession_id varchar(255), 
  out oResult int,
  out oMemberId int,
  out oStatus tinyint(1),
  out oAuthority tinyint(2),
  out oBlock tinyint(1),
  out oSessionId varchar(255)
  )
BEGIN
  DECLARE iResult INT DEFAULT 0;

  SELECT COUNT(*), member_id, status, authority, block, session_id 
  INTO iResult, oMemberId, oStatus, oAuthority, oBlock, oSessionId 
  FROM account WHERE device_id = iDevice_id AND auth_type = iAuth_type;

  IF iResult = 0 THEN
    INSERT INTO `account` (device_id, auth_type, status, authority, block, session_id, ipaddr, reg_date)
    VALUES (iDevice_id, iAuth_type, 0, 0, 0, iSession_id, iIpAddr, NOW());
    
	SELECT member_id, status, authority, block, session_id
	INTO oMemberId, oStatus, oAuthority, oBlock, oSessionId
    FROM `account` WHERE device_id = iDevice_id AND auth_type = iAuth_type;
	
	SET oResult = 101;
  ELSE
    UPDATE `account` SET ipAddr = iIpAddr, session_id = iSession_id WHERE device_id = iDevice_id AND auth_type = iAuth_type;
	
  	SET oResult = 1;
  END IF;
  
  
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_buy_cashshop_items` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_buy_cashshop_items`(
	in i_member_id int,
	in i_gold int,
	in i_heart int,
    in i_film int,
    out o_rtn int
)
main: BEGIN

	if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;

    
    
	update user_data 
	set 
		gold=i_gold,
        heart=i_heart,
        film=i_film,
		up_date=NOW()
	where member_id=i_member_id;
    

	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_buy_myroom_item` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_buy_myroom_item`(
    in i_member_id int,
	in i_item_id int,
	in i_price int,
	in i_price_type int,
    out o_rtn int
)
main: BEGIN

	declare v_old_point int default 0;
	declare v_new_point int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	if i_price_type = 1 then
		select gold into v_old_point from user_data where member_id=i_member_id;
		set v_new_point = v_old_point - i_price;
		update user_data 
		set 
			gold=v_new_point,
			up_date=NOW()
		where member_id=i_member_id;
	 elseif i_price_type = 2 then
		select film into v_old_point from user_data where member_id=i_member_id;
		set v_new_point = v_old_point - i_price;
		update user_data 
		set 
			film=v_new_point,
			up_date=NOW()
		where member_id=i_member_id;
	 elseif i_price_type = 3 then
		select heart into v_old_point from user_data where member_id=i_member_id;
		set v_new_point = v_old_point - i_price;
		update user_data 
		set 
			heart=v_new_point,
			up_date=NOW()
		where member_id=i_member_id;
	 end if;
	 
	 insert into theman_log.user_shop_item_buy_log (member_id, price_type, item_id, item_price, before_point, after_point, reg_date)
        values (i_member_id, i_price_type, i_item_id, i_price, v_old_point, v_new_point, NOW());
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_buy_myroom_items` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_buy_myroom_items`(
    in i_member_id int,
	in i_item_id int,
	in i_price int,
	in i_price_type int,
	in i_myitem_cnt int,
	in i_myitem_str varchar(256),
	in i_buyalbum_cnt int,
	in i_buyalbum_str varchar(256),
	in i_soldoutpkg_cnt int,
	in i_soldoutpkg_str varchar(256),
    out o_rtn int
)
main: BEGIN

	declare v_old_point int default 0;
	declare v_new_point int default 0;
	declare v_loop_cnt int default 0;
	declare v_item_num int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	if i_price_type = 1 then
		select gold into v_old_point from user_data where member_id=i_member_id;
		set v_new_point = v_old_point - i_price;
		update user_data 
		set 
			gold=v_new_point,
			up_date=NOW()
		where member_id=i_member_id;
	 elseif i_price_type = 2 then
		select film into v_old_point from user_data where member_id=i_member_id;
		set v_new_point = v_old_point - i_price;
		update user_data 
		set 
			film=v_new_point,
			up_date=NOW()
		where member_id=i_member_id;
	 elseif i_price_type = 3 then
		select heart into v_old_point from user_data where member_id=i_member_id;
		set v_new_point = v_old_point - i_price;
		update user_data 
		set 
			heart=v_new_point,
			up_date=NOW()
		where member_id=i_member_id;
	 end if;
	 
	 insert into theman_log.user_shop_item_buy_log (member_id, price_type, item_id, item_price, before_point, after_point, reg_date)
        values (i_member_id, i_price_type, i_item_id, i_price, v_old_point, v_new_point, NOW());
		
	set v_loop_cnt = 1;
	if i_myitem_cnt	> 0 then
		while v_loop_cnt <= i_myitem_cnt do
            
			
            SELECT SUBSTRING_INDEX(SUBSTRING_INDEX(i_myitem_str, ',', v_loop_cnt), ',', -1) into v_item_num;
            
            if v_item_num > 0 then
                insert into user_myroom_item (member_id,item_id,reg_date)
				values (i_member_id, v_item_num, NOW());
            end if;
            
            set v_loop_cnt = v_loop_cnt + 1;
        end while;
	end if;
	
	set v_loop_cnt = 1;
	if i_buyalbum_cnt	> 0 then
		while v_loop_cnt <= i_buyalbum_cnt do
            
			
            SELECT SUBSTRING_INDEX(SUBSTRING_INDEX(i_buyalbum_str, ',', v_loop_cnt), ',', -1) into v_item_num;
            
            if v_item_num > 0 then
                insert into user_collection_album (member_id,album_id,reg_date)
				values (i_member_id, v_item_num, NOW());
            end if;
            
            set v_loop_cnt = v_loop_cnt + 1;
        end while;
	end if;
	
	set v_loop_cnt = 1;
	if i_soldoutpkg_cnt	> 0 then
		while v_loop_cnt <= i_soldoutpkg_cnt do
            
			
            SELECT SUBSTRING_INDEX(SUBSTRING_INDEX(i_soldoutpkg_str, ',', v_loop_cnt), ',', -1) into v_item_num;
            
            if v_item_num > 0 then
                insert into user_soldout_item (member_id,pkg_id,reg_date)
				values (i_member_id, v_item_num, NOW());
            end if;
            
            set v_loop_cnt = v_loop_cnt + 1;
        end while;
	end if;
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_change_wear` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_change_wear`(
    in i_member_id int,
	in i_cloth int,
	in i_shoes int,
	in i_accessary int,
    out o_rtn int
)
main: BEGIN
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	
	update user_myroom_info 
	set 
		item_id=i_cloth,
		up_date=NOW()
	where member_id=i_member_id and item_type = 10;
	
	update user_myroom_info 
	set 
		item_id=i_shoes,
		up_date=NOW()
	where member_id=i_member_id and item_type = 100;
	
	update user_myroom_info 
	set 
		item_id=i_accessary,
		up_date=NOW()
	where member_id=i_member_id and item_type = 101;
	 
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_change_wear_lists` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_change_wear_lists`(
    in i_member_id int,
	in i_lists varchar(128),
    out o_rtn int
)
main: BEGIN
    declare v_cloth_num int default 0;
	declare v_shoes_num int default 0;
	declare v_accessary_num int default 0;
	
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	if i_lists is null or i_lists = '' then set o_rtn = -100; leave main; end if;
	
	SELECT SUBSTRING_INDEX(SUBSTRING_INDEX(i_lists, ',', 1), ',', -1) into v_cloth_num;
	SELECT SUBSTRING_INDEX(SUBSTRING_INDEX(i_lists, ',', 2), ',', -1) into v_shoes_num;
	SELECT SUBSTRING_INDEX(SUBSTRING_INDEX(i_lists, ',', 3), ',', -1) into v_accessary_num;
	
	if v_cloth_num <= 0 then set o_rtn = -101; leave main; end if;
	if v_shoes_num <= 0 then set o_rtn = -102; leave main; end if;
	if v_accessary_num <= 0 then set o_rtn = -103; leave main; end if;
	
	update user_myroom_info 
	set 
		item_id=v_cloth_num,
		up_date=NOW()
	where member_id=i_member_id and item_type = 10;
	
	update user_myroom_info 
	set 
		item_id=v_shoes_num,
		up_date=NOW()
	where member_id=i_member_id and item_type = 100;
	
	update user_myroom_info 
	set 
		item_id=v_accessary_num,
		up_date=NOW()
	where member_id=i_member_id and item_type = 101;
	 
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_char_select` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_char_select`(
    in i_member_id int,
	in i_cur_story int,
	in i_actor_id int,
    out o_rtn int
)
main: BEGIN
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	update user_data 
	set 
		select_actor=i_actor_id,
		cur_story=i_cur_story,
		up_date=NOW()
	where member_id=i_member_id;
	 
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_create_user` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_create_user`(
    in i_member_id int,
    in i_first_name varchar(32),
	in i_last_name varchar(32),
    out o_rtn int
)
main: BEGIN
    
    declare v_chk int default 0;
    declare v_user_chk int default 0;
	declare v_gold int default 0;
	declare v_film int default 0;
	declare v_heart int default 0;
	declare v_passion int default 0;
	declare v_happy int default 0;
	declare v_first_actor int default 0;
	declare v_first_story int default 0;
	declare v_base_cloth int default 0;
	declare v_base_shoes int default 0;
	declare v_base_accessory int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
    
    select count(*) into v_chk from account where member_id = i_member_id;
    
    if v_chk = 1 then
	
		select count(*) into v_user_chk from user_data where member_id = i_member_id;
		if v_user_chk = 1 then set o_rtn = -101; leave main; end if;
        
        start transaction;
        
        if length(i_first_name) <= 0 then set o_rtn = -102; leave main; end if;
        if length(i_last_name) <= 0 then set o_rtn = -103; leave main; end if;
        
        select gold, film, heart, passion, happy, first_actor, first_story, base_cloth, base_shoes, base_accessory
        into v_gold, v_film, v_heart, v_passion, v_happy, v_first_actor, v_first_story, v_base_cloth, v_base_shoes, v_base_accessory
        from user_default_setting
        where idx = 1;
        
        insert into user_data (member_id, first_name, last_name, gold, film,heart,passion,happy,select_actor,cur_story,reg_date)
        values (i_member_id, i_first_name,i_last_name,v_gold, v_film, v_heart, v_passion, v_happy, v_first_actor, v_first_story,NOW());
        
        insert into user_myroom_info (member_id, item_type, item_id, reg_date)
        values (i_member_id, 10, v_base_cloth, NOW());
		insert into user_myroom_info (member_id, item_type, item_id, reg_date)
        values (i_member_id, 100, v_base_shoes, NOW());
		insert into user_myroom_info (member_id, item_type, item_id, reg_date)
        values (i_member_id, 101, v_base_accessory, NOW());
        
        
        update account set status=1 where member_id=i_member_id;
         
        commit;
        set o_rtn = 1;
    else
        set o_rtn = -99;
    end if;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_finish_quiz` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_finish_quiz`(
    in i_member_id int,
	in i_actor_id int,
	in i_quiz_id int,
    out o_rtn int
)
main: BEGIN
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	insert into user_scene_quiz (member_id, actor_id, scene_id, reg_date)
        values (i_member_id, i_actor_id, i_quiz_id, NOW());
	 
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_get_user_store_bill` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_get_user_store_bill`(
    in i_member_id int,
	in i_key_value varchar(64),
	in i_trans_value varchar(1024),
    out o_rtn int
)
main: BEGIN
    
    declare v_chk int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
    
    select count(*) into v_chk from user_store_bill where member_id = i_member_id and key_value=i_key_value and trans_value=i_trans_value;
    
    if v_chk = 1 then
        set o_rtn = 1;
    else
        set o_rtn = -99;
    end if;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_insert_user_store_bill` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_insert_user_store_bill`(
    in i_member_id int,
    in i_item_id int,
	in i_store_type tinyint,
	in i_shop_type tinyint,
	in i_sale_price int,
	in i_key_value varchar(64),
	in i_trans_value varchar(1024),
    out o_rtn int
)
main: BEGIN
    
    declare v_chk int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
    
    select count(*) into v_chk from user_store_bill where member_id = i_member_id and key_value=i_key_value and trans_value=i_trans_value;
    
    if v_chk = 0 then
	
        insert into user_store_bill (member_id, item_id, store_type, shop_type, sale_price, key_value, trans_value, reg_date)
        values (i_member_id, i_item_id, i_store_type, i_shop_type, i_sale_price, i_key_value, i_trans_value, NOW());
        set o_rtn = 1;
    else
        set o_rtn = -99;
    end if;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_load_userdata` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_load_userdata`(
  in i_member_id int,
  out o_rtn int,
  out o_userdata text
)
main: BEGIN
    
    declare v_chk int default 0;
    declare v_user_data text;
    declare v_album text;
    declare v_buyalbum text;
    declare v_mypage text;
    declare v_soldoutpackage text;
    declare v_clearscene text;
    declare v_quizscene text;
    declare v_endingscene text;
    declare v_wearing text;
    declare v_resetcheck text;
    
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
    
    select count(*) into v_chk from user_data where member_id = i_member_id;
    
    if v_chk = 1 then
        
        select 
          group_concat(json_object(
          'first_name',first_name,'last_name',last_name, 'tutorial_clear',tutorial_clear, 'gold',gold,
          'film',film,'heart',heart, 'passion',passion, 'happy',happy,'select_actor',select_actor, 'cur_story',cur_story)) into v_user_data
        from user_data where member_id=i_member_id;
        
        select GROUP_CONCAT(json_object('actor_id',a.actor_id,'lists',a.album_ids) separator '|') as v_album from 
          ( select actor_id, GROUP_CONCAT(album_id) as album_ids from user_album where member_id=i_member_id group by actor_id ) a into v_album;
        
        select GROUP_CONCAT(album_id) into v_buyalbum from user_collection_album where member_id=i_member_id order by idx;
        
        select GROUP_CONCAT(item_id) into v_mypage from user_myroom_item where member_id=i_member_id order by idx;
        
        select GROUP_CONCAT(pkg_id) into v_soldoutpackage from user_soldout_item where member_id=i_member_id order by idx;
        
        select GROUP_CONCAT(item_id) into v_wearing from user_myroom_info where member_id=i_member_id order by item_type;
        
        select GROUP_CONCAT(json_object('actor_id',a.actor_id,'lists',a.scene_ids) separator '|') from 
          ( select actor_id, GROUP_CONCAT(scene_id) as scene_ids from user_scene_quiz where member_id=i_member_id group by actor_id ) a into v_quizscene;
        
        select GROUP_CONCAT(json_object('actor_id',a.actor_id,'lists',a.scene_ids) separator '|') from 
          ( select actor_id, GROUP_CONCAT(scene_id) as scene_ids from user_scene_clear where member_id=i_member_id group by actor_id ) a into v_clearscene;
          
		select GROUP_CONCAT(json_object('actor_id',a.actor_id,'lists',a.scene_ids) separator '|') from 
          ( select actor_id, GROUP_CONCAT(scene_id) as scene_ids from user_scene_ending where member_id=i_member_id group by actor_id ) a into v_endingscene;
          
		select GROUP_CONCAT(actor_id) into v_resetcheck from user_scene_reset where member_id=i_member_id order by actor_id;  

          
		          
        select 
          group_concat(
            json_object(
            'user_data',v_user_data,'album',v_album,'buyalbum',v_buyalbum,'mypage',v_mypage,
            'soldoutpackage',v_soldoutpackage,'quizscene',v_quizscene,'wearing',v_wearing,'clearscene',v_clearscene,
            'endingscene',v_endingscene,'resetcheck',v_resetcheck
            )
          ) 
          into o_userdata;
	      
        set o_rtn = 1;
    else
        set o_rtn = -99;
    end if;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_login_reward` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_login_reward`(
    in i_member_id int,
	in i_max_reward_count int,
    out o_rtn int,
    out o_reward_count int
)
main: BEGIN
    
 
   
    declare v_chk int default 0;
    declare v_chk_date int default 0;
    declare v_chk_month_date int default 0;
    
    declare v_old_reward_count int default 0;
    declare v_new_reward_count int default 0;
            
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; set o_reward_count = -1; leave main; end if;
    
    select count(*) into v_chk from user_login_reward where member_id = i_member_id;
    select count(*) into v_chk_date from user_login_reward where member_id = i_member_id and DATE_FORMAT(up_date,'%Y-%m-%d %T') <= DATE_FORMAT(NOW(),'%Y-%m-%d 07:00:00');
    select count(*) into v_chk_month_date from user_login_reward where member_id = i_member_id and TIMESTAMPDIFF(DAY,DATE_FORMAT(first_reward_date,'%Y-%m-%d %T'),DATE_FORMAT(NOW(),'%Y-%m-%d 07:00:00')) >= 30;
    
    
    if v_chk = 0 then
	
        insert into user_login_reward (member_id, reward_count, reg_date, first_reward_date, up_date)
        values (i_member_id, 1, NOW(), NOW(), NOW());
        
        update user_data 
			set 
				film=film + 1,
				up_date=NOW()
		where member_id=i_member_id;
                    
        set o_rtn = 1;
        set o_reward_count = 1;
    else
    
		select reward_count into v_old_reward_count from user_login_reward where member_id = i_member_id;
                
        if v_chk_date = 0 then
        
			set o_rtn = -100;
            set o_reward_count = v_old_reward_count;
            leave main;
        
        else
        
			if v_chk_month_date = 0 then
            
				if v_old_reward_count > i_max_reward_count then
                
					update user_data 
					set 
						film=film + 1,
						up_date=NOW()
					where member_id=i_member_id;
                    
                    update user_login_reward
					set 
						up_date = NOW()
					where member_id=i_member_id;
                    
					set o_rtn = 1;
                    set o_reward_count = 0;
				else
                
					update user_data 
					set 
						film=film + 1,
						up_date=NOW()
					where member_id=i_member_id;
                    
					update user_login_reward
					set 
						reward_count = v_old_reward_count + 1,
						up_date = NOW()
					where member_id=i_member_id;
                    
                    set o_rtn = 1;
                    set o_reward_count = v_old_reward_count + 1;
				end if;
            
            else
            
				update user_data 
				set 
					film=film + 1,
					up_date=NOW()
				where member_id=i_member_id;
            
				update user_login_reward
				set 
					reward_count = 1,
                    first_reward_date = NOW(),
					up_date = NOW()
				where member_id=i_member_id;
                
                set o_rtn = 1;
				set o_reward_count = 1;
            end if;
            
        end if;
		
        
    end if;

END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_start_quiz` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_start_quiz`(
    in i_member_id int,
	in i_heart int,
    out o_rtn int
)
main: BEGIN
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	update user_data 
	set 
		heart=i_heart,
		up_date=NOW()
	where member_id=i_member_id;
	 
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_story_end` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_story_end`(
    in i_member_id int,
	in i_film int,
	in i_cur_story int,
	in i_actor_id int,
	in i_scene_id int,
	in i_tutorial_clear tinyint,
    out o_rtn int
)
main: BEGIN
    
    declare v_chk int default 0;
    declare v_user_chk int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
    
    select count(*) into v_chk from user_data where member_id = i_member_id;
    
    if v_chk = 1 then
	
		select count(*) into v_user_chk from user_scene_clear where member_id = i_member_id and actor_id = i_actor_id and scene_id = i_scene_id;
		if v_user_chk = 1 then set o_rtn = -101; leave main; end if;
        
        start transaction;
        
		insert into user_scene_clear (member_id, actor_id, scene_id, reg_date)
        values (i_member_id, i_actor_id, i_scene_id, NOW());
		
        update user_data 
		set 
			tutorial_clear=i_tutorial_clear,
			film=i_film,
			cur_story=i_cur_story,
			up_date=NOW()
		where member_id=i_member_id;
         
        commit;
        set o_rtn = 1;
    else
        set o_rtn = -99;
    end if;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_story_reset` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_story_reset`(
    in i_member_id int,
	in i_type int,
	out o_rtn int
)
main: BEGIN
    
    declare v_chk int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
          
    select count(*) into v_chk from user_scene_reset where member_id = i_member_id and actor_id = i_type;
    
    if v_chk = 0 then
	
        insert into user_scene_reset (member_id, actor_id, reg_date)
        values (i_member_id, i_type, NOW());
        set o_rtn = 1;
    else
    
		update user_scene_reset
		set 
			actor_id = i_type
		where member_id=i_member_id;
    
        set o_rtn = 1;
    end if;

END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_story_save_ending` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_story_save_ending`(
    in i_member_id int,
	in i_type int,
    in i_scene int,
	out o_rtn int
)
main: BEGIN
    
 
   
    declare v_chk int default 0;
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
      
    select count(*) into v_chk from user_scene_ending where member_id = i_member_id and actor_id=i_type and scene_id=i_scene;
    
    if v_chk = 0 then
	
        insert into user_scene_ending (member_id, actor_id, scene_id, reg_date)
        values (i_member_id, i_type, i_scene, NOW());
        set o_rtn = 1;
    else
       
        set o_rtn = -100;
    end if;

END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_update_cost` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_update_cost`(
    in i_member_id int,
	in i_type int,
	in i_cost int,
    out o_rtn int
)
main: BEGIN
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;

    if i_type = 1
    then 
		update user_data 
		set 
			gold=gold-i_cost,
			up_date=NOW()
		where member_id=i_member_id;
     elseif i_type = 2 
     then
		update user_data 
		set 
			heart=heart-i_cost,
			up_date=NOW()
		where member_id=i_member_id;
     elseif i_type = 3 
     then 
		update user_data 
		set 
			film=film-i_cost,
			up_date=NOW()
		where member_id=i_member_id;
        end if;

	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_update_favor` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_update_favor`(
    in i_member_id int,
	in i_happy_pt int,
	in i_passion_pt int,
    out o_rtn int
)
main: BEGIN
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	update user_data 
	set 
		happy=happy+i_happy_pt,
		passion=passion+i_passion_pt,
		up_date=NOW()
	where member_id=i_member_id;
	 
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_update_user_point` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_update_user_point`(
    in i_member_id int,
	in i_gold int,
	in i_film int,
	in i_heart int,
    out o_rtn int
)
main: BEGIN
    
    if i_member_id is null or i_member_id = '-1' or i_member_id = '' then set o_rtn = -100; leave main; end if;
	update user_data 
	set 
		gold=i_gold,
		film=i_film,
		heart=i_heart,
		up_date=NOW()
	where member_id=i_member_id;
	 
	set o_rtn = 1;
END main ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-09-24 15:59:10
