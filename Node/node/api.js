

function who(number)
{

    var value = getmsg(number,"eeeeee");
    console.log(value);
}


function getmsg(number,s_name)
{
    
    var name = s_name;
    var msgcol = ["aaaaa","bbbb" + name + "ccccc"];

    return msgcol[number];
}



who(0);
who(1);