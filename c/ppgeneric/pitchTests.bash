#!/bin/bash
#
# pitchTests.bash
#

DefaultTestSortList="nativeqsort clrspcHeapSort wppcInsertionSort wppcShiftDownHeapSort wppcShiftUpHeapSort"
if ( $# == 1 )
then
	TestSortList=$1
else
	exeIntTests.bats
	TestSortList=$DefaultTestSortList
fi

echo "Building Int Item Test Configuration:"

make clean
export PPMACROS=-D__INT_ITEMTYPE
make all

echo "First run Criterion Tests:"
echo '=================================================='
./itemtypeTests
echo '--------------------------------------------------'
./heapsortTests
echo '--------------------------------------------------'
./insertionsortTests
echo '--------------------------------------------------'
./mergesortTests
echo '--------------------------------------------------'

echo "The following sort types will be tested:  $TestSortList."

for st in $TestSortList
do
	echo 'vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv'
	date
	echo "Running Int Tests On $st."
	export SortType=$st
	./exeIntTests.bats
	echo '..................................................'
done

#
# End of pitchTests.bash
