for ((i=1;;i++)) do
    echo $i
    ./gen $i > in
    ./correct < in > expected
    diff -w <(./b < in) expected || break
done