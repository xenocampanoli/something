#!/usr/bin/env bats
#
# exeIntTests.bats
#

@test "simple default run" {
    records="$(./ssorts -s$SortType | grep 'records sorted, .*clock ticks counted.*approximately.*seconds' | awk '{print $1 }')"
	[ "$records" = "16" ]
    clockticks="$(./ssorts -s$SortType | grep 'records sorted, .*clock ticks counted.*approximately.*seconds' | awk '{print $4 }')"
	[ "$clockticks" -lt 16 ]
    seconds="$(./ssorts -s$SortType | grep 'counted.*approximately.*0.00.*seconds')"
	[ -n "$seconds" ]
}

@test "0 try run" {
	control=$(sort ../../trydata/intvector0.lst | md5sum | awk '{ print $1 }')
    msg="$(./ssorts -s$SortType -n0 -obatstest2.0.lst | grep 'records sorted, .*clock ticks counted.*approximately.*seconds')";
	[ -n "$msg" ] 
	recordcount=$(cat outdata/batstest2.0.lst | wc -l)
	[ "$recordcount" -eq 16 ]
	testresult=$(cat outdata/batstest2.0.lst | md5sum | awk '{ print $1 }')
	[ "$control" = "$testresult" ]
}

@test "1 try run" {
    msg="$(./ssorts -s$SortType -n1 -obatstest2.1.lst | grep 'records sorted, .*clock ticks counted.*approximately.*seconds')";
	recordcount=$(cat outdata/batstest2.1.lst | wc -l)
	[ -n "$msg" ] 
	[ "$recordcount" -eq 100 ]
}

@test "2 try run" {
    msg="$(./ssorts -s$SortType -n2 -obatstest2.2.lst | grep 'records sorted, .*clock ticks counted.*approximately.*seconds')";
	recordcount=$(cat outdata/batstest2.2.lst | wc -l)
	[ -n "$msg" ] 
	[ "$recordcount" -eq 1000 ]
}

@test "3 try run" {
    msg="$(./ssorts -s$SortType -n3 -obatstest2.3.lst | grep 'records sorted, .*clock ticks counted.*approximately.*seconds')";
	recordcount=$(cat outdata/batstest2.3.lst | wc -l)
	[ -n "$msg" ] 
	[ "$recordcount" -eq 10000 ]
}

@test "4 try run" {
    msg="$(./ssorts -s$SortType -n4 -obatstest2.4.lst | grep 'records sorted, .*clock ticks counted.*approximately.*seconds')";
	recordcount=$(cat outdata/batstest2.4.lst | wc -l)
	[ -n "$msg" ] 
	[ "$recordcount" -eq 100000 ]
}

# End of exeIntTests.bats
