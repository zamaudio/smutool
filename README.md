smutool
=======

This tool aids in the reverse engineering of AMD SMU.
The SMU is a LatticeMico32 co-processor residing in the mainboard
for controlling thermal management, clocks, and fans etc.

The purpose of this project is to collaborate with others to
create a free alternative firmware SMU stack that interoperates with coreboot.

Compiling
=========
You need libpci-dev
```
make
```

RAM dumping
===========
```
sudo ./smudump > ram
```

ROM dumping
===========
(Code needs tweaking on different machines):
```
sudo ./smutool > rom
```

User firmware signing
=====================
```
python signsmu.py myfirmware
```

License
=======
This project is released under GPLv3
