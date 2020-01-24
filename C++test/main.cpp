#include <bits/stdc++.h>
using namespace std;

class Complex //������
{
    double real, image; //������ʵ�����鲿
public:
    Complex() = default;
    Complex(double x, double y);//���캯��
    //ʹ���ڲ������ں��������ַ���ʵ�����������������غ���
    //1�����������>>�����<<���ļ������ܹ�ʵ������������������
    //2��������˷�*�������*=���Ƚ������==�����ܹ�ʵ����������
    //friend Complex operator*(Complex a, Complex b);//���������������*��
    Complex operator*(Complex& c);
    Complex operator*=(Complex& c);
    //friend Complex operator*=(Complex& a,const Complex& b);//�������ء�*=�������
    Complex &operator=(const Complex& a);//���ظ�ֵ�����
    bool operator==(Complex& c);
    //friend bool operator==(Complex& a, Complex& b);//�������ء�==�������
    friend ofstream& operator<<(ofstream& out, Complex& a);//���ز����������<<"
    friend ifstream& operator>>(ifstream& input, Complex& a);//������ȡ�������>>��
};


//���캯��
Complex::Complex(double x, double y)
{
    real = x;
    image = y;
}
//���������������*��
/*Complex operator*(Complex a, Complex b)

{
    return Complex(a.real * b.real - a.image * b.image, a.real * b.image + a.image * b.real);
}*/
//���������������*��
Complex Complex::operator*(Complex& c)
{
    return Complex(real * c.real - image * c.image, real * c.image + image * c.real);
}
//���ظ�ֵ�����
Complex &Complex::operator=(const Complex& a)
{
    real = a.real;
    image = a.image;
    return *this;
}
//�������ء�*=�������
Complex Complex ::operator*=(Complex& c)
{
    double r = real;
    real=real * c.real - image * c.image;
    image= r * c.image + image * c.real;
    return *this;
}

//�������ء�*=�������
/*Complex operator*=(Complex& a, const Complex& b)


{
    double r = a.real;
    a.real=a.real * b.real - a.image * b.image;
    a.image= r * b.image + a.image * b.real;
    return a;
}*/
//�������ء�==�������
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
//���ز����������<<"
ofstream& operator<<(ofstream& out, Complex& a)
{
    out<<a.real<<" "<<a.image;
    return out;
}
//������ȡ�������>>��
ifstream& operator>>(ifstream& input, Complex& a)
{
    input>>a.real;
    input>>a.image;
    return input;
}
int main()
{
    // �������������Complex����
    Complex *cs[] =
    {
        new Complex(2.0, 3.5),
        new Complex(1, 3.6),
        new Complex(14, 5),
        new Complex(3, 0.1)
    };
// �������ϸ����ĳ˻�
   Complex r1 = *cs[0];
    for (int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        r1 *= *cs[i];
   Complex r2 = (*cs[0])*(*cs[1])*(*cs[2])*(*cs[3]);
// ���r1��r2�ıȽϽ��
    cout<<(r1==r2)<<endl;

//���ļ�data.txt������д���ĸ�����
    ofstream fout("data.txt");
    if(!fout)
    {
        cout<<"Cannot open output file.\n";
        exit(1);
    }
    for (int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        fout<<(*cs[i])<<endl;
    fout.close();
//���ļ��ж��븴��
    ifstream fin("data.txt");
    if(!fin)
    {
        cout<<"Cannot open input file.\n";
        return 1;
    }
    for(int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        fin >> *cs[i];
    fin.close();
//�޸ĵ���������
    Complex change(1.4, 50);
    *cs[2] = change;//�޸ĵ���������
    ofstream foutt("data.txt");
    for(int i=0; i<sizeof(cs)/sizeof(Complex *); i++)
        foutt << *cs[i] <<endl;
//    foutt << (*cs[1] * *cs[3]);
    foutt.close();

    (*cs[1]) *= (*cs[3]);
//׷�ӵڶ����͵��ĸ������ĳ˻����ļ�β��
    ofstream ffout("data.txt",ios::app);//׷�ӱ���
    if(!ffout)
    {
        cout<<"Cannot open output file.\n";
        exit(1);
    }
    ffout<<(*cs[1])<<endl;
    ffout.close();


    /*ofstream out("data.txt",ios::binary);//�����ƴ�
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
