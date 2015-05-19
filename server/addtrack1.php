<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Add Track</title>

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



<form id="addtrackform" action="api.cgi">
<fieldset>
<legend>Add Track:</legend>
<table width="200" border="1">
	<tr>
    	<td>
         <select name="language"required>
            <option value="1">English</option>
            <option value="2">Francais</option>
            <option value="3">Espanol</option>
            <option value="4">Deustch</option>
            <option value="5">Russian</option>
        </select> 
        
        </td>
    </tr>
	<tr>
    	<td>
         <select name="knowledgeid"required>
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
            <option value="4">4</option>
            <option value="5">5</option>
        </select> 
        
        </td>
    </tr>
  <tr>
    <td>
    
    <input type="file" name="audiofile" size="32">
  
    </td>
  </tr>
</table>


</fieldset>

    <br>
    <center>
      <p>
       	<input type="submit" value="Add Track">
        <input type="reset" value="Clear Field">
        <input type="button" onclick="window.location.replace('main.php')" value="Cancel" />
</form>
<div id="result"></div>

<script type="text/javascript">
$("#addtrackform").submit(function(event) {

  /* stop submitting form */
  event.preventDefault();

  /* get some values from elements on the page: */
  var $form = $( this ),
  	act = "7",
    tn = $form.find( "input[name='audiofile']" ).val(),
	kid = $form.find( "input[name='knowledgeid']" ).val(),
	lang = $form.find( "input[name='language']" ).val(),
    url = $form.attr( "action" );


  /* Send the data using post */
  var posting = $.post( url, {	action: act,
  								findtrack: tn, 
								knowledgeid: kid,
								language: lang,
								} );

  /* Put the results in a div */
  posting.done(function( data ) {
	  switch(data)//needs to parse actual response data
	  {
		case 'OK': 
			alert('Track Deleted');
			break;
		case 'FALSE':
			alert('Track Not Found');
			break;
		  
	  }
	  
	var content = $( data ).find( "#content" );
	$( "#result" ).empty().append( content );

  });
});

</script>
</body>
</html>
