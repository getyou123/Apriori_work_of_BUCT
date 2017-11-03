#include"Apr.h"


Apr::Apr() {
	clock_t Start, End;
	getPreData("retail.dat");//
	cout << "������ݵĶ���" << endl;
	Start = clock();
	getMinSup();
	cout << "���ɳ�ʼ���ĺ�ѡ��" << endl;
	getCone();
	cout << "�õ���ʼ���ĺ�ѡ����\n���ʼ����Ƶ����" << endl;
	getLone();
	cout << "�õ���ʼ����Ƶ����" << endl;
	Work();
	End = clock();
	cout << "It takes " << double((End - Start) / CLOCKS_PER_SEC) << "s" << endl;
	//show();
}
void Apr::getMinSup()
{
	cout << "������С��֧�ֶȣ�" << endl;
	int a = 0;
	cin >> a;
	//a = 2000;
	this->Minsup = a;
}


void Apr::getPreData(string Path)//ʵ�ִ��ļ��ж�ȡ���е�ԭʼ����
{
	ifstream in;
	in.open(Path.c_str());
	if (!in.is_open())
	{
		cout << "����ʱ��������" << endl;
		exit(0);
	}
	string tmp;
	while (getline(in, tmp))
	{
		/*cout << tmp << endl;*/
		this->data.push_back(tmp);
	}
}

void Apr::getCone()//�õ���ʼ�ĺ�ѡ״̬
{
	int len = data.size();
	//cout << len;
	for (int i = 0; i < len; i++)
	{
		//cout << i << endl;
		string tmp = "";
		int lenj = data[i].size();
		for (int j = 0; j <= lenj; j++)
		{
			if (j != lenj&&data[i][j] != ' ')tmp += data[i][j];
			else {
				set<string> tmpset;
				if (tmp != "")tmpset.insert(tmp);
				if (Ck.find(tmpset) != Ck.end())
				{
					Ck[tmpset]++;
				}
				else if (tmpset.size() != 0)
				{
					Ck[tmpset] = 1;
				}
				//cout << tmp << endl;
				tmp = "";
			}
		}
	}
}

bool Apr::find(string Substr, string String)
{
	auto it = String.find(Substr);
	if (it == string::npos)
	{
		return false;
	}
	else
	{
		string Cmp = "";
		for (int i = 0; i<String.size(); ++i)
		{
			if (String[i] != ' ')Cmp += String[i];
			else {
				if (Cmp == Substr)
				{
					return true;
				}
				else { Cmp = ""; }

			}
		}
		return false;
	}
}

void Apr::getLone()
{
	for (auto iter = Ck.begin(); iter != Ck.end(); iter++)
	{
		if (iter->second >= this->Minsup)
		{
			Lk.insert(*iter);
			Lone.insert(*iter);
		}
	}
}



int Apr::getCount(set<string>& Set)//����һ��set string����ִ���
{
	int ct = 0;
	int len = data.size();
	for (int i = 0; i < len; ++i)
	{
			int n = 0;
			for (const string a : Set)
			{
				if (a != ""&&find(a, data[i]))//if (a!=""&&data[i].find(a) != string::npos)
				{
					n++;
				}
				else {
					break;
				}
			}
			if (n == Set.size())
			{
				ct++;
			}
	}
	return ct;
}

set<string> Apr::Add(set<string> a, set<string> b)//ʵ������set string�Ĳ���
{
	set<string> Settmp;
	for (const string& a1 : a)
	{
		Settmp.insert(a1);
	}
	for (const string& b1 : b)
	{
		Settmp.insert(b1);
	}
	return Settmp;
}

void Apr::Work()
{
	int Num = 1;
	int Sum = 0;
	while (!Ck.empty())
	{
		cout << "L" << Num++ << ":" << endl;
		for (auto iter = Lk.begin(); iter != Lk.end(); ++iter)
		{
			for (const string b : iter->first)
			{
				cout << b << " ";
			}
			Sum++;
			cout << endl;
		}
		Ck.clear();
		for (auto iter1 = Lk.begin(); iter1 != Lk.end(); ++iter1)
		{
			for (auto iter2 = Lone.begin(); iter2 != Lone.end(); ++iter2)
			{
				set<string> tmpSet = Add(iter1->first, iter2->first);
				if (tmpSet.size() == iter1->first.size() + 1)
				{
					int counttmp = getCount(tmpSet);
					if (counttmp > this->Minsup)
					{
						Ck.insert(make_pair(tmpSet, counttmp));
					}
				}
			}
		}
		Lk.clear();
		for (auto iter4 = Ck.begin(); iter4 != Ck.end(); ++iter4)
		{
			Lk.insert(*iter4);
		}
	}
	cout << "Total number:" << Sum << " ";
}

