<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Add User Confirmation</title>
</head>

<body>

<?php
$pin = $_POST["pin"];
echo $pin;
//print_r($_POST);
?>
<h1>Your Pin: <?php echo $pin;?> </h1>

<form >
    <input type="hidden" name="pin" value="<?php echo $pin;?>">
	<input type="button" onclick="window.location.replace('main.php')" value="Back to Main Menu" />
</form>



</body>
</html>