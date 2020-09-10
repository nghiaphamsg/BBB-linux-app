<h1> Discuss About User LED And Basic C/C++ </h1>


### Usage:
- Generate execute and binary file
```shell
make
```
- Clean execute and binary file
```shell
make clean
```

### Step 1: Transfer execute file from host to target (Beaglebone balck)
```shell
sftp debian@192.168.7.2
sftp> put /home/host/controlLed_C /home/tagert/<...>
```

### Step 2: Execute
- Usage: `./controlLed_C <option> <state>`
```shell
./controlLed_C brightness 1
./controlLed_C trigger heartbeat
```
- Usage: `./controlLed_Cpp <option>`
```shell
./controlLed_Cpp flash
```
