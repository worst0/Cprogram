/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: yanzw
	> Mail: yanzw@pm.me
	> Created Time: 2021年09月23日 星期四 19时34分44秒
 ************************************************************************/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define N 20
#define T 10
/*类Vector_define：探究在类中对vector进行定义的特点*/
class Vector_define
{
private:
	int i, j;
	/*一维vector*/
	//vector<int>a(N);				/*在自定义类中无法对vector实现圆括号()初始化长度的定义*/
	vector<int>a{ N };				/*此种花括号{}的初始化可以定义。作用：只是输入一个元素，而非定义长度*/
	vector<int>a1{ 1,2,3 };			/*支持直接输入元素*/
	vector<int>b;					/*正常定义，空的，无长度*/
	
	/*二维vector*/
	//vector<vector<int>>c(N, vector<int>(T));			/*该种定义同一维，无效定义*/
	vector<vector<int>>c{ N };							/*二维vector该种花括号{}定义有效。作用：占行，而非输入元素，这和一维不一样*/
	//vector<vector<int>>c{ 1,2,3 };					/*无效定义*/
	vector<vector<int>>d{ N ,vector<int> {T} };			/*该种定义，支持行定义，不支持列定义，但支持行添加*/
	vector<vector<int>>d1{ N ,vector<int> {1,2,3} };	/*支持行直接输入元素，且是为每一行都插入*/
	vector<vector<int>>e;								/*正常定义，空的，无长度*/
public:
	void test1()
	{
		/*teat a*/
		cout << "a.size()=" << a.size() << endl;	/* a.size()=1 ，可知类中花括号只是添加了元素而已*/
		for (i = 0; i < a.size(); i++)
		{
			cout << a[i] << "  ";					/* 只输出 20 ，也即只有一个元素*/
		}
		cout << endl << endl;
		
		/*teat b*/
		cout << "b.size()=" << b.size() << endl;	/* b.size()=0 ,没有元素，正常*/
		/*for (i = 0; i < a.size(); i++)
		{
			cout << b[i] << "  ";					// 报错：out of range! 空的容器，没有长度，没有东西输出！
		}
		cout << endl ;*/
		cout << endl;
		/*teat c*/
		cout << "c.size()=" << c.size() << endl;	/* c.size()=20，可知二维vector支持花括号{}定义行数 */
		for (i = 0; i < c.size(); i++)
		{
			for (j = 0; j < c[i].size(); j++)
			{
				cout << c[i][j] << "  ";			/* 不报错，有行没列,输出不了什么， */
			}
			cout << endl;
		}
		cout << endl;
		/*teat d*/
		cout << "d.size()=" << d.size() << endl;	/* d.size()=20，花括号{}行定义仍旧有效 */
		for (i = 0; i < d.size(); i++)
		{
			cout << "d[" << i << "].size()=" << d[i].size() << "  ";
		}											/* d[i].size()=1，可知花括号{}列长定义无效 */
		cout << endl;
		for (i = 0; i < d.size(); i++)
		{
			for (j = 0; j < d[i].size(); j++)
			{
				cout << d[i][j] << "  ";			/* d[i][j]=T，可知花括号{}列长定义无效,只是添加了一个元素 */
			}
			cout << endl;
		}
		cout << endl;
		/*teat e*/
		cout << "e.size()=" << e.size() << endl;	/* e.size()=0，行0，列空 */
		for (i = 0; i < e.size(); i++)
		{
			cout << "e[" << i << "].size()=" << e[i].size() << "  ";
		}											/* 列空 */
		cout << endl;
		for (i = 0; i < e.size(); i++)
		{
			for (j = 0; j < e[i].size(); j++)
			{
				cout << e[i][j] << "  ";			/* 容器空 */
			}
			cout << endl;
		}
		cout << endl;
	}
};
/*类Vector_memory：探究在类中定义的vector的内存特点*/
class Vector_memory
{
private:
	int i, j;
	/*一维*/
	vector<int>a;
	vector<int>b{ 1,2,3 };
	vector<int>c;
	vector<int>d;
	
	/*二维*/
	vector<vector<int>>e;
	vector<vector<int>>f{ N };
	vector<vector<int>>g{ N,vector<int>{1,2,3} };
public:
	void test2()
	{
		/*一维内存*/
		cout << "a.capacity()=" << a.capacity() << endl;	/* a.capacity()=0 */
		cout << "a.size()=" << a.size() << endl << endl;	/* a.capacity()=0 */
	
		cout << "b.capacity()=" << b.capacity() << endl;	/* a.capacity()=3，不会预留空间*/
		cout << "b.size()=" << b.size() << endl << endl;	/* a.capacity()=3 */
	
		//①往 a 中添加元素：研究 pushback() 对内存的改变
		for (i = 0; i < N; i++)
		{
			a.push_back(i + 1);
		}
		cout << "a.capacity()=" << a.capacity() << endl;	/* a.capacity()=28，可知pushback()会预留部分空间*/
		cout << "a.size()=" << a.size() << endl << endl;	/* a.size()=20，实际空间等于元素个数*/
		//②给 a 重设长度：研究 resize() 对内存的改变
		a.resize(30);
		cout << "a.capacity()=" << a.capacity() << endl;	/* a.capacity()=42，可知resize()会对缓存区进行重新分配和空间预留*/
		cout << "a.size()=" << a.size() << endl << endl;	/* a.capacity()=30，可知resize()会产生初始值*/
															
		//③给 c 重设长度：研究 resize() 对内存的改变
		c.resize(25);
		cout << "c.capacity()=" << c.capacity() << endl;	/* c.capacity()=25，可以发现：当对空容器resize()，不会预留空间*/
		cout << "c.size()=" << c.size() << endl << endl;	/* c.capacity()=25*/
		//④给 a 预设长度：研究 reserve() 对内存的改变
		a.reserve(50);
		cout << "a.capacity()=" << a.capacity() << endl;	/* a.capacity()=50，可知reserve()不会对缓存区进行重新分配和空间预留*/
		cout << "a.size()=" << a.size() << endl << endl;	/* a.size()=30，可知reserve()不会产生初始值*/
		
		//⑤给 a 添加超出它预设capcity的元素：研究 capcity 的变化
		for (i = 0; i < 25; i++)
		{
			a.push_back(i + 1);
		}
		cout << "a.capacity()=" << a.capacity() << endl;	/* a.capacity()=75，可知当元素超出预设的capcity，就会触发空间预留*/
		cout << "a.size()=" << a.size() << endl << endl;	/* a.size()=55*/
		
		/*二维内存*/
		cout << "e.capacity()=" << e.capacity() << endl;		/* e.capacity()=0，列的capcity报错 */
		
		cout << "f.capacity()=" << f.capacity() << endl;		/* f.capacity()=20 */
		cout << "f[0].capacity()=" << f[0].capacity() << endl;	/* f[0].capacity()=0，指定行则有列的capcity */
		cout << "g.capacity()=" << g.capacity() << endl;		/* g.capacity()=20 */
		cout << "g[2].capacity()=" << g[2].capacity() << endl;	/* g[2].capacity()=3，可知每行都被插入了相同的元素 */
		/*经过一维vector的探究，选出一些适合二维的节省资源的定义方式！*/
		//①对于可求得固定行、列信息的二维vector，定义如下：
		vector<vector<int>>h{ N };
		for (i = 0; i < h.size(); i++)
		{
			h[i].reserve(T);
		}
		cout << "h.capacity()=" << h.capacity() << endl;		/* h.capacity()=20 */
		cout << "h[0].capacity()=" << h[0].capacity() << endl;	/* h[0].capacity()=10 */
		cout << endl;
		//②对于可求得固定行信息，但是列长未知的二维vector，定义如下：
		vector<vector<int>>p{ N };
		/*通过push_back压入元素，会有预留空间*/
		for (i = 0; i < p.size(); i++)
		{
			for (j = 0; j < i + 1; j++)
			{
				p[i].push_back(j + 1);
			}
		}
		/*看看预留空间：发现确实有预留现象！*/
		for (i = 0; i < p.size(); i++)
		{
			cout << "p[" << i << "].size()=" << p[i].size() << endl;
			cout << "p[" << i << "].capacity()=" << p[i].capacity() << endl;
		}
		cout << endl;
		/*有没有办法切去多余的空间？——利用swap()方法去除vector多余的容量*/
		vector<vector<int>>(p).swap(p);
		for (i = 0; i < p.size(); i++)
		{
			cout << "p[" << i << "].size()=" << p[i].size() << endl;
			cout << "p[" << i << "].capacity()=" << p[i].capacity() << endl;
		}
		cout << endl;
		//③对于无任何信息的二维vector，直接定义空的就行。
		vector<vector<int>>t;
		/*注意：若一开始没有定义行，那么是无法通过reserve()固定行的；
			只能通过resize()的方式。
		*/
	}
};
/*类Vector_release：探究如何彻底释放在类中定义的vector的内存*/
class Vector_release
{
private:
	int i, j;
	
public:
	vector<vector<int>> a;
	vector<vector<int>> b{ N };
	vector<vector<int>> c;
	vector<int>d{ 1,2,3 };
	
	void define()
	{
		//①经过以上测试的探索，我们可以有新的定义方式：用 行、列resize()+swap()
		a.resize(N);
		for (i = 0; i < a.size(); i++)
		{
			a[i].resize(i + 1);
		}
		vector<vector<int>>(a).swap(a);			/*切除多余空间*/
		//输出
		for (i = 0; i < a.size(); i++)
		{
			for (j = 0; j < a[i].size(); j++)
			{
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		/*cout << "a.size()" << a.size() << endl;
		for (i = 0; i < a.size(); i++)
		{
			cout << "a[" << i << "].capacity()=" << a[i].capacity() << endl;
		}
		cout << endl;*/
		//②用 指定行、列reserve()+push_back()定义
		for (i = 0; i < N; i++)
		{
			b[i].reserve(T);
		}
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < T; j++)
			{
				b[i].push_back(1);
			}
		}
		cout << "bbbbb" << endl;
		for (i = 0; i < b.size(); i++)
		{
			for (j = 0; j < b[i].size(); j++)
			{
				cout << b[i][j] << "  ";
			}
			cout << endl;
		}
		cout << endl;
		//③copy一个
		c = a;
		
	}
	void clean()
	{
		
		//b.clear();	/*报错！：因为b在定义时，指定了行数，所以不能clear行*/
		
		//for (i = 0; i < b.size(); i++)
		//{
		//	b[i].clear();	
		//}/*可以清空列元素，但是列的capacity还在。但至少可以保证循环时的push_back()不会溢出内存*/
		
		for (i = 0; i < b.size(); i++)
		{
			vector<int>().swap(b[i]);
		}/*可以清空列元素以及列的capacity。*/
		//c.clear();/*二维vector.clear()，可以彻底清除列的capacity，但是保留着行的capacity*/
		vector<vector<int>>().swap(c);/*利用swap()彻底清除capacity*/
		
		d.clear();/*一维vector.clear()，保留着列的capacity*/
		
	}
};
int main()
{
	Vector_define v1;
	v1.test1();
	Vector_memory v2;
	v2.test2();
	Vector_release v3;
	for (int it = 0; it < 4; it++)
	{
		cout << "第" << it << "次：" << endl;
		
		v3.define();
		v3.clean();
		
		for (int i = 0; i < v3.a.size(); i++)
		{
			cout << "a[i].capacity[" << i << "]=" << v3.a[i].capacity() << "  ";
		}
		cout << endl << endl;
		
		for (int i = 0; i < v3.b.size(); i++)
		{
			cout << "b[i].capacity[" << i << "]=" << v3.b[i].capacity() << "  ";
		}
		cout << endl << endl;
		
		cout << "c.capacity()=" << v3.c.capacity() << endl;
		for (int i = 0; i < v3.c.size(); i++)
		{
			cout << "c[i].capacity[" << i << "]=" << v3.c[i].capacity() << "  ";
		}
		cout << endl;
		cout << "d.capacity()=" << v3.d.capacity() << endl;
	}
	return 0;
	system("pause");
}
