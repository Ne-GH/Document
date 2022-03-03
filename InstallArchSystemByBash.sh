STARTINSTALL(){
    echo "This is funtion STARTINSTALL..."
    lsblk
    echo -en "Please input your disk number (such as : /dev/sdbx)"
    read DISK
    ONE="1"
    TWO="2"
    THREE="3"
    DEVSTR="/dev/"
    DEVDISK="$DEVSTR$DISK"


    echo $DISK
    echo $DEVDISK

    echo "$DEVDISK'1'"
    echo -en "o\nn\n\n\n+512M\nn\n\n\n\nw\n" | sudo fdisk $DEVDISK
    yes | mkfs.fat -F 32 "$DEVDISK$ONE"
    yes | mkfs.ext4 "$DEVDISK$TWO"


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


