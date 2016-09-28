#!/bin/sh
clear
touch users.txt
touch process.txt
get_users () { who | awk {'print $1'} | sort -u > users.txt; }
process_tree ()
{
    ps -ef | awk {'print $2 " " $3'}> process.txt
    currentID=$(echo $$)
    parentID=$(cat process.txt | grep -w $currentID | awk {'print $2'} | grep -v -w $currentID)
    echo ' '$currentID
    while [ $currentID -ne 1 ];
    do
        echo '  |'
        echo ' '$parentID
        currentID=$parentID
        if [ $currentID != 1 ]
        then
            parentID=$(cat process.txt | grep -w $currentID | awk {'print $2'} | grep -v -w $currentID)
        fi
    done
}
while [ 1 ]
do
    echo '       Select A Menu Option       '
    echo '----------------------------------'
    echo '1- Ancestry History'
    echo '2- Who Is Online'
    echo '3- What Process Any Use Is Running'
    echo '4- Exit'
    echo '----------------------------------'
    read option

    case $option in
        1) process_tree
            ;;
        2) get_users;
            cat users.txt;;
        3) get_users
            inc=1
            while read line
            do
                echo $inc')' $line
                inc=$(($inc+1))
            done < users.txt
            echo 'Select a currently online user:'
            read user
            username=$(sed -n $user'p' users.txt)
            if [ $username != 'USERNAME' ]
            then
                ps -ef | grep $username | grep -v USERNAME | grep -v root
            else
                ps -ef | grep $username | grep -v root
            fi
            ;;
        4) rm users.txt; rm process.txt
            break;;
        *) echo 'Please pick between 1-4';;
    esac
done