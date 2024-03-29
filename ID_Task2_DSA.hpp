
#include "main.hpp"


template <typename T>
class List
{
public:
    //! Hàm của thầy
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;

    //! Hàm hỗ trợ thêm
    virtual List<T> *subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
    virtual double distanceEuclidean(const List<T> *image) = 0;
};

template <typename T>
class Image : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node *next;

    public:
        Node(T pointer, Node *next = nullptr) : pointer(pointer), next(next) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    Image()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~Image()
    {
        this->clear();
    }
    void push_back(T value)
    {
        // TODO: implement task 1
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void push_front(T value)
    {
        // TODO: implement task 1
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > size)
        {
            return;
        }

        // TODO: implement task 1
        if (index == 0)
        {
            this->push_front(value);
        }
        else if (index == size)
        {
            this->push_back(value);
        }
        else
        {
            Node *newNode = new Node(value);
            Node *temp = head;

            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }

            newNode->next = temp->next;
            temp->next = newNode;
            size++;
        }
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
            return;

        // TODO: implement task 1
        Node *temp;
        if (index == 0)
        {
            temp = head;
            head = head->next;
            if (!head)
            {
                tail = nullptr;
            }
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; i++)
            {
                current = current->next;
            }

            temp = current->next;
            current->next = temp->next;
            if (!current->next)
            {
                tail = current;
            }
        }

        delete temp;
        size--;
    }

    T &get(int index) const
    {
        if (index < 0 || index >= this->size)
            throw std::out_of_range("get(): Out of range");

        // TODO: implement task 1
        Node *current = head; // Bắt đầu từ nút đầu tiên

        // Di chuyển đến vị trí index trong danh sách
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        // Trả về con trỏ đến phần tử tại vị trí index
        return current->pointer;
    }

    int length() const
    {
        return size;
    }

    void clear()
    {
        // TODO: implement task 1
        Node *current = head;
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp; // Giải phóng bộ nhớ của nút hiện tại
            size--;
        }
        head = tail = nullptr; // Cập nhật con trỏ đầu danh sách
        size = 0;              // Đặt kích thước danh sách về 0
    }

    void print() const
    {
        if (size == 0)
            OUTPUT << "nullptr" << endl;
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (i == this->size - 1)
                OUTPUT << temp->pointer << endl;
            else
                OUTPUT << temp->pointer << " ";
            temp = temp->next;
        }
    }

    void reverse()
    {
        // TODO: implement task 1
        if (this->size <= 1)
            return;
        Node *current = head;
        Node *prev = nullptr;
        Node *next = nullptr;

        tail = head;
        while (current != nullptr)
        {
            // Lưu trữ con trỏ đến nút tiếp theo của nút hiện tại
            next = current->next;
            // Thay đổi con trỏ next của nút hiện tại để trỏ về nút trước đó
            current->next = prev;
            // Di chuyển con trỏ prev và current về phía trước
            prev = current;
            current = next;
        }

        // Cập nhật con trỏ đầu danh sách để trỏ đến nút cuối cùng (trước khi đảo ngược)
        head = prev;
    }

    void printStartToEnd(int start, int end) const
    {
        Node *current = head;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                OUTPUT << current->pointer << endl;
            else
                OUTPUT << current->pointer << " ";
        }
    }

    List<T> *subList(int start, int end)
    {

        if (this->size <= start)
            return nullptr;
        Node *current = this->head;
        for (int i = 0; i < start; ++i)
        {
            current = current->next;
        }
        List<T> *result = new Image<T>();

        // TODO: implement task 1
        //^ gợi ý: dùng push_back
        for (int i = start; i < end && current != nullptr; ++i)
        {
            result->push_back(current->pointer);
            current = current->next;
        }
        return result;
    }

    double distanceEuclidean(const List<T> *image)
    {
        double distance = 0.0;
        if (this->length() > image->length())
        {
            int i = 0;
            for (i = 0; i < image->length(); i++)
            {
                distance += (this->get(i) - image->get(i)) * (this->get(i) - image->get(i));
            }
            for (int j = i; j < this->length(); j++)
            {
                distance += this->get(j) * this->get(j);
            }
        }
        else
        {
            int i = 0;
            for (i = 0; i < this->length(); i++)
            {
                distance += (this->get(i) - image->get(i)) * (this->get(i) - image->get(i));
            }
            for (int j = i; j < image->length(); j++)
            {
                distance += image->get(j) * image->get(j);
            }
        }
        return sqrt(distance);
    }
};




class Dataset {
private:
    List<List<int>*>* data;
    List<string>* nameCol;
    //You may need to define more
public:
    //! Hàm khởi tạo
    Dataset()
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int>*>();
    }
    //! Hàm hủy
    ~Dataset()
    {
        delete data;
        delete nameCol;
    }
    Dataset(const Dataset& other)
    {
        this->nameCol = new Image<string>();
        this->data = new Image<List<int>*>();
        //TODO: implement Task 2
         for (int i=0; i<other.data->length(); i++){
                this->data->push_back(other.data->get(i));
                    
        }

    }
    Dataset& operator=(const Dataset& other)
    {
        if(this!=&other){
            delete data;
            delete nameCol;
        }
        if(other.nameCol){
            this->nameCol = new Image<string>();
            this->data = new Image<List<int>*>();
            this->nameCol = other.nameCol;
            for (int i=0; i<other.data->length(); i++){
                this->data->push_back(other.data->get(i));
                    
            }
        }
        //TODO: implement Task 2
        return *this;
    }
    //remake-------------------------------------------------------------------------------------
    bool loadFromCSV(const char* fileName)
    {   
        ifstream file(fileName);
        //* kiểm tra mở file
        if(file.is_open())
        {
            string str;
            int number;

            //* xử lý hàng đầu tiên chuyển , thành ' ' dùng thư viện stringstream
            file >> str;
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == ',') str[i] = ' ';
            }
            stringstream ss(str);  
            while(ss >> str) nameCol->push_back(str);

             //* xử lý các hàng còn lại , thành ' ' dùng thư viện stringstream
            while(file >> str)
            {
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') str[i] = ' ';
                }
                stringstream ss(str);  
                List<int>* temp = new Image<int>();
                while(ss >> number) temp->push_back(number);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void getShape(int& nRows, int& nCols) const
    {
        //TODO: implement Task 2
       nRows=data->length();
       nCols=nameCol->length();

    }
    void columns() const
    {
        
        if (data == nullptr ) {
            return;
        }
        for (int i = 0; i < nameCol->length(); ++i) {
            cout << nameCol->get(i) << " ";
        }
    
        //TODO: implement Task 2
    }
    void printHead(int nRows = 5, int nCols = 5) const
{
    if(nRows <= 0 || nCols <= 0 || data == nullptr) return;
    int totalRows = data->length();
    nRows = min(nRows, totalRows);

    for (int i = 0; i < nRows; ++i) {
        List<int>* row = data->get(i);
        printStartToEnd(0, min(nCols, row->length()));
    }
}
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if(nRows <= 0 || nCols <= 0)  return;
        //TODO: implement Task 2
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        //TODO: implement Task 2
        return false;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        //TODO: implement Task 2
    }


    double distanceEuclidean(const List<int>* x, const List<int>* y) const{
        //TODO: implement Task 2 copy code từ implement Task 1 chỉnh
    }


    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const
    {
       //TODO: implement Task 3 
       return Dataset();
    }
    double score(const Dataset& y_test) const
    {   
        //TODO: implement Task 3 
        return -1;
    }
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    //You may need to define more
public:
    kNN(int k = 5):k(k){};
    void fit(const Dataset& X_train, const Dataset& y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset& X_test)
    { 
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset& y_test, const Dataset& y_pred)
    {   
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset& X, Dataset& Y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& Y_train, Dataset& Y_test)
{
    //* phân chia X
    int nRowsX, nColsX;
    X.getShape(nRowsX, nColsX);
    X_train = X.extract(0, test_size * nRowsX, 0, -1);
    X_test = X.extract(test_size * nRowsX, -1 , 0, -1);

    //* phân chia Y
    int nRowsY, nColsY;
    Y.getShape(nRowsY, nColsY);
    Y_train = Y.extract(0, test_size * nRowsY, 0, -1);
    Y_test = Y.extract(test_size * nRowsY, -1 , 0, -1);
}

// Please add more or modify as needed
