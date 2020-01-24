#include <bits/stdc++.h>
using namespace std;

class Complex //复数类
{
    double real, image; //复数的实部和虚部
public:
    Complex() = default;
    Complex(double x, double y);//构造函数
    //使用在操作类内和类外两种方法实现类的以下运算符重载函数
    //1、运算符输入>>和输出<<到文件，并能够实现连续输入和输出运算
    //2、运算符乘法*、运算符*=、比较运算符==，并能够实现连续运算
    //friend Complex operator*(Complex a, Complex b);//类外重载运算符“*”
    Complex operator*(Complex& c);
    Complex operator*=(Complex& c);
    //friend Complex operator*=(Complex& a,const Complex& b);//类外重载“*=”运算符
    Complex &operator=(const Complex& a);//重载赋值运算符
    bool operator==(Complex& c);
    //friend bool operator==(Complex& a, Complex& b);//类外重载“==”运算符
    friend ofstream& operator<<(ofstream& out, Complex& a);//重载插入运算符“<<"
    friend ifstream& operator>>(ifstream& input, Complex& a);//重载提取运算符“>>”
};


//构造函数
Complex::Complex(double x, double y)
{
    real = x;
    image = y;
}
//类外重载运算符“*”
/*Complex operator*(Complex a, Complex b)

{
    return Complex(a.real * b.real - a.image * b.image, a.real * b.image + a.image * b.real);
}*/
//类内重载运算符“*”
Complex Complex::operator*(Complex& c)
{
    return Complex(real * c.real - image * c.image, real * c.image + image * c.real);
}
//重载赋值运算符
Complex &Complex::operator=(const Complex& a)
{
    real = a.real;
    image = a.image;
    return *this;
}
//类内重载“*=”运算符
Complex Complex ::operator*=(Complex& c)
{
    double r = real;
    real=real * c.real - image * c.image;
    image= r * c.image + image * c.real;
    return *this;
}

//类外重载“*=”运算符
/*Complex operator*=(Complex& a, const Complex& b)


{
    double r = a.real;
    a.real=a.real * b.real - a.image * b.image;
    a.image= r * b.image + a.image * b.real;
    return a;
}*/
//类外重载“==”运算符
/*bool operator==(Complex& a, Complex& b)
{
    if(a.real == b.real && a.image == b.image)
        return true;
    return false;
}*/

bool Complex::operator==(Complex& c)
{
    if(real == c.real && image == c.image)
        return true;
    return false;
}
//重载插入运算符“<<"
ofstream& operator<<(ofstream& out, Complex& a)
{
    out<<a.real<<" "<<a.image;
    return out;
}
//重载提取运算符“>>”
ifstream& operator>>(ifstream& input, Complex& a)
{
    input>>a.real;
    input>>a.image;
    return input;
}
int main()
{
    // 创建多个复数类Complex对象
    Complex *cs[] =
    {
        new Complex(2.0, 3.5),
        new Complex(1, 3.6),
        new Complex(14, 5),
        new Complex(3, 0.1)
    };
// 计算以上复数的乘积
   Complex r1 = *cs[0];
    for (int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        r1 *= *cs[i];
   Complex r2 = (*cs[0])*(*cs[1])*(*cs[2])*(*cs[3]);
// 输出r1和r2的比较结果
    cout<<(r1==r2)<<endl;

//打开文件data.txt向其中写入四个复数
    ofstream fout("data.txt");
    if(!fout)
    {
        cout<<"Cannot open output file.\n";
        exit(1);
    }
    for (int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        fout<<(*cs[i])<<endl;
    fout.close();
//从文件中读入复数
    ifstream fin("data.txt");
    if(!fin)
    {
        cout<<"Cannot open input file.\n";
        return 1;
    }
    for(int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        fin >> *cs[i];
    fin.close();
//修改第三个复数
    Complex change(1.4, 50);
    *cs[2] = change;//修改第三个复数
    ofstream foutt("data.txt");
    for(int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        foutt << *cs[i] <<endl;
//    foutt << (*cs[1] * *cs[3]);
    foutt.close();

    (*cs[1]) *= (*cs[3]);
//追加第二个和第四个复数的乘积到文件尾部
    ofstream ffout("data.txt",ios::app);//追加保存
    if(!ffout)
    {
        cout<<"Cannot open output file.\n";
        exit(1);
    }
    ffout<<(*cs[1])<<endl;
    ffout.close();


    /*ofstream out("data.txt",ios::binary);//二进制打开
    if(!out)
    {
        cout<<"Cannot open output file.\n";
        abort();
    }
    for (int i=sizeof(cs)/sizeof(Complex *)-1; i>=0; i--)
      out.write((char*) & (*cs[i]), sizeof(*cs[i]));
    out.close();
*/
    return 0;
}
