# About
MYSQL C API for C++. The whole Mysql Server connections pack in the 1 code.



© SHaDe,Moderator of www.scripts.ge



Code cleared and translated to English by me.

# MYSQL library installation

If you are running Windows, it requires to install Mysql.h library:


- https://mega.co.nz/#!AYp2GLrB!rmRcIntRih_tENLPdR_dGvGBWa0Tdls2xzxgzLlUDfY


For Linux you require compiler GCC.
install library via package manager:
```
sudo apt-get install libmysql++ && sudo apt-get install libmysql++-dev
```
    
# Usage

To include header:
```cpp
#include <mysql.h>
```
Or
```cpp
#include <sys/mysql.h>
```
Code compilation:
```
g++ -o 'softwarename' 'Source.cpp' `mysql_config --cflags --libs` && ./'softwarename'
```
  
