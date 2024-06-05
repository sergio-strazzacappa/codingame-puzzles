read lightX lightY initialTX initialTY

while true; do
    read remainingTurns
    direction=""

    if [ $initialTY -lt $lightY ]; then
        direction+="S"
        ((initialTY++))
    fi

    if [ $initialTY -gt $lightY ]; then
        direction+="N"
        ((initialTY--))
    fi

    if [ $initialTX -lt $lightX ]; then
        direction+="E"
        ((initialTX++))
    fi

    if [ $initialTX -gt $lightX ]; then
        direction+="W"
        ((initialTX--))
    fi

    echo $direction
done