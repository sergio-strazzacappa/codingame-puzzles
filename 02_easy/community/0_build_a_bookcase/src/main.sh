#!/usr/bin/env bash

read -r height
read -r width
read -r number_of_shelves

draw_top() {
    local mid=$(( width / 2 ))
    local i=0
    
    # Print the left half of the top
    while [[ $i -lt $mid ]]; do
        echo -n "/"
        (( i++ ))
    done

    # Print the middle of the top if needed
    if [[ $((width % 2)) -eq 1 ]]; then
        echo -n "^"
        (( i++ ))
    fi

    # Print the right hand of the top
    while [[ $i -lt $width ]]; do
        echo -n "\\"
        (( i++ ))
    done

    echo ""
    (( height-- ))
}

build_shelves() {
    local shelf_min_height=$(( height / number_of_shelves ))
    local bigger_shelves=$(( height % number_of_shelves ))
    local current_shelf=0

    while [[ $current_shelf -lt $number_of_shelves ]]; do
        local height=$shelf_min_height

        if [[ $bigger_shelves -ge $(( number_of_shelves-current_shelf )) ]]; then
            (( height++ ))
        fi

        local i=0
        while [[ $i -lt $height ]]; do
            echo -n "|"

            # Draw spaces
            local j=0
            while [[ $j -lt $(( width-2 )) && $i -lt $(( height-1 )) ]]; do
               echo -n " "
               (( j++ ))
            done

            # Draw the bottom of the shelf
            local j=0
            while [[ $j -lt $(( width-2 )) && $i -eq $(( height-1 )) ]]; do
               echo -n "_"
               (( j++ ))
            done
            echo "|"
            (( i++ ))
        done

        (( current_shelf++ ))
    done
}

draw_top
build_shelves
