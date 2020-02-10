#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speeker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
using namespace std;

class SpeechManager
{
public:
	// ���캯��
	SpeechManager();
	// ��ʾ�˵�
	void show_Menu();

	// �˳�ϵͳ
	void exitSystem();

	// ��ʼ�����Ժ�����
	void initSpeech();

	// ����12��ѡ��
	void createSpeaker();

	// ��ʼ�������������̿���
	void startSpeech();

	// ��ǩ
	void speechDraw();

	// ����
	void speechContest();

	// ��ʾ�÷�
	void showScore();

	// �����¼
	void saveRecord();

	// ��ȡ��¼
	void loadRecord();

	// �ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	// ��������¼
	map<int, vector<string>>m_Record;

	// ��ʾ�����¼
	void showRecord();

	// ��ռ�¼
	void clearRecord();

	//��������
	~SpeechManager();

	// ��Ա����
	vector<int> v1; // �����һ�ֱ���ѡ�ֱ������

	vector<int> v2; // ��һ�ֽ���ѡ�ֱ������

	vector<int> victory; // ʤ��ǰ����ѡ�ֱ������

	map<int, Speaker> m_Speaker; // ��ű���Լ���Ӧ����ѡ������

	int m_Index; // ��ű�������

};