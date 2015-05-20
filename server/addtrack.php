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
