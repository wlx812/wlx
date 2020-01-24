#pragma once  //��ֹͷ�ļ��ظ�����
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "Boss.h"
#include "Manager.h"
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManger
{
public:
	//���캯��
	WorkerManger();
	//չʾ�˵�
	void Show_Menu();
	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker ** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�յı�־
	bool m_FileIsEmpty;

	//ͳ���ļ��е�����
	int get_EmpNum();

	//��ʼ��ְ��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ����
	int IsExist(int id);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//���������
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//��������
	~WorkerManger();
};