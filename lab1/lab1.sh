#!/bin/bash
 
RED='\033[0;31m'
YELLOW='\033[0;33m'
REDBG='\033[37;1;41m'
NC='\033[0m'
ME1='%-10s'
ME2='%-20s'
ME3='%-15s'
ME4='%-5s\n'

echo

#Дата:
echo -en "${YELLOW}Дата: ${NC}"
date

#Имя
echo -en "${YELLOW}Имя учетной записи: ${NC}"
whoami

#Домен
echo -en "${YELLOW}Доменное имя ПК: ${NC}"
hostname

#Процессор
echo -en "${REDBG}Процессор:${NC}" 
echo
echo -en "${YELLOW}Модель: ${NC}"
lscpu | grep -i 'Model name' | awk '{print $3,$4,$5,$6}'
echo -en "${YELLOW}Архитектура: ${NC}"
lscpu | grep -i 'Architecture' | awk '{print $2}'
echo -en "${YELLOW}Тактовая частота: ${NC}"
lscpu | grep -i 'CPU MHz' | awk '{print $2,$3}'
echo -en "${YELLOW}Количество ядер: ${NC}"
lscpu | grep -i 'CPU(s)' | awk 'NR == 1{print $2}'
echo -en "${YELLOW}Количество потоков на одно ядро: ${NC}"
lscpu | grep -i 'Thread(s) per core' | awk '{print $4}'

#Оперативная память
echo -en "${REDBG}Оперативная память:${NC}"
echo
echo -en "${YELLOW}Всего: ${NC}"
free -m | awk 'NR == 2{print $2}'
echo -en "${YELLOW}Доступно: ${NC}"
free -m | awk 'NR == 2{print $4}'

echo -en "${REDBG}Жесткий диск:${NC}" 
echo
echo -en "${YELLOW}Всего: ${NC}"
df -h | awk 'NR == 2{print $2}'
echo -en "${YELLOW}Доступно: ${NC}"
df -h | awk 'NR == 2{print $4}'
echo -en "${YELLOW}Смонтировано в корневую директорию: ${NC}"
df -h | awk 'NR == 9{print $6}'
echo -en "${YELLOW}SWAP всего: ${NC}"
free -m |  awk 'NR == 3{print $2}'
echo -en "${YELLOW}SWAP доступно: ${NC}"
free -m |  awk 'NR == 2{print $7}' 
echo -en "${REDBG}Сетевые интерфейсы:${NC}"
echo
count=0
for iface in $(ls /sys/class/net/)
do
count=$(( $count + 1 ))
done
echo -e "${YELLOW}Количество интерфейсов - ${NC}$count"

printf "Имя"
printf "		MAC-адрес"
printf "	   IP-адрес"
printf "	Пропускная способность\n"

infn=0
for interface in $(ifconfig -s -a | awk '{print $1}')
do
	if (( $infn > 0 )); then
		printf "${ME1} " $interface
		printf "${ME2} " $(ifconfig $interface | grep "ether" | awk '{if ($2 != 0) printf $2; else printf "-"}')
		printf "${ME3} " $(ifconfig $interface | grep "inet " | awk '{printf $2}')
		printf "${ME4}" $(ifconfig $interface | grep "mtu" | awk '{print $3 $4}')
	fi
	infn=$(($infn + 1))
done