#include <iostream>
using namespace std;
#include "workerManger.h"
#include "worker.h"
#include "employee.h"
#include "Boss.h"
#include "Manager.h"

int main()
{
	//实例化一个管理者对象
	WorkerManger wm;
	
	int choice = 0;
	while (true)
	{
		//调用成员函数显示菜单
		wm.Show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退出
			wm.ExitSystem();
			break;
		case 1://增加
			wm.Add_Emp();
			break;
		case 2://显示
			wm.Show_Emp();
			break;
		case 3://删除
			wm.Del_Emp();
			break;
		case 4://修改
			wm.Mod_Emp();
			break;
		case 5://查找
			wm.Find_Emp();
			break;
		case 6://排序
			wm.Sort_Emp();
			break;
		case 7://清空
			wm.Clean_File();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}
	

	system("pause");
	return 0;
}