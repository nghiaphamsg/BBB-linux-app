<h1> How To Setting The BBB CPU Frequency </h1>

- Install package
```shell
sudo apt-get install cpufrequtils
```

- Find out information about the current state of the BBB
```shell
cpufreq-info
```

**Note:** The default governor is ondemand, which will dynamically switch CPU frequencies if the BBB reaches 95% of CPU load. 

- You can see that different governors are available, with the profile names conservative, ondemand, userspace, powersave, and performance. To enable one of these governors type the following:
```shell
sudo cpufreq-set -g performance
```

- And frequency steps: 300 MHz, 600 MHz, 720 MHz, 800 MHz, 1000 MHz
```shell
sudo cpufreq-set -f 1000MHz
```


|Option |Contain    |Value						        |
|-------|-----------|-----------------------------------------------------------|
|-d	|Max Speed  | 300M, 600M, 720M, 800M, 1000M(1G)				|
|-u     |Min Speed  | 300M, 600M, 720M, 800M, 1000M(1G)				|
|-g	|Governor   | conservative, userspace, powersave, ondemand, performance	|
|-f	|Frequency  | 300M, 600M, 720M, 800M, 1000M(1G)				|


- Otherwise you can edit `/etc/default/cpufrequtils` (you might need to create it if it doesn't exist). Specify the governor with the GOVERNOR variable:
```text
# valid values: userspace conservative powersave ondemand performance
# get them from cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors 
GOVERNOR="conservative"
MAX_SPEED=1000000
MIN_SPEED=600000
```
Specify the governor to use at **boot**




