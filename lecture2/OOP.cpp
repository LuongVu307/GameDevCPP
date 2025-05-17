#include <iostream>
#include <vector>
#include <fstream>

class Student
{
    std::string m_first = "First";
    std::string m_last = "Last";
    int m_id = 0;
    float m_avg = 0;

public:

    Student() {} //Constructor
    Student(std::string first, std::string last, int id, float avg) //Constructor with initialization
        : m_first(first)
        , m_last(last)
        , m_id(id)
        , m_avg(avg)
    {
    }

    int getAvg() const
    {
        return m_avg;
    }

    int getID() const
    {
        return m_id;
    }
    std::string getFirst() const
    {
        return m_first;
    }
    std::string getLast() const
    {
        return m_last;
    }

    void print() const //Making a function constant
    {
        std::cout << m_first << " " << m_last << " " << m_id << " " << m_avg << std::endl;
    }

};

class Course
{
    std::string m_name = "Course";
    std::vector<Student> m_students;

public:

    Course() {}

    Course(const std::string& name): //Using referrence
    m_name(name)
    {
    }


    void addStudent(const Student s)
    {
        m_students.push_back(s);
    }

    const std::vector<Student>& getStudents() const
    {
        return m_students;
    }

    void loadFromile(const std::string& filename)
    {
        std::ifstream fin(filename);
        std::string first, last;
        int id;
        float avg;

        while (fin >> first)
        {
            fin >> last >> id >> avg;

            addStudent(Student(first, last, id, avg));
        }
        
    }


    void print() const 
    {
        for (const auto& s : m_students)
        {
            s.print();
        }
    }


};

int main(int argc, char * argv[])
{
    Student s1;
    Student s2("Gia", "Vu", 100, 2.42);
    const Student s3("Mit", "Nguyen", 290192, 9.99);

    s3.print();

    Course C1("COMP 4300");

    C1.addStudent(s1);
    C1.addStudent(s2);
    C1.addStudent(s3);
    C1.addStudent(Student("Billy", "Bob", 3, 50.0));

    C1.print();

    //Loading from files
    std::cout << std::endl;

    Course C2("COMP 4300");
    
    C2.loadFromile("student.txt");
    C2.print();

    return 0;
}