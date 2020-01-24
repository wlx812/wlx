#include "workerManger.h"

WorkerManger::WorkerManger()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		this->m_EmpNum = 0;  //��ʼ����¼����
		this->m_EmpArray = NULL; //��ʼ������ָ��
		this->m_FileIsEmpty = true;  //��ʼ���ļ��Ƿ�Ϊ��
		ifs.close();
		return;
	}
	//�ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->m_EmpNum = 0;  //��ʼ����¼����
		this->m_EmpArray = NULL; //��ʼ������ָ��
		this->m_FileIsEmpty = true;  //��ʼ���ļ��Ƿ�Ϊ��
		ifs.close();
		return;
	}
	//���ļ����ڲ��Ҽ�¼������
	int num = this->get_EmpNum();
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker*[this->m_EmpNum];
	this->init_Emp();

	
}
//չʾ�˵�
void WorkerManger::Show_Menu()
{
	cout << "*********************************************" << endl;
	cout << "*********** ��ӭʹ��ְ������ϵͳ! ***********" << endl;
	cout << "************** 0:�˳�����ϵͳ ***************" << endl;
	cout << "************** 1:����ְ����Ϣ ***************" << endl;
	cout << "************** 2:��ʾְ����Ϣ ***************" << endl;
	cout << "************** 3:ɾ����ְְ�� ***************" << endl;
	cout << "************** 4:�޸�ְ����Ϣ ***************" << endl;
	cout << "************** 5:����ְ����Ϣ ***************" << endl;
	cout << "************** 6:���ձ������ ***************" << endl;
	cout << "************** 7:��������ĵ� ***************" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
}

//���ְ��
void WorkerManger::Add_Emp()
{
	cout << "��������ӵ�ְ��������" << endl;
	int addNum = 0;  //�����û�����������
	cin >> addNum;
	if(addNum > 0)
	{
		//��������¿ռ�Ĵ�С
		int newSize = this->m_EmpNum + addNum; //�¿ռ����� = ԭ����¼���� + ��������

		//�����¿ռ�
		Worker ** newSpace = new Worker*[newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id; //ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��

			cout << "������� " << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;

			cout << "������� " << i + 1 << "����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		
		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		this->m_FileIsEmpty = false;  //ְ����Ϊ��
		//��ʾ��ӳɹ�
		cout << "�ɹ���� " << addNum << " ����ְ����" << endl;
		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}
	//��������� �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//ͳ���ļ��е�����
int WorkerManger::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); // ���ļ�  ���ļ�

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ������
		num++;
	}
	return num;
}
//�˳�ϵͳ
void WorkerManger::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//�����ļ�
void WorkerManger::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�--д�ļ�

	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	//�ر��ļ�
	ofs.close();
}
//��ʼ��ְ��
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
		if (dId == 1) //��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) // ����
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

//��ʾְ��
void WorkerManger::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
//ɾ��ְ��
void WorkerManger::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		//���ձ��ɾ��ְ��
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) //ְ�����ڣ�����Ҫɾ��indexλ���ϵ�ְ��
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼����Ա����
			//ͬ�����µ��ļ�
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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

//�޸�ְ��
void WorkerManger::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)//���ҵ�ְ��
		{
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "�鵽�� " << id << " ��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//��������
			this->m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ�!" << endl;
			this->save(); //���浽�ļ�
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManger::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ����氮���߼�¼Ϊ��!" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			//�����
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ������Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else if(select == 2)
		{
			//������
			string name;
			cout << "��������ҵ�������";
			cin >> name;
			bool flag = false;  //�ж��Ƿ�鵽, Ĭ��δ�ҵ�
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ " 
						<< this->m_EmpArray[i]->m_ID 
						<< "��ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cout << "�����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����
void WorkerManger::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1������ְ�������������" << endl;
		cout << "2������ְ����Ž�������" << endl;

		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
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
			//�ж�һ��ʼ�϶�����Сֵ�����ֵ�ǲ��Ǽ������Сֵ�����ֵ ������� ����
			if (i != MinOrMax)
			{
				Worker * temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[MinOrMax];
				this->m_EmpArray[MinOrMax] = temp;
			}
		}
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();//����������浽�ļ�
		this->Show_Emp();//չʾ����ְ��

	}
}

//����ļ�
void WorkerManger::Clean_File()
{
	cout << "ȷ�������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
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