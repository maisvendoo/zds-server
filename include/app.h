#ifndef     APP_H
#define     APP_H

#include    <QCoreApplication>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class App : public QCoreApplication
{
public:

    App(int argc, char *argv[]);

    virtual ~App();

    int exec();

private:

};

#endif // APP_H
