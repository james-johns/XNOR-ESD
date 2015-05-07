#!/usr/bin/perl

use CGI;
use DBI;
use Switch;

### Environment variable definitions
$logfile='./gstreamer.log';
$audio_base_path = "./";

$remote_addr = "$ENV{REMOTE_ADDR}";
if ($remote_addr eq "") {
    $remote_addr = "127.0.0.1";
}

### Functions

sub login
{ 
  # Finds and returns the "pin"
  my $temp = &parse(\@REQ_ARG, 'pin');
  print "$temp <br>";
}

sub logout
{
  print "@_  --> logout <br>";
}

sub addUser
{
  print "@_  --> addUser <br>";
}

sub completePayment
{
  print "@_  --> completePayment <br>";
}

sub findUser
{
  print "@_  --> findUser <br>";
}

sub editUser
{
  print "@_  --> editUser <br>";
}

sub deleteUser
{
  print "@_  --> deleteUser <br>";
}

sub addTrack
{
  print "@_  --> addTrack <br>";
}

sub deleteTrack
{
  print "@_  --> deleteTrack <br>";
}

sub streamTrack
{
  print "@_  --> streamTrack <br>";
}

sub parse
{
  my $match;
  my @reqArg = @{@_[0]};
  my $searchArg = @_[1];  

  foreach (@reqArg)
  {
    if ( ( $_ =~ /$searchArg/ ) )
    {
      $match = $_;
      last;
    }
  }
  
  return $match;
}

### Main program flow
my $q = CGI->new();

### Parsing a HTTP Request, QUERY_STRING
### is a environment variable passed by the Apachi Web Server
### split separates the string according to a specified delimiter "&"
###
### It then separates the array into two arrays both sides of the "=" delimiter
@REQ_ARG = split (/&/, "$ENV{'QUERY_STRING'}");
$MAINREQ;
$MAINARG;

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

print $q->header(), $q->start_html();

switch ($MAINREQ)
{
  case "action"
  {
    switch ($MAINARG)
    {
      case "0"      {&logout(@REQ_ARG)}
      case "1"      {&login(@REQ_ARG)}
      case "2"      {&addUser(@REQ_ARG)}
      case "3"      {&completePayment(@REQ_ARG)}
      case "4"      {&findUser(@REQ_ARG)}
      case "5"      {&editUser(@REQ_ARG)}
      case "6"      {&deleteUser(@REQ_ARG)}
      case "7"      {&addTrack(@REQ_ARG)}
      case "9"      {&deleteTrack(@REQ_ARG)}
      else          {print "Error invalid request type<br>"}
    }
  }  
  case "token"      {&streamTrack(@REQ_ARG)}
  else              {print "invalid request<br>"}  
}

#my $dbh = DBI->connect('dbi:mysql:ESD','root','root')
#  or die "Connection Error: $DBI::errstr\n";
#print "<h1>Museum Audio Guide Web API</h1>\n";

#$sql = "SELECT * FROM ESD.KnowledgeLvl";
# $sth = $dbh->prepare($sql);
# $sth->execute
# or die "SQL Error: $DBI::errstr\n";
 
# while (@row = $sth->fetchrow_array) {
# print "@row\n";
# }

print $q->end_html();
