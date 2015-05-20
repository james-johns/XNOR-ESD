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



<form id="adduserform" action="192.168.1.3">
<fieldset>
<legend>Add User:</legend>
<table width="200" border="1">
  <tr>
    <td><input type="text" size="32" name="firstname" placeholder="First Name" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="surname" placeholder="Surname" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="addrline1" placeholder="Address Line 1" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="addrline2" placeholder="Address Line 2"></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="addrline3" placeholder="Address Line 3"></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="city" placeholder="City" required></td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="postcode" placeholder="Post Code" required></td>
  </tr>
  <tr>
    <td>
    <select id="selcountry" name="country" required>
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
    </td>
  </tr>
  <tr>
    <td><input type="text" size="32" name="mobilenum" placeholder="Mobile Number" required></td>
  </tr>
</table>


</fieldset>

    <br>

       	<input type="submit" value="Add User">
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
  	act = "2",
    fn = $form.find( "input[name='firstname']" ).val(),
	sn = $form.find( "input[name='surname']" ).val(),
	adl1 = $form.find( "input[name='addrline1']" ).val(),
	adl2 = $form.find( "input[name='addrline2']" ).val(),
	adl3 = $form.find( "input[name='addrline3']" ).val(), //Town
	cty = $form.find( "input[name='city']" ).val(),
	pc = $form.find( "input[name='postcode']" ).val(),
	cntry = $form.find( "input[name='country']" ).val(),
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
  								fullname: fullnam,
								address: fulladdress,
								mobilenum: mb } );

  /* Put the results in a div */
  posting.done(function( data ) {
	 // alert(data);
	  
	  if (data != '!'){
		  //alert(data);
		  	var url = 'au-confirmation.php';
			var form = $('<form action="' + url + '" method="post">' +
			  '<input type="text" name="clientID" value="' + data + '" />' +
			  '</form>');
			$('body').append(form);
			form.submit();
	  }
	  else{
		  alert('Registration Error');
	  }
  });
});

</script>
</body>
</html>