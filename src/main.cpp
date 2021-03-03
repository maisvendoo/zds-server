#include    "app.h"

#include    <QTcpServer>
#include    <QTcpSocket>
#include    <QDebug>
#include    <QFile>
#include    <QDataStream>

#include    "zds-auth-data.h"

class TcpServer : public QTcpServer
{
public:

    TcpServer(QObject *parent = Q_NULLPTR) : QTcpServer(parent)
      , socket(Q_NULLPTR)
    {
        connect(this, &TcpServer::newConnection, this, &TcpServer::slotConnected);

        if (listen(QHostAddress::Any, 7691))
        {
            qDebug() << "Server started...";
        }
    }

    virtual ~TcpServer()
    {

    }

private:

    QTcpSocket *socket;

private slots:

    void slotConnected()
    {
        qDebug() << "Connected client";

        socket = this->nextPendingConnection();

        connect(socket, &QTcpSocket::readyRead, this, &TcpServer::slotReceive);
        connect(socket, &QTcpSocket::disconnected, this, &TcpServer::slotDisconnected);
    }

    void slotDisconnected()
    {
        qDebug() << "Disconnected client";
    }

    void slotReceive()
    {
        QByteArray data = socket->readAll();

        QFile dump("../data/dump.bin");

        if (dump.open(QIODevice::WriteOnly))
        {
            dump.write(data);
            dump.close();
        }

        zds_auth_data_t zds_auth;
        memcpy((void *) &zds_auth, data.data(), data.count());

        switch (zds_auth.id)
        {
        case 1:

            QByteArray code;
            code.append(0xC8);

            socket->write(code);
            socket->flush();

            QByteArray time;
            time.append(12);
            time.append(5);

            socket->write(time);
            socket->flush();

            break;
        }
    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    App app(argc, argv);

    TcpServer server;

    return app.exec();
}
