<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Add User Confirmation</title>
<script type="text/javascript">
function checkData(tid) {
	switch(tid) {
      	case "edit":
         	alert('a');
			<?php echo $clientID ?>
         	break;
      	case "delete":
         	alert('b');
         	break;
		case "search":
         	alert('b');
			window.location.replace('searchuser.php')
         	break;
		case "cancel":
         	alert('b');
			window.location.replace('main.php')
         	break;
      }
   }
</script>
</head>

<body>

<?php
$userdata = $_POST["userdata"];
echo $userdata;


//print_r($_POST);
?>
<h1>User exists! </h1>
Select an option:

<form >
    <input type="hidden" name="userdata" value="<?php echo $userdata;?>">
    <input type="button" id="edit" name="edit" value="Edit User" onClick="return checkData(this.id);">
	<input type="button" id="delete" name="delete"value="Delete User" onClick="return checkData(this.id);">
    <input type="button" id="search" name="edit" onclick="return checkData(this.id);" value="Search Again" />
	<input type="button" id="cancel" name="edit" onclick="return checkData(this.id);" value="Cancel" />
	
    
   
   
</form>

<script type="text/javascript">
function checkData(tid) {
	switch(tid) {
      	case "edit":
         	alert('a');
         	break;
      	case "delete":
         	alert('b');
         	break;
		case "search":
         	alert('b');
			window.location.replace('searchuser.php')
         	break;
		case "cancel":
         	alert('b');
			window.location.replace('main.php')
         	break;
      }
   }


//$("#sucomfirmationform").submit(function(event) {
//	
//	
//	/* stop submitting form */
//  	event.preventDefault();
//	
//	var btn = $(this).find("input[type=submit]:focus" );
// 	alert("haaaaaaaaaaaa");
//	/* note: you can return false to prevent the default behavior
//	   of the form--that is; stop the page from submitting */ 
//	
//	/*if delete then delete if edit then post to edit page,,if edit user,, will send a request to cdd server and will retrieve info ..then pass to edituser page..then if payment details is available then grayed out paydetails .if not then display add payment whichc will go to paymentphp page*/
//	
//
//	
//
//	
//
//	
//	/* get client id from php post */
//  	var cID = "<?php echo $clientID ?>";
//	//alert(cID);
//	
//	/* get some values from elements on the page: */
//  	var $form = $( this ), 
//	cID = $form.find( "input[name='clientID']" ).val(),
//	url = $form.attr( "action" );
//	
//	/* Send the data using post */
//	var posting = $.post( url, { clientID: cID });
//  
//  
//}



</script>

</body>
</html>