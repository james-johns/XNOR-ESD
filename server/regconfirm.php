<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Registration Confirmation</title>

<style>
#header {
    background-color:#979797;
    color:white;
    text-align:center;
    padding:5px;
	width: 800px;
    margin: 0 auto;
}

#formsection {
    width:790px;
	margin: 0 auto;
	
	font-family:"Gill Sans", "Gill Sans MT", "Myriad Pro", "DejaVu Sans Condensed", Helvetica, Arial, sans-serif;
}

#customerinformation {
	width:100%;
    float:left;

}

#trackmanagement {
	width:100%;
    float:left;
}

#rpumanagement {
	width:100%;
    float:left;
	
}

#footer {
    background-color:#979797;
    color:white;
    clear:both;
    text-align:center;
    padding:5px;
	width:800px;
	margin: 0 auto;
}
fieldset {
	border: 1px solid black;
	width: 100%;
}

legend {
	color: black;
	padding: 2px 6px;
	background: white;

	
}
table {
    border: 0px;
	width: 100%;
	background-color:#E8E8E8;
}
td {
    padding: 5px;
}
.error {
	color: #FF0000;
}
</style>
</head>
<body>

<?php
// define variables and set to empty values
$forenameError = "";
$surnameError = "";
$addrline1Error = "";
$addrline2Error = "";
$addrline3Error = "";
$towncityError = "";
$countyregionError = "";
$postcodeError = "";
$countryError = "";
$languageError = "";
$mobilenumError = "";
$paytransidError = "";
$paytypeError = "";
$paydateError = "";
$paytimeError = "";

$buttonflag = 0;
$postflag = 0;

$forename = "";
$surname = "";
$addrline1 = "";
$addrline2 = "";
$addrline3 = "";
$towncity = "";
$countyregion = "";
$postcode = "";
$country = "";
$language = "";
$mobilenum = "";
$paytransid = "";
$paytype = "";
$paydate = "";
$paytime = "";


if(isset($_POST['register'])) { 
	$buttonflag = 1;
	$postflag = 1;
}
else if(isset($_POST['reset'])) { 
	$buttonflag  = 2;
	$postflag = 1;
}
else if(isset($_POST['search'])) { 
	$buttonflag  = 3;
	$postflag = 1;
}
else if(isset($_POST['savechanges'])) { 
	$buttonflag  = 4;
	$postflag = 1;	
}
else if(isset($_POST['delete'])) { 
	$buttonflag  = 5;
	$postflag = 1;	
}
else if(isset($_POST['uploadtrack'])) { 
	$postflag = 2;	
}
else if(isset($_POST['replacetrack'])) { 
	$postflag = 2;	
}
else if(isset($_POST['deletetrack'])) { 
	$postflag = 2;	
}
else if(isset($_POST['logoutrpu'])) { 
	$postflag = 3;	
}
	
if ($_SERVER["REQUEST_METHOD"] == "POST") {
	
	if ($postflag == 1){
		// First Name
		if (empty($_POST["forename"])) {
			if ($buttonflag == 1){ //then do check
				$forenameError = "First Name is required";
			}
		} 
		else {
			
			// Reset here
			$forename = test_input($_POST["forename"]);
			if (!preg_match("/^[a-zA-Z ]*$/",$forename)) {
				$forenameError = "Invalid characters detected";
			}
		}
	   // Surname
		if (empty($_POST["surname"])) {
			if ($buttonflag == 1){
				$surnameError = "Surname is required";
			}
		} 
		else {
			$surname = test_input($_POST["surname"]);
			if (!preg_match("/^[a-zA-Z ]*$/",$surname)) {
				$surnameError = "Invalid characters detected";
			}
		}
		// First line of address
		if (empty($_POST["addrline1"])) {
			if ($buttonflag == 1){		
				$addrline1Error = "First line of address is required";
			}
		} 
		else {
			$addrline1 = test_input($_POST["addrline1"]);
			if (!preg_match("/^[A-z0-9 ]*$/",$addrline1)) {
				$addrline1Error = "Invalid characters detected";
			}
		}
		// Second line of address
		if (empty($_POST["addrline2"])) {
			$addrline2 = "";
		} 
		else {
			$addrline2 = test_input($_POST["addrline2"]);
			if (!preg_match("/^[A-z0-9 ]*$/",$addrline2)) {
				$addrline2Error = "Invalid characters detected";
			}
		}
	
		// Third line of address
		if (empty($_POST["addrline3"])) {
			$addrline3 = "";
		} 
		else {
			$addrline3 = test_input($_POST["addrline3"]);
			if (!preg_match("/^[A-z0-9 ]*$/",$addrline3)) {
				$addrline3Error = "Invalid characters detected";
			}
		}
		// Town or City
		if (empty($_POST["towncity"])) {
			if ($buttonflag == 1){	
				$towncityError = "Town/ City is required";
			}
		} 
		else {
			$towncity = test_input($_POST["towncity"]);
			if (!preg_match("/^[A-z0-9 ]*$/",$towncity)) {
				$towncityError = "Invalid characters detected";
			}
		}
		
		//County or Region
		if (empty($_POST["countyregion"])) {
			$countyregion = "";
		} 
		else {
			$countyregion = test_input($_POST["addrline3"]);
			if (!preg_match("/^[A-z0-9 ]*$/",$countyregion)) {
				$countyregionError = "Invalid characters detected";
			}
		}
		
		// Poscode
		if (empty($_POST["postcode"])) {
			if ($buttonflag == 1){	
				$postcodeError = "Postcode is required";
			}
		} 
		else {
			$postcode = test_input($_POST["postcode"]);
			if (!preg_match("/^[A-z0-9 ]*$/",$postcode)) {
				$postcodeError = "Invalid characters detected";
			}
		}
		
		// country
		if (empty($_POST["country"])) {
			if ($buttonflag == 1){	
				$countryError = "Country is required";
			}
		} 
		
		// language
		if (empty($_POST["language"])) {
			if ($buttonflag == 1){			
				$languageError = "Language is required";
			}
		} 
		else {
			$language = test_input($_POST["language"]);
			if (!preg_match("/^[a-zA-Z ]*$/",$language)) {
				$languageError = "Invalid characters detected";
			}
		}
		
		//Mobile Number
		if (empty($_POST["mobilenum"])) {
			if ($buttonflag == 1){			
				$mobilenumError = "Mobile number is required";
			}
		} 
		else {
			$mobilenum = test_input($_POST["mobilenum"]);
			if (!preg_match("/^[1-9][0-9]{0,15}$/",$mobilenum)) {
				$mobilenumError = "Invalid characters detected";
			}
		}
		
		// Transaction ID
		if (empty($_POST["paytransid"])) {
			if ($buttonflag == 1){			
				$paytransidError = "Transaction Id is required";
			}
		} 
		else {
			$paytransid = test_input($_POST["language"]);
			if (!preg_match("/^[a-zA-Z ]*$/",$paytransid)) {
				$paytransidError = "Invalid characters detected";
			}
		}
		
		// Payment Type
		if (empty($_POST["paytype"])) {
			if ($buttonflag == 1){			
				$paytypeError = "Payment type is required";
			}
		} 
		else {
			$paytype = test_input($_POST["forename"]);
			if (!preg_match("/^[a-zA-Z ]*$/",$paytype)) {
				$paytypeError = "Invalid characters detected";
			}
		}
		
		// Payment Date
		if (empty($_POST["paydate"])) {
			if ($buttonflag == 1){			
				$paydateError = "Payment date is required";
			}
		} 
		
		// Payment Time
		if (empty($_POST["paytime"])) {
			if ($buttonflag == 1){			
				$paytimeError = "Payment time is required";
			}
		} 
	
			
		// edit
		function test_input($data) {
		   $data = trim($data);
		   $data = stripslashes($data);
		   $data = htmlspecialchars($data);
		   return $data;
		}
	}
	else if($postflag == 2){
		
	}
	else if($postflag == 3){
		
	}




//else if(isset($_POST['reset']) { 




// }





?>














<div id="header">
<h1>KIOSK Management</h1>
</div>


<div id="formsection">

<div id="customerinformation">
  <h2>Confirmation:</h2>
  <center>
  <p>Registration successful!</p>

    <button type="submit" onclick="window.location.href='payment.php'">Complete Payment</button>
    &nbsp;&nbsp;
    <button type="submit" onclick="window.location.href='main.php'" >Back to Main</button>
	</center>
</div>

<br>&nbsp;<br>

</div>
<div id="footer">
Footer
<?php
	print_r($_SERVER);
	print_r($_POST);
	print_r($_GET);
	print_r($_FILES);
?>
</div>





</body>
</html>