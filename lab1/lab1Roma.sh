#!/bin/bash
#

echo

#Дата:
echo -en "Дата: "
date

#Имя
echo -en "Имя учетной записи: "
whoami

#Домен
echo -en "Доменное имя ПК: "
hostname

#Процессор
echo -en "Процессор:" 
echo
echo -en "Модель: "
lscpu | grep -i 'Model name' | awk '{print $3,$4,$5,$6}'
echo -en "Архитектура: "
lscpu | grep -i 'Architecture' | awk '{print $2}'
echo -en "Тактовая частота: "
lscpu | grep -i 'CPU MHz' | awk '{print $2,$3}'
echo -en "Количество ядер: "
lscpu | grep -i 'CPU(s)' | awk 'NR == 1{print $2}'
echo -en "Количество потоков на одно ядро: "
lscpu | grep -i 'Thread(s) per core' | awk '{print $4}'

#Оперативная память
echo -en "Оперативная память:"
echo
echo -en "Всего: "
free -m | awk 'NR == 2{print $2}'
echo -en "Доступно: "
free -m | awk 'NR == 2{print $4}'

echo -en "Жесткий диск:" 
echo
echo -en "Всего: "
df -h | awk 'NR == 2{print $2}'
echo -en "Доступно: "
df -h | awk 'NR == 2{print $4}'
echo -en "Смонтировано в корневую директорию: "
df -h | awk 'NR == 9{print $6}'
echo -en "SWAP всего: "
free -m |  awk 'NR == 3{print $2}'
echo -en "SWAP доступно: "
free -m |  awk 'NR == 2{print $7}' 
echo -en "Сетевые интерфейсы:"
echo
count=0
for iface in $(ls /sys/class/net/)
do
count=$(( $count + 1 ))
done
echo "Количесвто интерфейсов: $count"
echo -e "Названия:"
for iface in $(ls /sys/class/net/)
do
echo $iface
done
echo
echo -e "MAC-адреса:"
ifconfig -a | grep "ether" | awk '{print $2}'
echo
echo -e "IP-адреса:"
ifconfig -a | grep "inet" | awk '{print $2}'
echo
echo -e "Пропускная способность:"
ifconfig -a | grep "mtu" | awk '{print $1} {print $3 $4}'