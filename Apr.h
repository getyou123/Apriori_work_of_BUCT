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
	vector<string> data;//�洢ԭʼ������
	map<set<string>, int> Ck;//��ѡ���
	map<set<string>, int> Lk;//Ƶ�����
	map<set<string>, int> Lone;//�洢��L1
	int Minsup;//��С��֧�ֶ�
public:
	Apr();
	void getMinSup();
	void getPreData(string Path);//ʵ�ִ��ļ��ж�ȡ���е�ԭʼ����
	void getCone();//�õ���ʼ�ĺ�ѡ״̬
	void getLone();//�õ���ʼ��Ƶ�����
	void getFlagone();//���ݵ���Lone���г�ʼ����ѡ��
	void Work();
	int getCount(set<string>& Set);//����һ��set string
	set<string> Add(set<string> a, set<string> b);//ʵ������set string�Ĳ���
	void show();//��ʾ���
	bool find(string Substr, string String);//ʵ�������Ĳ��ҷ���ֵ
};
