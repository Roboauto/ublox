#! /usr/bin/perl

use Cwd;

my $outputDir = "../gen/include/ublox_msgs/";

my $msg = @ARGV[0];
print "Generating $msg\n";

open my $fh, "< $msg" or die "Can't open file: $!";

my $file = do { local $/; <$fh> };

$file =~ s/int(\d+)/int$1_t/g;
$file =~ s/float32/float/g;
$file =~ s/float64/double/g;

my $includes= "";

if($file =~ s/([^\s]+)\s*\[(\d+)\]\s*([^\s]+)/std::array<$1, $2> $3/g) {
$includes = "$includes
#include <array>"
}
if($file =~ s/([^\s]+)\s*\[\](\s*)([^\s]+)/std::vector<$1>$2$3/g) {
$includes = "$includes
#include <vector>"
}



if ($file =~ /(NavDGPS_SV|NavSBAS_SV|NavSAT_SV|NavSVINFO_SV|RxmRAW_SV|RxmRAWX_Meas|RxmSVSI_SV|CfgINF_Block|CfgGNSS_Block|MonVER_Extension|EsfRAW_Block|EsfSTATUS_Sens)/) {
    $includes = "$includes
#include \"$1.h\"";
}

# fix static
$file =~ s/^([^#\n]+)=/static constexpr $1=/mg;

# add ;
$file =~ s/^((?:[\s]*[^\s]+)+?)(\s*)($|#)/$1;$2$3/mg;

my $structName = $msg;

$structName =~ s/\.\/(.*)\.msg/$1/;

# change # to // etc

$file =~ s/#/\/\//g;

$file =~ s/^(.*)$/        $1/mg;

$file = "#pragma once
$includes
#include <cstdint>

namespace ublox_msgs {
    struct $structName {
$file
    };
}
";

my $outputFile = "$outputDir/$msg";
$outputFile=~s/\.msg/.h/;

open my $fhWrite, ">  $outputFile" or die "Can't open file for write: $!";

print $fhWrite $file;
close $fhWrite;
