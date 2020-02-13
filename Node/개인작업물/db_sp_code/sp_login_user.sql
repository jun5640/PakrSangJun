DELIMITER ;
/*!50003 DROP PROCEDURE IF EXISTS `sp_login_user` */;
DELIMITER ;;
CREATE PROCEDURE `sp_login_user`(
    in i_user_id varchar(255),
	in i_user_pass varchar(32),
    out o_rtn int
)
main: BEGIN

	declare v_chk int default 0;
    declare v_user_chk int default 0;

	select count(*) into v_chk from user_data where user_id = i_user_id and user_pass = i_user_pass;


  if v_chk = 1 then
        set o_rtn = 1;
        
    else
        set o_rtn = -99;
        
    end if;


END main ;;