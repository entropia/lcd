#!/usr/bin/perl -w

use strict;

foreach my $file (@ARGV) {
   open(PPM, "<$file") or die "Could not open $file\n";
   
   my $str;

   if (defined($str = <PPM>)) {
      die "No PPM File: $file\n" unless ($str =~ /^P6/);
   } else {
      die "Read error\n";
   }

   my ($width, $height);
   if (defined($str = <PPM>)) {
      ($width, $height) = split(/\s+/, $str);
      if (($width > 105) || ($height > 64)) {
         die "Wrong width/height $width/$height\n";
      }
   }

   my $maxval;
   die "Read error\n" unless (defined($maxval = <PPM>));
   die "Wrong color depth\n" if ($maxval > 255);

   my $arr;
   $arr .= $_ while(<PPM>);

   my @buf = unpack("C*", $arr);
   my @temp;
   my @lcd;

   for (my $i=0; $i<105*8; $i++) {
      $lcd[$i] = 0;
   }
   my $row = 0;
   for (my $y=0; $y<$height/8; $y++) {
      for (my $x=0; $x<$width; $x++) {
         my $byte = 0;

         for (my $i=0; $i<8; $i++) {
            my $pix = $buf[($y * 8 + $i ) * $width * 3 + $x * 3];
            $byte |= ($pix > 128 ? 0 : 1) << $i;
         }

         $lcd[$y*105+$x] = $byte;
      }
   }

   open(LCD, ">/dev/lcd0") or die "Could not open lcd0!\n";
   print LCD pack("C*", @lcd);
   close LCD;


   close PPM;
}
