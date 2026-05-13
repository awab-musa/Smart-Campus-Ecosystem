#ifndef BOOKSTORE_MEDIA_H
#define BOOKSTORE_MEDIA_H
#include "Resource.h"
class BookstoreMedia : public Resource
{
private:
    string isbn;
    string author;
    int edition;
public:
    BookstoreMedia();
    BookstoreMedia(const string &id, const string &name,
                   double price, int stock,
                   const string &isbn, const string &author,
                   int edition);
    string getIsbn() const;
    string getAuthor() const;
    int getEdition() const;
    void setIsbn(const string &i);
    void setAuthor(const string &a);
    void setEdition(int e);
    string getMediaType() const;
    string getFullTitle() const;
    void displayInfo() const override;
    string getCategory() const override;
    string serialize() const override;
    string getTypeTag() const override;
    static BookstoreMedia* fromString(const string& line);
};
#endif
