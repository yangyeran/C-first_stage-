@[toc](目录)

## string模拟实现

补：

* stoi字符串转整型

  ```c++
  int stoi (const string&  str, size_t* idx = 0, int base = 10);
  ```

  * stol ,stoul,stof,stod,stold,stoll,stoull转不同的类型(看结尾的字符，f--float....)

* to_string 整型转字符串(也可以是浮点型等等)

  ```c++
  string to_string (int val);
  string to_string (long val);
  string to_string (long long val);
  string to_string (unsigned val);
  string to_string (unsigned long val);
  string to_string (unsigned long long val);
  string to_string (float val);
  string to_string (double val);
  string to_string (long double val);string to_string (int val);
  ```

* tolower 大写字符转小写字符

  ```c++
  int tolower ( int c );
  ```

* toupper 小写字符转大写字符

  ```c++
  int toupper ( int c );
  ```

* reverse 逆置字符串

  ```c++
  template <class BidirectionalIterator>
  void reverse (BidirectionalIterator first, BidirectionalIterator last);//里面传迭代器，普遍都是左闭右开
  ```

---

有两个swap一个是全局的，一个是string库里面的它们有什么区别呢？

```c++
string s1("hello word");
string s2("xxxxxxxxxx");
s1.swap(s2);//--->效率高--仅仅对成员变量进行交换即可
swap(s1,s2);//代价很大--三次string的深拷贝
template <class T>
   void swap(T&a,T&b)
{
    T c(a);
    a=b;
    b=c;
}
```

* 
