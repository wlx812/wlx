//��ͨԱ���ļ�
#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "worker.h"

class Employee : public Worker
{
public:
	//���캯��
	Employee(int id, string name, int dID);  

	//��ʾ������Ϣ
	void showInfo();

	//��ȡ��λ����
	string getDeptName();
};
