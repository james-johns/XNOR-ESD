#!/usr/bin/perl

use CGI;

$logfile='./gstreamer.log';

$remote_addr = "$ENV{REMOTE_ADDR}";

if ($remote_addr eq "") {
    $remote_addr = "127.0.0.1";
}

$q = CGI->new();
print $q->header(), $q->start_html();

print "<h1>Museum Audio Guide Web API</h1>\n";

$apikey = $q->param('key');

print "|";
print "$remote_addr";
print "|";
print "\nAPI key: $apikey<br />\n";
print "Client IP: $remote_addr<br />\n";
print "gst-launch-1.0 filesrc location=./test2.ogg ! tcpclientsink host=$remote_addr port=3000<br />\n";
$pid = 0;
if ($apikey == 1234) {
    if (($pid = fork()) == 0) {
	close(STDOUT);
	close(STDERR);
	open(STDOUT, ">", $logfile);
	open(STDERR, ">", $logfile);
	exec("gst-launch-1.0", "filesrc", "location=./test2.ogg", "!", "tcpclientsink", "host=$remote_addr", "port=3000");
	exit(0);
    } else {
	print "200 OK<br />\n";
    }
} else {
    print "400 Error<br />";
}

print $q->end_html();
