#include <QObject>
#include <QStringList>

class QTcpSocket;
class WebPage;
class Command;

class Connection : public QObject {
  Q_OBJECT

  public:
    Connection(QTcpSocket *socket, WebPage *page, QObject *parent = 0);

  public slots:
    void checkNext();
    void finishCommand(bool success, QString &response);
    void pendingLoadFinished(bool success);

  private:
    void readLine();
    void readDataBlock();
    void processNext(const char *line);
    Command *createCommand(const char *name);
    void processArgument(const char *line);
    void startCommand();
    void writeResponse(bool success, QString &response);

    QTcpSocket *m_socket;
    QString m_commandName;
    Command *m_command;
    QStringList m_arguments;
    int m_argumentsExpected;
    WebPage *m_page;
    int m_expectingDataSize;
};

