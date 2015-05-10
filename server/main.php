<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>XnOR MADS KIOSK</title>


<style>
body {
    background-color: #001941;
} 
#main {
    color:white;
    text-align:center;
    padding:5px;
	width: 700px;
    margin: 0px auto;
}

table {
    border: 0px;
	

}
td {
    padding: 5px;
}

</style>
</head>
<body>

<div id="main">
<table width="200" border="0">
  <tr>
    <td colspan="3" align="center"><img src="img/header.png"></td>
    </tr>
  <tr>
    <td align="center"><input type="image" src="img/reguserbutton.png" value="registerUser" title="Register User" onclick="window.location.href='registeruser.php'" /></td>
    <td align="center"><input type="image" src="img/searchuserbutton.png" value="searchUser" title="Search User, Complete Payment" onclick="window.location.href='searchuser.php'" /> </td>
    <td align="center"><input type="image" src="img/deluserbutton.png" value="deleteUser" title="Delete User" onclick="window.location.href='registeruser.php'" /></td>
    </tr>
  <tr>
    <td align="center"><img src="img/openbutton.png"></td>
    <td align="center"><input type="image" src="img/logoutrpubutton.png" value="logoutRPU" title="Logout RPU" onclick="window.location.href='registeruser.php'" /></td>
    <td align="center"><img src="img/openbutton.png"></td>
    </tr>
  <tr>
    <td align="center"><input type="image" src="img/addtrackbutton.png" value="addTrack" title="Add Track" onclick="window.location.href='addtrack.php'" /></td>
    <td align="center"><input type="image" src="img/replacetrackbutton.png" value="deleteTrack" title="Delete Track" onclick="window.location.href='registeruser.php'" /></td>
    <td align="center"><input type="image" src="img/deltrackbutton.png" value="replaceTrack" title="Replace Track" onclick="window.location.href='registeruser.php'" /></td>
    </tr>
</table>

</div>


</body>
</html>
