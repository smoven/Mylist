#include <iostream>
using namespace std;

template<class T> class MyList;
template<class T> ostream & operator<<(ostream &, const MyList<T> &);
template<class T> MyList<T> operator + (const MyList<T> &, const MyList<T> &);
template<class T> MyList<T> operator + (const MyList<T> &, const T &);

template<class T>
class MyList{
    friend ostream &operator<< <T>(ostream &os, const MyList<T> &obj);
    friend MyList<T> operator+<>  (const MyList<T> &l1, const MyList<T> &l2);
    friend MyList<T> operator+<> (const MyList<T> &l1, const T &item);

private:
	T *a;
	int size;
	int curlen; 
	void double_space();
	int judge(int i, char *s="index", int op=1);  
	int divide1(int start, int end) ;
	int divide2(int start, int end) ;
	void sort(int start, int end,const bool less=true);  

public:
	MyList(int len = 0):curlen(len){
		size = 100;
		a = new T [size];
	}
	MyList(int num, const T &item);
	MyList(const MyList &l);
    MyList(const T* arr, int len);
    MyList &operator = (const MyList &l);
    void push(const T &item);
    T pop();
	void insert(int index, const T &item);
	void clean();
	int get_size() const { return size; }
	int get_curlen() const { return curlen; }
	void erase(int start, int end); 
	T get_item(int index) { index = judge(index); return a[index]; }
	MyList get_item(int start, int end);
	int count(const T &item) const;
	void remove(const T &item);
    T &operator [](int index);
	MyList &operator += (const T &item);
	MyList &operator += (const MyList &l);
	void sort(bool less=true);
	void reverse();
	~MyList(){delete [] a; size = curlen = 0;}
};

template<class T>
MyList<T> :: MyList(int num, const T &item): size(num), curlen(num) {
    a=new T[size];
    for(int i=0;i<curlen;++i)a[i]=item;
}

template<class T>
MyList<T> :: MyList(const MyList<T> &l){
	size=l.size;
	curlen=l.curlen;
	a=new T[size];
	for(int i=0;i<curlen;++i)a[i]=l.a[i];
}

template<class T>
MyList<T> :: MyList(const T* arr, int len): size(len), curlen(len) {
    a=new T[size];
    for(int i=0;i<curlen;++i)a[i]=arr[i];
}

template<class T>
MyList<T> &MyList<T> :: operator=(const MyList<T> &l){
    if(this == &l) return *this;
    delete a;         
    size=l.size;
    curlen=l.curlen;
	a=new T [size];
	for(int i=0;i<curlen;++i)a[i]=l.a[i];
    return *this;
}

template<class T>
int MyList<T> :: judge(int i,char *s,int op){ 
    bool flag=false;                            
    do {
        try{
            if(op==1){
                if(i<0||i>=curlen) {throw -1;}
                else flag=true;
            }
            if(op==2){     
                if(i<(-1)*curlen||i>=curlen){throw -1;}  
                else flag=true;
            }
        }
        catch(int){ 
                cout<<"The "<<s<<" is out of the range! \nGive the right "<<s<<" :";
                cin>>i;
                }
    } while(!flag);
    return i;
}

template<class T>
void MyList<T> :: double_space(){
    T *tmp=a;
    size *=2;
    a=new T [size];
    for(int i=0;i<curlen;++i){
        a[i]=tmp[i];
    }
    delete [] tmp;
}

template<class T>
void MyList<T> :: push(const T &item){
    if(size==0){           
        size=100;
        a=new T [size];
    }
    else if(size==curlen)double_space();
    a[curlen]=item;  
    ++curlen;
}

template<class T>
ostream &operator<<(ostream &os,const MyList<T> &obj){
    os << "[";
    if(obj.curlen){        
        for(int i=0;i<obj.curlen-1;++i){
            os<<obj.a[i]<<",";
        }
        os<<obj.a[obj.curlen-1];
    }
    os<<"]";
    return os;
}

template<class T>
T MyList<T> :: pop(){
    try{
        if(curlen==0)throw -1;   
        else return a[--curlen];
    }
    catch(int){ 
        cout<<"You cannot pop the empty Mylist";
    }
}


template<class T>
void MyList<T> :: insert(int index, const T &item){
    index=judge(index);
    if(size == curlen)double_space();
    for(int i=curlen;i>index;--i)a[i]=a[i-1];
    a[index]=item;
    ++curlen;
}


template<class T>
void MyList<T> :: clean(){
    size=0;
    curlen=0;
    delete [] a;  
    a=NULL;
}


template<class T>
void MyList<T> :: erase(int start, int end){
    start=judge(start, "start");
    end=judge(end,"end");
    int len=(end-start+1);
    curlen-=len;
    for(int i=start;i<curlen;++i) a[i]=a[i+len];
}

template<class T>
T &MyList<T> :: operator [](int index){
    index=judge(index);
    return a[index];
}

template<class T>
MyList<T> MyList<T> :: get_item(int start, int end){
    start=judge(start, "start",2);
    end=judge(end,"end",2);
    MyList<T> tmp;
    start=(start + curlen)%curlen; 
    end=(end + curlen)%curlen;
    if(start>end) return tmp;
    tmp.curlen=tmp.size=end-start+1;
    tmp.a=new T [tmp.curlen];
    for(int i=start; i<=end; ++i) tmp.a[i-start]=a[i];
    return tmp;
}

template<class T>
int MyList<T> :: count(const T &item) const{
    int cnt=0;
    for(int i=0;i<curlen;++i) if(a[i]==item)++cnt;
    return cnt;
}

template<class T>
void MyList<T> :: remove(const T &item){
    int i;
    for(i=0;i<curlen;++i)
        if(a[i]==item) break;
    for(i=0;i<curlen;++i)
        a[i]=a[i+1];
    --curlen;
}

template<class T>
MyList<T> &MyList<T> :: operator+= (const T &item){
    push(item);
    return *this;
}

template<class T>
MyList<T> &MyList<T> :: operator += (const MyList<T> &l){
    while(curlen + l.curlen > size) double_space();  
    for(int i=curlen;i<curlen+l.curlen;++i)
        a[i]=l.a[i-curlen];
    curlen+=l.curlen;
    return *this;
}

template<class T>
MyList<T> operator+ (const MyList<T> &l1, const MyList<T> &l2){
    MyList<T> tmp(l1);
    tmp+=l2;
    return tmp;
}

template<class T>
MyList<T> operator+ (const MyList<T> &l1, const T &item){
    MyList<T> tmp(l1);
    tmp+=item;
    return tmp;
}

template<class T>
int MyList<T> :: divide1(int start, int end){
    int i=start,j=end;
    T sample=a[start];
    do{while(i<j&&a[j]>=sample) --j;
        if(i<j){a[i]=a[j];++i;}
        while(i<j &&a[i]<= sample) ++i;
        if(i<j){a[j]=a[i];--j;}
    } 
	while(i!=j);
    a[i]=sample;
    return i;
}

template<class T>
int MyList<T> :: divide2(int start, int end){ 
    int i=start,j=end;
    T sample=a[start];
    do{while (i<j&&a[j]<=sample) --j;
        if(i<j){a[i]=a[j];++i;}
        while(i<j&&a[i]>=sample) ++i;
        if(i<j){a[j]=a[i];--j;}
    } 
	while(i!=j);
    a[i]=sample;
    return i;
}

template<class T>
void MyList<T> :: sort(bool less){
    sort(0,curlen-1,less);
}

template<class T>
void MyList<T> :: sort(int start, int end, bool less){ 
    int mid;
    if(start>=end) return;
    if(less) mid=divide1(start,end);
    else
        mid=divide2(start,end);
    sort(start,mid-1,less);
    sort(mid+1,end,less);
}

template<class T>
void MyList<T> :: reverse(){
    T tmp;
    for(int i=0;i<curlen/2;++i){
        tmp=a[i];
        a[i]=a[curlen-1-i];
        a[curlen-1-i]=tmp;
    }
}

int main()
{   MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i){
		a.push(i);
	}
    // a = [0, 1, 2, 3, 4]
	a[3]=15; // a = [0, 1, 2, 15, 4]
	//a[-1] = 15;  
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for(i=0;i<a.get_curlen();++i)
		cout<<a[i]<<endl;
    b=a.get_item(4, -3); // b = []
	b=a.get_item(3, -1); // b = [1, 0, 12]
	a+=b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.pop()<<endl;
	b.push(1);
	b.push(2);
	cout<<b<<endl;
	cout<<b.pop()<<endl;
	cout<<b.get_curlen()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b=a+a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	b.sort();
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for(i=0;i<100;++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
    return 0;
}
