<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>XnOR MADS KIOSK</title>
<!--CSS for the Main Menu Page-->
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
  	<!--XNOR Logo goes here-->
    <td colspan="3" align="center"><img src="img/header.png"></td>
    </tr>
  <tr>
  	<!--Menu Options goes here-->
    <td align="center"><input type="image" src="img/reguserbutton.png" value="registerUser" title="Register User" onclick="window.location.href='adduser.php'" /></td>
    <td align="center"><input type="image" src="img/searchuserbutton.png" value="searchUser" title="Search User, Complete Payment" onclick="window.location.href='searchuser.php'" /> </td>
    <td align="center"><input type="image" src="img/deluserbutton.png" value="deleteUser" title="Delete User" onclick="window.location.href='deleteuser.php'" /></td>
    </tr>
  <tr>
    <td align="center"><input type="image" src="img/edituserbutton.png" value="logoutRPU" title="Logout RPU" onclick="window.location.href='saveedituser.php'" /></td>
    <td align="center"><input type="image" src="img/logoutrpubutton.png" value="logoutRPU" title="Logout RPU" onclick="window.location.href='logoutrpu.php'" /></td>
    <td align="center"><input type="image" src="img/startbroadcastbutton.png" value="startBroadcast" title="Start Broadcast" onclick="window.location.href='broadcast.php'" /></td>
    </tr>
  <tr>
    <td align="center"><input type="image" src="img/addtrackbutton.png" value="addTrack" title="Add Track" onclick="window.location.href='addtrack.php'" /></td>
    <td align="center"><input type="image" src="img/deltrackbutton.png" value="replaceTrack" title="Replace Track" onclick="window.location.href='deletetrack.php'" /></td>
	<td align="center"><input type="image" src="img/openbutton.png" /></td>
    </tr>
</table>
</div>
</body>
</html>