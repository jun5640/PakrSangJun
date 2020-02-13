DELIMITER ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_create_user` */;
DELIMITER ;;
CREATE PROCEDURE `sp_create_user`(
    in i_user_id varchar(255),
	in i_user_pass varchar(32),
    out o_rtn int
)
main: BEGIN

	declare v_chk int default 0;

    if i_user_id is null or i_user_id = '-1' or i_user_id = '' then set o_rtn = -100; leave main; end if;
    if i_user_pass is null or i_user_pass = '-1' or i_user_pass = '' then set o_rtn = -100; leave main; end if;
    
    select count(*) into v_chk from user_data where user_id = i_user_id and user_pass = i_user_pass;
    if v_chk = 1 then set o_rtn = -101; leave main; end if;
	
    insert into user_data (user_id,user_pass,updatetime,createtime)
    values (i_user_id,i_user_pass,NOW(),NOW());

	set o_rtn = 1;

END main ;;

