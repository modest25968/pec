#ifndef BACKLOADER_H
#define BACKLOADER_H

class AbstractBackend;

//TODO: do singleton
class BackLoader
{

public:
    BackLoader();
    AbstractBackend* getBack();

private:
    AbstractBackend* ab;
};

#endif // BACKLOADER_H
