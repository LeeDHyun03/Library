#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;
    int bookPcs = 0;
    Book(const string& title, const string& author, const int& bookPcs)
        : title(title), author(author), bookPcs(bookPcs) {
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장
    vector<Book> rentalBooks; // 대여한 책 목록 저장
public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author, const int& bookPcs) {
        books.push_back(Book(title, author, bookPcs)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << "   " << bookPcs << "권" << endl;
    }
    void rentalBook(Book book)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].author == book.author && books[i].title == book.title)
            {
                books[i].bookPcs--;
                rentalBooks.push_back(books[i]);
            }
            break;
        }
    }
    void returnBook()
    {
        if (rentalBooks.empty()) {
            cout << "현재 대여한 책이 없습니다." << endl;
            return;
        }

        cout << "현재 대여 도서 목록:" << endl;
        for (size_t i = 0; i < rentalBooks.size(); i++) { // 일반적인 for문 사용
            cout << "-" << i << "  " << books[i].title << " by " << books[i].author << endl;
        }
        cout << "반납하려는 도서의 번호를 입력해주세요.\n 입력:  ";
        int bookNum = 0;
        cin >> bookNum;
        Book retuningBook = searchBook(rentalBooks[bookNum].title);
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].title == retuningBook.title && books[i].author == retuningBook.author)
            {
                books[i].bookPcs++;
                break;
            }
        }
        rentalBooks.erase(rentalBooks.begin() + bookNum);
        cout << "도서 반납이 완료되었습니다.\n";
    }
    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    Book searchBook(string keyword)
    {
        bool isFind = false;
        for (int i = 0; i < books.size(); i++)
        {
           if (!books[i].title.compare(keyword) || !books[i].author.compare(keyword))
           {
               isFind = true;
               return books[i];
           }
        }
        if (!isFind)
        {
            Book nullBook("Null", "Null", 0);
            return nullBook;
        }
    }
};

int main() {
    BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 검색" << endl; // 현재 책 목록에 있는 책 중 작가 or 제목으로 책 검색
        cout << "4. 책 대여" << endl; // 현재 책 목록 중 원하는 책을 대여(재고 없을 시 불가능)
        cout << "5. 책 대여" << endl; // 현재 책 목록 중 원하는 책을 대여(재고 없을 시 불가능)
        cout << "6. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            int bookPcs;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            cout << "책 권수: ";
            cin >> bookPcs;
            manager.addBook(title, author, bookPcs); // 입력받은 책 정보를 추가
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) 
        {
            // 3번 선택: 책 검색
            // 현재 책 목록 중 작가 or 제목으로 검색된 책 목록을 출력합니다.
            cout << "\n책 검색을 시작합니다." << endl;
            cout << "입력: ";
            string searchKeyword;
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, searchKeyword); // 제목 입력 (공백 포함)
            Book book = manager.searchBook(searchKeyword);
            if (book.title == "Null")
            {
                cout << "검색하신 키워드에 해당하는 책 또는 작가가 없습니다." << endl;
                return 0;
            }
            cout << "검색 결과: " << book.title << " by " << book.author << "   " << book.bookPcs << "권" << endl;
        }
        else if (choice == 4)
        {
            // 4번 선택: 책 대여
            // 현재 책 목록 중 원하는 책을 재고가 있을 경우 대여해줍니다.
            string title;
            cout << "\n책 대여를 시작합니다. 원하는 책 이름을 입력해주세요." << endl;
            manager.displayAllBooks();
            cout << "입력: ";
            cin.ignore();
            getline(cin, title);
            Book book = manager.searchBook(title);
            if(book.bookPcs == 0) cout << "\n 현재 대여하려고 하시는 책의 재고가 모두 소진되었습니다. 다음에 다시 와주세요." << endl;
            manager.rentalBook(book);
        }
        else if (choice == 5)
        {
            // 5번 선택: 책 반납
            // 대여한 책을 반납합니다.
            manager.returnBook();
        }
        else if (choice == 6)
        {
            // 6번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
