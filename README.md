# MyCK
小组成员 戴泽雨 ShinobiAqua
project1_ver2.0为项目工程文件

请无视SM2/SM2-master，此为早期版本

222222222222中为可执行文件可以直接运行

### 运行指导

直接运行可执行文件或者用vs打开工程文件后用在x86下进行编译

### 项目名称

SM2的PGP加解密实现，SM2标量乘法的双基链方法实现

### 项目简介

项目拜读了已有的实现方法，在此基础上进一步完善

我的主要工作是修复了其中的一个bug，该bug会导致有一定概率产生解密失败的情况，解密在某些条件下会由于明密文中0的错误填充而使得解密错误。

第二个主要工作是替换了其中的传统naf窗口方法标量乘，使用了双基方法的标量乘法，使得速度有了一定的提升。

双基链参考V.Dimitrov L.Imbert P.K.Mishra的文章Efficient and secure elliptic curve point multiplication using double-based chains

其中双基链分解方法使用了树形方法，以及更进一步优化树形的滑动窗口方法，实现在resolve.c中

分解的算法在代码中不便说明，以图片的形式在仓库中给出
