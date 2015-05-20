<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Add User</title>

  <script src="https://code.jquery.com/jquery-1.10.2.js"></script>
</head>
<body>

<?php

//print_r($_POST);

//if (isset($_POST['submit'])){
	//$name = htmlentities($_POST['name'], ENT_QUOTES, 'UTF-8');	
	//$fullname = implode('+', $_POST['fullname']);
	

//}
?>



<form id="logoutrpuform" action="server.php">
<fieldset>
<legend>Logout RPU:</legend>
<table width="200" border="1">
  <tr>
    <td><input type="text" size="32" name="pin" placeholder="RPU PIN" required></td>
  </tr>
</table>


</fieldset>

    <br>
    <center>
      <p>
       	<input type="submit" value="Logout RPU">
        <input type="reset" value="Clear Field">
        <input type="button" onclick="window.location.replace('main.php')" value="Cancel" />
</form>
<div id="result"></div>

<script type="text/javascript">
$("#logoutrpuform").submit(function(event) {

  /* stop submitting form */
  event.preventDefault();

  /* get some values from elements on the page: */
  var $form = $( this ),
  	act = "0",
    pn = $form.find( "input[name='pin']" ).val(),
    url = $form.attr( "action" );


  /* Send the data using post */
  var posting = $.post( url, {	action: act,
  								pin: pn } );

  /* Put the results in a div */
  posting.done(function( data ) {
	 if (data === "OK"){
		alert('RPU Logout Success!');
		window.location.href = "main.php";
	  }
	  else{
		  alert('RPU Logout Error!');
	  }
	  
	var content = $( data ).find( "#content" );
	$( "#result" ).empty().append( content );

  });
});

</script>
</body>
</html>