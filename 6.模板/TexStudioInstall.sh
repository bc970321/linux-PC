#!/bin/bash

Cmd[0]="sudo apt-get install -y texlive"
Cmd[1]="sudo apt-get install -y texlive-lang-chinese"
Cmd[2]="sudo apt-get install -y texlive-lang-chinese"
Cmd[3]="sudo apt-get install -y texlive-font*"
Cmd[4]="sudo apt-get install -y texlive-xetex texlive-latex-extra"
Cmd[5]="sudo apt-get install -y texstudio"

for ((i = 0; i < 6; i++));
do
    echo -e "\033[1;34m${Cmd[${i}]}\033[0m";
    eval ${Cmd[${i}]};
    if [[ ${?} -ne 0 ]];
    then
        echo -e "\033[1;34msudo apt-get install -f\033[0m";
        sudo apt-get install -y -f;
        eval ${Cmd[${i}]};
        echo -e "\033[1;34m${Cmd[${i}]}\033[0m";
    fi
done

echo -e "\033[1;32m请打开texStudio设置自行自行更改语言与编译器\033[0m";
echo -e "\033[1;32mOK\033[0m";
