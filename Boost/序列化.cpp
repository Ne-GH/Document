#include <iostream>
#include <vector>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Item {
    int *p = nullptr;
public:
    Item() { }
    void Change(int num) {
        if (p == nullptr)
            p = new int(num);
        else
            *p = num;
    }
    void Out() {
        std::cout << *p << " ";
    }

    template<class Archive>
    void serialize(Archive &ar,const unsigned int version) {
        // 反序列化
        if (Archive::is_loading::value) {
            if (p == nullptr) {
                p = new int;
            }
            ar & *p;
        }
        else {
            ar & *p;
        }
    }
};

class Base {
    std::vector<Item *> vec;
public:
    void Change() {
        for(int i = 0;i < 5; ++i) {
            auto item = new Item();
            item->Change(i);
            vec.push_back(item);
        }
    }
    void Out() {
        for (int i = 0;i < vec.size(); ++i) {
            vec[i]->Out();
        }
        std::cout << std::endl;
    }
    template<class Archive>
    void serialize(Archive &ar,const unsigned int version) {
        // 反序列化
        if (Archive::is_loading::value) {
            size_t size;
            ar & size;
            vec.resize(size);
            for (int i = 0;i < size; ++i) {
                ar & vec[i];
            }
        }
        // 序列化
        else {
            size_t size = vec.size();
            ar & size;
            for (int i = 0;i < vec.size(); ++i) {
                ar & vec[i];
            }
        }
    }
};

class Derived : public Base {
public:

    void Change() {
        dynamic_cast<Base *>(this)->Change();
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        // 调用 Base 类的序列化方法
        ar & boost::serialization::base_object<Base>(*this);
    }
    void Out() {
        Base::Out();
    }


};


int main() {
    Derived d1;
    {
        d1.Change();
        std::ofstream ofs("file");
        boost::archive::text_oarchive oa(ofs);
        oa << d1;
    }
    Derived d2;
    {
        std::ifstream ifs("file");
        boost::archive::text_iarchive ia(ifs);
        ia >> d2;
    }
    d2.Out();


    return 0;
}
