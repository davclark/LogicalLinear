#!/usr/bin/perl
use Cwd;
use File::Find;

my $path="/home/dav/PamDavis";
find (\&process, "$path/INPUT_FILES");

sub process
{
   if (($_=~/.jpg$/) || ($_ =~/.JPG$/)) {
	print "found jpg $_\n";
#	$newfile = (split(/\//,$_))[1];
      	$newfile=$_;
	chop($newfile);
	chop($newfile);
	chop($newfile);
	$newfile .= "pnm";
	system("jpegtopnm $_ > $newfile");
	$newfile2=$newfile;
	chop($newfile2);
	chop($newfile2);
	chop($newfile2);
	$newfile2 .= "pgm";
	print ("Converting $newfile to $newfile2\n");
	system("ppmtopgm $newfile > $newfile2");
	$newfile3=$newfile2;
	chop($newfile3);
	chop($newfile3);
	chop($newfile3);
	$newfile3 .= "ps";
	print ("Executing pgmloglin on $newfile2.\n");
	system ("$path/bin/pgmloglin $newfile2 $newfile3");
	system ("mv *.ps $path/EDGE_DETECTED_OUTPUT");
	system ("mv *.pgm *.pnm $path/EDGE_DETECTED_OUTPUT/working_files");
    }
}
