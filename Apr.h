#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<map>
#include<set>
#include<cstdlib>
#include<ctime>
using namespace std;
class Apr {
private:
	vector<string> data;//存储原始的数据
	map<set<string>, int> Ck;//候选项集合
	map<set<string>, int> Lk;//频繁项集合
	map<set<string>, int> Lone;//存储的L1
	int Minsup;//最小的支持度
public:
	Apr();
	void getMinSup();
	void getPreData(string Path);//实现从文件中读取所有的原始数据
	void getCone();//得到初始的候选状态
	void getLone();//得到初始的频繁项集合
	void getFlagone();//根据的是Lone进行初始化的选择
	void Work();
	int getCount(set<string>& Set);//根据一个set string
	set<string> Add(set<string> a, set<string> b);//实现两个set string的并集
	void show();//显示结果
	bool find(string Substr, string String);//实现真正的查找返回值
};
