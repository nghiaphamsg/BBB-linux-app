<h1> How To Fix Debian Version Outdate</h1>

### Target (BBB)

#### Step 1: Move and edit file
```shell
cd /etc/apt; sudo vi source.list
```
#### Step 2: Rewrite again
replace `jessie` to `stretch` in `sources.list` file:

```text
deb http://httpredir.debian.org/debian/ stretch main contrib non-free
#deb-src http://httpredir.debian.org/debian/ stretch main contrib non-free

deb http://httpredir.debian.org/debian/ stretch-updates main contrib non-free
#deb-src http://httpredir.debian.org/debian/ stretch-updates main contrib non-free

deb http://security.debian.org/ stretch/updates main contrib non-free
#deb-src http://security.debian.org/ stretch/updates main contrib non-free

#deb http://httpredir.debian.org/debian stretch-backports main contrib non-free
##deb-src http://httpredir.debian.org/debian stretch-backports main contrib non-free

```

### Step 3: And now you can upgrade gcc/g++:
```shell
sudo apt-get -y install gcc-6 g++-6
```
