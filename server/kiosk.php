<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Untitled Document</title>

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
  <h2>Manage Customer Details:</h2>
<p align="right"><span class="error">* Required field for registration.</span></p>
<form method="post" action="api.cgi">
<fieldset>
<legend>Customer Information:</legend>

<table width="200" border="0">
  <tr>
    <td width="33%" align="right">First Name: *</td>
    <td width="67%"><input type="text" size="32" maxlength="32" name="forename">
    <span class="error"> <?php echo $forenameError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Surname: *</td>
    <td><input type="text" size="32" maxlength="32" name="surname">
    <span class="error"> <?php echo $surnameError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Address Line 1: *</td>
    <td><input type="text" size="32" maxlength="32" name="addrline1">
    <span class="error"> <?php echo $addrline1Error;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Address Line 2:</td>
    <td><input type="text" size="32" maxlength="32" name="addrline2">
    <span class="error"> <?php echo $addrline2Error;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Address Line 3:</td>
    <td><input type="text" size="32" maxlength="32" name="addrline3">
    <span class="error"> <?php echo $addrline3Error;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Town/City: *</td>
    <td><input type="text" size="32" maxlength="32" name="towncity">
    <span class="error"> <?php echo $towncityError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">County/Region:</td>
    <td><input type="text" size="32" maxlength="32" name="countyregion">
    <span class="error"> <?php echo $countyregionError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">postcode: *</td>
    <td><input type="text" size="32" maxlength="32" name="postcode">
    <span class="error"> <?php echo $postcodeError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">country: *</td>
    <td>
    <select name="country">
    <option value="">Country...</option>
    <option value="AF">Afghanistan</option>
    <option value="AL">Albania</option>
    <option value="DZ">Algeria</option>
    <option value="AS">American Samoa</option>
    <option value="AD">Andorra</option>
    <option value="AG">Angola</option>
    <option value="AI">Anguilla</option>
    <option value="AG">Antigua &amp; Barbuda</option>
    <option value="AR">Argentina</option>
    <option value="AA">Armenia</option>
    <option value="AW">Aruba</option>
    <option value="AU">Australia</option>
    <option value="AT">Austria</option>
    <option value="AZ">Azerbaijan</option>
    <option value="BS">Bahamas</option>
    <option value="BH">Bahrain</option>
    <option value="BD">Bangladesh</option>
    <option value="BB">Barbados</option>
    <option value="BY">Belarus</option>
    <option value="BE">Belgium</option>
    <option value="BZ">Belize</option>
    <option value="BJ">Benin</option>
    <option value="BM">Bermuda</option>
    <option value="BT">Bhutan</option>
    <option value="BO">Bolivia</option>
    <option value="BL">Bonaire</option>
    <option value="BA">Bosnia &amp; Herzegovina</option>
    <option value="BW">Botswana</option>
    <option value="BR">Brazil</option>
    <option value="BC">British Indian Ocean Ter</option>
    <option value="BN">Brunei</option>
    <option value="BG">Bulgaria</option>
    <option value="BF">Burkina Faso</option>
    <option value="BI">Burundi</option>
    <option value="KH">Cambodia</option>
    <option value="CM">Cameroon</option>
    <option value="CA">Canada</option>
    <option value="IC">Canary Islands</option>
    <option value="CV">Cape Verde</option>
    <option value="KY">Cayman Islands</option>
    <option value="CF">Central African Republic</option>
    <option value="TD">Chad</option>
    <option value="CD">Channel Islands</option>
    <option value="CL">Chile</option>
    <option value="CN">China</option>
    <option value="CI">Christmas Island</option>
    <option value="CS">Cocos Island</option>
    <option value="CO">Colombia</option>
    <option value="CC">Comoros</option>
    <option value="CG">Congo</option>
    <option value="CK">Cook Islands</option>
    <option value="CR">Costa Rica</option>
    <option value="CT">Cote D'Ivoire</option>
    <option value="HR">Croatia</option>
    <option value="CU">Cuba</option>
    <option value="CB">Curacao</option>
    <option value="CY">Cyprus</option>
    <option value="CZ">Czech Republic</option>
    <option value="DK">Denmark</option>
    <option value="DJ">Djibouti</option>
    <option value="DM">Dominica</option>
    <option value="DO">Dominican Republic</option>
    <option value="TM">East Timor</option>
    <option value="EC">Ecuador</option>
    <option value="EG">Egypt</option>
    <option value="SV">El Salvador</option>
    <option value="GQ">Equatorial Guinea</option>
    <option value="ER">Eritrea</option>
    <option value="EE">Estonia</option>
    <option value="ET">Ethiopia</option>
    <option value="FA">Falkland Islands</option>
    <option value="FO">Faroe Islands</option>
    <option value="FJ">Fiji</option>
    <option value="FI">Finland</option>
    <option value="FR">France</option>
    <option value="GF">French Guiana</option>
    <option value="PF">French Polynesia</option>
    <option value="FS">French Southern Ter</option>
    <option value="GA">Gabon</option>
    <option value="GM">Gambia</option>
    <option value="GE">Georgia</option>
    <option value="DE">Germany</option>
    <option value="GH">Ghana</option>
    <option value="GI">Gibraltar</option>
    <option value="GB">Great Britain</option>
    <option value="GR">Greece</option>
    <option value="GL">Greenland</option>
    <option value="GD">Grenada</option>
    <option value="GP">Guadeloupe</option>
    <option value="GU">Guam</option>
    <option value="GT">Guatemala</option>
    <option value="GN">Guinea</option>
    <option value="GY">Guyana</option>
    <option value="HT">Haiti</option>
    <option value="HW">Hawaii</option>
    <option value="HN">Honduras</option>
    <option value="HK">Hong Kong</option>
    <option value="HU">Hungary</option>
    <option value="IS">Iceland</option>
    <option value="IN">India</option>
    <option value="ID">Indonesia</option>
    <option value="IA">Iran</option>
    <option value="IQ">Iraq</option>
    <option value="IR">Ireland</option>
    <option value="IM">Isle of Man</option>
    <option value="IL">Israel</option>
    <option value="IT">Italy</option>
    <option value="JM">Jamaica</option>
    <option value="JP">Japan</option>
    <option value="JO">Jordan</option>
    <option value="KZ">Kazakhstan</option>
    <option value="KE">Kenya</option>
    <option value="KI">Kiribati</option>
    <option value="NK">Korea North</option>
    <option value="KS">Korea South</option>
    <option value="KW">Kuwait</option>
    <option value="KG">Kyrgyzstan</option>
    <option value="LA">Laos</option>
    <option value="LV">Latvia</option>
    <option value="LB">Lebanon</option>
    <option value="LS">Lesotho</option>
    <option value="LR">Liberia</option>
    <option value="LY">Libya</option>
    <option value="LI">Liechtenstein</option>
    <option value="LT">Lithuania</option>
    <option value="LU">Luxembourg</option>
    <option value="MO">Macau</option>
    <option value="MK">Macedonia</option>
    <option value="MG">Madagascar</option>
    <option value="MY">Malaysia</option>
    <option value="MW">Malawi</option>
    <option value="MV">Maldives</option>
    <option value="ML">Mali</option>
    <option value="MT">Malta</option>
    <option value="MH">Marshall Islands</option>
    <option value="MQ">Martinique</option>
    <option value="MR">Mauritania</option>
    <option value="MU">Mauritius</option>
    <option value="ME">Mayotte</option>
    <option value="MX">Mexico</option>
    <option value="MI">Midway Islands</option>
    <option value="MD">Moldova</option>
    <option value="MC">Monaco</option>
    <option value="MN">Mongolia</option>
    <option value="MS">Montserrat</option>
    <option value="MA">Morocco</option>
    <option value="MZ">Mozambique</option>
    <option value="MM">Myanmar</option>
    <option value="NA">Nambia</option>
    <option value="NU">Nauru</option>
    <option value="NP">Nepal</option>
    <option value="AN">Netherland Antilles</option>
    <option value="NL">Netherlands (Holland, Europe)</option>
    <option value="NV">Nevis</option>
    <option value="NC">New Caledonia</option>
    <option value="NZ">New Zealand</option>
    <option value="NI">Nicaragua</option>
    <option value="NE">Niger</option>
    <option value="NG">Nigeria</option>
    <option value="NW">Niue</option>
    <option value="NF">Norfolk Island</option>
    <option value="NO">Norway</option>
    <option value="OM">Oman</option>
    <option value="PK">Pakistan</option>
    <option value="PW">Palau Island</option>
    <option value="PS">Palestine</option>
    <option value="PA">Panama</option>
    <option value="PG">Papua New Guinea</option>
    <option value="PY">Paraguay</option>
    <option value="PE">Peru</option>
    <option value="PH">Philippines</option>
    <option value="PO">Pitcairn Island</option>
    <option value="PL">Poland</option>
    <option value="PT">Portugal</option>
    <option value="PR">Puerto Rico</option>
    <option value="QA">Qatar</option>
    <option value="ME">Republic of Montenegro</option>
    <option value="RS">Republic of Serbia</option>
    <option value="RE">Reunion</option>
    <option value="RO">Romania</option>
    <option value="RU">Russia</option>
    <option value="RW">Rwanda</option>
    <option value="NT">St Barthelemy</option>
    <option value="EU">St Eustatius</option>
    <option value="HE">St Helena</option>
    <option value="KN">St Kitts-Nevis</option>
    <option value="LC">St Lucia</option>
    <option value="MB">St Maarten</option>
    <option value="PM">St Pierre &amp; Miquelon</option>
    <option value="VC">St Vincent &amp; Grenadines</option>
    <option value="SP">Saipan</option>
    <option value="SO">Samoa</option>
    <option value="AS">Samoa American</option>
    <option value="SM">San Marino</option>
    <option value="ST">Sao Tome &amp; Principe</option>
    <option value="SA">Saudi Arabia</option>
    <option value="SN">Senegal</option>
    <option value="RS">Serbia</option>
    <option value="SC">Seychelles</option>
    <option value="SL">Sierra Leone</option>
    <option value="SG">Singapore</option>
    <option value="SK">Slovakia</option>
    <option value="SI">Slovenia</option>
    <option value="SB">Solomon Islands</option>
    <option value="OI">Somalia</option>
    <option value="ZA">South Africa</option>
    <option value="ES">Spain</option>
    <option value="LK">Sri Lanka</option>
    <option value="SD">Sudan</option>
    <option value="SR">Suriname</option>
    <option value="SZ">Swaziland</option>
    <option value="SE">Sweden</option>
    <option value="CH">Switzerland</option>
    <option value="SY">Syria</option>
    <option value="TA">Tahiti</option>
    <option value="TW">Taiwan</option>
    <option value="TJ">Tajikistan</option>
    <option value="TZ">Tanzania</option>
    <option value="TH">Thailand</option>
    <option value="TG">Togo</option>
    <option value="TK">Tokelau</option>
    <option value="TO">Tonga</option>
    <option value="TT">Trinidad &amp; Tobago</option>
    <option value="TN">Tunisia</option>
    <option value="TR">Turkey</option>
    <option value="TU">Turkmenistan</option>
    <option value="TC">Turks &amp; Caicos Is</option>
    <option value="TV">Tuvalu</option>
    <option value="UG">Uganda</option>
    <option value="UA">Ukraine</option>
    <option value="AE">United Arab Emirates</option>
    <option value="GB">United Kingdom</option>
    <option value="US">United States of America</option>
    <option value="UY">Uruguay</option>
    <option value="UZ">Uzbekistan</option>
    <option value="VU">Vanuatu</option>
    <option value="VS">Vatican City State</option>
    <option value="VE">Venezuela</option>
    <option value="VN">Vietnam</option>
    <option value="VB">Virgin Islands (Brit)</option>
    <option value="VA">Virgin Islands (USA)</option>
    <option value="WK">Wake Island</option>
    <option value="WF">Wallis &amp; Futana Is</option>
    <option value="YE">Yemen</option>
    <option value="ZR">Zaire</option>
    <option value="ZM">Zambia</option>
    <option value="ZW">Zimbabwe</option>
    </select>  
    <span class="error"> <?php echo $countryError;?></span>
    </td>
  </tr>
    <tr>
    <td align="right">language: *</td>
    <td><input type="text" size="32" maxlength="32" name="language">
    <span class="error"> <?php echo $languageError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Contact mobile number: *</td>
    <td><input type="text" size="32" maxlength="32" name="mobilenum">
    <span class="error"> <?php echo $mobilenumError;?></span>
    </td>
  </tr>
</table>
</fieldset>

<br>

<fieldset>
<legend>Payment Details:</legend>

<table width="200" border="0">
  <tr>
    <td width="33%" align="right">Transaction Id: *</td>
    <td width="67%"><input type="text" size="32" maxlength="32" name="paytransid">
    <span class="error"> <?php echo $paytransidError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Payment Type: *</td>
    <td><input type="text" size="32" maxlength="16" name="paytype">
    <span class="error"> <?php echo $paytypedError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Date: *</td>
    <td><input type="date" size="32" maxlength="16" name="paydate">
    <span class="error"> <?php echo $paydateError;?></span>
    </td>
  </tr>
  <tr>
    <td align="right">Time: *</td>
    <td><input type="time" size="32" maxlength="16" name="paytime">
    <span class="error"> <?php echo $paytimeError; ?></span>
    </td>
  </tr>
</table>

</fieldset>
PIN HOLDER
<center>
  <p>
    <button type="submit" name="register" >Register</button>
    <button type="submit" name="reset" >Reset</button>
    <button type="submit" name="search" >Search</button>
    <button type="submit" name="savechanges" >Save Changes</button>
    <button type="submit" name="delete" >Delete</button>
  </p>
</center>
&nbsp;<br>
</form>
</div>

<br><br>
<div id = "trackmanagement">
<h2>Manage Track:</h2>
<form method="post" action="api.cgi" enctype="multipart/form-data">
<fieldset>
<legend>Upload Track:</legend>
Choose the file to upload:
<input type="file" name="fileid" /><br />
<button type="submit" name="uploadtrack">Upload</button>
</fieldset>
<br>
<fieldset>
<legend>Replace Track:</legend>
Enter track id to replace: 
<input type="text" size="16" maxlength="16" name="trackid">
Choose new file to upload:
<input type="file" name="fileid" /><br />
<button type="submit" name="replacetrack">Replace</button>
</fieldset>
<br>
<fieldset>
<legend>Delete Track:</legend>
Track ID: 
<input type="text" size="32" maxlength="32" name="trackid">
<button type="submit" name="deletetrack" >Delete</button>
</fieldset>
</form>

 </div>
 
 <br><br>
<div id = "rpumanagement">
<h2>Manage RPU:</h2>
<form method="post" action="api.cgi">
<fieldset>
<legend>Logout RPU:</legend>
Enter RPU Token:
<input type="text" size="32" maxlength="32" name="rputoken">
<button type="submit" name="logoutrpu" >Logout</button>
</fieldset>
</form>
</div>
 
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