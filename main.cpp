#include    <QCoreApplication>

#include    <QTcpServer>
#include    <QTcpSocket>
#include    <QDebug>
#include    <QFile>
#include    <QDataStream>

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

        socket->disconnectFromHost();
        socket->abort();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TcpServer server;

    return app.exec();
}
