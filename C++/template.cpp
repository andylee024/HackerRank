

// class template declaration
template <class T>
class AddElements{
    private:
        T _ele;
    
    public:
        AddElements(T ele){ _ele = ele;}
        T add(T y){ return _ele + y;}
};

// class template specialization
template <>
class AddElements<string>{
private:
    string _ele;
    
public:
    
    AddElements(string ele){
        _ele = ele;
    }
    
    string concatenate(string y){
        return _ele + y;
    }
};




