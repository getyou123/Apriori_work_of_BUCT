#include"Apr.h"


Apr::Apr() {
	clock_t Start, End;
	getPreData("retail.dat");//
	cout << "完成数据的读入" << endl;
	Start = clock();
	getMinSup();
	cout << "生成初始化的候选集" << endl;
	getCone();
	cout << "得到初始化的候选集，\n求初始化的频繁集" << endl;
	getLone();
	cout << "得到初始化的频繁集" << endl;
	Work();
	End = clock();
	cout << "It takes " << double((End - Start) / CLOCKS_PER_SEC) << "s" << endl;
	//show();
}
void Apr::getMinSup()
{
	cout << "输入最小的支持度：" << endl;
	int a = 0;
	cin >> a;
	//a = 2000;
	this->Minsup = a;
}


void Apr::getPreData(string Path)//实现从文件中读取所有的原始数据
{
	ifstream in;
	in.open(Path.c_str());
	if (!in.is_open())
	{
		cout << "读入时发生错误" << endl;
		exit(0);
	}
	string tmp;
	while (getline(in, tmp))
	{
		/*cout << tmp << endl;*/
		this->data.push_back(tmp);
	}
}

void Apr::getCone()//得到初始的候选状态
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



int Apr::getCount(set<string>& Set)//根据一个set string求出现次数
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

set<string> Apr::Add(set<string> a, set<string> b)//实现两个set string的并集
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

