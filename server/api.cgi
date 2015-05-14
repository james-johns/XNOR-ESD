#!/usr/bin/perl

use CGI;
use DBI;
use Switch;
use Digest::MD5 qw(md5 md5_hex md5_base64);
use Time::Piece;

### Environment variable definitions
$logfile='./gstreamer.log';
$audio_base_path = "/home/james/public_html/esd/audio/"; # should be reconfigured to a better location, base path for audio file storage
my $q = CGI->new();

$HTTP_TYPE = 'text/plain';
$HTTP_RESPONSE_OK = 'HTTP/1.1 200 OK';

print $q->header(-type=>$HTTP_TYPE, -status=>$HTTP_RESPONSE_OK); # required no matter what our response is

$remote_addr = "$ENV{REMOTE_ADDR}";
if ($remote_addr eq "") {
    $remote_addr = "127.0.0.1";
}

#################################################################
########################## Functions ############################
#################################################################

sub login
{ 
    @args = $q->param;
    print("@args --> login");
  my $CDSHandle;
  
  # Finds and returns the "pin" value
  my $pin = $q->param('pin');

  if (!$pin)
  {
    print "PIN number required<br>";
  }
  else
  {
    my $dateTime = localtime->strftime('%m/%d/%Y');
    my $token = md5_hex($dateTime);
    my $CDSHandle = &connectCDS();
    my $sth = $CDSHandle->prepare("SELECT pin FROM ESD.RPU WHERE pin='$pin';");
    $sth->execute
      or die "SQL Error: $DBI::errstr\n";
     
    my $found = $sth->fetch();
    
    if (@$found eq "")
    {
      print "could not find a record <br>";
    }
    else
    {
      print "$token";
      print ':';
      $sth = $CDSHandle->prepare("SELECT knowledgeLvl FROM ESD.KnowledgeLvl;");
      $sth->execute
        or die "SQL Error: $DBI::errstr\n";
      
      my $row;
      my $message = '';
      while ($row = $sth->fetchrow_array)
      {  # retrieve one row
         $message .= $row . '-';
      }
      $message = substr($message, 0, -1);
      print "$message";
      
      print ':';
      $sth = $CDSHandle->prepare("SELECT language FROM ESD.Language;");
      $sth->execute
        or die "SQL Error: $DBI::errstr\n";
      
      $message = '';
      while ($row = $sth->fetchrow_array)
      {  # retrieve one row
         $message .= $row . '-';
      }
      $message = substr($message, 0, -1);
      print "$message";     
    }
  }     
}

#################################################################

sub logout
{
  print "@_  --> logout <br>";
}

#################################################################

sub addUser
{
  my $CDSHandle;
  my @fullname = split( /-/, $q->param('fullname'));
  my $address = $q->param('address');
  my $language = $q->param('language');
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
    print "$id\n";
    #print "@fullname - $address - $language - $mobile";
  }
}

#################################################################

sub completePayment
{
  print "@_  --> completePayment <br>";
}

#################################################################

sub findUser
{
  print "@_  --> findUser <br>";
}

#################################################################

sub editUser
{
  print "@_  --> editUser <br>";
}

#################################################################

sub deleteUser
{
  print "@_  --> deleteUser <br>";
}

#################################################################

sub addTrack
{
    my @args = $q->param;
  print "@args  --> addTrack <br>\n";
  my $args = shift;
  my $file = $q->param('file');
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
  print "@_  --> deleteTrack <br>";
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
    open(LOCAL, ">$filepath") or die $!;
    while(<$file>) {
        print LOCAL $_;
    }
    print "$file has been successfully uploaded... thank you.\n";
}

#################################################################

sub streamTrack
{
  print "@_  --> streamTrack <br>";
  my $trackid = $q->param('trackid');
  my $language = $q->param('language');
  my $knowledge = $q->param('knowledge');

  my $trackpath = getTrackPath($trackid, $language, $knowledge);
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
    my $pid = 0;
    if (-e $file) {
	if (($pid = fork()) == 0) {
	    close(STDOUT);
	    close(STDERR);
	    open(STDOUT, ">", $logfile);
	    open(STDERR, ">", $logfile);
	    exec("gst-launch-1.0", "filesrc", "location=$file", "!", 
		 "tcpclientsink", "host=$target_ip", "port=3000");
	    exit;
	} else {
	    print "Success\n\n";
	    print "gst-launch-1.0 filesrc location=$file ! ";
	    print "tcpclientsink host=$target_ip port=3000<br />\n";
	}
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
print "ACTION: $action\n";
print "TOKEN: $token\n";

if ($action ne "") {
    switch ($action)
    {
      case "0"      {&logout(\@REQ_ARG)}
      case "1"      {&login(\@REQ_ARG)}
      case "2"      {&addUser(\@REQ_ARG)}
      case "3"      {&completePayment(\@REQ_ARG)}
      case "4"      {&findUser(\@REQ_ARG)}
      case "5"      {&editUser(\@REQ_ARG)}
      case "6"      {&deleteUser(\@REQ_ARG)}
      case "7"      {&addTrack()}
      case "9"      {&deleteTrack(\@REQ_ARG)}
      else          {print "Error invalid action"}
    }
  }  
elsif ($token ne "") {
    &streamTrack(\@REQ_ARG);
}
else {
      print "invalid request";
}  

