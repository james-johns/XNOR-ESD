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



<form id="deletetrackform" action="server.php">
<fieldset>
<legend>Delete Track:</legend>
<table width="200" border="1">
  <tr>
    <td><input type="text" size="32" name="findtrack" placeholder="Track Name" required></td>
  </tr>
</table>


</fieldset>

    <br>
    <center>
      <p>
       	<input type="submit" value="Delete Track">
        <input type="reset" value="Clear Field">
        <input type="button" onclick="window.location.replace('main.php')" value="Cancel" />
</form>
<div id="result"></div>

<script type="text/javascript">
$("#deletetrackform").submit(function(event) {

  /* stop submitting form */
  event.preventDefault();

  /* get some values from elements on the page: */
  var $form = $( this ),
  	act = "6",
    tn = $form.find( "input[name='findtrack']" ).val(),
    url = $form.attr( "action" );


  /* Send the data using post */
  var posting = $.post( url, {	action: act,
  								findtrack: tn } );

  /* Put the results in a div */
  posting.done(function( data ) {
	 if (data === "OK"){
		alert('Track Deleted!');
		window.location.href = "main.php";
	  }
	  else{
		  alert('Track Deletion Error!');
	  }
	  
	var content = $( data ).find( "#content" );
	$( "#result" ).empty().append( content );

  });
});

</script>
</body>
</html>