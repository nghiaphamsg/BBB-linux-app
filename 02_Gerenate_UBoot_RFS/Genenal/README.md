<h1> General Directory</h1>

**Copy all generated file into here:**

```shell
  cp /linux-4.4/arch/arm/boot/uImage .
  cp /linux-4.4/arch/arm/boot/dts/am335x-boneblack.dtb .
  cp /u-boot-2017.05-rc2/MLO .
  cp /u-boot-2017.05-rc2/u-boot.img .
  cp /u-boot-2017.05-rc2/spl/u-boot-spl.bin .
```
**Directory tree**
```text
├── Busybox_and_minimal_fs
│   └── RFS_Static (ROOT_FS)
│       ├── bin
│       ├── lib       Linux Kernel Modules
│       ├── sbin
│       └── usr
│
├── Genenal (BOOT)
    ├── am335x-boneblack.dtb
    ├── MLO
    ├── u-boot.img
    ├── u-boot-spl.bin
    └── uImage
```

