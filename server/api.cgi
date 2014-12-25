#!/usr/bin/perl

use CGI;

$q = CGI->new();
print $q->header(), $q->start_html();



print "<h1>Museum Audio Guide Web API</h1>";
$apikey = $q->param('key');

print "200 OK<br />";

print "API key: $apikey<br />";


$q->end_html();
