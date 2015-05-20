<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Search User</title>

  <script src="https://code.jquery.com/jquery-1.10.2.js"></script>
</head>
<body>

<?php

//print_r($_POST);

//if (isset($_POST['submit'])){
	//$name = htmlentities($_POST['name'], ENT_QUOTES, 'UTF-8');	
	//$fullname = implode('+', $_POST['fullname']);
	

//}

//if user exist then post to edit user page
//display no matching if dont match
//display payment info but grayed if if available
//THIS WILL GO TO su-confirmation wether to edit it or add payment

?>



<form id="deleteuserform" action="server.php">
<fieldset>
<legend>Delete User by Name:</legend>
<table width="200" border="1">
  <tr>
    <td><input type="text" size="32" name="firstname" placeholder="First Name" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="surname" placeholder="Surname" required></td>
  </tr>
</table>


</fieldset>

    <br>
    <center>
      <p>
       	<input type="submit" value="Delete User">
        <input type="reset" value="Clear Fields">
        <input type="button" onclick="window.location.replace('main.php')" value="Cancel" />
</form>
<div id="result"></div>

<script type="text/javascript">
$("#deleteuserform").submit(function(event) {

  	/* stop submitting form */
  	event.preventDefault();

  	/* get some values from elements on the page: */
  	var $form = $( this ),
  	act = "6",
    fn = $form.find( "input[name='firstname']" ).val(),
	sn = $form.find( "input[name='surname']" ).val(),
    url = $form.attr( "action" );
	
	var firstname = fn.concat('-');
	var fullnam = firstname.concat(sn);

  /* Send the data using post */
  var posting = $.post( url, {	action: act,
  								fullname: fullnam } );

  /* Put the results in a div */
  posting.done(function( data ) {
	  
	 if (data === "OK"){
		alert('User Deleted!');
		window.location.href = "main.php";
	  }
	  else{
		  alert('User Deletion Error!');
	  }
	  
	var content = $( data ).find( "#content" );
	$( "#result" ).empty().append( content );

  });
});
</script>
</body>
</html>