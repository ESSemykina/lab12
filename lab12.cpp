#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Teacher;
class Student {
public:

    Student(const std::string& name)
    {
        m_student_name = name;
        std::cout << m_student_name << " constructor" << std::endl;
    }
    ~Student()
    {
        std::cout << m_student_name << " destructor" << std::endl;
    }

    const std::string& GetStudentName()
    {
        return m_student_name;
    }

    const std::weak_ptr<Teacher> GetTeacher()
    {
        return m_teacher;
    }

    friend void AddStudents(std::shared_ptr<Teacher>& Teacher, std::shared_ptr<Student>& Student);

private:
    std::string m_student_name;
    std::weak_ptr<Teacher> m_teacher;
};

class Teacher {
public:
    Teacher(const std::string& name)
    {
        m_teacher_name = name;
        std::cout << m_teacher_name << " constructor " << std::endl;
    }
    ~Teacher()
    {
        std::cout << m_teacher_name << " destructor " << std::endl;
    }
    void AddStudent(std::shared_ptr<Student>& Student)
    {
        m_students.push_back(Student);
    }

    void StudentsList() {
        std::cout << std::endl;
        std::cout << m_teacher_name << ":" << std::endl;
        for (auto const& student : m_students)
            std::cout << student->GetStudentName() << std::endl;
        std::cout << " " << std::endl;
    }

    const std::string& GetTeacherName()
    {
        return m_teacher_name;
    }

    friend void AddStudents(std::shared_ptr<Teacher>& Teacher, std::shared_ptr<Student>& Student);

private:
    std::string m_teacher_name;
    std::vector<std::shared_ptr<Student>> m_students;

};

void AddStudents(std::shared_ptr<Teacher>& Teacher, std::shared_ptr<Student>& Student)
{
    Student->m_teacher = Teacher;
    Teacher->AddStudent(Student);
}

int main() {
    auto Teacher1{ std::make_shared<Teacher>("Teacher Oleg") };
    auto Teacher2{ std::make_shared<Teacher>("Teacher Dima") };
    auto Student1{ std::make_shared<Student>("Student Julia") };
    auto Student2{ std::make_shared<Student>("Student Masha") };
    auto Student3{ std::make_shared<Student>("Student Dasha") };
    auto Student4{ std::make_shared<Student>("Student Vika") };

    AddStudents(Teacher1, Student1);
    AddStudents(Teacher1, Student2);
    AddStudents(Teacher2, Student3);
    AddStudents(Teacher2, Student4);
    Teacher1->StudentsList();
    Teacher2->StudentsList();

    return 0;
}

