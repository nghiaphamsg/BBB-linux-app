<h2> How To Share Network Between Host And Target </h2>


### HOST
- Setting to share internet between wifi (wlp2s0) and ethernet (enxf4e11ea6c577/enxf4e11ea6c57a)
```shell
iptables --table nat --append POSTROUTING --out-interface wlp2s0 -j MASQUERADE
iptables --append FORWARD --in-interface enxf4e11ea6c577 -j ACCEPT
iptables --append FORWARD --in-interface enxf4e11ea6c57a -j ACCEPT
```
- Enable IP forwarding
```shell
echo 1 > /proc/sys/net/ipv4/ip_forward
```
or using script
```shell
sudo ./host
```

### Target (BBB)
```shell
sudo echo "nameserver 8.8.8.8" >> /etc/resolv.conf
sudo echo "nameserver 8.8.4.4" >> /etc/resolv.conf
```
```shell
sudo route add default gw 192.168.6.1 usb1
sudo route add default gw 192.168.7.1 usb0
```
or using script
```shell
sudo ./target
```
