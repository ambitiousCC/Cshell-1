# 基于C完成的Linux shell（完全开源）

[![shell,c](https://img.shields.io/badge/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84-C%2B%2B-brightgreen)](https://github.com/cuichenxu/Cshell)

本仓库包括以下内容：
1. 基于c实现的Shell源码，其中包括了初始demo和第一个版本
2. 在实验中遇到的问题和解决策略

## 内容列表
- [说明](#说明)
- [使用](#使用)
- [展望](#展望)
- [如何贡献](#如何贡献)

## 说明
此仓库目前由[@LiFulian](https://github.com/LiFulian)[@cuichenxu](https://github.com/cuichenxu)[@ambitiousCC](https://github.com/ambitiousCC)共同开发而成

目前已经完成基本shell命令13个(by 2020.11.12)

其中代码学习了Internet中较好的shell实现方法，经过理解后整合成独立程序。目前测试中，暂无较大bug，但由于系统的多样性和不可预知性，在您的机器上可能出现问题。如果您发现问题，请第一时间提交issue。

## 使用
[![Linux GCC](https://img.shields.io/badge/Linux-GCC-yellow)](https://github.com/cuichenxu/Cshell)

### 目录介绍

|README.md 		
|run.sh 		运行程序
|需求分析.docx
|bin 			源码
--|cmds.c
--|cmds.h
--|cmds.o
--|ls.c
--|ls.h
--|ls.o
--|main.c
--|makefile 	make
--|ps.c
--|ps.h
--|ps.o

### 运行

直接运行`run.sh`即可
```powershell
$ chmod a+x run.sh
$ ./run.sh
```

## 展望

此程序只是一个雏形，我们团队正在努力不断更新新的内容。

## 如何贡献

只需要您`star`一下我们的开源仓库，`fork`提交代码即可
