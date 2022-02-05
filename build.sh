g++ test-fcm.cpp fcm.cpp -o test-fcm
g++ test-lang.cpp lang.cpp fcm.cpp -o test-lang
g++ test-findlang1.cpp findlang.cpp lang.cpp fcm.cpp -o test-findlang1
g++ test-findlang2.cpp findlang.cpp lang.cpp fcm.cpp -o test-findlang2

echo "Run test-fcm: ./test-fcm [text] [k] [a]"
echo "Run test-lang: ./test-lang [text] [text] [k] [a]"
echo "Run test-findlang1: ./test-findlang1 [text] [data] [k] [a]"
echo "Run test-findlang2: ./test-findlang2 [text] [data] [k] [a]"
echo " "
