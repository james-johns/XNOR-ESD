<?php
//echo '2343';// \nfirstname=john \nsurname=lazo';


$act = $_POST['action'];
if ($act == '0')//logout rpu
{
	echo "OK";
}
elseif ($act == '1')//login rpu
{
	echo "OK";
}
elseif ($act == '2')//Add a user
{
	echo "1234"; // client ID
}
elseif ($act == '3')// complete payment
{
	echo "9999";// PIN
}
elseif ($act == '4')// search user
{
	echo "9999";
}
elseif ($act == '5')// save changes / edit user
{
	echo "9999";
}
elseif ($act == '6')// delete user
{
	echo "OK";
}
elseif ($act == '7')// add track
{
	echo "OK";
}
elseif ($act == '8') //delete track
{
	echo "OK";
}

//print_r($_POST);

//var_dump($_POST)

 //echo json_encode(array("firstname"=>"John","surname"=>"2pm"));


?>