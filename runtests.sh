source build.sh

# read -p "k: " k
# read -p "a: " a
k=3
a=0.5
data="data.csv"

cd texts
texts=$(ls)
cd ..

for text in $texts
do
    tmp="texts/$text"
    echo "----- $text -----"

    # test fcm
    ./test-fcm $tmp $k $a

    # test lang
    ./test-lang $tmp $tmp $k $a

    # test findlang - training
    ./test-findlang1 $tmp $data $text $text $k $a
done

echo " "

for text in $texts
do
    tmp="texts/$text"
    echo "----- $text -----"

    #test findlang - 2
    ./test-findlang2 $tmp $data $k $a
done

echo " "
