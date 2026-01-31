#!/bin/bash

i=1
while [ $i -eq 1 ]
do
    printf "Enter 1st number: "
    read x
    printf "Enter 2nd number: "
    read y

    echo "1 Addition"
    echo "2 Subtraction"
    echo "3 Multiplication"
    echo "4 Division"
    echo "5 Exit"
    printf "Enter your choice:"
    read c
    
case $c in
1) echo "`expr $x + $y`";;
2) echo "`expr $x - $y`";;
3) echo "`expr $x \* $y`";;
4) if [ $y -eq 0 ]
    then 
        echo "Denominator can't be 0"
    else      
        result=$(echo "scale=2; $x / $y" | bc)
        echo "$result"
    fi;;
5) exit 0;;
*) echo "Invalid input";;
esac
done
