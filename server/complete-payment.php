<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Add User</title>

  <script src="https://code.jquery.com/jquery-1.10.2.js"></script>
</head>
<body>

<?php
$clientID = isset($_POST['clientID']) ? $_POST['clientID'] : '';
//$clientID = $_POST["clientID"];
//echo $clientID;

//print_r($_POST);
//if (isset($_POST['submit'])){
	//$name = htmlentities($_POST['name'], ENT_QUOTES, 'UTF-8');	
	//$fullname = implode('+', $_POST['fullname']);
	

//}
?>



<form id="completepaymentform" action="192.168.1.3">
<fieldset>
<legend>Add Payment:</legend>

<input type="hidden" name="clientID" value="<?php echo $clientID;?>">


<table width="200" border="1">
    <tr>
    	<td><input type="text" size="32" name="paytransid" placeholder="Transaction Id" required></td>
    </tr>
    <tr>
    	<td>
        Payment Type: <br>

        <input type="radio" name="paytype" value="cash" checked>Cash
        <br>
        <input type="radio" name="paytype" value="Visa">Visa
		<br>
		<input type="radio" name="paytype" value="Master">Master 
		<br>       
        </td>
    </tr>
</table>

</fieldset>

    <br>
    <center>
      <p>
       	<input type="submit" value="Complete Payment">
        <input type="reset" value="Clear Fields">
        <input type="button" onclick="window.location.replace('main.php')" value="Cancel" />
</form>
<div id="result"></div>

<script type="text/javascript">
$("#completepaymentform").submit(function(event) {

  	/* stop submitting form */
  	event.preventDefault();

  	/* get some values from elements on the page: */
  	var $form = $( this ),
  	act = "3",
    pid = $form.find( "input[name='paytransid']" ).val(),
	pt = $form.find( "input[name='paytype']" ).val(),
	cID = $form.find( "input[name='clientID']" ).val(),
    url = $form.attr( "action" );


  /* Send the data using post */
  var posting = $.post( url, {	action: act,
  								paytransid: pid,
								paytype: pt,
								clientID: cID } );

  /* Put the results in a div */
  posting.done(function( data ) {
	  //var data = str.split("\n"); 
	  //alert(data);
	  if (data){
	  //alert(data);
		var url = 'cp-confirmation.php';
		var form = $('<form action="' + url + '" method="post">' +
		  '<input type="text" name="pin" value="' + data + '" />' +
		  '</form>');
		$('body').append(form);
		form.submit();
	  }
	  else{
		  alert('Registration Error');
	  }
	  
	  //alert(data);
	//  switch(data)//needs to parse actual response data
	//  {
	//	case 'OK': 
//		  	alert(data); //REDIRECT HERE!
//			//au-confirmation.php
//			var uid = $(this).data('data');
//
//			if (uid != undefined || uid != null) {
//				window.location = 'auconf.php?userid=' + uid;
//			}   

			// DISPLAY PIN
		//	alert("Payment Complete!"); 
			//window.location.href = "main.php"; //can be redirected to a page instead like au-confirmation

	//		break;
	//	case 'FALSE':
	//		alert('Payment Error');
	//		break;
		  
	//  }
	  
	//var content = $( data ).find( "#content" );
	//$( "#result" ).empty().append( content );

  });
});

</script>
</body>
</html>