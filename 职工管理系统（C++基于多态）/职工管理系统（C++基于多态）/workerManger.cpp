#include "workerManger.h"

WorkerManger::WorkerManger()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		this->m_EmpNum = 0;  //初始化记录人数
		this->m_EmpArray = NULL; //初始化数组指针
		this->m_FileIsEmpty = true;  //初始化文件是否为空
		ifs.close();
		return;
	}
	//文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->m_EmpNum = 0;  //初始化记录人数
		this->m_EmpArray = NULL; //初始化数组指针
		this->m_FileIsEmpty = true;  //初始化文件是否为空
		ifs.close();
		return;
	}
	//当文件存在并且记录有数据
	int num = this->get_EmpNum();
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker*[this->m_EmpNum];
	this->init_Emp();

	
}
//展示菜单
void WorkerManger::Show_Menu()
{
	cout << "*********************************************" << endl;
	cout << "*********** 欢迎使用职工管理系统! ***********" << endl;
	cout << "************** 0:退出管理系统 ***************" << endl;
	cout << "************** 1:增加职工信息 ***************" << endl;
	cout << "************** 2:显示职工信息 ***************" << endl;
	cout << "************** 3:删除离职职工 ***************" << endl;
	cout << "************** 4:修改职工信息 ***************" << endl;
	cout << "************** 5:查找职工信息 ***************" << endl;
	cout << "************** 6:按照编号排序 ***************" << endl;
	cout << "************** 7:清空所有文档 ***************" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
}

//添加职工
void WorkerManger::Add_Emp()
{
	cout << "请输入添加的职工数量：" << endl;
	int addNum = 0;  //保存用户的输入数量
	cin >> addNum;
	if(addNum > 0)
	{
		//计算添加新空间的大小
		int newSize = this->m_EmpNum + addNum; //新空间人数 = 原来记录人数 + 新增人数

		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id; //职工编号
			string name; //职工姓名
			int dSelect; //部门选择

			cout << "请输入第 " << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第 " << i + 1 << "个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工岗位 " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;
			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[] this->m_EmpArray;
		
		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		this->m_FileIsEmpty = false;  //职工不为空
		//提示添加成功
		cout << "成功添加 " << addNum << " 名新职工！" << endl;
		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	//按任意键后 清屏回到上级目录
	system("pause");
	system("cls");
}

//统计文件中的人数
int WorkerManger::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); // 打开文件  读文件

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数
		num++;
	}
	return num;
}
//退出系统
void WorkerManger::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

//保存文件
void WorkerManger::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //用输出的方式打开文件--写文件

	//将每个人的数据写到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	//关闭文件
	ofs.close();
}
//初始化职工
void WorkerManger::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker *worker = NULL;
		if (dId == 1) //普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) // 经理
		{
			worker = new Manager(id, name, dId);
		}
		else
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManger::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
//删除职工
void WorkerManger::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		//按照编号删除职工
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) //职工存在，并且要删除index位置上的职工
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录的人员个数
			//同步更新到文件
			this->save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败！未找到该职工！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManger::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//修改职工
void WorkerManger::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)//查找到职工
		{
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到： " << id << " 号职工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//更新数据
			this->m_EmpArray[ret] = worker;
			cout << "修改成功!" << endl;
			this->save(); //保存到文件
		}
		else
		{
			cout << "修改失败！查无此人！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManger::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存爱或者记录为空!" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			//按编号
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//找到职工
				cout << "查找成功！该职工的信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败！查无此人！" << endl;
			}
		}
		else if(select == 2)
		{
			//按姓名
			string name;
			cout << "请输入查找的姓名：";
			cin >> name;
			bool flag = false;  //判断是否查到, 默认未找到
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为 " 
						<< this->m_EmpArray[i]->m_ID 
						<< "的职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败！查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入的选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序
void WorkerManger::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按照职工编号升序排列" << endl;
		cout << "2、按照职工编号降序排列" << endl;

		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[MinOrMax]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						MinOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[MinOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						MinOrMax = j;
					}
				}
			}
			//判断一开始认定的最小值或最大值是不是计算的最小值或最大值 如果不是 交换
			if (i != MinOrMax)
			{
				Worker * temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[MinOrMax];
				this->m_EmpArray[MinOrMax] = temp;
			}
		}
		cout << "排序成功！排序后的结果为：" << endl;
		this->save();//排序后结果保存到文件
		this->Show_Emp();//展示所有职工

	}
}

//清空文件
void WorkerManger::Clean_File()
{
	cout << "确定清空吗？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
WorkerManger::~WorkerManger()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}