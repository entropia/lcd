#!/usr/bin/perl -w

use strict;
use LWP::Protocol::https;
use HTTP::Request::Common qw(POST GET);
use HTTP::Response;
use HTTP::Headers;
use LWP::UserAgent;

my $scroller = "/home/manuel/cvs/lcd/userland/scroller2";
my @newslist;

my $ua = LWP::UserAgent->new(env_proxy => 1);

my $request = HTTP::Request->new('GET', 'https://www.congress.ccc.de/');

my $response = $ua->request($request);
unless ($response->is_success) {
   warn "HTTP error ".$response->error_as_HTML."\n";
   return;
}  

my $content = $response->content;

while ($content =~ /Subject: (.*?)<br>.*?Category: (.*?)<p>/igs) {
   my ($type, $cont) = ($2, $1);
   push (@newslist, [$type, $cont]);
}

@newslist = reverse (splice @newslist, 0, 5);
foreach my $elem (@newslist) {
   my ($type, $cont) = @{$elem};
   print "$type\: $cont\n";
   system($scroller, "$type\: $cont");
}


