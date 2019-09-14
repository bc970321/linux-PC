THIS_PATH=$(cd `dirname $0`;pwd)
cd $THIS_PATH
##要求传入的数据格式为yyyyMMdd的两个开始和结束参数，如20160901 20160910
start=$1
end=$2
##将输入的日期转为的时间戳格式
startDate=`date -d "${start}" +%s`
endDate=`date -d "${end}" +%s`
##计算两个时间戳的差值除于每天86400s即为天数差
stampDiff=`expr $endDate - $startDate`
dayDiff=`expr $stampDiff / 86400`
##根据天数差循环输出日期
    echo $dayDiff
