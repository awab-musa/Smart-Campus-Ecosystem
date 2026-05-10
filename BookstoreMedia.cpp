#include "../include/BookstoreMedia.h"
#include <iomanip>
#include <sstream>

BookstoreMedia::BookstoreMedia()
    : Resource(), isbn(""), author(""), edition(1) {}

BookstoreMedia::BookstoreMedia(const string &id, const string &name,
                               double price, int stock,
                               const string &isbn, const string &author,
                               int edition)
    : Resource(id, name, price, stock),
      isbn(isbn), author(author), edition(edition) {}

string BookstoreMedia::getIsbn() const { return isbn; }
string BookstoreMedia::getAuthor() const { return author; }
int BookstoreMedia::getEdition() const { return edition; }

void BookstoreMedia::setIsbn(const string &i) { isbn = i; }
void BookstoreMedia::setAuthor(const string &a) { author = a; }
void BookstoreMedia::setEdition(int e) { edition = e; }

string BookstoreMedia::getMediaType() const
{
    return "Book";
}

string BookstoreMedia::getFullTitle() const
{
    return name + " — Edition " + to_string(edition) + " by " + author;
}

void BookstoreMedia::displayInfo() const
{
    cout << *this;
    cout << "  Author       : " << author << "\n"
         << "  ISBN         : " << isbn << "\n"
         << "  Edition      : " << edition << "\n"
         << "  Media Type   : " << getMediaType() << "\n";
}

string BookstoreMedia::getCategory() const
{
    return "Bookstore Media";
}

string BookstoreMedia::getTypeTag() const
{
    return "BOOK";
}

string BookstoreMedia::serialize() const
{
    ostringstream oss;
    oss << getTypeTag() << "|"
        << resourceID << "|"
        << name << "|"
        << fixed << setprecision(2) << price << "|"
        << stock << "|"
        << isbn << "|"
        << author << "|"
        << edition;
    return oss.str();
}