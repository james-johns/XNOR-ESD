#!/usr/bin/perl

use Net::Telnet ();

$pid = fork();

if($pid == 0) {
    system("vlc --ttl 12 -vvv --color -I telnet --telnet-password videolan --rtsp-host 127.0.0.1 --rtsp-port 5540 --rtsp-caching=150");
}
elsif($pid) {
    sleep(2);
    
    $t = new Net::Telnet(Port => "4212");
    $t->open("127.0.0.1");
    
    $t->waitfor('/password: ?$/i');
    $t->print("videolan");
    
    $t->cmd("new 127.0.0.1 vod enabled");
    $t->cmd("setup 127.0.0.1 input /home/rob/cat.mp3");

    $t->cmd("new broadcast vod enabled");
    $t->cmd("setup broadcast input /home/rob/a.ogg");
}
