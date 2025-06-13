#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace std 사용

class Book 
{
public:
    string title;
    string author;
    int stock;       // 책 재고
    
    Book(const string& title, const string& author)
        : title(title), author(author), stock(3) {}  // 생성자 초기화 리스트
   
    // 대여 기능
    bool rentBook() 
    {
        if (stock > 0)  // 재고 있으면 대여 가능
        {
            stock--;    // 대여 시 재고 1권 감소
            return true;
        }
        return false;   // 재고 없으면 대여 불가
    }

    // 반납 기능
    void returnBook()
    {
        stock++;    // 반납 시 재고 1권 증가
    }
    
};

class BookManager
{
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    // 책 제목, 저자를 매개변수로 받음
    // 문자열 상수와 참조로 받음 -> 값 변경 방지, 메모리 최적화
    void addBook(const string& title, const string& author)
    {
        books.push_back(Book(title, author)); // push_back 사용해 책 추가
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const
    {
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        // 책 목록 출력
        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++)   // 일반적인 for문 사용
        {
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // 책 제목으로 검색
    // 책 제목 길이 길수도 있으니까 참조로 가져옴
    void searchBookByTitle(const string& title)
    {
        // 책을 찾았는지 아닌지를 끝까지 확인해야 하기 때문
        // for문 안에서 조건이 맞는 책을 한 권도 못 찾은 경우
        // "찾을 수 없습니다" 메시지를 출력

        bool found = false; // 아직 책을 못 찾은 상태

        // size_t 벡터의 양수 전용.      
        // books.size()는 books에 들어있는 원소(책)의 개수를 반환하는 함수
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].title == title)    // i번째 책 제목이 내가 찾는 제목과 일치
            {
                cout << "책 제목: " << books[i].title << " 작가: " << books[i].author;
                cout << " 재고: " << books[i].stock << "권" << endl;
                found = true;   // for문 돌면서 책 찾으면 true
                break;
            }
        }

        if (!found)
        {
            cout << "해당 제목의 책을 찾을 수 없습니다." << endl;
        }
    }

    // 작가로 검색
    void searchBookByAuthor(const string& author)
    {
        bool found = false;
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].author == author)
            {
                cout << "- " << books[i].title << " (재고: " << books[i].stock << "권)" << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "해당 작가의 책을 찾을 수 없습니다." << endl;
        }
    }

    // 대여 (제목 먼저, 없으면 작가로 찾기)
    void rentBookByTitleOrAuthor(const string& input)
    {
        // 1. 제목으로 먼저 찾기
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].title == input)
            {
                if (books[i].rentBook())
                    cout << "책 '" << books[i].title << "' 대여가 완료되었습니다." << endl;
                else
                    cout << "책 '" << books[i].title << "'은 대여할 수 없습니다." << endl;
                return;
            }
        }

        // 2. 제목으로 못 찾았으면 → 작가 이름으로 찾기
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].author == input)
            {
                if (books[i].rentBook())
                    cout << "작가 '" << books[i].author << "'의 책 '" << books[i].title << "' 대여 완료되었습니다." << endl;
                else
                    cout << "작가 '" << books[i].author << "'의 책은 대여할 수 없습니다." << endl;
                return;
            }
        }

        cout << "해당 제목 또는 작가의 책을 찾을 수 없습니다." << endl;
    }

    // 반납
    void returnBookByTitleOrAuthor(const string& input)
    {
        // 1. 제목으로 먼저 찾기
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].title == input)
            {
                books[i].returnBook();
                cout << "책 '" << books[i].title << "'이 반납되었습니다." << endl;
                return;
            }
        }

        // 2. 제목으로 못 찾았으면 → 작가 이름으로 찾기
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].author == input)
            {
                books[i].returnBook();
                cout << "작가 '" << books[i].author << "'의 책 '" << books[i].title << "'이 반납되었습니다." << endl;
                return;
            }
        }

        cout << "해당 제목 또는 작가의 책을 찾을 수 없습니다." << endl;
    }
};

   
int main() 
{   
    // 객체 생성
    BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) 
    {
        // 콘솔창 출력 내용 클린
        system("cls");

        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 제목으로 책 검색" << endl;
        cout << "4. 작가 이름으로 책 검색" << endl;
        cout << "5. 책 대여" << endl;
        cout << "6. 책 반납" << endl;
        cout << "7. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;  // 1 입력하면 cin이 \n 처리 못해서 남아있음 (잔여 버퍼)
        cin.ignore(); // 이전 입력의 잔여 버퍼(\n)를 제거 -> 새로운 입력 받을 준비

        if (choice == 1) 
        {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;   // 책 제목, 저장명 저장할 변수 선언
            cout << "책 제목: ";
            getline(cin, title); // 제목 입력 (공백 포함) 받아 title에 저장
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함) 받아 author에 저장
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) 
        {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3)
        {
            // 3번 선택: 제목으로 책 검색
            string title;
            cout << "책 제목: ";
            getline(cin, title);
            manager.searchBookByTitle(title);
        }
        else if (choice == 4)
        {
            // 4번 선택: 작가 이름으로 책 검색
            string author;
            cout << "작가 이름: ";
            getline(cin, author);
            manager.searchBookByAuthor(author);
        }
        else if (choice == 5)
        {
            string input;
            cout << "책 제목 또는 작가 이름: ";
            getline(cin, input);
            manager.rentBookByTitleOrAuthor(input);
        }
        else if (choice == 6)
        {
            string input;
            cout << "책 제목 또는 작가 이름: ";
            getline(cin, input);
            manager.returnBookByTitleOrAuthor(input);
        }
        else if (choice == 7) 
        {
            // 7번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else 
        {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }

        // Press any key
        system("pause");
    }

    return 0; // 프로그램 정상 종료
}