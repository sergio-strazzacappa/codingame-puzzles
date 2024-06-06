read n
read temp
op=0

if [ "$temp" = "" ]; then
    closestTemp=0
else
    closestTemp=99999
fi

for t in $temp; do
    let op1=-$closestTemp
    let op2=-$t
    
    if [ $t -gt 0 ] && [ $t -lt $closestTemp ] && [ $closestTemp -gt 0 ]; then
        closestTemp=$t
    elif [ $t -lt 0 ] && [ $t -gt $closestTemp ] && [ $closestTemp -lt 0 ]; then
        closestTemp=$t
    elif [ $t -gt 0 ] && [ $t -lt $op1 ] && [ $closestTemp -lt 0 ]; then
        closestTemp=$t
    elif [ $t -lt 0 ] && [ $op2 -lt $closestTemp ] && [ $closestTemp -gt 0 ]; then
        closestTemp=$t
    elif [ $t -eq $op1 ] && [ $t -gt 0 ]; then
        closestTemp=$t
    fi
done

echo $closestTemp
