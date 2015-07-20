/*
Navicat MySQL Data Transfer

Source Server         : 82
Source Server Version : 50155
Source Host           : 192.168.9.82:3306
Source Database       : gw_power

Target Server Type    : MYSQL
Target Server Version : 50155
File Encoding         : 65001

Date: 2015-07-20 14:36:13
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `t_active`
-- ----------------------------
DROP TABLE IF EXISTS `t_active`;
CREATE TABLE `t_active` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '活动类型',
  `name` varchar(200) NOT NULL DEFAULT '' COMMENT '活动名称',
  `status` int(11) NOT NULL DEFAULT '0' COMMENT '状态',
  `start_dt` datetime NOT NULL DEFAULT '2000-01-01 00:00:00' COMMENT '开始dt',
  `end_dt` datetime NOT NULL DEFAULT '2000-01-01 00:00:00' COMMENT '结束dt',
  `loop_interval` int(11) NOT NULL DEFAULT '0' COMMENT '时间间隔（分钟）',
  `start_date` int(11) NOT NULL DEFAULT '0' COMMENT '开服多少天，开始这个活动',
  `end_date` int(11) NOT NULL DEFAULT '0' COMMENT '开服多少天，结束这个活动',
  `day_of_week` varchar(11) NOT NULL DEFAULT '' COMMENT '星期几（用#隔开）',
  `js_str` varchar(1000) NOT NULL DEFAULT '' COMMENT '扩展字符串',
  PRIMARY KEY (`id`),
  KEY `idx_active_id` (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of t_active
-- ----------------------------
INSERT INTO `t_active` VALUES ('1', '0', 'helloworld', '0', '2000-01-01 00:00:00', '2000-01-01 00:00:00', '0', '0', '0', '', '');
