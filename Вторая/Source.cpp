#include<iostream>
#include<algorithm>
#include<iterator>
#include<queue>
#include<set>
#include<functional>
#include<memory>
using namespace std;
template<class tip>
struct MyTip		// Пользовательский тип данных
{
	tip x;
	char bukva;
	int cifra;
};
template<class tip>
bool operator> (MyTip<tip> lev, MyTip<tip> prav);
template<class tip>
bool operator< (MyTip<tip> lev, MyTip<tip> prav);
template<class T>
multiset<T, less<T>>* increaseSort(multiset<T, greater<T>>*);
template<class T>
multiset<T, greater<T>>* decreaseSort(multiset<T, less<T>>*);
template<class tip>
bool pred(const MyTip<tip> &);

int main()
{
	multiset<MyTip<float>> multik;
	multik.insert({ (float)2.5, 'a', 15 });
	multik.insert({ (float)5.5, 'b', 10 });
	multik.insert({ (float)-5.5, 'a', 38 });
	multik.insert({ (float)0.0, 'o', 0 });
	multik.insert({ (float)3.33, 'z', 3 });
	multik.insert({ (float)7.49, 'q', 50 });

	multiset<MyTip<float>, greater<MyTip<float>>> multik_ub = *decreaseSort(&multik);

	for (multiset<MyTip<float>, greater<MyTip<float>>>::iterator i = multik_ub.begin(); i != multik_ub.end(); ++i)
		cout << i->x << " " << i->cifra << " " << i->bukva << endl;

	multiset<MyTip<float>, greater<MyTip<float>>>::iterator el = find_if(multik_ub.begin(), multik_ub.end(), pred<float>);

	queue<MyTip<float>> myq;
	
	for (;;)
	{
		if ((el == multik_ub.end()))
			break;
		myq.push(*el);
		el = find_if(++el, multik_ub.end(), pred<float>);
	}

	for (int i = 0; i < myq.size(); ++i)
	{
		cout << (myq.front()).x << " " << (myq.front()).cifra << " " << (myq.front()).bukva << endl;
		myq.push(myq.front());
		myq.pop();
	}

	multiset<MyTip<float>> buf;
	int sz = myq.size();
	for (int i = 0; i < sz; ++i)
	{
		buf.insert(myq.front());
		myq.pop();
	}
	for (multiset<MyTip<float>>::iterator i = buf.begin(); i != buf.end(); ++i)
		myq.push(*i);

	multik.clear();
	for (multiset<MyTip<float>, greater<MyTip<float>>>::iterator i = multik_ub.begin(); i != multik_ub.end(); ++i)
		multik.insert(*i);

	for (int i = 0; i < myq.size(); ++i)
	{
		cout << (myq.front()).x << " " << (myq.front()).cifra << " " << (myq.front()).bukva << endl;
		myq.push(myq.front());
		myq.pop();
	}

	for (multiset<MyTip<float>>::iterator i = multik.begin(); i != multik.end(); ++i)
		cout << i->x << " " << i->cifra << " " << i->bukva << endl;

	multiset<MyTip<float>> cont3;
	for (int i = 0; i < myq.size(); ++i)
	{
		cont3.insert(myq.front());
		myq.pop();
	}
	for (multiset<MyTip<float>>::iterator i = multik.begin(); i != multik.end(); ++i)
		cont3.insert(*i);

	int n = count_if(cont3.begin(), cont3.end(), pred<float>);
	cout << n << endl;

	if (find_if(cont3.begin(), cont3.end(), pred<float>) != cont3.end())
		cout << "Yes\n";

	return 0;
		
}

template<class tip>
bool operator> (MyTip<tip> lev, MyTip<tip> prav)
{
	return (lev.x > prav.x);
}
template<class tip>
bool operator< (MyTip<tip> lev, MyTip<tip> prav)
{
	return (lev.x < prav.x);
}
template<class T>
multiset<T, less<T>>* increaseSort(multiset<T, greater<T>> *mts)
{
	multiset<T, less<T>> *sorted = new multiset<T, less<T>>;
	for (multiset<T>::iterator i = mts->begin(); i != mts->end(); ++i)
		sorted->insert(*i);
	return sorted;
}
template<class T>
multiset<T, greater<T>>* decreaseSort(multiset<T, less<T>> *mts)
{
	multiset<T, greater<T>> *sorted = new multiset<T, greater<T>>;
	for (multiset<T>::iterator i = mts->begin(); i != mts->end(); ++i)
		sorted->insert(*i);
	return sorted;
}
template<class tip>
bool pred(const MyTip<tip> &T)
{
	if (T.x < 3)
		return true;
	return false;
}
