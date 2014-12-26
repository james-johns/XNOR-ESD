#!/usr/bin/perl

use CGI;

### Environment variable definitions
$logfile='./gstreamer.log';
$audio_base_path = "./";

$remote_addr = "$ENV{REMOTE_ADDR}";
if ($remote_addr eq "") {
    $remote_addr = "127.0.0.1";
}

### Functions

## Audio stream functions
# stream_audio_track(file_name, target_ip)
sub stream_audio_track
{
    my $file      = $audio_base_path . @_[0];
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
	    print "gst-launch-1.0 filesrc location=$file ! ";
	    print "tcpclientsink host=$target_ip port=3000<br />\n";
	}
    } else {
	print "\n\nAudio track does not exist\n";
    }
    return $pid;
}

## Database communication functions
# get_track_name_by_id(track_id)
# returns string containing track file name
sub get_track_name_by_id
{
    my $id = @_[0];
    my $track_name;
    if ($id eq "0001") {
	$track_name = "test2.ogg";
    }
    return $track_name;
}

### Main program flow
my $q = CGI->new();
print $q->header(), $q->start_html();

print "<h1>Museum Audio Guide Web API</h1>\n";

my $apikey = $q->param('key');
my $trackid = $q->param('trackid');

print "|";
print "$remote_addr";
print "|";
print "\nAPI key: $apikey<br />\n";
print "Client IP: $remote_addr<br />\n";
print "Track ID: $trackid<br />\n";

if ($apikey == 1234) {
    my $track_name = get_track_name_by_id($trackid);
    if ($track_name ne "") {
	my $pid = stream_audio_track($track_name, $remote_addr);
	if ($pid) {
	    print "\n\nAudio stream has begun<br />\n";
	} else {
	    print "\n\nError starting audio stream\n";
	}
    } else {
	print "\n\nInvalid track id\n";
    }
} else {
    print "\n\nInvalid API key\n";
}

print $q->end_html();
