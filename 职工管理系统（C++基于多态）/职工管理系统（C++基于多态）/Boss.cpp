#include "Boss.h"

//���캯��
Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//��ʾ������Ϣ
void Boss::showInfo()
{
	cout << "ְ�����:  " << this->m_ID
		<< "\tְ������:  " << this->m_Name
		<< "\t��λ:  " << this->getDeptName()
		<< "\t��λְ��:  ����˾��������" << endl;
}

//��ȡ��λ����
string Boss::getDeptName()
{
	return string("�ϰ�");
}