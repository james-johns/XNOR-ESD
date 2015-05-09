#!/usr/bin/perl

use CGI;
use DBI;
use Switch;
use Digest::MD5 qw(md5 md5_hex md5_base64);
use Time::Piece;

### Environment variable definitions
$logfile='./gstreamer.log';
$audio_base_path = "./";
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
  my $CDSHandle;
  my $refReqArg = shift;
  
  # Finds and returns the "pin" value
  my $pin = &parse($refReqArg, 'pin');

  if ($pin eq "")
  {
    print "parsing error<br>";
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
  print "@_  --> addUser <br>";
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
  print "@_  --> addTrack <br>";
}

#################################################################

sub deleteTrack
{
  print "@_  --> deleteTrack <br>";
}

#################################################################

sub streamTrack
{
  print "@_  --> streamTrack <br>";
}

#################################################################
### Takes two arguments one is request_argument reference, the
### second is a request type to find
### it then returns the argument value of the request
### and deletes the entry from the main array
sub parse
{
  my @match;
  my $refReqArg = shift;
  my $searchArg = shift;

  foreach $index (0 .. $#$refReqArg)
  { 
    if ($refReqArg->[$index] =~ /$searchArg/)
    {
      @match = split(/=/, $refReqArg->[$index]);
      splice @$refReqArg, $index, 1;
      last;
    }  
  }
  
  return @match[1];
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

### environment variables MAINREQ - type of the request
### MAINARG the request argument
### REQ_ARG holds a parsed URI request, it is passed through
### an environment variable to the CGI script
### split creates an array, by spliting the URI request
### based on a "&" character
@REQ_ARG = split (/&/, "$ENV{'QUERY_STRING'}");
$MAINREQ;
$MAINARG;

### loops through the array of request_argument array
### finds the main request type: "action" or "token"
### one is for streaming file with an RPU, the rest for
### the other actions.
### It then deletes the found element from an array
### (so that further array manipulations are 1 iteration shorter)
foreach my $index (0 .. $#REQ_ARG)
{
  if ( ( @REQ_ARG[$index] =~ /action/) || (@REQ_ARG[$index] =~ /token/) )
  {
    my @TEMP = split(/=/, $REQ_ARG[$index]);
    $MAINREQ = $TEMP[0];
    $MAINARG = $TEMP[1];
    splice @REQ_ARG, $index, 1;
    last;
  }
}

### NOTE: backslash "\" before array "@" REQ_ARG means that it is
### passed into a subroutine as a reference
###
### Main state machine, based on the request type "action" or "token"
### calls appropriate subroutines as described in the
### "URI REQUEST AND WEB API" document
switch ($MAINREQ)
{
  case "action"
  {
    switch ($MAINARG)
    {
      case "0"      {&logout(\@REQ_ARG)}
      case "1"      {&login(\@REQ_ARG)}
      case "2"      {&addUser(\@REQ_ARG)}
      case "3"      {&completePayment(\@REQ_ARG)}
      case "4"      {&findUser(\@REQ_ARG)}
      case "5"      {&editUser(\@REQ_ARG)}
      case "6"      {&deleteUser(\@REQ_ARG)}
      case "7"      {&addTrack(\@REQ_ARG)}
      case "9"      {&deleteTrack(\@REQ_ARG)}
      else          {print "Error invalid request type<br>"}
    }
  }  
  case "token"      {&streamTrack(\@REQ_ARG)}
  else              {print "invalid request<br>"}  
}
