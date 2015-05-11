<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Add User Confirmation</title>
</head>

<body>

<?php
$clientID = $_POST["clientID"];
echo $clientID;

?>
<h1>Add user successful! </h1>
Do you want to complete the payment?

<form id="aucomfirmationform" action="complete-payment.php">
    <input type="hidden" name="clientID" value="<?php echo $clientID;?>">
	<input type="submit" value="Yes">
	<input type="button" onclick="window.location.replace('main.php')" value="No" />
</form>


<script type="text/javascript">

$("#aucomfirmationform").submit(function(event) {
	
	/* stop submitting form */
  	event.preventDefault();
	
	/* get client id from php post */
  	var cID = "<?php echo $clientID ?>";
	alert(cID);
	
	/* get some values from elements on the page: */
  	var $form = $( this ), 
	cID = $form.find( "input[name='clientID']" ).val(),
	url = $form.attr( "action" );
	
	/* Send the data using post */
	var posting = $.post( url, { clientID: cID });
  
  
}

</script>

</body>
</html>