STARTINSTALL(){
    echo "This is funtion START"


}

NOSTART(){
    echo "Bye"
}


Main(){
    echo -en "I always install arch,but i haven't more time,so write this bash.\nThis bash will think your install system desk is /dev/sdb2,if you shuld modify this,please modify this bash file.If you read all tips ,Please confirm to continue.[Y/N]"
    read ConfirmStart
    case "$ConfirmStart" in
        Y|y|YES|Yes|yes)
            STARTINSTALL ;;
        *)
            NOSTART ;;
    esac
}
Main


