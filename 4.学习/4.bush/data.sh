#!/bin/bash
#check date
year=$1
month=$2
day=$3
if echo $day|grep -q '^0'
then
    day=`echo $day |sed 's/^0//'`
fi
if cal $month $year >/dev/null 2>/dev/null
then
    daym=`cal $month $year|egrep -v "$year|Su"|grep -w "$day"`
    if [ "$daym" != "" ]
    then
        echo YES
    else
        echo NO
    exit 1
    fi
else
    echo NO
    exit 1
fi
