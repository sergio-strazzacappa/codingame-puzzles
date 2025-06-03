read surface_n
for (( i=0; i<surface_n; i++ )); do
    read land_x land_y
done

while true; do
    read x y h_speed v_speed fuel rotate power
    if [ $v_speed -lt -39 ]; then
        power=4
    else
        power=0
    fi

    echo "0 $power"
done