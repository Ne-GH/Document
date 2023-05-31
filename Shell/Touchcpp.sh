#!/usr/bin/sh

filename="$1.cpp"

cat <<EOF > "$filename"
#include <iostream>

using namespace std;

int main () {


    return 0;
}
EOF
