#!/usr/bin/perl

use CGI;

$q = CGI->new();
print $q->header(), $q->start_html();

print "<h1>Museum Audio Guide Web API</h1>";

$apikey = $q->param('key');
print "API key: $apikey<br />\n";

if ($apikey == 1234) {
    if (fork() == 0) {
	close STDOUT;
	close STDERR;
	open STDOUT, ">", './gstreamer.log';
	open STDERR, ">", './gstreamer.log';
	exec('gst-launch-1.0 filesrc location=./test2.ogg ! tcpclientsink host=127.0.0.1  port=3000');
	exit(0);
    } else {
	print "200 OK<br />\n";
    }
} else {
    print "400 Error<br />";
}

print $q->end_html();
