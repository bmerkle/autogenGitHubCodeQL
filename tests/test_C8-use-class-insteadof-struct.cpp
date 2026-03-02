struct GoodStruct {  
    int x;  
    void foo();  
};

struct BadStruct {  
private:  
    int secret;  
public:  
    int x;  
};
