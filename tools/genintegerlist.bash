#!/bin/bash
#
#  genintegerlist.bash - Create data for testing.
#

readonly ScriptDir=$(dirname $0)
readonly DataDirectory=$ScriptDir/..
readonly DataFile=$DataDirectory/integerlist.lst

function printUsage
{
	echo "USAGE:  ./genintegerlist.bash <iterations>"
}

if (( $# == 1 ))
then
	(( iterations = $1 ))
	if [[ $iterations =~ ^[0-9][0-9]*$ ]]
	then
		iterations=$1
	else
		echo "Invalid Usage:  sole argument must be a whole number."
		printUsage
		exit 1
	fi
else
		printUsage
		exit 0
fi

rm -rf $DataFile
(( i = 0 ))
while (( i < iterations ))
do
	echo $RANDOM >>$DataFile
	(( i = i + 1 ))
done

wc $DataFile
echo "Ending.  Data in $DataFile."
#
# End of genintegerlist.bash
