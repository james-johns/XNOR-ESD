<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Edit User</title>

  <script src="https://code.jquery.com/jquery-1.10.2.js"></script>
</head>
<body>

<?php

//print_r($_POST);
$clientID = isset($_POST['clientID']) ? $_POST['clientID'] : '';
$fullname = isset($_POST['fullname']) ? $_POST['fullname'] : '';
$address = isset($_POST['address']) ? $_POST['address'] : '';
$mobilenum = isset($_POST['mobilenum']) ? $_POST['mobilenum'] : '';
$language = isset($_POST['language']) ? $_POST['language'] : '';
$knowledgelvl = isset($_POST['knowledgelvl']) ? $_POST['knowledgelvl'] : '';
$paydetails = isset($_POST['paydetails']) ? $_POST['paydetails'] : '';

$fln = explode("-",$fullname);

$firstname = $fln[0];
$surname = $fln[1];
$tadd = explode("+",$address);
$addrline1 = str_replace ("-", " ", $tadd[0]);
if ($tadd[1] != '_'){
	$addrline2 = str_replace ("-", " ", $tadd[1]);
}
else{
	$addrline2 = " ";
}
if ($tadd[2] != '_'){
	$addrline3 = str_replace ("-", " ", $tadd[2]);
}
else{
	$addrline3 = " ";
}

$city =  $tadd[3];
$postcode =  str_replace ("-", " ", $tadd[4]);
$country = str_replace ("-", " ", $tadd[5]);

if ($language != '_'){
	$language = str_replace ("-", " ", $tadd[1]);
}
else{
	$language = " ";
}
if ($knowledgelvl != '_'){
	$knowledgelvl = str_replace ("-", " ", $tadd[2]);
}
else{
	$knowledgelvl = " ";
}



//6
//if (isset($_POST['submit'])){
	//$name = htmlentities($_POST['name'], ENT_QUOTES, 'UTF-8');	
	//$fullname = implode('+', $_POST['fullname']);
	
//if payment exists ..grayed out if not then make it available for edit
//}
?>



<form id="adduserform" action="server.php">
<fieldset>
<legend>Edit User:</legend>
<table width="200" border="1">
  <tr>
    <td><input type="text" size="32" name="firstname" value="<?php echo $firstname;?>" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="surname" value="<?php echo $surname;?>" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="addrline1" value="<?php echo $addrline1;?>" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="addrline2" value="<?php echo $addrline2;?>"></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="addrline3" value="<?php echo $addrline3;?>"></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="city" value="<?php echo $city;?>" placeholder="City" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="postcode" value="<?php echo $postcode;?>" placeholder="Post Code" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="postcode" value="<?php echo $country;?>" placeholder="Post Code" required>
    </td>
  </tr>
    <td><input type="text" size="32" name="mobilenum" placeholder="Mobile Number" value="<?php echo $mobilenum;?>" required></td>
  </tr>
    <tr>
    <td><input type="text" size="32" value="<?php echo $language;?>" ></td>
  </tr>
  <tr>
    <td><input type="text" size="32" value="<?php echo $knowledgelvl;?>" ></td>
  </tr>
  <tr>
</table>
<br>
Payment Details:
<table width="265" border="1">
  <tr>
  	<td>Transaction Id</td>
  </tr>
    <tr>
  	<td>Payment Type</td>
  </tr>
    <tr>
  	<td>Payment Date </td>
  </tr>
      <tr>
  	<td>Payment Time </td>
  </tr>
</table>
</fieldset>

    <br>
    <center>
      <p>
       	<input type="submit" value="Save Changes">
        <input type="reset" value="Clear Fields">
        <input type="button" onclick="window.location.replace('main.php')" value="Cancel" />
</form>
<div id="result"></div>

<script type="text/javascript">
$("#adduserform").submit(function(event) {

  /* stop submitting form */
  event.preventDefault();

  /* get some values from elements on the page: */
  var $form = $( this ),
  	act = "5",
    fn = $form.find( "input[name='firstname']" ).val(),
	sn = $form.find( "input[name='surname']" ).val(),
	adl1 = $form.find( "input[name='addrline1']" ).val(),
	adl2 = $form.find( "input[name='addrline2']" ).val(),
	adl3 = $form.find( "input[name='addrline3']" ).val(),
	cty = $form.find( "input[name='city']" ).val(),
	cnty = $form.find( "input[name='county']" ).val(),
	pc = $form.find( "input[name='postcode']" ).val(),
	cntry = $form.find( "input[name='country']" ).val(),
	lang = $form.find( "input[name='language']" ).val(),
	kl = $form.find( "input[name='knowledgelvl']" ).val(),
	mb = $form.find( "input[name='mobilenum']" ).val(),
    url = $form.attr( "action" );

var e = document.getElementById("selcountry");
var selectedcountry = e.options[e.selectedIndex].text;

	var firstname = fn.concat('-');
	var fullnam = firstname.concat(sn);
	
	//if addl2 is not empty then add..then check addl3 if npt empty then add

	//join string
	var repadl1 = adl1.split(' ').join('-');
	if (repadl2){
		var repadl2 = adl2.split(' ').join('-'); //check if emptyu
	}
	else{
		var repadl2 = "?";	
	}
	
	if (repadl3){
		var repadl3 = adl3.split(' ').join('-'); // check if empty // town		
	}
	else{
		var repadl3 = "?";	
	}
	
	//alert(cntry);

	var repcity = cty.split(' ').join('-');
	var reppc = pc.split(' ').join('-');
	
	var firstadd =  repadl1.concat('+');
	var secadd  = repadl2.concat('+');
	var thirdadd = repadl3.concat('+');
	var fourthadd = repcity.concat('+');
	var fifthadd = reppc.concat('+');
	var country = selectedcountry.split(' ').join('-'); 

	
	var fulladdress = firstadd.concat(secadd,thirdadd,fourthadd,fifthadd,country);
	 

	
  /* Send the data using post */
  var posting = $.post( url, {	action: act,
  								firstname: fn,
								surname: sn,
								addrline1: adl1,
								addrline2: adl2,
								addrline3: adl3,
								city: cty,
								county: cnty,
								postcode: pc,
								country: cntry,
								language: lang,
								knowledgelvl: kl,
								mobilenum: mb } );

  /* Put the results in a div */
  posting.done(function( data ) {
	  switch(data)//needs to parse actual response data
	  {
		case 'OK': 
//		  	alert(data); //REDIRECT HERE!
//			//au-confirmation.php
//			var uid = $(this).data('data');
//
//			if (uid != undefined || uid != null) {
//				window.location = 'auconf.php?userid=' + uid;
//			}   
			var clientID = "12314";
			var url = 'au-confirmation.php';
			var form = $('<form action="' + url + '" method="post">' +
			  '<input type="text" name="clientID" value="' + clientID + '" />' +
			  '</form>');
			$('body').append(form);
			form.submit();
			break;
		case 'FALSE':
			alert('Registration Error');
			break;
		  
	  }
	  
	var content = $( data ).find( "#content" );
	$( "#result" ).empty().append( content );

  });
});

</script>
</body>
</html>