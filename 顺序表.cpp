#include <iostream>
using namespace std;

template <typename T>
class SeqList {
protected:
    T* data;
    int length;
    int capacity;
    // 扩容函数，将容量扩大至 newCapacity
    // 返回 true 表示扩容成功，false 表示失败
    bool increaseSize(int newCapacity){
        if (newCapacity<capacity) return false;
        //else capacity=newCapacity; //只修改了 capacity，但没有重新分配更大的空间
        //应当要开辟一块更大的新空间
        T* newdata=new T[newCapacity];
        for (int i=0;i<length;i++){
            newdata[i]=data[i];
        }
        delete[] data;
        data=newdata;
        capacity=newCapacity;
        return true;
    }
public:
    // 构造函数，默认初始容量为 4
    SeqList(int initCapacity = 4):
        length(0),capacity(initCapacity){
        data= new T[capacity]; //问题：局部变量遮蔽成员变量
    }
    
    // 析构函数，释放动态分配的内存
    ~SeqList(){
        delete[] data;
    }
    
    // 拷贝构造函数，实现深拷贝
    SeqList(const SeqList<T>& other){
        if (*this != other){  //自赋值检查
            length=other.length;
            capacity=other.capacity;
            delete[] data;
            data=new T[capacity];
            for (int i=0;i<length;i++){
                data[i]=other.data[i];
            }
        }
    }
    
    // 拷贝赋值运算符，实现深拷贝
    // 需要检查自赋值，释放旧空间，分配新空间并复制数据
    SeqList<T>& operator=(const SeqList<T>& other){
        if (this != &other){  //应当要比较两地址
            length=other.length;
            capacity=other.capacity;
            delete[] data;
            data=new T[capacity];
            for (int i=0;i<length;i++){
                data[i]=other.data[i];
            }
            //delete[] other.data;  及其危险
            other.data=nullptr;
        }
        return *this //应当要返回当前对象的引用
    }

    // 判断顺序表是否为空
    // 返回 true 表示为空，false 表示非空
    bool empty() const{if (length>0) return false; else return true;}
    
    // 返回顺序表当前元素个数
    int size() const{return length;}
    
    // 返回顺序表当前最大容量
    int getCapacity() const{ return capacity;}
    
    // 获取第 i 个位置的元素，i 从 1 开始
    // 用引用参数 e 带回元素值
    // 返回 true 表示获取成功，false 表示位置不合法
    bool getElem(int i, T& e) const{
        if (i>=1 && i<=length){
            e=data[i-1];
            return true;
        }
        return false;
    
    }
    // 查找第一个值为 e 的元素
    // 返回元素的位置（从 1 开始），找不到返回 0
    int locateElem(const T& e) const{
        for (int i=0;i<length;i++){
            if (data[i]==e){
                return i+1;
            }
        }
        return 0;
    }

    // 在第 i 个位置插入元素 e，i 从 1 开始
    // 合法范围：1 <= i <= length + 1
    // 插入前若容量已满则自动扩容
    // 返回 true 表示插入成功，false 表示失败
    bool insert(int i, const T& e){
        //检查Pos是否合法
        if (!(1<=i && i<=length+1)){
            return false;
        }
        //先检查插入后是否会超容量，若是，则应扩容
        if (length==capacity){
            //capacity++;  应当要直接扩容，而不是做表面工作
        }
        for (int k=length-1;k>=i;k--){ //范围写错，原本的那个占着的也得向右移动
            data[k+1]=data[k];
        }
        data[i-1]=e;
        length++;
        return true;
    }
    
    // 删除第 i 个位置的元素，i 从 1 开始
    // 合法范围：1 <= i <= length
    // 用引用参数 e 带回被删除的元素值
    // 返回 true 表示删除成功，false 表示失败
    bool remove(int i, T& e){
        //检查Pos是否合法
        if (!(1<=i && i<=length+1)){
            return false;
        }
        e=data[i-1]; //补上
        for (int k=i-1;k<=length-2;k++){
            data[k]=data[k+1];
        }
        length--;
        return true;

    }
    
    // 在末尾追加一个元素
    // 返回 true 表示追加成功，false 表示失败
    bool pushBack(const T& e){
        if (length==capacity) return false;  //应当要尝试扩容，而不是直接不干！
        else data[length]=e;  
        length++;
        return true;
    }
    
    // 删除末尾元素
    // 用引用参数 e 带回被删除的元素值
    // 返回 true 表示删除成功，false 表示失败
    bool popBack(T& e){
        if (length==0) return false;
        else e=data[length-1];
        length--;
        return true;
    }

    // 输出顺序表中所有元素，用于调试
    void print() const{
        for (int i=0;i<length;i++){
            cout<<data[i]<<" ";
        }
        cout<<endl;
    }
};