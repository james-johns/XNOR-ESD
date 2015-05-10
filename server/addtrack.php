<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Registration Form</title>

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
	$postflag = 2;
}
else if(isset($_POST['reset'])) { 
	$buttonflag  = 2;
	$postflag = 2;
}
else if(isset($_POST['search'])) { 
	$buttonflag  = 3;
	$postflag = 2;
}
else if(isset($_POST['savechanges'])) { 
	$buttonflag  = 4;
	$postflag = 2;	
}
else if(isset($_POST['delete'])) { 
	$buttonflag  = 5;
	$postflag = 2;	
}
else if(isset($_POST['uploadtrack'])) { 
	$postflag = 1;	
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
   $error = 0;
	if ($postflag == 1){
		// File
		if (empty($_POST["file"])) {
                        $fileError = "File is required";
                        $error += 1;
		} 
                // Exhibit Number
		if (empty($_POST["trackid"])) {
                        $trackidError = "Exhibit Number is required";
                        $error += 1;
		} 
		else {
			$trackid = test_input($_POST["trackid"]);
			if (!preg_match("/^[1-9]*$/",$trackid)) {
				$trackidError = "Invalid characters detected";
                                $error += 1;
			}
		}
		// Language
		if (empty($_POST["language"])) {
                        $languageError = "Language is required";
                        $error += 1;
		} 
		else {
			$language = test_input($_POST["language"]);
			if (!preg_match("/^[0-9]*$/",$language)) {
				$languageError = "Invalid characters detected";
                                $error += 1;
			}
		}
		// Knowledge level
		if (empty($_POST["knowledge"])) {
			$knowledgeError = "Knowledge level is required";
                        $error += 1;
	        }
		else {
			$knowledge = test_input($_POST["knowledge"]);
			if (!preg_match("/^[0-9]*$/",$addrline2)) {
				$knowledgeError = "Invalid characters detected";
                        $error += 1;
			}
		}
	
                if ($error == 0) {

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
  <h2>Register User:</h2>
<p align="right"><span class="error">* Required field for registration.</span></p>
<form method="POST" enctype="multipart/form-data" action="api.cgi" id="registrationform">
<input type="hidden" name="action" value="7">
<fieldset>
<legend>Customer Information:</legend>

<table width="200" border="0">
  <tr>
    <td align="right">File: *</td>
    <td><input type="file" name="filename">
    <span class="error"> <?php echo $fileError;?></span>
    </td>
  </tr>
  <tr>
    <td width="33%" align="right">Exhibit Number: *</td>
    <td width="67%"><input type="text" size="32" maxlength="32" name="trackid">
    <span class="error"> <?php echo $trackidError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Language: *</td>
    <td><input type="text" size="32" maxlength="32" name="language">
    <span class="error"> <?php echo $languageError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">KnowledgeLevel: *</td>
    <td><input type="text" size="32" maxlength="32" name="knowledge">
    <span class="error"> <?php echo $knowledgeError;?></span>
    </td>
  </tr>
</table>
</fieldset>

<br>
<center>
  <p>
    <button type="submit" form="registrationform" value="Upload">Register</button>
    &nbsp;&nbsp;
    <button type="submit" name="reset" >Reset Fields</button>
     &nbsp;&nbsp;
    <button type="submit" name="cancel" onclick="window.location.href='main.php'">Cancel</button>
  </p>
</center>
&nbsp;<br>
</form>
</div>

<br><br>

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
