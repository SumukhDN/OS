echo "Enter the number of elements in the array: "
read n
echo "Enter the elemnts of the array: "
for((i=0;i<n;i++))
do
    read element
    array+=($element)
done
largest=${array[0]}
for((i=0;i<n;i++))
do
    if [[ ${array[i]} > $largest ]] #you can use -gt instead of >
    then
        largest=${array[i]}
    fi
done
echo "The largest element in the array is: $largest" 
