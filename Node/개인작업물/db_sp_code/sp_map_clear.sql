DELIMITER ;

/*!50003 DROP PROCEDURE IF EXISTS `sp_map_clear` */;

DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_map_clear`(
  in i_user_id varchar(255),
  in i_map_id int,
  out o_rtn int,
  out o_userdata text
)
main: BEGIN

    declare v_chk int default 0;
	declare v_clear_map text;

	select count(*) into v_chk from user_map_clear where user_id = i_user_id and map_id = i_map_id;


  if v_chk = 0 then
        
        insert into user_map_clear (user_id,map_id,updatetime)
		values (i_user_id,i_map_id,NOW());
        
        select GROUP_CONCAT(map_id) into v_clear_map from user_map_clear where user_id = i_user_id  order by idx;

		select 
          group_concat(
            json_object(
            'clearmaps',v_clear_map
            )
          ) 
          into o_userdata;
          
         set o_rtn = 1;
    else
        set o_rtn = -99;
        
    end if;
    

END main ;;
