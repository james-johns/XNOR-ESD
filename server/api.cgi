#!/usr/bin/perl
use CGI;
use DBI;
use Switch;
use Digest::MD5 qw(md5 md5_hex md5_base64);
use Time::Piece;
use Net::Telnet ();

### Environment variable definitions
$logfile='./gstreamer.log';
$audio_base_path = "/home/rob/audio/"; # should be reconfigured to a better location, base path for audio file storage
my $q = CGI->new();

$HTTP_TYPE = 'text/plain';
$HTTP_RESPONSE_OK = 'HTTP/1.1 200 OK';

print $q->header(-type=>$HTTP_TYPE, -status=>$HTTP_RESPONSE_OK); # required no matter what our response is

$remote_addr = "$ENV{REMOTE_ADDR}";
if ($remote_addr eq "") {
    $remote_addr = "127.0.0.1";
}

my $debug = $q->param('debug');

#################################################################
########################## Functions ############################
#################################################################

sub debugPrint
{
    my $args = shift;
    if ($debug ne "") {
	foreach $arg ($args) {
	    print ("$arg");
	}
    }
}

sub login
{ 
    @args = $q->param;
    debugPrint("@args --> login");
  my $CDSHandle;
  
  # Finds and returns the "pin" value
  my $pin = $q->param('pin');

  if (!$pin)
  {
    print "!\n";
  }
  else
  {
    my $dateTime = localtime->strftime('%m/%d/%Y');
    my $token = md5_hex($dateTime);
    my $CDSHandle = &connectCDS();
    my $sth = $CDSHandle->prepare("SELECT RPU FROM ESD.Session WHERE RPU='$pin';");
    $sth->execute
      or die "SQL Error: $DBI::errstr\n";
     
    my $found = $sth->fetch();
    
    if (@$found eq "")
    {
      print "!\n";
    }
    else
    {
      print "$token";
      print ':';
      $sth = $CDSHandle->prepare("SELECT * FROM ESD.KnowledgeLvl;");
      $sth->execute
        or die "SQL Error: $DBI::errstr\n";
      
      my $row;
      my $message = '';
      while (@row = $sth->fetchrow_array)
      {  # retrieve one row
         $message .= join(".", @row) . '-';
      }
      $message = substr($message, 0, -1);
      print "$message";
      
      print ':';
      $sth = $CDSHandle->prepare("SELECT * FROM ESD.Language;");
      $sth->execute
        or die "SQL Error: $DBI::errstr\n";
      
      $message = '';
      while (@row = $sth->fetchrow_array)
      {  # retrieve one row
         $message .= join(".", @row) . '-';
      }
      $message = substr($message, 0, -1);
      print "$message";     
    }
  }     
}

#################################################################

sub logout
{
  debugPrint "@_  --> logout <br>";
}

#################################################################

sub addUser
{
  my $CDSHandle;
  my @fullname = split( /-/, $q->param('fullname'));
  my $address = $q->param('address');
  my $mobile = $q->param('mobilenum');
  if (!@fullname)
  {
    print "Name and Surname is required!\n";
  }
  else
  {
    $CDSHandle = &connectCDS();
    $CDSHandle->do('INSERT INTO ESD.Client (forename, surname, mobilePhone, address) VALUES (?,?,?,?)',
      undef, $fullname[0], $fullname[1], $mobile, $address)
        or die "SQL Error: $DBI::errstr\n";
    my $id = $CDSHandle->last_insert_id(undef, undef, undef, undef);
    print "$id";
  }
}

#################################################################

sub completePayment
{
  my $CDSHandle;  
  my $userid = $q->param('userid');
  
  # for some reason $q->param('name'); does`t work in a list context 
  my @payment = split(/ /, $q->param('paymentdetails'));
  if (!$userid && !@payment)
  {
    print "!\n";
    return;
  }
  
  $CDSHandle = &connectCDS();
  my $query = '';
    
  # creating a new transaction entry
  # Message body has to start at the beginning of the line
  my $idTransaction;
  if (($payment[1] ne '!') && ($payment[0] ne '!'))
  {
    $query = << 'END_MESSAGE';
INSERT INTO ESD.Transaction (transaction, paymentType)
VALUES (?,?)            
END_MESSAGE
    $CDSHandle->do($query, undef, $payment[0], $payment[1])
      or die "SQL Error: $DBI::errstr\n";
    $idTransaction = $CDSHandle->last_insert_id(undef, undef,undef, undef);  
  }
  
  # create a new session entry
  $query = '';
  # Message body has to start at the beginning of the line
  $query = << 'END_MESSAGE';
INSERT INTO ESD.Session (idClient, idTransaction, RPU)
VALUES (?,?,?)            
END_MESSAGE
  
  #generate random 4 digit number
  $rpuPin = "";
  for (1..4)
  {
    $rpuPin .= 1 + int(rand(8));
  }
  
  $CDSHandle->do($query, undef, $userid, $idTransaction, $rpuPin)
    or die "SQL Error: $DBI::errstr\n";
 
  print "$rpuPin\n";    
}

#################################################################

sub findUser
{
  debugPrint "@_  --> findUser <br>";
}

#################################################################

sub editUser
{
  debugPrint "@_  --> editUser <br>";
}

#################################################################

sub deleteUser
{
  debugPrint "@_  --> deleteUser <br>";
}

#################################################################

sub addTrack
{
    my @args = $q->param;
  debugPrint "@args  --> addTrack <br>\n";
  my $args = shift;
  my $file = $q->param('filename');
  my $trackid = $q->param('trackid');
  my $language = $q->param('language');
  my $knowledge = $q->param('knowledge');

  if (!$trackid) {
      print "Track ID required to create new track\n $trackid";
      return;
  }
  if (!$language) {
      print "Language required to create new track\n $language";
      return;
  }
  if (!$knowledge) {
      print "Knowledge Level required to create new track\n $knowledge";
      return;
  }
  if (!$file) {
      print "Audio file required to create new track\n $file";
      return;
  }

  my $filepath = getTrackPath($trackid, $language, $knowledge);
    print "Saving to $filepath";
  storeFile($file, $filepath);
}

#################################################################

sub deleteTrack
{
  debugPrint "@_  --> deleteTrack <br>";
  my $args = shift;
  my $file = $q->param('filename');
  my $trackid = $q->param('trackid');
  my $language = $q->param('language');
  my $knowledge = $q->param('knowledge');

  if ($trackid ne "") {
      print "Track ID required to create new track";
      return;
  }
  if ($language ne "") {
      print "Language required to create new track";
      return;
  }
  if ($knowledge ne "") {
      print "Knowledge Level required to create new track";
      return;
  }
  if ($file ne "") {
      print "Audio file required to create new track";
      return;
  }

  my $filepath = getTrackPath($trackid, $language, $knowledge);
  # delete file
}

sub storeFile {
    my $file = @_[0];
    my $filepath = @_[1];

#    $file=~m/^.*(\\|\/)(.*)/; # strip the remote path and keep the filename
#    my $name = $2;
    open(LOCAL, ">$filepath") or print $!;
    while(<$file>) {
        print LOCAL $_;
    }
    print "$file has been successfully uploaded... thank you.\n";
}

#################################################################

sub streamTrack
{
  debugPrint "@_  --> streamTrack <br>";
  my $trackid = $q->param('trackid');
  my $language = $q->param('language');
  my $knowledge = $q->param('knowledge');

  my $trackpath = getTrackPath($trackid, $language, $knowledge);
  debugPrint "Track path: $trackpath\n";
  stream_audio_track($trackpath, $remote_addr);
}

#################################################################
### getTrackPath($trackid, $language, $knowledgeLevel)
###
### Return path to file for request language, knowledge level and track ID
###
sub getTrackPath
{
    return $audio_base_path . @_[0] . @_[1] . @_[2] . ".ogg";
}

#################################################################
### stream_audio_track($trackPath, $targetIP);
###
### Begin streaming audio track.
###
### Checks that track file exists, and will begin streaming to target IP
### if it does. Else prints an error message.
sub stream_audio_track
{
    my $file      = @_[0];
    my $target_ip = @_[1];
    my $id = $target_ip;

    debugPrint "RPU ID = $id\n";

    if (-e $file) {
	my $tel = new Net::Telnet(Port => "4212");
	$tel->open("127.0.0.1");
	$tel->waitfor('/password: ?$/i');
	$tel->print("videolan");
	
	$tel->cmd("control $id stop");
	$tel->cmd("del $id"); 
	$tel->cmd("new $id vod enabled");
	$tel->cmd("setup $id input $file");
	$tel->cmd("quit");

    } else {
	print "\n\nError Audio track does not exist\n";
	print "$file";
    }
    return $pid;
}


#################################################################

sub connectCDS
{
  my $dbh = DBI->connect('dbi:mysql:ESD','root','root')
    or die "Connection Error: $DBI::errstr\n";

  return $dbh;
}


#################################################################
####################### MAIN PROGRAM FLOW #######################
#################################################################

### NOTE: backslash "\" before array "@" REQ_ARG means that it is
### passed into a subroutine as a reference
###
### Main state machine, based on the request type "action" or "token"
### calls appropriate subroutines as described in the
### "URI REQUEST AND WEB API" document
$action = $q->param('action');
$token = $q->param('token');
debugPrint "ACTION: $action\n";
debugPrint "TOKEN: $token\n";

if ($action ne "") {
    switch ($action)
    {
      case "0"      {&logout()}
      case "1"      {&login()}
      case "2"      {&addUser()}
      case "3"      {&completePayment()}
      case "4"      {&findUser()}
      case "5"      {&editUser()}
      case "6"      {&deleteUser()}
      case "7"      {&addTrack()}
      case "9"      {&deleteTrack()}
      else          {print "Error invalid action"}
    }
  }  
elsif ($token ne "") {
    &streamTrack();
}
else {
      print "invalid request";
}  

